#pragma once
#include "raylib.h"
#include "vec2.hpp"
constexpr int OBSTACLE_DEBUG = true;

class Obstacle {
public:
    Vector2 pos;
    int mask[16][16];

    Obstacle(Image img) {
        //cassert;


        if constexpr (OBSTACLE_DEBUG) { TraceLog(LOG_INFO, "image"); };

        for (int x: range(16)) {
            for (int y: range(16)) {
                if (((char *) img.data)[(y * 16 + x) * 4 + 1] == 0) {
                    mask[x][y] = 1;
                } else {
                    mask[x][y] = 0;
                }
            }
        };

        if constexpr (OBSTACLE_DEBUG) {
            for (int y: range(16)) {
                char t[17];
                for (int x: range(16)) {
                    t[x] = 'A' + mask[x][y];
                }
                t[16] = 0;
                TraceLog(LOG_INFO, t);
            };
        };
    }
};
