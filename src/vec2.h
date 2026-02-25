#pragma once

#include <stdint.h>
#include <cmath>

template <typename T>
struct Vec2 {
    T x;
    T y;

    Vec2<T> operator-() const { return {-x, -y}; }

    Vec2<T>& operator+=(const Vec2<T>& other) {
        x += other.x;
        y += other.y;
        return *this;
    }

    Vec2<T>& operator-=(const Vec2<T>& other) {
        x -= other.x;
        y -= other.y;
        return *this;
    }

    Vec2<T>& operator*=(const Vec2<T>& other) {
        x *= other.x;
        y *= other.y;
        return *this;
    }

    Vec2<T>& operator/=(const Vec2<T>& other) {
        x /= other.x;
        y /= other.y;
        return *this;
    }

    T get_length() const;
    T get_length_sq() const;

    static T dot(const Vec2<T>& a, const Vec2<T>& b);
    static Vec2<T> normalize(const Vec2<T>& v);
};

template <typename T>
inline Vec2<T> operator+(const Vec2<T>& a, const Vec2<T>& b) {
    return {a.x + b.x, a.y + b.y};
}

template <typename T>
inline Vec2<T> operator-(const Vec2<T>& a, const Vec2<T>& b) {
    return {a.x - b.x, a.y - b.y};
}

template <typename T>
inline Vec2<T> operator*(const Vec2<T>& a, const Vec2<T>& b) {
    return {a.x * b.x, a.y * b.y};
}

template <typename T>
inline Vec2<T> operator*(const Vec2<T>& a, const T& scale) {
    return {a.x * scale, a.y * scale};
}

template <typename T>
inline Vec2<T> operator/(const Vec2<T>& a, const Vec2<T>& b) {
    return {a.x / b.x, a.y / b.y};
}

template <typename T>
inline Vec2<T> operator/(const Vec2<T>& a, const T& scale) {
    return {a.x / scale, a.y / scale};
}

// ~~~ specific type definitions ~~~

#define DEF_VEC2_LEN(T, sqrt_func)            \
    template <>                               \
    inline T Vec2<T>::get_length() const {    \
        return sqrt_func(x * x + y * y);      \
    }                                         \
                                              \
    template <>                               \
    inline T Vec2<T>::get_length_sq() const { \
        return x * x + y * y;                 \
    }

DEF_VEC2_LEN(float, std::sqrtf)
DEF_VEC2_LEN(double, std::sqrt)

#define DEF_VEC2_DOT(T)                                         \
    template <>                                                 \
    inline T Vec2<T>::dot(const Vec2<T>& a, const Vec2<T>& b) { \
        return a.x * b.x +                                      \
               a.y * b.y;                                       \
    }

DEF_VEC2_DOT(float)
DEF_VEC2_DOT(double)

#define DEF_VEC2_NORM(T)                                  \
    template <>                                           \
    inline Vec2<T> Vec2<T>::normalize(const Vec2<T>& v) { \
        return v / v.get_length();                        \
    }

DEF_VEC2_NORM(float)
DEF_VEC2_NORM(double)

using Vec2f = Vec2<float>;
using Vec2d = Vec2<double>;
using Vec2i = Vec2<int32_t>;
using Vec2u = Vec2<uint32_t>;
