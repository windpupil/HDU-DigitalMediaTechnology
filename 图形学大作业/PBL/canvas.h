#pragma once
#include <fstream>
#include <algorithm>
#include <vector>

#include "matrix.h"
#include "visibility.h"

//表示颜色的类型，颜色分量的取值位于区间[0,255]
struct Color {
    float r;
    float g;
    float b;
};
//定义颜色常量
const Color WHITE{ 255,255,255 }, BLACK{ 0,0,0 }, RED{ 255,0,0 }, GREEN{ 0,255,0 };

//画布类
class Canvas {
private:
    Color* pixels;
    float* z_buffer;
    Color foreground_color;
    int height, width;
public:
    //构造函数
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

    //绘制画布背景
    void clear(const Color& c) {
        for (int y = 0; y < height; y++)
            for (int x = 0; x < width; x++) {
                setPixel(x, y, c);
            }
    }
    //设置画布前景色
    void setColor(const Color& c) {
        foreground_color = c;
    }

    //设置指定像素的颜色
    void setPixel(int x, int y, Color c) {
        if (x < 0 || x >= width || y < 0 || y >= height)
            return;
        pixels[y * width + x] = c;
    }
    //设置指定像素的深度
    void setDepth(int x, int y, float d) {
        if (x < 0 || x >= width || y < 0 || y >= height)
            return;
        z_buffer[y * width + x] = d;
    }
    //获取指定像素的颜色
    Color getPixel(int x, int y) {
        if (x < 0 || x >= width || y < 0 || y >= height)
            return foreground_color;
        return pixels[y * width + x];
    }
    //获取指定像素的深度
    float getDepth(int x, int y) {
        if (x < 0 || x >= width || y < 0 || y >= height)
            return FLT_MAX;
        return z_buffer[y * width + x];
    }
    //输出图像到PPM文件，默认文件名为image.ppm
    void outputPPM() {
        ofstream out("image.ppm");
        //写入ppm文件前两行信息
        out << "P3\n" << width << ' ' << height << "\n255\n";
        //按行遍历像素数组，把像素颜色写入文件，原点在左下角，水平x方向，垂直y方向
        for (int y = height - 1; y >= 0; y--) {
            for (int x = 0; x < width; x++) {
                Color c = getPixel(x, y);
                out << c.r << ' ' << c.g << ' ' << c.b << '\n';
            }
        }
    }
    //输出图像到屏幕
    void outputScreen();
    Vec deCasteljau(const vector<Vec>& P, float t) {
        int n = P.size() - 1;        
        //TODO：计算曲线上与参数t对应的点C
        vector<Vec> Q = P;
        for (int k = 1; k <= n; k++) {
            for (int i = 0; i <= n - k; i++) {
                Q[i] = (1 - t)*Q[i] + t * Q[i + 1];
            }
        }
        return Q[0];
    }

    //x：参数，在区间[t[k],t[k+1])内
    //k：x所在的参数区间的编号
    //t：节点向量
    //c：控制点数组
    //p：曲线的次数
    Vec deBoor(int k, float x, const vector<float>& t, 
        const vector<Vec>& c, int p) {
        //TODO：给出参数x，求对应点的坐标
    }
    //矩形
    //p4------p3
    //|        |
    //|        |
    //p1------p2
    
    int getW()const { return width; }
    int getH()const { return height; }
};