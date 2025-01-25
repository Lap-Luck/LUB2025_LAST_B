#include "obstacle.hpp"

Obstacle::ObstacleId Obstacle::globalIdCounter = 0;
CutLine::CutLineId CutLine::globalIdCounter = 0;


std::vector<ObstacleMask> LoadObstacleMasks(Image _img,int num)
{
    std::vector<ObstacleMask> vres;
    Color cs[2]={BLACK, RED};
    for (int color_id:range(num)){
        Color c=cs[color_id];
        ObstacleMask res;
        if constexpr (OBSTACLE_DEBUG) { TraceLog(LOG_INFO, "image"); };

        // Fill mask vector
        {
            res.size = {_img.width, _img.height};
            res.mask.clear(); res.mask.resize(res.size.x);
            for (int x : range(res.size.x))
            {
                res.mask[x].resize(res.size.y);
            }
        }

        for (int x : range(res.size.x))
        {
            for (int y : range(res.size.y))
            {
                if (
                    (((char*)_img.data)[(y * res.size.x + x) * 4 + 0] == c.r) &&
                    (((char*)_img.data)[(y * res.size.x + x) * 4 + 1] == c.g)

                    )
                {
                    res.mask[x][y] = 1;
                }
                else
                {
                    res.mask[x][y] = 0;
                }
            }
        };

        res.segments = ObstacleMaskGenerateSegments(res.mask,res.size);
        vres.push_back(std::move(res));
    }

    return vres;
}
ObstacleMask LoadObstacleMask(Image img) {
    return LoadObstacleMasks(img)[0];
}