#pragma once

class Matrix4f {
public:
    Matrix4f();
    Matrix4f(float value);
    Matrix4f(const Matrix4f& other);
    Matrix4f(float f11, float f12, float f13, float f14,
             float f21, float f22, float f23, float f24,
             float f31, float f32, float f33, float f34,
             float f41, float f42, float f43, float f44);

private:
    float m_matrix[4*4];
};
