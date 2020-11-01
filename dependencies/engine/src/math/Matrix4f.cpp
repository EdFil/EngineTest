//
// Created by edgar on 6/6/19.
//

#include "Matrix4f.hpp"

#include <cmath>
#include <cstring>

Matrix4f::Matrix4f() {
    m_matrix[0] = 1.0f;
    m_matrix[1] = 0.0f;
    m_matrix[2] = 0.0f;
    m_matrix[3] = 0.0f;
    m_matrix[4] = 0.0f;
    m_matrix[5] = 1.0f;
    m_matrix[6] = 0.0f;
    m_matrix[7] = 0.0f;
    m_matrix[8] = 0.0f;
    m_matrix[8] = 0.0f;
    m_matrix[10] = 1.0f;
    m_matrix[11] = 0.0f;
    m_matrix[12] = 0.0f;
    m_matrix[13] = 0.0f;
    m_matrix[14] = 0.0f;
    m_matrix[15] = 1.0f;
}

Matrix4f::~Matrix4f() = default;

Matrix4f::Matrix4f(const Matrix4f& other) {
    memcpy(&m_matrix, &other.m_matrix, 16 * sizeof(float));
}

Matrix4f::Matrix4f(Matrix4f&& other) noexcept {
    memcpy(&m_matrix, &other.m_matrix, 16 * sizeof(float));
}

Matrix4f::Matrix4f(const float f11, const float f12, const float f13, const float f14,
                   const float f21, const float f22, const float f23, const float f24,
                   const float f31, const float f32, const float f33, const float f34,
                   const float f41, const float f42, const float f43, const float f44) {
    m_matrix[0] = f11;
    m_matrix[1] = f12;
    m_matrix[2] = f13;
    m_matrix[3] = f14;
    m_matrix[4] = f21;
    m_matrix[5] = f22;
    m_matrix[6] = f23;
    m_matrix[7] = f24;
    m_matrix[8] = f31;
    m_matrix[9] = f32;
    m_matrix[10] = f33;
    m_matrix[11] = f34;
    m_matrix[12] = f41;
    m_matrix[13] = f42;
    m_matrix[14] = f43;
    m_matrix[15] = f44;
}

Matrix4f& Matrix4f::operator=(const Matrix4f& other) {
    memcpy(&m_matrix, &other.m_matrix, 16 * sizeof(float));
    return *this;
}

Matrix4f& Matrix4f::operator=(Matrix4f&& other) noexcept {
    memcpy(&m_matrix, &other.m_matrix, 16 * sizeof(float));
    return *this;
}
