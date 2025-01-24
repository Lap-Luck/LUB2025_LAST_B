#pragma once

#include <raylib.h>

struct ImVec2;

template <typename T>
struct Vec2
{
    Vec2() = default;
    constexpr Vec2(T inX, T inY) : x(inX),y(inY) {};
    constexpr Vec2(const ImVec2& in) : x(in.x),y(in.x) {};

    explicit operator struct Vector2()
    {
        return (struct Vector2){x,y};
    }

    void operator+=(const Vec2& other)
    {
        x += other.x;
        y += other.y;
    }

    Vec2 operator*(T other)
    {
        return {x*other,y*other};
    }

    T x {};
    T y {};
};

using Vec2i = Vec2<int>;
using Vec2f = Vec2<float>;



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