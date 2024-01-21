#pragma once
#include <fstream>
#include <algorithm>
#include <vector>

#include "matrix.h"
#include "visibility.h"

//��ʾ��ɫ�����ͣ���ɫ������ȡֵλ������[0,255]
struct Color {
    float r;
    float g;
    float b;
};
//������ɫ����
const Color WHITE{ 255,255,255 }, BLACK{ 0,0,0 }, RED{ 255,0,0 }, GREEN{ 0,255,0 };

//������
class Canvas {
private:
    Color* pixels;
    float* z_buffer;
    Color foreground_color;
    int height, width;
public:
    //���캯��
    Canvas(int h, int w) :height(h), width(w) {
        pixels = new Color[h * w];
        z_buffer = new float[h * w];
        for (int i = 0; i < h * w; i++)
            z_buffer[i] = FLT_MAX;
        clear(WHITE);
    }
    ~Canvas() {
        delete [] pixels;
        delete[] z_buffer;
    }

    //���ƻ�������
    void clear(const Color& c) {
        for (int y = 0; y < height; y++)
            for (int x = 0; x < width; x++) {
                setPixel(x, y, c);
            }
    }
    //���û���ǰ��ɫ
    void setColor(const Color& c) {
        foreground_color = c;
    }

    //����ָ�����ص���ɫ
    void setPixel(int x, int y, Color c) {
        if (x < 0 || x >= width || y < 0 || y >= height)
            return;
        pixels[y * width + x] = c;
    }
    //����ָ�����ص����
    void setDepth(int x, int y, float d) {
        if (x < 0 || x >= width || y < 0 || y >= height)
            return;
        z_buffer[y * width + x] = d;
    }
    //��ȡָ�����ص���ɫ
    Color getPixel(int x, int y) {
        if (x < 0 || x >= width || y < 0 || y >= height)
            return foreground_color;
        return pixels[y * width + x];
    }
    //��ȡָ�����ص����
    float getDepth(int x, int y) {
        if (x < 0 || x >= width || y < 0 || y >= height)
            return FLT_MAX;
        return z_buffer[y * width + x];
    }
    //���ͼ��PPM�ļ���Ĭ���ļ���Ϊimage.ppm
    void outputPPM() {
        ofstream out("image.ppm");
        //д��ppm�ļ�ǰ������Ϣ
        out << "P3\n" << width << ' ' << height << "\n255\n";
        //���б����������飬��������ɫд���ļ���ԭ�������½ǣ�ˮƽx���򣬴�ֱy����
        for (int y = height - 1; y >= 0; y--) {
            for (int x = 0; x < width; x++) {
                Color c = getPixel(x, y);
                out << c.r << ' ' << c.g << ' ' << c.b << '\n';
            }
        }
    }
    //���ͼ����Ļ
    void outputScreen();
    Vec deCasteljau(const vector<Vec>& P, float t) {
        int n = P.size() - 1;        
        //TODO�����������������t��Ӧ�ĵ�C
        vector<Vec> Q = P;
        for (int k = 1; k <= n; k++) {
            for (int i = 0; i <= n - k; i++) {
                Q[i] = (1 - t)*Q[i] + t * Q[i + 1];
            }
        }
        return Q[0];
    }

    //x��������������[t[k],t[k+1])��
    //k��x���ڵĲ�������ı��
    //t���ڵ�����
    //c�����Ƶ�����
    //p�����ߵĴ���
    Vec deBoor(int k, float x, const vector<float>& t, 
        const vector<Vec>& c, int p) {
        //TODO����������x�����Ӧ�������
    }
    //����
    //p4------p3
    //|        |
    //|        |
    //p1------p2
    
    int getW()const { return width; }
    int getH()const { return height; }
};