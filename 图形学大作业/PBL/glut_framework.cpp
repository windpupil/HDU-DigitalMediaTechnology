#define GLUT_DISABLE_ATEXIT_HACK
#include "scene.h"
#include "canvas.h"
#include "GLUT.H"
//����
Texture texture1("../hducg23/models/PBL/����/����.png");
//����
Texture texture2("../hducg23/models/PBL/����/��������.jpg");
//����
Texture texture3("../hducg23/models/PBL/����/����.png");
//ֲ��
Texture texture4("../hducg23/models/PBL/����/ֲ��.png");
//����
Texture texture5("../hducg23/models/PBL/����/��ɫ.png");
//��Χ
Texture texture6("../hducg23/models/PBL/����/ǽ��.jpg");
//��̨
Texture texture7("../hducg23/models/PBL/����/��ɫ.png");
//�ڰ�
Texture texture8("../hducg23/models/PBL/����/��ɫ.png");

void Canvas::outputScreen()
{
	glBegin(GL_POINTS);	
	//���б����������飬��opengl���㺯����������
	//ԭ�������½ǣ�ˮƽx���򣬴�ֱy����
	for (int y = height - 1; y >= 0; y--) {
		for (int x = 0; x < width; x++) {
			Color c = getPixel(x, y);
			glColor3f(float(c.r)/255, float(c.g)/255, float(c.b)/255);
			glVertex3f(x, y, getDepth(x, y));
		}
	}
	glEnd();
}

//���Ƴ���
//�ӿڴ�С
int viewport_width = 800, viewport_height = 600;
float xmove = 0;
float ymove = 0;
Scene scene;
Object obj;//����
Object obj2;//ֲ��
Object obj3;//����
Object obj4;//����
Object obj5;//����
Object obj6;//��Χ
Object obj7;//��̨
Object obj8;//�ڰ�

Object obj9;//����
Object obj10;//����
Matrix4 m;//�任����


//��������
void display(void)
{
	int texture_num = 0;
	//���û�������ɫ
	glClearColor(1.f, 1.f, 1.f, 0.f);
	glClear(GL_COLOR_BUFFER_BIT);
  
	//���Ƴ���
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
	//ˢ��֡����
	glFlush();
}
//���̽����¼�
void keyboard(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 'w'://�������ǰ
	case 'W':
	{
		scene.SetCameraView(0, 0, -1,scene.camera);
		glutPostRedisplay();
		break;
	}
	case 's'://��������
	case 'S':
	{
		scene.SetCameraView(0, 0, 1, scene.camera);
		glutPostRedisplay();
		break;
	} 
	case 'a'://���������
	case 'A':
	{
		scene.SetCameraView(1 , 0,0, scene.camera);
		glutPostRedisplay();
		break;
	}
	case 'd'://���������
	case 'D':
	{
		scene.SetCameraView(-1,0, 0, scene.camera);
		glutPostRedisplay();
		break;
	}
	case 'z'://���������
	case 'Z':
	{
		scene.SetCameraView(0, 1, 0, scene.camera);
		glutPostRedisplay();
		break;
	}
	case 'c'://���������
	case 'C':
	{
		scene.SetCameraView(0, -1, 0, scene.camera);
		glutPostRedisplay();
		break;
	}
	case 'q'://�����������ת
	case 'Q':
	{
		scene.SetCameraView(0.1, scene.camera);
		glutPostRedisplay();
		break;
	}
	case 'e'://�����������ת
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

//��꽻���¼�
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

//ͶӰ��ʽ��modelview��ʽ������
void reshape(int w, int h)
{
	viewport_width = w, viewport_height = h;
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);//�ӿڴ�С
	glMatrixMode(GL_PROJECTION);//����ͶӰģʽ�Լ��Ӿ����С
	glLoadIdentity();
	//����opengl��ͶӰ��ʽΪ����ͶӰ
	//ͶӰƽ���С���ӿڴ�Сһ��
	//��glVertex2fģ�⻭����
	glOrtho(0, w, 0, h,	-200, 200);
	//��opengl����ͼ�任����Ϊ��λ����
	//������Camera�����Լ�ʵ����ͼ��ͶӰ���ӿڱ任
	glMatrixMode(GL_MODELVIEW); 
	glLoadIdentity();
}
//��ʼ������
void initScene()
{
	obj.loadObj("../hducg23/models/PBL/ģ��/����.obj");
	m.setTranslate(Vec{ 8,0,2 });
	obj.setTransform(m);

	obj2.loadObj("../hducg23/models/spot/plant.obj");
	m.setTranslate(Vec{ 7,0,2 });
	obj2.setTransform(m);

	obj3.loadObj("../hducg23/models/PBL/ģ��/����.obj");
	m.setTranslate(Vec{ 10,0,-8 });
	obj3.setTransform(m);

	obj4.loadObj("../hducg23/models/PBL/ģ��/����.obj");
	m.setTranslate(Vec{ 10,0,-7.8 });
	obj4.setTransform(m);


	obj5.loadObj("../hducg23/models/PBL/ģ��/����.obj");
	m.setTranslate(Vec{ 8,0,0 });
	obj5.setTransform(m);


	obj6.loadObj("../hducg23/models/PBL/ģ��/��Χ.obj");
	m.setRotate(180, Vec{ 0,1,0 });
	obj6.setTransform(m);

	obj7.loadObj("../hducg23/models/PBL/ģ��/��̨.obj");
	m.setTranslate(Vec{ 15,0,0 });
	obj7.setTransform(m);


	obj8.loadObj("../hducg23/models/PBL/ģ��/�ڰ�.obj");
	m.setTranslate(Vec{ 18,0,0 });
	obj8.setTransform(m);

	obj9.loadObj("../hducg23/models/PBL/ģ��/����.obj");
	m.setTranslate(Vec{ 6.9,0,-8 });
	obj9.setTransform(m);

	obj10.loadObj("../hducg23/models/PBL/ģ��/����.obj");
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
//��������
int main(int argc, char **argv)
{
	//��ʼ������
	initScene();
	
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB);
	glutInitWindowSize(viewport_width, viewport_height);
	glutInitWindowPosition(50, 50);
	glutCreateWindow("3_��ĩ����ҵ");
 
	glutReshapeFunc(reshape);
	glutDisplayFunc(display);
	glutKeyboardFunc(keyboard);
	glutMouseFunc(mouse);
	
	glutMainLoop();
	return 0;
}
