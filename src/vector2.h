#ifndef BABA_IS_YOU_VECTOR2_H
#define BABA_IS_YOU_VECTOR2_H

#include "Vector2.hpp"

#include <functional>

template<class T>
struct Vector2 {
    T x, y;

    explicit Vector2(T x = 0, T y = 0) : x(x), y(y) {}

    Vector2 operator+(const Vector2 &v) const { return Vector2(x + v.x, y + v.y); }

    Vector2 operator-(const Vector2 &v) const { return Vector2(x - v.x, y - v.y); }

    Vector2 operator/(T k) const { return Vector2(x / k, y / k); }

    bool operator==(const Vector2 &v) const { return x == v.x && y == v.y; }

    bool operator!=(const Vector2 &v) const { return !(*this == v); }

    Vector2 operator*(T k) const { return Vector2(x * k, y * k); }

    Vector2 operator*(const Vector2 &v) const { return Vector2(x * v.x, y * v.y); }

    explicit operator godot::Vector2() const { return {static_cast<real_t>(x), static_cast<real_t>(y)}; }

    T length_squared() const { return x * x + y * y; }

    T dot(const Vector2 &v) const { return x * v.x + y * v.y; }
};

template<class T>
Vector2<T> operator*(T k, const Vector2<T> &v) { return Vector2(v.x * k, v.y * k); }

namespace std {
    template<class T>
    struct hash<Vector2<T>> {
        size_t operator()(const Vector2<T> &p) const {
            auto hash1 = std::hash<T>{}(p.x);
            auto hash2 = std::hash<T>{}(p.y);
            return hash1 ^ hash2;
        }
    };
}

using TilePosition = Vector2<long>;

#endif //BABA_IS_YOU_VECTOR2_H
