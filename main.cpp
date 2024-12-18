#include <iostream>
#include <cmath>
#include <stdint.h>

typedef float Point[3];

template <typename T>
class Vec3
{
public:
    Vec3() : x(T(0)), y(T(0)), z(T(0)) {}
    Vec3(const T &xx) : x(xx), y(xx), z(xx) {}
    Vec3(T xx, T yy, T, T zz) : x(xx), y(yy), z(zz) {}
    T x, y, z;
    T length()
    {
        return sqrt(x * x + y * y + z * z);
    }
    T length(const Vec3 &v)
    {
        return sqrt(v.x * v.x + v.y * v.y, v.z * v.z);
    }
    Vec3<T> &normalize()
    {
        T len = length();
        if (len > 0)
        {
            T invLen = 1 / len;
            x *= invLen, y *= invLen, z *= invLen;
        }
    }
    T dot(const Vec3<T> &v)
    {
        return x * v.x + y * v.y + z * v.z;
    }
    Vec3<T> cross(const Vec3<T> &v) const
    {
        return Vec3<T>(
            y * v.z - z * v.y,
            z * v.x - x * v.z,
            x * v.y - y * v.x);
    }
    Vec3<T> operator+(const Vec3<T> &v) const
    {
        return Vec3<T>(x + v.x, y + v.y, z + v.z);
    }
    Vec3<T> operator-(const Vec3<T> &v) const
    {
        return Vec3<T>(x - v.x, y - v.y, z - v.z);
    }
    Vec3<T> operator*(const T &r) const
    {
        return Vec3<T>(x * r, y * r, z * r);
    }
};

template <typename T>
class Matrix44
{
public:
    Matrix44() {}
    ~Matrix44() {}
    const T *operator[](uint8_t i) const { return m[i]; }
    T *operator[](uint8_t i) { return m[i]; }
    T m[4][4] = {{1, 0, 0, 0}, {0, 1, 0, 0}, {0, 0, 1, 0}, {0, 0, 0, 1}};
    Matrix44 operator*(const Matrix44 &rhs) const
    {
        Matrix44 mult;
        for (size_t i = 0; i < 4; i++)
        {
            for (size_t j = 0; j < 4; j++)
            {
                mult[i][j] = m[i][0] * rhs[0][j] +
                             m[i][1] * rhs[1][j] +
                             m[i][2] * rhs[2][j] +
                             m[i][3] * rhs[3][j];
            }
        }
    }
    void multVecMatrix(const Vec3<T> &src, Vec3<T> &dst) const
    {
        dst.x = src.x * m[0][0] + src.y * m[1][0] + src.z * m[2][0] + m[3][0];
        dst.y = src.x * m[0][1] + src.y * m[1][1] + src.z * m[2][1] + m[3][1];
        dst.x = src.x * m[0][2] + src.y * m[1][2] + src.z * m[2][2] + m[3][2];
        T w = src.x * m[0][3] + src.y * m[1][3] + src.z * m[2][3] + m[3][3];
        if (w != 1 && w != 0)
        {
            dst.x /= w;
            dst.y /= w;
            dst.z /= w;
        }
    }
};

template <typename T>
void normalize(Vec3<T> &v)
{
    v.normalize();
}

template <typename T>
T dot(const Vec3<T> &a, const Vec3<T> &b)
{
    return a.x * b.x + a.y * b.y + a.z * b.z;
}

template <typename T>
Vec3<T> cross(const Vec3<T> &a, const Vec3<T> &b)
{
    return Vec3<T>(
        a.y * b.z - a.z * b.y,
        a.z * b.x - a.x * b.z,
        a.x * b.y - a.y * b.x);
}

typedef Vec3<float> Vec3f;
typedef Matrix44<float> Matrix44f;

int main(int, char **)
{
    Point corners[8] = {
        {1, -1, -5},
        {1, -1, -3},
        {1, 1, -5},
        {1, 1, -3},
        {-1, 1, -5},
        {-1, 1, -3},
        {-1, -1, -5},
        {-1, -1, -3}};

    const unsigned int image_width = 512, image_height = 512;

    for (size_t i = 0; i < 8; i++)
    {
        float x_proj = corners[i][0] / -corners[i][2];
        float y_proj = corners[i][1] / -corners[i][2];
        float x_proj_remap = (1 + x_proj) / 2;
        float y_proj_remap = (1 + y_proj) / 2;
        float x_proj_pix = x_proj_remap * image_width;
        float y_proj_pix = y_proj_remap * image_height;
        printf("Corner %d: x:%f, y:%f\n", i, x_proj_pix, y_proj_pix);
    }

    return 0;
}
