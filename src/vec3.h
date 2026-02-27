#pragma once

#include <stdint.h>
#include <cmath>

template <typename T>
struct Vec3 {
    T x;
    T y;
    T z;

    Vec3() : x(), y(), z() { }
    Vec3(T s) : x(s), y(s), z(s) { }
    Vec3(T x, T y, T z) : x(x), y(y), z(z) { }
    Vec3(const Vec3<T>& v) : x(v.x), y(v.y), z(v.z) { }

    Vec3<T>& operator=(const Vec3<T>& other) {
        x = other.x;
        y = other.y;
        z = other.z;
        return *this;
    }

    Vec3<T> operator-() const { return Vec3<T>(-x, -y, -z); }

    // ~~~ one-sided operators ~~~

    Vec3<T>& operator+=(const Vec3<T>& other) {
        x += other.x;
        y += other.y;
        z += other.z;
        return *this;
    }

    Vec3<T>& operator-=(const Vec3<T>& other) {
        x -= other.x;
        y -= other.y;
        z -= other.z;
        return *this;
    }

    Vec3<T>& operator*=(const Vec3<T>& other) {
        x *= other.x;
        y *= other.y;
        z *= other.z;
        return *this;
    }

    Vec3<T>& operator*=(T scale) {
        x *= scale;
        y *= scale;
        z *= scale;
        return *this;
    }

    Vec3<T>& operator/=(const Vec3<T>& other) {
        x /= other.x;
        y /= other.y;
        z /= other.z;
        return *this;
    }

    Vec3<T>& operator/=(T scale) {
        x /= scale;
        y /= scale;
        z /= scale;
        return *this;
    }

    // ~~~ static functions ~~~

    static T length_sq(const Vec3<T>& v) {
        return v.x * v.x + v.y * v.y + v.z * v.z;
    }

    static T length(const Vec3<T>& v);
    static bool near_zero(const Vec3<T>& v);

    static T dot(const Vec3<T>& a, const Vec3<T>& b) {
        return a.x * b.x +
               a.y * b.y +
               a.z * b.z;
    }
    static Vec3<T> cross(const Vec3<T>& a, const Vec3<T>& b) {
        return Vec3<T>(
            a.y * b.z - a.z * b.y,
            a.z * b.x - a.x * b.z,
            a.x * b.y - a.y * b.z
        );
    }
    static Vec3<T> normalize(const Vec3<T>& v) {
        return v / Vec3<T>::length(v);
    }

    static Vec3<T> reflect(const Vec3<T>& v, const Vec3<T>& n) {
        return v - (n * static_cast<T>(2) * dot(v, n));
    }
};

// ~~~ vector math operators ~~~

template <typename T>
inline Vec3<T> operator+(const Vec3<T>& a, const Vec3<T>& b) {
    return Vec3<T>(a.x + b.x, a.y + b.y, a.z + b.z);
}

template <typename T>
inline Vec3<T> operator-(const Vec3<T>& a, const Vec3<T>& b) {
    return Vec3<T>(a.x - b.x, a.y - b.y, a.z - b.z);
}

template <typename T>
inline Vec3<T> operator*(const Vec3<T>& a, const Vec3<T>& b) {
    return Vec3<T>(a.x * b.x, a.y * b.y, a.z * b.z);
}

template <typename T>
inline Vec3<T> operator*(const Vec3<T>& a, T scale) {
    return Vec3<T>(a.x * scale, a.y * scale, a.z * scale);
}

template <typename T>
inline Vec3<T> operator*(T scale, const Vec3<T>& a) {
    return Vec3<T>(a.x * scale, a.y * scale, a.z * scale);
}

template <typename T>
inline Vec3<T> operator/(const Vec3<T>& a, const Vec3<T>& b) {
    return Vec3<T>(a.x / b.x, a.y / b.y, a.z / b.z);
}

template <typename T>
inline Vec3<T> operator/(const Vec3<T>& a, T scale) {
    return Vec3<T>(a.x / scale, a.y / scale, a.z / scale);
}

// ~~~ specific type function definitions ~~~

#define DEFINE_VEC3(T, sqrt_func, abs_func, zero_min)        \
    template <>                                              \
    inline T Vec3<T>::length(const Vec3<T>& v) {             \
        return sqrt_func(v.x * v.x + v.y * v.y + v.z * v.z); \
    }                                                        \
                                                             \
    template <>                                              \
    inline bool Vec3<T>::near_zero(const Vec3<T>& v) {       \
        return (abs_func(v.x) < zero_min) &&                 \
               (abs_func(v.y) < zero_min) &&                 \
               (abs_func(v.z) < zero_min);                   \
    }

DEFINE_VEC3(float, std::sqrtf, std::fabsf, 1e-8f)
DEFINE_VEC3(double, std::sqrt, std::fabs, 1e-8)
DEFINE_VEC3(long double, std::sqrtl, std::fabsl, 1e-8)

// ~~~ type defines themselves ~~~

typedef Vec3<bool> Vec3b;
typedef Vec3<float> Vec3f;
typedef Vec3<double> Vec3d;
typedef Vec3<long double> Vec3l;
typedef Vec3<int32_t> Vec3i;
typedef Vec3<uint32_t> Vec3u;
