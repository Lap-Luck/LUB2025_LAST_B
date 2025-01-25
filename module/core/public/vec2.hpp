#pragma once

#include <raylib.h>
#include "raymath.h"

template <typename T>
struct Vec2
{
    Vec2() = default;
    Vec2(T inX, T inY) : x(inX),y(inY) {};

    Vec2(struct Vector2 in) : x(in.x),y(in.y) {};

    operator struct Vector2()
    {
        return (struct Vector2){x,y};
    }

    Vec2 operator+(Vec2<T> other)
    {
        return Vector2Add(*this, other);
    }

    Vec2 operator+=(Vec2<T> other)
    {
        *this = operator+(other);
        return *this;
    }

    Vec2 operator+(T other)
    {
        return Vector2AddValue(*this, other);
    }

    Vec2 operator+=(T other)
    {
        *this = operator+(other);
        return *this;
    }

    Vec2 operator-(Vec2<T> other)
    {
        return Vector2Subtract(*this, other);
    }

    Vec2 operator-=(Vec2<T> other)
    {
        *this = operator-(other);
        return *this;
    }

    Vec2 operator-(T other)
    {
        return Vector2Subtract(*this, other);
    }

    Vec2 operator-=(T other)
    {
        *this = operator-(other);
        return *this;
    }

    Vec2 operator*(T other)
    {
        return Vector2Scale(*this, other);
    }

    Vec2 operator*=(T other)
    {
        *this = operator*(other);
        return *this;
    }

    float dotProduct(Vec2<T> other)
    {
        return Vector2DotProduct(*this, other);
    }

    Vec2<T> crossProduct(Vec2<T> other)
    {
        return Vector2CrossProduct(*this, other);
    }

    float length()
    {
        return Vector2Length(*this);
    }

    float lengthSqr()
    {
        return Vector2LengthSqr(*this);
    }

    void normalizeThat()
    {
        *this = Vector2Normalize(*this);
    }

    Vec2 normalized()
    {
        return Vector2Normalize(*this);
    }


    T x {};
    T y {};
};

using Vec2i = Vec2<int>;
using Vec2f = Vec2<float>;



