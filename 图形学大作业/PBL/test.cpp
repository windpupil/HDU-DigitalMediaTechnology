#include "camera.h"
#include "canvas.h"
#include "clipping.h"
#include "filling.h"
#include "visibility.h"
#include "scene.h"

#include <algorithm>
#include <iostream>

using namespace std;

// ͼ���Ⱥ͸߶�
const int image_width = 800;
const int image_height = 600;

void testEllipse(){
    Canvas canvas(image_height, image_width);
    //��2�£�������Բ
    canvas.setColor(BLACK);
    int a = min(image_width, image_height) / 4 - 10;
    canvas.drawEllipse(image_width / 2, image_height / 2, a, a / 2);
    canvas.drawEllipse(image_width / 2, image_height / 2, a, a / 1.5);
    canvas.drawEllipse(image_width / 2, image_height / 2, a, a * 2);

    //���ͼ���ļ�
    canvas.outputPPM();
}
void testTransform(){
    Canvas canvas(image_height, image_width);
    //��3�£����α任
    //����
    //p4------p3
    //|        |
    //|        |
    //p1------p2
    //TODO��������ε��ĸ���������
    Vec p1{}, p2{}, p3{}, p4{};

    //���Ƴ�ʼλ�õľ���
    canvas.setColor(BLACK);
    canvas.drawRect(p1, p2, p3, p4);

    //TODO��������ת��ƽ�ơ����źʹ��о���
    Matrix R, T, S, SH;

    //TODO������ƽ�ƺ���ת�ĸ��ϱ任
    Matrix M1; //��ƽ������ת
    Matrix M2; //����ת��ƽ��

    //������ƽ������ת�Ľ��
    canvas.setColor(RED);
    canvas.drawRect(M1 * p1, M1 * p2, M1 * p3, M1 * p4);

    //��������ת��ƽ�ƵĽ��
    canvas.setColor(GREEN);
    canvas.drawRect(M2 * p1, M2 * p2, M2 * p3, M2 * p4);

    //TODO��ʵ���������ϱ任
    
    //���ͼ���ļ�
    canvas.outputPPM();
}
void testViewProjection(){
    Canvas canvas(image_height, image_width);
    //��4������
    //��������1���������� �� �������
    //���λ��
    Vec eye{ 4,5,6 };
    //���f��
    Vec forward{ 5,7,-5 };
    //�Ϸ���
    Vec up{ 0,1,0 };
    //һ�������������
    Vec pw{ 5,6,7 };
    //����������󣬹�����ͼ�任����
    Camera cam{ eye, eye - forward, up };
    //����任
    Vec4 pe = cam.world2eye(pw);
    //���(����С�����4λ�Ļ�)Ӧ����[-1.4142, 0.7101, 0.7035]
    cout << pe;

    //��������2
    cout << "��������2" << endl;
    eye = Vec{ 0,0,0 }; //���λ��
    Vec at{ 0,0,-1 };   //�������ĵ�
    //��������ϵ���������������������    
    Vec p1{ -1,0,-2 }, p2{ 2,0,-2 }, p3{ 0,3,-3 };
    //�������������������������ϵ����������ϵ���µ����꣨������꣩
    //�����������ͼ�任����
    cam = Camera(eye, at, up);
    Vec4 pe1 = cam.world2eye(p1),
        pe2 = cam.world2eye(p2),
        pe3 = cam.world2eye(p3);
    cout << "�������" << endl;
    cout << pe1 << pe2 << pe3;

    //��������3
    //Զ���ü�ƽ���z����ֱ�Ϊf��n
    //�ü����ڵ�x��y�������С���ֵ�ֱ�Ϊl��r��b��t
    //������2���������任Ϊ�ü�����ͱ�׼�豸����
    
    cout << "��������3" << endl;
    float n = 1, f = 3, l = -2, r = 2, b = -1.5, t = 1.5;
    cam.setPerspective(l, r, b, t, n, f);
    Vec4 pc1 = cam.eye2clip(pe1),
        pc2 = cam.eye2clip(pe2),
        pc3 = cam.eye2clip(pe3);
    cout << "�ü�����" << endl;
    cout << pc1 << pc2 << pc3;
    Vec pn1 = cam.clip2ndc(pc1),
        pn2 = cam.clip2ndc(pc2),
        pn3 = cam.clip2ndc(pc3);
    cout << "��׼�豸����" << endl;
    cout << pn1 << pn2 << pn3;

    //��������4
    //������3�ı�׼�豸����任Ϊ��������
    
    //Vec pv1 = cam.ndc2viewport(pn1, image_width, image_height),
      //  pv2 = cam.ndc2viewport(pn2, image_width, image_height),
        //pv3 = cam.ndc2viewport(pn3, image_width, image_height);

    Vec pv1 = cam.world2viewport(p1, image_width, image_height),
        pv2 = cam.world2viewport(p2, image_width, image_height),
        pv3 = cam.world2viewport(p3, image_width, image_height);

    cout << "��������4���������꣺" << endl;
    cout << pv1 << pv2 << pv3;
    canvas.drawLine(pv1, pv2);
    canvas.drawLine(pv2, pv3);
    canvas.drawLine(pv3, pv1);

    //���ͼ���ļ�
    canvas.outputPPM();
}
void testLineClip() {
    //��5������1��ʵ��CSֱ�߶βü�
    //����������
    //���ڣ����½�����[5,3]�����Ͻ�����[15,15]
    //�߶�1��[2,6]-->[4,10]
    //�߶�2��[7,18]-->[10,10]
    //�߶�3��[10,1]-->[18,10]
    //�߶�4��[12,12]-->[14,10]
    float x0 = 2, y0 = 6, x1 = 4, y1 = 10;
    cout << "�߶�1�ü�ǰ��" << endl << "[" << x0 << "," << y0 << "]-->"
        << "[" << x1 << "," << y1 << "]" << endl;
    clipLine(5, 3, 15, 15, x0, y0, x1, y1);
    cout << "�߶�1�ü���" << endl << "[" << x0 << "," << y0 << "]-->"
        << "[" << x1 << "," << y1 << "]" << endl << endl;

    x0 = 7, y0 = 18, x1 = 10, y1 = 10;
    cout << "�߶�2�ü�ǰ��" << endl << "[" << x0 << "," << y0 << "]-->"
        << "[" << x1 << "," << y1 << "]" << endl;
    clipLine(5, 3, 15, 15, x0, y0, x1, y1);
    cout << "�߶�2�ü���" << endl << "[" << x0 << "," << y0 << "]-->"
        << "[" << x1 << "," << y1 << "]" << endl << endl;

    x0 = 10, y0 = 1, x1 = 18, y1 = 10;
    cout << "�߶�3�ü�ǰ��" << endl << "[" << x0 << "," << y0 << "]-->"
        << "[" << x1 << "," << y1 << "]" << endl;
    clipLine(5, 3, 15, 15, x0, y0, x1, y1);
    cout << "�߶�3�ü���" << endl << "[" << x0 << "," << y0 << "]-->"
        << "[" << x1 << "," << y1 << "]" << endl << endl;

    x0 = 12, y0 = 12, x1 = 14, y1 = 10;
    cout << "�߶�4�ü�ǰ��" << endl << "[" << x0 << "," << y0 << "]-->"
        << "[" << x1 << "," << y1 << "]" << endl;
    clipLine(5, 3, 15, 15, x0, y0, x1, y1);
    cout << "�߶�4�ü���" << endl << "[" << x0 << "," << y0 << "]-->"
        << "[" << x1 << "," << y1 << "]" << endl << endl;
}
void testPolygonClip() {
    //��5������2��ʵ��WA����βü�    
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
    //�����ζ������������
    Vec A{ -1,0,-2 }, B{ 2,0,-2 }, C{ 0,3,-3 };
    cout << "�����ζ�����������꣺" << endl;
    cout << A << B << C << endl;

    //�����ͶӰ����
    Camera camera{ Vec{0,0,0},Vec{0,0,-1},Vec{0,1,0} };
    camera.setPerspective(-2, 2, -1.5, 1.5, 1, 3);

    //һ�����������
    Vec bc{ 1.0 / 3,1.0 / 3,1.0 / 3 };
    //bc����������
    Vec bc_world = bc[0] * A + bc[1] * B + bc[2] * C;
    //bc���������
    Vec4 bc_eye = camera.world2eye(bc_world);
    //bc���ӿ�����
    Vec bc_img = camera.world2viewport(bc_world, 400, 300);
    Vec A_img = camera.world2viewport(A, 400, 300),
        B_img = camera.world2viewport(B, 400, 300),
        C_img = camera.world2viewport(C, 400, 300);

    //bc_img����������
    Vec bc_from_img = baryCentri(A_img, B_img, C_img, bc_img);
        
    cout << "��������ϵ�µ��������ꣻ" << bc << endl;
    cout << "�����ӿ����������������꣺" << bc_from_img << endl;

    //TODO:��Ȳ�ֵ
    float bc_d = 0;
    cout << "�������ϵ�µ���ȣ�" << bc_eye.z() << endl;
    cout << "��ֵ�õ�����ȣ�" << bc_d << endl;

    //������
    //canvas.fillTriangle(A_img, B_img, C_img);
}
void testScene() {
    Canvas canvas(image_height, image_width);
    //��������
    Scene scene;

    //����һ��������
    Cube cube;

    //����һ����
    Sphere sphere;
    //������z�᷽���ƶ�һ����λ��ʹ������������������Ķ����غϡ�
    Matrix4 r, t;
    r.setRotate(45, Vec{ 1,0,0 });
    cube.setTransform(r);
    t.setTranslate(Vec{ 0,0,1 });
    sphere.setTransform(t);

    scene.addObject(cube);
    scene.addObject(sphere);
    scene.draw(canvas);

    //���ͼ���ļ�
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

    //������
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
    
    //����ͶӰ���ڴ�С
    //��֤ͶӰ���ڱ������ӿڱ���һ��
    if (w > h)
        camera.setPerspective(-0.5 * w / h, 0.5 * w / h, -0.5, 0.5, n, f);
    else
        camera.setPerspective(-0.5, 0.5, -0.5 * h / w, 0.5 * h / w, n, f);

    Scene scene;
    scene.setCamera(camera);
    scene.drawTriangle(t1, canvas, &texture);
    scene.drawTriangle(t2, canvas, &texture);

    //���ͼ���ļ�
    canvas.outputPPM();
}
int main() {    
    testObj();
    return 0;
}
