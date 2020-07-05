#ifndef BABA_IS_YOU_VECTOR2_H
#define BABA_IS_YOU_VECTOR2_H

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

    explicit operator godot::Vector2() const { return godot::Vector2(static_cast<T>(x), static_cast<T>(y)); }
};

template<class T>
Vector2<T> operator*(T k, const Vector2<T> &v) { return Vector2(x * k, y * k); }

struct HashVector2 {
    template<class T>
    size_t operator()(const Vector2<T> &p) const {
        auto hash1 = std::hash<T>{}(p.x);
        auto hash2 = std::hash<T>{}(p.y);
        return hash1 ^ hash2;
    }
};

using TilePosition = Vector2<long>;

#endif //BABA_IS_YOU_VECTOR2_H
