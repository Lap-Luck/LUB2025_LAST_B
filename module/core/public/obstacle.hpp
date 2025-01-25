#pragma once
#include <functional>
#include <stdlib.h>
#include <vector>

#include "math.hpp"
#include "raylib.h"
#include "vec2.hpp"

constexpr int OBSTACLE_DEBUG = true;

class ObSegment
{
public:
    int ax, ay, bx, by {};

    ObSegment(int _ax, int _ay, int _bx, int _by) : ax(_ax), ay(_ay), bx(_bx), by(_by) {}
};

class CutLine
{
public:
    Vec2f A, B;

    CutLine(Vec2f _A, float _len)
    {
        A = _A;
        B = _A + Vec2f(0, _len);
    }

    void draw()
    {
        DrawLine(A.x, A.y, B.x, B.y,PINK);
    }
};


#define X_ID 0
#define Y_ID 1

class ObstacleMask
{
public:
    Vec2i size {};
    std::vector<std::vector<int>> mask {};
    std::vector<ObSegment> segments {};


    void load(Image _img)
    {
        if constexpr (OBSTACLE_DEBUG) { TraceLog(LOG_INFO, "image"); };

        // Fill mask vector
        {
            size = {_img.width, _img.height};
            mask.clear(); mask.resize(size.x);
            for (int x : range(size.x))
            {
                mask[x].resize(size.y);
            }
        }

        for (int x : range(16))
        {
            for (int y : range(16))
            {
                if (((char*)_img.data)[(y * 16 + x) * 4 + 1] == 0)
                {
                    mask[x][y] = 1;
                }
                else
                {
                    mask[x][y] = 0;
                }
            }
        };

        int hmap_min[2][16];
        int hmap_max[2][16];
        {
            //generate hmap
            for (int a : range(16))
            {
                hmap_min[0][a] = 1000;
                hmap_min[1][a] = 1000;
                hmap_max[0][a] = 1000;
                hmap_max[1][a] = 1000;
                for (int per : range(2))
                {
                    for (int b : range(16))
                    {
                        {
                            int coord[2] = {a, b};

                            int x = coord[(X_ID + per) % 2];
                            int y = coord[(Y_ID + per) % 2];
                            if (mask[x][y] == 1)
                            {
                                hmap_min[per][a] = b;
                                break;
                            }
                        }
                    }
                    for (int b : range(16))
                    {
                        b = 16 - 1 - b;
                        {
                            int coord[2] = {a, b};

                            int x = coord[(X_ID + per) % 2];
                            int y = coord[(Y_ID + per) % 2];
                            if (mask[x][y] == 1)
                            {
                                hmap_max[per][a] = b;
                                break;
                            }
                        }
                    }
                }
            }
        }


        for (int xm : range(16 - 1))
        {
            int xp = xm + 1;
            if (abs(hmap_min[X_ID][xm] - hmap_min[X_ID][xp]) <= 1)
            {
                if (hmap_min[X_ID][xm] != 1000)
                {
                    int ym = hmap_min[X_ID][xm];
                    int yp = hmap_min[X_ID][xp];
                    segments.push_back({xm, ym, xp, yp});
                }
            }
            if (abs(hmap_max[X_ID][xm] - hmap_max[X_ID][xp]) <= 1)
            {
                if (hmap_max[X_ID][xm] != 1000)
                {
                    int ym = hmap_max[X_ID][xm];
                    int yp = hmap_max[X_ID][xp];
                    segments.push_back({xm, ym, xp, yp});
                }
            }
        }
        //remove doubles
        for (int ym : range(16 - 1))
        {
            int yp = ym + 1;
            if (abs(hmap_min[Y_ID][ym] - hmap_min[Y_ID][yp]) <= 1)
            {
                if (hmap_min[Y_ID][ym] != 1000)
                {
                    int xm = hmap_min[Y_ID][ym];
                    int xp = hmap_min[Y_ID][yp];
                    segments.push_back({xm, ym, xp, yp});
                }
            }
            if (abs(hmap_max[Y_ID][ym] - hmap_max[Y_ID][yp]) <= 1)
            {
                if (hmap_max[Y_ID][ym] != 1000)
                {
                    int xm = hmap_max[Y_ID][ym];
                    int xp = hmap_max[Y_ID][yp];
                    segments.push_back({xm, ym, xp, yp});
                }
            }
        }


        if constexpr (OBSTACLE_DEBUG)
        {
            for (int y : range(16))
            {
                char t[17];
                for (int x : range(16))
                {
                    t[x] = 'A' + mask[x][y];
                }
                t[16] = 0;
                TraceLog(LOG_INFO, t);
            };
        };
    }

};


class Obstacle
{
public:
    using ObstacleId = int;
    static ObstacleId globalIdCounter;
    ObstacleId unique_id {};

    struct
    {
        bool pendingDestroy {false};
    } flags;

    Vector2 pos {};
    float scale {1};
    bool debug_draw = true;

    std::function<void(class Bubble*)> onHit;

    ObstacleMask* mask;

    Obstacle(ObstacleMask* _mask, Vector2 _pos, float _scale)
    : pos(_pos), scale(_scale), mask(_mask)
    {
        unique_id = globalIdCounter;
        globalIdCounter++;
    }


    Rectangle box()
    {
        return Rectangle(pos.x, pos.y, scale * 16, scale * 16);
    }

    void draw()
    {
        if (debug_draw)
        {
            for (int y : range(16))
            {
                for (int x : range(16))
                {
                    if (mask->mask[x][y] == 1)
                    {
                        DrawRectangleLines(pos.x + x * scale, pos.y + y * scale, scale, scale,
                                           Color((x * 64) % 255, 255, 0, 255));
                        //DrawRectangleLines(pos.x+x*20.0,pos.y+y*20.0,20,20,Color((i%7)*10,i,0,255));
                    }
                }
            }
            for (int s_id : range(mask->segments.size()))
            {
                ObSegment s = mask->segments[s_id];
                DrawLine(pos.x + ((float)s.ax + 0.5) * scale, pos.y + ((float)s.ay + 0.5) * scale,
                         pos.x + ((float)s.bx + 0.5) * scale, pos.y + ((float)s.by + 0.5) * scale,RED);
            }
        }
    }
};
