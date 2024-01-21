#define GLUT_DISABLE_ATEXIT_HACK
#include "scene.h"
#include "canvas.h"
#include "GLUT.H"
//椅子
Texture texture1("../hducg23/models/PBL/纹理/椅子.png");
//窗帘
Texture texture2("../hducg23/models/PBL/纹理/窗帘纹理.jpg");
//桌子
Texture texture3("../hducg23/models/PBL/纹理/桌子.png");
//植物
Texture texture4("../hducg23/models/PBL/纹理/植物.png");
//窗户
Texture texture5("../hducg23/models/PBL/纹理/白色.png");
//周围
Texture texture6("../hducg23/models/PBL/纹理/墙壁.jpg");
//讲台
Texture texture7("../hducg23/models/PBL/纹理/银色.png");
//黑板
Texture texture8("../hducg23/models/PBL/纹理/黑色.png");

void Canvas::outputScreen()
{
	glBegin(GL_POINTS);	
	//按行遍历像素数组，用opengl画点函数绘制像素
	//原点在左下角，水平x方向，垂直y方向
	for (int y = height - 1; y >= 0; y--) {
		for (int x = 0; x < width; x++) {
			Color c = getPixel(x, y);
			glColor3f(float(c.r)/255, float(c.g)/255, float(c.b)/255);
			glVertex3f(x, y, getDepth(x, y));
		}
	}
	glEnd();
}

//绘制场景
//视口大小
int viewport_width = 800, viewport_height = 600;
float xmove = 0;
float ymove = 0;
Scene scene;
Object obj;//椅子
Object obj2;//植物
Object obj3;//窗户
Object obj4;//窗帘
Object obj5;//桌子
Object obj6;//周围
Object obj7;//讲台
Object obj8;//黑板

Object obj9;//窗户
Object obj10;//窗帘
Matrix4 m;//变换矩阵


//绘制内容
void display(void)
{
	int texture_num = 0;
	//设置画布背景色
	glClearColor(1.f, 1.f, 1.f, 0.f);
	glClear(GL_COLOR_BUFFER_BIT);
  
	//绘制场景
	Canvas canvas(viewport_height, viewport_width);
	scene.draw(canvas, &texture1, texture_num, &obj);
	scene.draw(canvas, &texture2, texture_num, &obj2);
	scene.draw(canvas, &texture3, texture_num, &obj3);
	scene.draw(canvas, &texture4, texture_num, &obj4);
	scene.draw(canvas, &texture5, texture_num, &obj5);
	scene.draw(canvas, &texture6, texture_num, &obj6);
	scene.draw(canvas, &texture7, texture_num, &obj7);
	scene.draw(canvas, &texture8, texture_num, &obj8);
	scene.draw(canvas, &texture5, texture_num, &obj9);
	scene.draw(canvas, &texture4, texture_num, &obj10);

	canvas.outputScreen();
	canvas.outputPPM();
	//刷新帧缓存
	glFlush();
}
//键盘交互事件
void keyboard(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 'w'://摄像机向前
	case 'W':
	{
		scene.SetCameraView(0, 0, -1,scene.camera);
		glutPostRedisplay();
		break;
	}
	case 's'://摄像机向后
	case 'S':
	{
		scene.SetCameraView(0, 0, 1, scene.camera);
		glutPostRedisplay();
		break;
	} 
	case 'a'://摄像机向左
	case 'A':
	{
		scene.SetCameraView(1 , 0,0, scene.camera);
		glutPostRedisplay();
		break;
	}
	case 'd'://摄像机向右
	case 'D':
	{
		scene.SetCameraView(-1,0, 0, scene.camera);
		glutPostRedisplay();
		break;
	}
	case 'z'://摄像机向上
	case 'Z':
	{
		scene.SetCameraView(0, 1, 0, scene.camera);
		glutPostRedisplay();
		break;
	}
	case 'c'://摄像机向下
	case 'C':
	{
		scene.SetCameraView(0, -1, 0, scene.camera);
		glutPostRedisplay();
		break;
	}
	case 'q'://摄像机向左旋转
	case 'Q':
	{
		scene.SetCameraView(0.1, scene.camera);
		glutPostRedisplay();
		break;
	}
	case 'e'://摄像机向右旋转
	case 'E':
	{
		scene.SetCameraView(-0.1, scene.camera);
		glutPostRedisplay();
		break;
	}
	case 'u':
	case 'U':
	{
		scene.flag1 = 1 - scene.flag1;
		glutPostRedisplay();
		break;
	}case 'i':
	case 'I':
	{
		scene.flag2 = 1 - scene.flag2;
		glutPostRedisplay();
		break;
	}case 'o':
	case 'O':
	{
		scene.flag3 = 1 - scene.flag3;
		glutPostRedisplay();
		break;
	}
	case 27:
		exit(0);
		break;
	}
}

//鼠标交互事件
void mouse(int button, int state, int x, int y)
{
	switch (button)
	{
	case GLUT_LEFT_BUTTON:
		if (state == GLUT_DOWN)
		{
			//scene.flag1
			glutPostRedisplay();
		}
		break;
	case GLUT_RIGHT_BUTTON:
		if (state == GLUT_DOWN)
		{
			
			glutPostRedisplay();
		}
		break;
	default:
		break;
	}
}

//投影方式、modelview方式等设置
void reshape(int w, int h)
{
	viewport_width = w, viewport_height = h;
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);//视口大小
	glMatrixMode(GL_PROJECTION);//设置投影模式以及视景体大小
	glLoadIdentity();
	//设置opengl的投影方式为正交投影
	//投影平面大小与视口大小一致
	//用glVertex2f模拟画像素
	glOrtho(0, w, 0, h,	-200, 200);
	//将opengl的视图变换矩阵为单位矩阵
	//我们在Camera类中自己实现视图、投影和视口变换
	glMatrixMode(GL_MODELVIEW); 
	glLoadIdentity();
}
//初始化场景
void initScene()
{
	obj.loadObj("../hducg23/models/PBL/模型/椅子.obj");
	m.setTranslate(Vec{ 8,0,2 });
	obj.setTransform(m);

	obj2.loadObj("../hducg23/models/spot/plant.obj");
	m.setTranslate(Vec{ 7,0,2 });
	obj2.setTransform(m);

	obj3.loadObj("../hducg23/models/PBL/模型/窗户.obj");
	m.setTranslate(Vec{ 10,0,-8 });
	obj3.setTransform(m);

	obj4.loadObj("../hducg23/models/PBL/模型/窗帘.obj");
	m.setTranslate(Vec{ 10,0,-7.8 });
	obj4.setTransform(m);


	obj5.loadObj("../hducg23/models/PBL/模型/桌子.obj");
	m.setTranslate(Vec{ 8,0,0 });
	obj5.setTransform(m);


	obj6.loadObj("../hducg23/models/PBL/模型/周围.obj");
	m.setRotate(180, Vec{ 0,1,0 });
	obj6.setTransform(m);

	obj7.loadObj("../hducg23/models/PBL/模型/讲台.obj");
	m.setTranslate(Vec{ 15,0,0 });
	obj7.setTransform(m);


	obj8.loadObj("../hducg23/models/PBL/模型/黑板.obj");
	m.setTranslate(Vec{ 18,0,0 });
	obj8.setTransform(m);

	obj9.loadObj("../hducg23/models/PBL/模型/窗户.obj");
	m.setTranslate(Vec{ 6.9,0,-8 });
	obj9.setTransform(m);

	obj10.loadObj("../hducg23/models/PBL/模型/窗帘.obj");
	m.setTranslate(Vec{ 6.9,0,-7.8 });
	obj10.setTransform(m);

	scene.addObject(obj, 0);
	scene.addObject(obj2, 0);
	scene.addObject(obj3, 0);
	scene.addObject(obj4, 0);
	scene.addObject(obj5, 0);
	scene.addObject(obj6, 0);
	scene.addObject(obj7, 0);
	scene.addObject(obj8, 0);
	scene.addObject(obj9, 0);
	scene.addObject(obj10, 0);
}
//主调函数
int main(int argc, char **argv)
{
	//初始化场景
	initScene();
	
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB);
	glutInitWindowSize(viewport_width, viewport_height);
	glutInitWindowPosition(50, 50);
	glutCreateWindow("3_期末大作业");
 
	glutReshapeFunc(reshape);
	glutDisplayFunc(display);
	glutKeyboardFunc(keyboard);
	glutMouseFunc(mouse);
	
	glutMainLoop();
	return 0;
}
