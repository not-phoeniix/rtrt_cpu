#pragma once

#include <stdint.h>
#include <cmath>

template <typename T>
struct Vec3 {
    T x;
    T y;
    T z;

    Vec3<T> operator-() const { return {-x, -y, -z}; }

    Vec3<T>& operator+=(const Vec3<T>& other) {
        x += other.x;
        y += other.y;
        z += other.z;
        return *this;
    }

    Vec3<T>& operator*=(const Vec3<T>& other) {
        x *= other.x;
        y *= other.y;
        z *= other.z;
        return *this;
    }

    Vec3<T>& operator/=(const Vec3<T>& other) {
        x /= other.x;
        y /= other.y;
        z /= other.z;
        return *this;
    }

    T get_length() const;
    T get_length_sq() const;

    static T dot(const Vec3<T>& a, const Vec3<T>& b);
    static Vec3<T> cross(const Vec3<T>& a, const Vec3<T>& b);
    static Vec3<T> normalize(const Vec3<T>& v);
};

template <typename T>
inline Vec3<T> operator+(const Vec3<T>& a, const Vec3<T>& b) {
    return {a.x + b.x, a.y + b.y, a.z + b.z};
}

template <typename T>
inline Vec3<T> operator-(const Vec3<T>& a, const Vec3<T>& b) {
    return {a.x - b.x, a.y - b.y, a.z - b.z};
}

template <typename T>
inline Vec3<T> operator*(const Vec3<T>& a, const Vec3<T>& b) {
    return {a.x * b.x, a.y * b.y, a.z * b.z};
}

template <typename T>
inline Vec3<T> operator*(const Vec3<T>& a, const T& scale) {
    return {a.x * scale, a.y * scale, a.z * scale};
}

template <typename T>
inline Vec3<T> operator/(const Vec3<T>& a, const Vec3<T>& b) {
    return {a.x / b.x, a.y / b.y, a.z / b.z};
}

template <typename T>
inline Vec3<T> operator/(const Vec3<T>& a, const T& scale) {
    return {a.x / scale, a.y / scale, a.z / scale};
}

// ~~~ specific type definitions ~~~

#define DEF_VEC3_LEN(T, sqrt_func)               \
    template <>                                  \
    inline T Vec3<T>::get_length() const {       \
        return sqrt_func(x * x + y * y + z * z); \
    }                                            \
                                                 \
    template <>                                  \
    inline T Vec3<T>::get_length_sq() const {    \
        return x * x + y * y + z * z;            \
    }

DEF_VEC3_LEN(float, std::sqrtf)
DEF_VEC3_LEN(double, std::sqrt)

#define DEF_VEC3_DOT(T)                                         \
    template <>                                                 \
    inline T Vec3<T>::dot(const Vec3<T>& a, const Vec3<T>& b) { \
        return a.x * b.x +                                      \
               a.y * b.y +                                      \
               a.z * b.z;                                       \
    }

DEF_VEC3_DOT(float)
DEF_VEC3_DOT(double)

#define DEF_VEC3_CROSS(T)                                               \
    template <>                                                         \
    inline Vec3<T> Vec3<T>::cross(const Vec3<T>& a, const Vec3<T>& b) { \
        return {                                                        \
            a.y * b.z - a.z * b.y,                                      \
            a.z * b.x - a.x * b.z,                                      \
            a.x * b.y - a.y * b.z                                       \
        };                                                              \
    }

DEF_VEC3_CROSS(float)
DEF_VEC3_CROSS(double)

#define DEF_VEC3_NORM(T)                                  \
    template <>                                           \
    inline Vec3<T> Vec3<T>::normalize(const Vec3<T>& v) { \
        return v / v.get_length();                        \
    }

DEF_VEC3_NORM(float)
DEF_VEC3_NORM(double)

using Vec3f = Vec3<float>;
using Vec3d = Vec3<double>;
using Vec3i = Vec3<int32_t>;
using Vec3u = Vec3<uint32_t>;
