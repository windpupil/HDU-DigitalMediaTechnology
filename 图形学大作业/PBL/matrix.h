#pragma once
#include <iostream>
using namespace std;

class Vec4;
// ��ά����,�ɱ�ʾ��ά����������
class Vec
{
private:
    // ��ά����������
    float v[3];

public:
    Vec() : v{ 0, 0, 0 } {}
    // ���캯��
    Vec(float x, float y)
    {
        v[0] = x;
        v[1] = y;
        v[2] = 1;
    }
    Vec(float x, float y, float w)
    {
        v[0] = x;
        v[1] = y;
        v[2] = w;
    }
    Vec(const Vec4& vw);
    void normalize()
    {
        float length = sqrt(v[0] * v[0] + v[1] * v[1] + v[2] * v[2]);
        v[0] /= length;
        v[1] /= length;
        v[2] /= length;
    }
    // �����������������ȡ����ĵ�i������
    float operator[](int i) const
    {
        return v[i];
    }
    // ���ؿ���Ϊ��ֵ����������������ص�i���������������
    float& operator[](int i)
    {
        return v[i];
    }

    // ����x����
    float x() const
    {
        return v[0];
    }
    // ����y����
    float y() const
    {
        return v[1];
    }
    float z() const
    {
        return v[2];
    }
};
Vec operator+(const Vec& v1, const Vec& v2)
{
    return Vec(v1[0] + v2[0], v1[1] + v2[1], v1[2] + v2[2]);
}
Vec operator-(const Vec& v1, const Vec& v2)
{
    return Vec(v1[0] - v2[0], v1[1] - v2[1], v1[2] - v2[2]);
}
Vec operator*(float scale, const Vec& v)
{
    return Vec{ scale * v[0], scale * v[1], scale * v[2] };
}
Vec operator*(const Vec& v, float scale)
{
    return Vec{ scale * v[0], scale * v[1], scale * v[2] };
}
Vec operator/(float scale, const Vec& v)
{
    return Vec{ scale / v[0], scale / v[1], scale / v[2] };
}
Vec operator/(const Vec& v, float scale)
{
    return Vec{ v[0] / scale, v[1] / scale, v[2] / scale };
}
// �����࣬���ڱ�ʾ��ά��α任
class Matrix
{
private:
    float m[3][3] = { 0 };

public:
    // ��ʼ��Ϊ��λ����
    Matrix()
    {
        SetIdentity();
    }
    // ���õ�i�е�j��Ԫ�ص�ֵ
    void Set(int i, int j, float v)
    {
        m[i][j] = v;
    }
    // ��ȡ��i������
    Vec GetRow(int i) const
    {
        Vec v;
        for (int j = 0; j < 3; j++)
            v[j] = m[i][j];
        return v;
    }
    // ��ȡ��j������
    Vec GetCol(int j) const
    {
        Vec v;
        for (int i = 0; i < 3; i++)
            v[i] = m[i][j];
        return v;
    }

    // ���쵥λ����
    void SetIdentity()
    {
        for (int i = 0; i < 3; i++)
            for (int j = 0; j < 3; j++)
                m[i][j] = 0;

        for (int i = 0; i < 3; i++)
            m[i][i] = 1;
    }
    // wyh������ƽ�ƾ���
    void SetTranslate(float tx, float ty)
    {
        for (int i = 0; i < 3; i++)
            m[i][i] = 1;
        m[0][2] = tx;
        m[1][2] = ty;

    }
    // wyh��������ת���󣬲���Ϊ����
    void SetRotate(float degree)
    {
        float theta = degree / 180 * 3.141592654;
        float c = cos(theta), s = sin(theta);
        m[0][0] = c;
        m[0][1] = -s;
        m[1][0] = s;
        m[1][1] = c;
        m[2][2] = 1;
    }
    // wyh���������ž���
    void SetScale(float sx, float sy)
    {
        m[0][0] = sx;
        m[1][1] = sy;
        m[2][2] = 1;
    }
    // wyh��������о���
    void SetShear(float shx = 0, float shy = 0)
    {
        m[0][0] = 1;
        m[0][1] = shx;
        m[1][0] = shy;
        m[1][1] = 1;
        m[2][2] = 1;
    }
};

// ��ӡ����
ostream& operator<<(ostream& o, const Matrix& m)
{
    for (int i = 0; i < 3; i++)
    {
        Vec row = m.GetRow(i);
        o << row[0] << " " << row[1] << " " << row[2] << endl;
    }

    return o;
}
// ��ӡ����
ostream& operator<<(ostream& o, const Vec& v)
{
    o << "[" << v[0] << "," << v[1] << "," << v[2] << "]" << endl;
    return o;
}

// ���س˷���������������������ĵ����result = v1 * v2
float operator*(const Vec& v1, const Vec& v2)
{
    float result = 0;
    for (int i = 0; i < 3; i++)
        result += v1[i] * v2[i];
    return result;
}

Vec operator-(const Vec& v)
{
    return Vec{ -v[0], -v[1], -v[2] };
}

// ������������������������Ĳ�ˣ�result = v1 ^ v2
Vec operator^(const Vec& v1, const Vec& v2)
{
    Vec result{ v1.y() * v2.z() - v1.z() * v2.y(),
               v1.z() * v2.x() - v1.x() * v2.z(),
               v1.x() * v2.y() - v1.y() * v2.x() };

    return result;
}
// wyh�����س˷����������������������, result = m * v
Vec operator*(const Matrix& m, const Vec& v)
{
    Vec result;
    for (int i = 0; i < 3; i++)
    {
        Vec row = m.GetRow(i);
        result[i] = row * v;
    }
    return result;
}
// wyh�����س˷���������������˾���result = m1 * m2
Matrix operator*(const Matrix& m1, const Matrix& m2)
{
    Matrix result;
    for (int i = 0; i < 3; i++)
    {
        Vec row = m1.GetRow(i);
        for (int j = 0; j < 3; j++)
        {
            Vec col = m2.GetCol(j);
            result.Set(i, j, row * col);
        }
    }
    return result;
}

// ��ά�������ɱ�ʾ��ά����������
class Vec4
{
public:
    // ���캯��
    Vec4(float x = 0, float y = 0, float z = 0)
    {
        v[0] = x;
        v[1] = y;
        v[2] = z;
        v[3] = 1;
    }
    Vec4(float x, float y, float z, float w)
    {
        v[0] = x;
        v[1] = y;
        v[2] = z;
        v[3] = w;
    }
    // �ӷ�������깹��������꣬�����Ϊ1
    Vec4(const Vec& vi)
    {
        v[0] = vi[0];
        v[1] = vi[1];
        v[2] = vi[2];
        v[3] = 1;
    }
    // �����������������ȡ����ĵ�i������
    float operator[](int i) const
    {
        return v[i];
    }
    float& operator[](int i)
    {
        return v[i];
    }
    float x() const
    {
        return v[0];
    }
    float y() const
    {
        return v[1];
    }
    float z() const
    {
        return v[2];
    }
    float w() const
    {
        return v[3];
    }

private:
    float v[4];
};
Vec::Vec(const Vec4& vw)
{
    v[0] = vw[0] / vw[3];
    v[1] = vw[1] / vw[3];
    v[2] = vw[2] / vw[3];
}
// ��ӡ����
ostream& operator<<(ostream& o, const Vec4& v)
{
    o << "[" << v[0] << "," << v[1] << "," << v[2] << "," << v[3] << "]" << endl;
    return o;
}
class Matrix4
{
public:
    // Ĭ�Ϲ��쵥λ����
    Matrix4()
    {
        setIdentity();
    }
    // ���õ�i�е�j��Ԫ�ص�ֵ
    void set(int i, int j, float v)
    {
        m[i][j] = v;
    }
    // ��ȡ��i�е�j��Ԫ�ص�ֵ
    float get(int i, int j) const
    {
        return m[i][j];
    }
    // ���쵥λ����
    void setIdentity()
    {
        for (int i = 0; i < 4; i++)
            for (int j = 0; j < 4; j++)
                m[i][j] = 0;

        for (int i = 0; i < 4; i++)
            m[i][i] = 1;
    }
    // ��ȡ��i������
    Vec4 GetRow(int i) const
    {
        Vec4 v;
        for (int j = 0; j < 4; j++)
            v[j] = m[i][j];
        return v;
    }
    // ��ȡ��j������
    Vec4 GetCol(int j) const
    {
        Vec4 v;
        for (int i = 0; i < 4; i++)
            v[i] = m[i][j];
        return v;
    }
    // ������ͼ�任����
    // eye�����λ��
    // at���������ĵ�
    // up���Ϸ���
    void setView(const Vec& eye, const Vec& at, const Vec& up)
    {
        Vec f(eye - at);
        f.normalize();

        Vec l = up ^ f;
        l.normalize();

        Vec u = f ^ l;
        m[0][0] = l.x();
        m[0][1] = l.y();
        m[0][2] = l.z();
        m[1][0] = u.x();
        m[1][1] = u.y();
        m[1][2] = u.z();
        m[2][0] = f.x();
        m[2][1] = f.y();
        m[2][2] = f.z();

        m[0][3] = -(l * eye);
        m[1][3] = -(u * eye);
        m[2][3] = -(f * eye);
    }
    //wyh����������ͶӰ���󣨲�һ���ԣ�
    void setOrtho(float l, float r, float b, float t, float n, float f)
    {
        m[0][0] = 2 / (r - l);
        m[0][3] = -(r + l) / (r - l);
        m[1][1] = 2 / (t - b);
        m[1][3] = -(t + b) / (t - b);
        m[2][2] = -2 / (f - n);
        m[2][3] = -(f + n) / (f - n);
        m[3][3] = 1;
    }
    // wyh������͸��ͶӰ����(��һ���ԣ�
    void setPerspective(float l, float r, float b, float t, float n, float f)
    {
        m[0][0] = 2 * n / (r - l);
        m[0][2] = (r + l) / (r - l);
        m[1][1] = 2 * n / (t - b);
        m[1][2] = (t + b) / (t - b);
        m[2][2] = -(f + n) / (f - n);
        m[2][3] = -2 * f * n / (f - n);
        m[3][2] = -1;
        m[3][3] = 0;
    }

    // ��������������ת�ı任����
    // �ο����ϣ�https://www.songho.ca/opengl/gl_rotate.html
    void setRotate(float degree, const Vec& axis)
    {
        setIdentity();
        float theta = degree / 180 * 3.141592654;
        float c = cos(theta), s = sin(theta);
        Vec r(axis);
        r.normalize();
        float x = r.x(), y = r.y(), z = r.z();

        m[0][0] = (1 - c) * x * x + c;
        m[0][1] = (1 - c) * x * y - s * z;
        m[0][2] = (1 - c) * x * z + s * y;

        m[1][0] = (1 - c) * x * y + s * z;
        m[1][1] = (1 - c) * y * y + c;
        m[1][2] = (1 - c) * y * z - s * x;

        m[2][0] = (1 - c) * x * z - s * y;
        m[2][1] = (1 - c) * y * z + s * x;
        m[2][2] = (1 - c) * z * z + c;
    }
    // ����ƽ�Ʊ任����
    void setTranslate(const Vec& tv)
    {
        setIdentity();
        m[0][3] = tv.x();
        m[1][3] = tv.y();
        m[2][3] = tv.z();
    }

private:
    float m[4][4];
};

// ���س˷���������������������ĵ����result = v1 * v2
float operator*(const Vec4& v1, const Vec4& v2)
{
    float sum = 0;
    for (int i = 0; i < 4; i++)
        sum += v1[i] * v2[i];
    return sum;
}

// ���س˷����������������������, result = m * v
Vec4 operator*(const Matrix4& m, const Vec4& v)
{
    Vec4 result;
    for (int i = 0; i < 4; i++)
    {
        Vec4 row = m.GetRow(i);
        result[i] = row * v;
    }
    return result;
}
// ���س˷���������������˾���result = m1 * m2
Matrix4 operator*(const Matrix4& m1, const Matrix4& m2)
{
    Matrix4 result;
    for (int i = 0; i < 4; i++)
    {
        Vec4 row = m1.GetRow(i);
        for (int j = 0; j < 4; j++)
        {
            Vec4 col = m2.GetCol(j);
            result.set(i, j, row * col);
        }
    }
    return result;
}
// ��ӡ����
ostream& operator<<(ostream& o, const Matrix4& m)
{
    for (int i = 0; i < 4; i++)
    {
        Vec4 row = m.GetRow(i);
        o << row;
    }
    return o;
}