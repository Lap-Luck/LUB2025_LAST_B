#pragma once

#include <stdlib.h>

class BubbleP {
public:
    Vec2f pos;
    Vec2f offset;
    Vec2f vel;

    BubbleP(Vec2f _pos,Vec2f _offset, Vec2f _vel) {
        pos=_pos;
        vel=_vel;
        offset=_offset;
    }

    void follow(Vec2f orgin,float lifetime) {


        if (lifetime>0.5) {
            pos=Vector2Lerp(pos,orgin+offset,0.1);
            if ((pos-orgin).length()>5.0+offset.length()) {
                pos=pos+(orgin-pos).normalized()*((pos-orgin).length()-(5.0+offset.length()))*0.5;
            }
        }
        else {
            pos=Vector2Lerp(pos,orgin+offset,0.05);
        }

    }

};

struct cInfo {
    Vector2 C;
    Vector2 A;
    Vector2 B;
    float d;
};

namespace {
    bool box_box_colide(Rectangle b,Vec2f pos,float r) {
        //if (b.x<=pos.x+r) {
           // if (b.y<=pos.y+r) {
                if (b.x+b.width>=pos.x-r) {
                    //if (b.y+b.height>=pos.y-r) {
                        return true;
                   // }
                }
           // }
       // }
        return false;
    }

}

class Bubble
{
public:
    Vector2 pos;
    Vector2 vel;
    float r;
    std::vector<BubbleP> particles;
    int cut_id;
    int last_cut_id;
    int divided;
    float lifetime;


    Bubble(Vector2 _pos,Vector2 _vel,float _r,int _divided=0,int p_num=10){
        this->pos=_pos;
        this->vel=_vel;
        this->r=_r;
        this->divided=_divided;
        this->lifetime=0.0f;
        cut_id=-1;
        last_cut_id=-1;
        for (int x : range(p_num)) {
            for (int y : range(p_num)) {
                Vec2f d={x-5,y-5};
                if (d.lengthSqr()<5*5) {
                    particles.push_back(BubbleP(
                            pos+d*(_r*0.2),d*(_r*0.2),vel
                    ));
                }

            }

        }
    }
    void check_cls(std::vector<CutLine> &cls) {
        cut_id=-1;
        for (int c_id:range(cls.size())) {
            CutLine cl=cls[c_id];
            Vector2 Ccl=ClosesPointInSegment(cl.A,cl.B,pos);
            float d=Vector2Distance(Ccl,pos);
            if (d<r) {
                if (c_id!=last_cut_id) {
                    cut_id=c_id;
                }
            }
        }
    }
    void frame(std::vector<Obstacle> &obs,std::vector<CutLine> &cls){
        if (IsKeyDown(KEY_RIGHT) || InputManager::get()->gyroscope.z < 0) vel.x=Lerp(vel.x,2000.0,0.001f);
        if (IsKeyDown(KEY_LEFT) || InputManager::get()->gyroscope.z > 0 ) vel.x=Lerp(vel.x,-2000.0,0.001f);

        this->lifetime+=0.016f;

        vel.y=Lerp(vel.y,-100.0,0.02f);
        pos=Vector2Add(pos,Vector2Scale(vel,0.016));

        std::vector<cInfo> cis = get_collding(obs);
        for (int ci_id:range(cis.size())) {
            cInfo ci= cis[ci_id];
            Vector2 A=ci.A;
            Vector2 B=ci.B;

            Vec2f C=ci.C;
            float d=ci.d;


            float pen=(r-d)*1.001;
            Vec2f pc=pos-C;
            pos=pos+(((pc).normalized())*pen);
            Vec2f AB=(A-B);
            if (AB.dotProduct(Vec2f(0,1))<0.01f) {
                vel.y+=fmax(0.0,vel.y);
            }
            if (pc.dotProduct(Vec2f(vel.x,0))<0) {
                vel.y+=fabs(vel.x)*0.5;
                vel.x=-vel.x*0.99;
            }
        }
        for (int p_id:range(particles.size())) {
            BubbleP& bp=particles[p_id];
            bp.follow(pos,lifetime);


        }

        check_cls(cls);

    }

    std::vector<cInfo> get_collding(std::vector<Obstacle> &obs) {
        std::vector<cInfo> res;
        for (int o_id:range(obs.size())) {
            Obstacle& o=obs[o_id];
            //if (box_box_colide(o.box(),pos,r)) {
            // o.s=false;
            //}
            {
                for (int s_id:range(o.mask->segments.size())) {
                    ObSegment s=o.mask->segments[s_id];
                    Vector2 A=o.pos+Vec2f{((float)s.ax+0.5f)*o.scale,((float)s.ay+0.5f)*o.scale};
                    Vector2 B=o.pos+Vec2f{((float)s.bx+0.5f)*o.scale,((float)s.by+0.5f)*o.scale};

                    Vec2f C=ClosesPointInSegment(A,B,pos);
                    float d=Vector2Distance(C,pos);
                    if (d<r) {
                        if(o.onHit) o.onHit(this);
                        res.push_back({C,A,B,d});
                    }
                }
            }

        }
        return res;
    }


    void draw() {
        DrawCircleV(pos,r, Color(255,255,0,100));
        for (int id:range(particles.size())) {
            BubbleP bp=particles[id];
            DrawCircleV(bp.pos,r/10, Color(255,0,0,255));

        }
    }

};