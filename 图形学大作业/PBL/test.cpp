#include "camera.h"
#include "canvas.h"
#include "clipping.h"
#include "filling.h"
#include "visibility.h"
#include "scene.h"

#include <algorithm>
#include <iostream>

using namespace std;

// 图像宽度和高度
const int image_width = 800;
const int image_height = 600;

void testEllipse(){
    Canvas canvas(image_height, image_width);
    //第2章：绘制椭圆
    canvas.setColor(BLACK);
    int a = min(image_width, image_height) / 4 - 10;
    canvas.drawEllipse(image_width / 2, image_height / 2, a, a / 2);
    canvas.drawEllipse(image_width / 2, image_height / 2, a, a / 1.5);
    canvas.drawEllipse(image_width / 2, image_height / 2, a, a * 2);

    //输出图像到文件
    canvas.outputPPM();
}
void testTransform(){
    Canvas canvas(image_height, image_width);
    //第3章：几何变换
    //矩形
    //p4------p3
    //|        |
    //|        |
    //p1------p2
    //TODO：定义矩形的四个顶点坐标
    Vec p1{}, p2{}, p3{}, p4{};

    //绘制初始位置的矩形
    canvas.setColor(BLACK);
    canvas.drawRect(p1, p2, p3, p4);

    //TODO：构造旋转、平移、缩放和错切矩阵
    Matrix R, T, S, SH;

    //TODO：构造平移和旋转的复合变换
    Matrix M1; //先平移再旋转
    Matrix M2; //先旋转再平移

    //绘制先平移再旋转的结果
    canvas.setColor(RED);
    canvas.drawRect(M1 * p1, M1 * p2, M1 * p3, M1 * p4);

    //绘制先旋转再平移的结果
    canvas.setColor(GREEN);
    canvas.drawRect(M2 * p1, M2 * p2, M2 * p3, M2 * p4);

    //TODO：实验其它复合变换
    
    //输出图像到文件
    canvas.outputPPM();
}
void testViewProjection(){
    Canvas canvas(image_height, image_width);
    //第4周任务：
    //测试用例1：世界坐标 → 相机坐标
    //相机位置
    Vec eye{ 4,5,6 };
    //相机f轴
    Vec forward{ 5,7,-5 };
    //上方向
    Vec up{ 0,1,0 };
    //一个点的世界坐标
    Vec pw{ 5,6,7 };
    //构造相机对象，构造视图变换矩阵
    Camera cam{ eye, eye - forward, up };
    //坐标变换
    Vec4 pe = cam.world2eye(pw);
    //结果(保留小数点后4位的话)应该是[-1.4142, 0.7101, 0.7035]
    cout << pe;

    //测试用例2
    cout << "测试用例2" << endl;
    eye = Vec{ 0,0,0 }; //相机位置
    Vec at{ 0,0,-1 };   //相机看向的点
    //世界坐标系下三角形三个顶点的坐标    
    Vec p1{ -1,0,-2 }, p2{ 2,0,-2 }, p3{ 0,3,-3 };
    //求三角形三个顶点在相机坐标系（右手坐标系）下的坐标（齐次坐标）
    //构造相机和视图变换矩阵
    cam = Camera(eye, at, up);
    Vec4 pe1 = cam.world2eye(p1),
        pe2 = cam.world2eye(p2),
        pe3 = cam.world2eye(p3);
    cout << "相机坐标" << endl;
    cout << pe1 << pe2 << pe3;

    //测试用例3
    //远近裁剪平面的z坐标分别为f、n
    //裁剪窗口的x和y坐标的最小最大值分别为l、r、b、t
    //将用例2的相机坐标变换为裁剪坐标和标准设备坐标
    
    cout << "测试用例3" << endl;
    float n = 1, f = 3, l = -2, r = 2, b = -1.5, t = 1.5;
    cam.setPerspective(l, r, b, t, n, f);
    Vec4 pc1 = cam.eye2clip(pe1),
        pc2 = cam.eye2clip(pe2),
        pc3 = cam.eye2clip(pe3);
    cout << "裁剪坐标" << endl;
    cout << pc1 << pc2 << pc3;
    Vec pn1 = cam.clip2ndc(pc1),
        pn2 = cam.clip2ndc(pc2),
        pn3 = cam.clip2ndc(pc3);
    cout << "标准设备坐标" << endl;
    cout << pn1 << pn2 << pn3;

    //测试用例4
    //将用例3的标准设备坐标变换为像素坐标
    
    //Vec pv1 = cam.ndc2viewport(pn1, image_width, image_height),
      //  pv2 = cam.ndc2viewport(pn2, image_width, image_height),
        //pv3 = cam.ndc2viewport(pn3, image_width, image_height);

    Vec pv1 = cam.world2viewport(p1, image_width, image_height),
        pv2 = cam.world2viewport(p2, image_width, image_height),
        pv3 = cam.world2viewport(p3, image_width, image_height);

    cout << "测试用例4，窗口坐标：" << endl;
    cout << pv1 << pv2 << pv3;
    canvas.drawLine(pv1, pv2);
    canvas.drawLine(pv2, pv3);
    canvas.drawLine(pv3, pv1);

    //输出图像到文件
    canvas.outputPPM();
}
void testLineClip() {
    //第5周任务1：实现CS直线段裁剪
    //测试用例：
    //窗口：左下角坐标[5,3]，右上角坐标[15,15]
    //线段1：[2,6]-->[4,10]
    //线段2：[7,18]-->[10,10]
    //线段3：[10,1]-->[18,10]
    //线段4：[12,12]-->[14,10]
    float x0 = 2, y0 = 6, x1 = 4, y1 = 10;
    cout << "线段1裁剪前：" << endl << "[" << x0 << "," << y0 << "]-->"
        << "[" << x1 << "," << y1 << "]" << endl;
    clipLine(5, 3, 15, 15, x0, y0, x1, y1);
    cout << "线段1裁剪后：" << endl << "[" << x0 << "," << y0 << "]-->"
        << "[" << x1 << "," << y1 << "]" << endl << endl;

    x0 = 7, y0 = 18, x1 = 10, y1 = 10;
    cout << "线段2裁剪前：" << endl << "[" << x0 << "," << y0 << "]-->"
        << "[" << x1 << "," << y1 << "]" << endl;
    clipLine(5, 3, 15, 15, x0, y0, x1, y1);
    cout << "线段2裁剪后：" << endl << "[" << x0 << "," << y0 << "]-->"
        << "[" << x1 << "," << y1 << "]" << endl << endl;

    x0 = 10, y0 = 1, x1 = 18, y1 = 10;
    cout << "线段3裁剪前：" << endl << "[" << x0 << "," << y0 << "]-->"
        << "[" << x1 << "," << y1 << "]" << endl;
    clipLine(5, 3, 15, 15, x0, y0, x1, y1);
    cout << "线段3裁剪后：" << endl << "[" << x0 << "," << y0 << "]-->"
        << "[" << x1 << "," << y1 << "]" << endl << endl;

    x0 = 12, y0 = 12, x1 = 14, y1 = 10;
    cout << "线段4裁剪前：" << endl << "[" << x0 << "," << y0 << "]-->"
        << "[" << x1 << "," << y1 << "]" << endl;
    clipLine(5, 3, 15, 15, x0, y0, x1, y1);
    cout << "线段4裁剪后：" << endl << "[" << x0 << "," << y0 << "]-->"
        << "[" << x1 << "," << y1 << "]" << endl << endl;
}
void testPolygonClip() {
    //第5周任务2：实现WA多边形裁剪    
    Node p0{ nullptr,nullptr,point{'0'},false };
    Node e{ nullptr,nullptr,point{'e'},true };
    Node p1{ nullptr,nullptr,point{'1'},true };
    Node f{ nullptr,nullptr,point{'f'},false };
    Node p2{ nullptr,nullptr,point{'2'},false };
    Node g{ nullptr,nullptr,point{'g'},true };
    Node p3{ nullptr,nullptr,point{'3'},true };
    Node h{ nullptr,nullptr,point{'h'},false };
    Node p4{ nullptr,nullptr,point{'4'},false };
    Node a{ nullptr,nullptr,point{'a'},false };
    Node b{ nullptr,nullptr,point{'b'},false };
    Node c{ nullptr, nullptr,point{ 'c' },false };
    Node d{ nullptr,nullptr,point{'d'},false };

    p0.next_p = &e;
    e.next_p = &p1;
    p1.next_p = &f;
    f.next_p = &p2;
    p2.next_p = &g;
    g.next_p = &p3;
    p3.next_p = &h;
    h.next_p = &p4;
    p4.next_p = &p0;

    a.next_w = &e;
    e.next_w = &b;
    b.next_w = &c;
    c.next_w = &d;
    d.next_w = &f;
    f.next_w = &g;
    g.next_w = &h;
    h.next_w = &a;

    vector<Node*> plist, wlist;
    plist.push_back(&p0);
    wlist.push_back(&a);

    vector<vector<point>> output;
    processVertices(plist, output);
    for (int i = 0; i < output.size(); i++) {
        cout << "loop " << i << ":" << endl;
        for (int j = 0; j < output[i].size(); j++) {
            cout << char(output[i][j].x) << " ";
        }
    }
}
void testVisibility()
{
    //三角形顶点的世界坐标
    Vec A{ -1,0,-2 }, B{ 2,0,-2 }, C{ 0,3,-3 };
    cout << "三角形顶点的世界坐标：" << endl;
    cout << A << B << C << endl;

    //相机和投影参数
    Camera camera{ Vec{0,0,0},Vec{0,0,-1},Vec{0,1,0} };
    camera.setPerspective(-2, 2, -1.5, 1.5, 1, 3);

    //一点的重心坐标
    Vec bc{ 1.0 / 3,1.0 / 3,1.0 / 3 };
    //bc的世界坐标
    Vec bc_world = bc[0] * A + bc[1] * B + bc[2] * C;
    //bc的相机坐标
    Vec4 bc_eye = camera.world2eye(bc_world);
    //bc的视口坐标
    Vec bc_img = camera.world2viewport(bc_world, 400, 300);
    Vec A_img = camera.world2viewport(A, 400, 300),
        B_img = camera.world2viewport(B, 400, 300),
        C_img = camera.world2viewport(C, 400, 300);

    //bc_img的重心坐标
    Vec bc_from_img = baryCentri(A_img, B_img, C_img, bc_img);
        
    cout << "世界坐标系下的重心坐标；" << bc << endl;
    cout << "根据视口坐标计算的重心坐标：" << bc_from_img << endl;

    //TODO:深度插值
    float bc_d = 0;
    cout << "相机坐标系下的深度：" << bc_eye.z() << endl;
    cout << "插值得到的深度：" << bc_d << endl;

    //深度填充
    //canvas.fillTriangle(A_img, B_img, C_img);
}
void testScene() {
    Canvas canvas(image_height, image_width);
    //场景对象
    Scene scene;

    //定义一个立方体
    Cube cube;

    //定义一个球
    Sphere sphere;
    //把球沿z轴方向移动一个单位，使得它的球心与立方体的顶点重合。
    Matrix4 r, t;
    r.setRotate(45, Vec{ 1,0,0 });
    cube.setTransform(r);
    t.setTranslate(Vec{ 0,0,1 });
    sphere.setTransform(t);

    scene.addObject(cube);
    scene.addObject(sphere);
    scene.draw(canvas);

    //输出图像到文件
    canvas.outputPPM();
}
void testCurve() {
    Canvas canvas(image_height, image_width);
    vector<Vec> pnts{ Vec{ 10,10,0 }, Vec{ 10,110,0 },
        Vec{ 110,110,0 }, Vec{ 110,10,0 } };
    canvas.drawBezier(pnts);
    canvas.outputPPM();
}
void testObj() {
    Object obj;
    obj.loadObj("./hducg23-master/models/spot/spot_triangulated_good.obj");
    Matrix4 m;
    m.setRotate(150, Vec{ 0,1,0 });
    obj.setTransform(m);
    
    Texture texture("./hducg23-master/models/spot/spot_texture.png");

    Scene scene;
    scene.addObject(obj);

    Canvas canvas(image_height, image_width);
    canvas.clear(Color{ 255,255,255 });
    scene.draw(canvas, &texture);
    canvas.outputPPM();
}
void testTexture() {
    Texture texture("./hducg23-master/models/rock/rock.png");

    Canvas canvas(image_height, image_width);
    canvas.clear(WHITE);

    //三角形
    Triangle t1(Vec3(-1, 0, -2),
        Vec3(2, 0, -2),
        Vec3(-1, 3, -3));
    t1.setTexCoord(0, 0, 0);
    t1.setTexCoord(1, 1, 0);
    t1.setTexCoord(2, 0, 1);

    Triangle t2(Vec3(-1, 3, -3),
        Vec3(2, 0, -2),
        Vec3(2, 3, -3));
    t2.setTexCoord(0, 0, 1);
    t2.setTexCoord(1, 1, 0);
    t2.setTexCoord(2, 1, 1);

    float n = 1, f = 3;
    Vec3 eye(0, 0, 0), center(0, 0, -1), up(0, 1, 0);
    Camera camera(eye, center, up);
    
    int w = canvas.getW();
    int h = canvas.getH();
    
    //设置投影窗口大小
    //保证投影窗口比例和视口比例一致
    if (w > h)
        camera.setPerspective(-0.5 * w / h, 0.5 * w / h, -0.5, 0.5, n, f);
    else
        camera.setPerspective(-0.5, 0.5, -0.5 * h / w, 0.5 * h / w, n, f);

    Scene scene;
    scene.setCamera(camera);
    scene.drawTriangle(t1, canvas, &texture);
    scene.drawTriangle(t2, canvas, &texture);

    //输出图像到文件
    canvas.outputPPM();
}
int main() {    
    testObj();
    return 0;
}
