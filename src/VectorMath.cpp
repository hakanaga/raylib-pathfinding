#include "VectorMath.hpp"

Vector3 Vector3Add(Vector3 v1, Vector3 v2)
{
    Vector3 result = {v1.x + v2.x, v1.y + v2.y, v1.z + v2.z};
    return result;
}

Vector3 Vector3Subtract(Vector3 v1, Vector3 v2)
{
    Vector3 result = {v1.x - v2.x, v1.y - v2.y, v1.z - v2.z};
    return result;
}

Vector3 Vector3Scale(Vector3 v, float scalar)
{
    Vector3 result = {v.x * scalar, v.y * scalar, v.z * scalar};
    return result;
}

float Vector3Length(const Vector3 v)
{
    return sqrtf(v.x * v.x + v.y * v.y + v.z * v.z);
}

Vector3 Vector3Normalize(Vector3 v)
{
    float length = Vector3Length(v);
    if (length != 0.0f)
    {
        float ilength = 1.0f / length;
        v.x *= ilength;
        v.y *= ilength;
        v.z *= ilength;
    }
    return v;
}

Vector3 Vector3Transform(Vector3 v, Matrix mat)
{
    Vector3 result = {0};

    float x = v.x;
    float y = v.y;
    float z = v.z;

    result.x = mat.m0 * x + mat.m4 * y + mat.m8 * z + mat.m12;
    result.y = mat.m1 * x + mat.m5 * y + mat.m9 * z + mat.m13;
    result.z = mat.m2 * x + mat.m6 * y + mat.m10 * z + mat.m14;

    return result;
}

Matrix MatrixRotateXYZ(Vector3 angle)
{
    Matrix result = {1.0f, 0.0f, 0.0f, 0.0f,
                     0.0f, 1.0f, 0.0f, 0.0f,
                     0.0f, 0.0f, 1.0f, 0.0f,
                     0.0f, 0.0f, 0.0f, 1.0f}; // MatrixIdentity()

    float cosz = cosf(-angle.z);
    float sinz = sinf(-angle.z);
    float cosy = cosf(-angle.y);
    float siny = sinf(-angle.y);
    float cosx = cosf(-angle.x);
    float sinx = sinf(-angle.x);

    result.m0 = cosz * cosy;
    result.m1 = (cosz * siny * sinx) - (sinz * cosx);
    result.m2 = (cosz * siny * cosx) + (sinz * sinx);

    result.m4 = sinz * cosy;
    result.m5 = (sinz * siny * sinx) + (cosz * cosx);
    result.m6 = (sinz * siny * cosx) - (cosz * sinx);

    result.m8 = -siny;
    result.m9 = cosy * sinx;
    result.m10 = cosy * cosx;

    return result;
}

Matrix MatrixTranslate(float x, float y, float z)
{
    Matrix result = {1.0f, 0.0f, 0.0f, x,
                     0.0f, 1.0f, 0.0f, y,
                     0.0f, 0.0f, 1.0f, z,
                     0.0f, 0.0f, 0.0f, 1.0f};

    return result;
}

Matrix MatrixMultiply(Matrix left, Matrix right)
{
    Matrix result = {0};

    result.m0 = left.m0 * right.m0 + left.m1 * right.m4 + left.m2 * right.m8 + left.m3 * right.m12;
    result.m1 = left.m0 * right.m1 + left.m1 * right.m5 + left.m2 * right.m9 + left.m3 * right.m13;
    result.m2 = left.m0 * right.m2 + left.m1 * right.m6 + left.m2 * right.m10 + left.m3 * right.m14;
    result.m3 = left.m0 * right.m3 + left.m1 * right.m7 + left.m2 * right.m11 + left.m3 * right.m15;
    result.m4 = left.m4 * right.m0 + left.m5 * right.m4 + left.m6 * right.m8 + left.m7 * right.m12;
    result.m5 = left.m4 * right.m1 + left.m5 * right.m5 + left.m6 * right.m9 + left.m7 * right.m13;
    result.m6 = left.m4 * right.m2 + left.m5 * right.m6 + left.m6 * right.m10 + left.m7 * right.m14;
    result.m7 = left.m4 * right.m3 + left.m5 * right.m7 + left.m6 * right.m11 + left.m7 * right.m15;
    result.m8 = left.m8 * right.m0 + left.m9 * right.m4 + left.m10 * right.m8 + left.m11 * right.m12;
    result.m9 = left.m8 * right.m1 + left.m9 * right.m5 + left.m10 * right.m9 + left.m11 * right.m13;
    result.m10 = left.m8 * right.m2 + left.m9 * right.m6 + left.m10 * right.m10 + left.m11 * right.m14;
    result.m11 = left.m8 * right.m3 + left.m9 * right.m7 + left.m10 * right.m11 + left.m11 * right.m15;
    result.m12 = left.m12 * right.m0 + left.m13 * right.m4 + left.m14 * right.m8 + left.m15 * right.m12;
    result.m13 = left.m12 * right.m1 + left.m13 * right.m5 + left.m14 * right.m9 + left.m15 * right.m13;
    result.m14 = left.m12 * right.m2 + left.m13 * right.m6 + left.m14 * right.m10 + left.m15 * right.m14;
    result.m15 = left.m12 * right.m3 + left.m13 * right.m7 + left.m14 * right.m11 + left.m15 * right.m15;

    return result;
}