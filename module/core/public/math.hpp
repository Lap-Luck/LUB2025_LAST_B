#pragma once
#include <cmath>

#include "raylib.h"
#include "raymath.h"
#include "vec2.hpp"

struct IntRangeIT{
    int value;
    bool operator!=(IntRangeIT b) {return value != b.value;}
    int operator*() {return value;}
    void operator++() {++value;}
};

struct IntRange{
    int to;
    IntRangeIT begin() {return (IntRangeIT){0}; }
    IntRangeIT end() {return (IntRangeIT){to};}
    bool has(int e){
        return (e>=0)&(e<to);
    }
};

inline IntRange range(int to){return (IntRange){to};}



inline Vec2f ClosesPointInSegment(Vec2f A,Vec2f B,Vec2f pos) {
    Vec2f ab=(B-A);
    Vec2f p=(pos-A);
    float k=p.dotProduct(ab)*(1.0f/ab.lengthSqr());
    k=Clamp(k,0.0f,1.0f);
    Vec2f C=A+Vec2f(ab*k);
    return C;
}

inline float DistanceSegment(Vector2 A,Vector2 B,Vector2 pos) {
    float d1=Vector2Distance(A,pos);
    float d2=Vector2Distance(B,pos);
    Vector2 ab=Vector2Subtract(A,B);
    Vector2 abn=Vector2(ab.y,-ab.x);
    float d3=1000.0+Vector2DotProduct(abn,Vector2Subtract(pos,A))/Vector2Length(abn);
    return fmin(d1,fmin(d2,d3));

}