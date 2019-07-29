#pragma once

#include <cmath>
#include <cassert>
#include <cinttypes>

class Vector3f {
public:
    float x, y, z;

    Vector3f() : x(0.0f), y(0.0f), z(0.0f) { }
    Vector3f(float value) : x(value), y(value), z(value) { }
    Vector3f(float x, float y, float z) : x(x), y(y), z(z) { }
    Vector3f(const Vector3f& other) : x(other.x), y(other.y), z(other.z) { }
    Vector3f(Vector3f&& other) noexcept : x(other.x), y(other.y), z(other.z) { }
    ~Vector3f() = default;

    Vector3f& operator=(const Vector3f& other) { 
        x = other.x; y = other.y; z = other.z;
        return *this;
    }

    Vector3f& operator=(Vector3f&& other) noexcept {
        x = other.x; y = other.y; z = other.z;
        return *this;
    }

    float operator[] (uint32_t i) const {
        assert(i < 3);
        return *(&x + i);
    }


    Vector3f& operator= (float rhs) {
        x = y = z = rhs;
        return *this;
    }

    bool operator== (const Vector3f& rhs) const {
        return (x == rhs.x && y == rhs.y && z == rhs.z);
    }

    bool operator!= (const Vector3f& rhs) const {
        return (x != rhs.x || y != rhs.y || z != rhs.z);
    }

    Vector3f operator+ (const Vector3f& rhs) const {
        return Vector3f(x + rhs.x, y + rhs.y, z + rhs.z);
    }

    Vector3f operator- (const Vector3f& rhs) const {
        return Vector3f(x - rhs.x, y - rhs.y, z - rhs.z);
    }

    Vector3f operator* (float rhs) const {
        return Vector3f(x * rhs, y * rhs, z * rhs);
    }

    Vector3f operator* (const Vector3f& rhs) const {
        return Vector3f(x * rhs.x, y * rhs.y, z * rhs.z);
    }

    Vector3f operator/ (float val) const {
        assert(val != 0.0);

        float fInv = 1.0f / val;
        return Vector3f(x * fInv, y * fInv, z * fInv);
    }

    Vector3f operator/ (const Vector3f& rhs) const {
        return Vector3f(x / rhs.x, y / rhs.y, z / rhs.z);
    }

    const Vector3f& operator+ () const {
        return *this;
    }

    Vector3f operator- () const {
        return Vector3f(-x, -y, -z);
    }

    friend Vector3f operator* (float lhs, const Vector3f& rhs) {
        return Vector3f(lhs * rhs.x, lhs * rhs.y, lhs * rhs.z);
    }

    friend Vector3f operator/ (float lhs, const Vector3f& rhs) {
        return Vector3f(lhs / rhs.x, lhs / rhs.y, lhs / rhs.z);
    }

    friend Vector3f operator+ (const Vector3f& lhs, float rhs) {
        return Vector3f(lhs.x + rhs, lhs.y + rhs, lhs.z + rhs);
    }

    friend Vector3f operator+ (float lhs, const Vector3f& rhs) {
        return Vector3f(lhs + rhs.x, lhs + rhs.y, lhs + rhs.z);
    }

    friend Vector3f operator- (const Vector3f& lhs, float rhs) {
        return Vector3f(lhs.x - rhs, lhs.y - rhs, lhs.z - rhs);
    }

    friend Vector3f operator- (float lhs, const Vector3f& rhs) {
        return Vector3f(lhs - rhs.x, lhs - rhs.y, lhs - rhs.z);
    }

    Vector3f& operator+= (const Vector3f& rhs) {
        x += rhs.x;
        y += rhs.y;
        z += rhs.z;

        return *this;
    }

    Vector3f& operator+= (float rhs) {
        x += rhs;
        y += rhs;
        z += rhs;

        return *this;
    }

    Vector3f& operator-= (const Vector3f& rhs) {
        x -= rhs.x;
        y -= rhs.y;
        z -= rhs.z;

        return *this;
    }

    Vector3f& operator-= (float rhs) {
        x -= rhs;
        y -= rhs;
        z -= rhs;

        return *this;
    }

    Vector3f& operator*= (float rhs) {
        x *= rhs;
        y *= rhs;
        z *= rhs;

        return *this;
    }

    Vector3f& operator*= (const Vector3f& rhs) {
        x *= rhs.x;
        y *= rhs.y;
        z *= rhs.z;

        return *this;
    }

    Vector3f& operator/= (float rhs) {
        assert(rhs != 0.0f);

        float inv = 1.0f / rhs;

        x *= inv;
        y *= inv;
        z *= inv;

        return *this;
    }

    Vector3f& operator/= (const Vector3f& rhs) {
        x /= rhs.x;
        y /= rhs.y;
        z /= rhs.z;

        return *this;
    }
};