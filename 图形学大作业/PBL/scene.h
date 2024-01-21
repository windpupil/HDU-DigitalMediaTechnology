#pragma once
#include "camera.h"
#include "canvas.h"
#include "OBJ_Loader.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include <vector>
#include <algorithm>
#define PI 3.1415926
using namespace std;

typedef Vec Vec3;
float max(float a, float b)
{
	if (a > b)
		return a;
	else
		return b;
}
//纹理类
class Texture
{
private:
	float* data;	//纹理图像数据，按行的顺序保存像素，每个像素占用c个float
	int w, h, c;	//图像宽度、高度、颜色通道数量（RGB为3，RGBA为4）
public:
	//构造函数
	Texture(const char* filename);
	//析构函数
	~Texture();
	
	//返回最近邻居像素颜色
	Vec3 getNN(float u, float v) const;
	//双线性插值，返回颜色
	Vec3 bilinearInterpolation(float u, float v) const;
};
Texture::Texture(const char* filename)
{
	//翻转y轴
	stbi_set_flip_vertically_on_load(true);
	//加载纹理图像
	data = stbi_loadf(filename, &w, &h, &c, 0);
}
Texture::~Texture()
{
	//释放纹理数据
	stbi_image_free(data);
}
//TODO:返回最近邻居像素颜色
//输入：纹理坐标u和v，取值范围为[0,1]
Vec3 Texture::getNN(float u, float v) const
{
	//图像空间坐标
	int x = u * w, y = v * h;
	if (x >= w)x--;
	if (y >= h)y--;

	return Vec3{ data[y * w * c + x * c] ,data[y * w * c + x * c + 1],
		data[y * w * c + x * c + 2] };
}
//TODO：双线性插值，返回颜色
//输入：纹理坐标u和v，取值范围为[0,1]
Vec3 Texture::bilinearInterpolation(float u, float v) const
{
	Vec3 color;
	float x = u * (w - 1), y = v * (h - 1);

	return color;
}

//三角形类
class Triangle {
public:
	//默认构造函数
	Triangle() {}
	//构造函数
	Triangle(const Vec3& A, const Vec3& B, const Vec3& C) {
		v[0] = A; v[1] = B; v[2] = C;
	}
	//对三角形就地做变换，改变它的顶点坐标值
	void transform(const Matrix4& m) {		
		for (int i = 0; i < 3; i++) {
			v[i] = m * Vec4{v[i]};
		}
	}
	//取第i个顶点
	Vec3 operator[](int i)const { return v[i]; }
	//设置顶点坐标
	void setVertex(const Vec3& A, const Vec3& B, const Vec3& C) {
		v[0] = A; v[1] = B; v[2] = C;
	}
	//设置顶点法向
	void setNormal(const Vec3& nA, const Vec3& nB, const Vec3& nC) {
		n[0] = nA; n[1] = nB; n[2] = nC;
	}
	Vec3 getNormal(int i)const { return n[i]; }
	//设置顶点纹理坐标
	void setTexCoord(int i, float u, float v) {
		t[i][0] = u;
		t[i][1] = v;
	}
	//取第i个顶点的颜色
	Vec getColor(int i)const { return c[i]; }
	//设置第i个顶点的颜色
	void setColor(int i, const Vec3& color) { c[i] = color; }
	//通过把三个顶点设为同一个颜色，设置面的颜色
	void setColor(const Vec3& color) { c[0] = c[1] = c[2] = color; }
	float getU(int i)const { return t[i][0]; }
	float getV(int i)const { return t[i][1]; }
private:
	//1.定义三角形的顶点及顶点属性（颜色）
	//三角形的三个顶点
	Vec3 v[3];
	//三角形顶点的法向
	Vec3 n[3];
	//顶点的颜色
	Vec3 c[3];
	//顶点对应的纹理坐标
	//t[i]第i个顶点的纹理坐标，u=t[i][0],b=t[i][1]，i=0,1,2
	float t[3][2];
};

//物体类
class Object {
public:
	//设置变换矩阵，并对每个三角形执行变换
	void setTransform(const Matrix4& trans) {
		m = trans;
		for (int i = 0; i < triangles.size();i++) {
			triangles[i].transform(m);
		}
	}
	//加载obj模型
	void loadObj(string path) {
		objl::Loader Loader;
		bool loadout = Loader.LoadFile(path);
		for (auto mesh : Loader.LoadedMeshes)
		{
			for (int i = 0; i < mesh.Vertices.size(); i += 3)
			{
				Vec A{ mesh.Vertices[i].Position.X, mesh.Vertices[i].Position.Y, mesh.Vertices[i].Position.Z }, 
					B{ mesh.Vertices[i + 1].Position.X, mesh.Vertices[i + 1].Position.Y, mesh.Vertices[i + 1].Position.Z }, 
					C{ mesh.Vertices[i + 2].Position.X, mesh.Vertices[i + 2].Position.Y, mesh.Vertices[i + 2].Position.Z };
				Vec nA{ mesh.Vertices[i].Normal.X, mesh.Vertices[i].Normal.Y, mesh.Vertices[i].Normal.Z }, 
					nB{ mesh.Vertices[i + 1].Normal.X, mesh.Vertices[i + 1].Normal.Y, mesh.Vertices[i + 1].Normal.Z }, 
					nC{ mesh.Vertices[i + 2].Normal.X, mesh.Vertices[i + 2].Normal.Y, mesh.Vertices[i + 2].Normal.Z };
				float tA[2]{ mesh.Vertices[i].TextureCoordinate.X, mesh.Vertices[i].TextureCoordinate.Y }, 
					tB[2]{ mesh.Vertices[i + 1].TextureCoordinate.X, mesh.Vertices[i + 1].TextureCoordinate.Y }, 
					tC[2]{ mesh.Vertices[i + 2].TextureCoordinate.X, mesh.Vertices[i + 2].TextureCoordinate.Y };
				
				Triangle t{A,B,C};
				t.setNormal(nA, nB, nC);
				t.setTexCoord(0,tA[0],tA[1]);
				t.setTexCoord(1,tB[0],tB[1]);
				t.setTexCoord(2,tC[0],tC[1]);
				
				triangles.push_back(t);
			}
		}
	}
	//获取三角形列表
	const vector<Triangle>& getTriangles() const { return triangles; }
protected:
	//物体的变换矩阵
	Matrix4 m;
	//物体的三角形列表
	vector<Triangle> triangles;
};

//场景
class Scene {
public:
	Camera camera;	//相机
	Scene() :camera{ Vec{0,0,100},Vec{0,0,-1},Vec{0,1,0} } {}
	Vec Light1_pos = camera.GetEye();
	Vec Light2_pos = camera.GetEye() + Vec{0,100,0};
	Vec Light3_pos = camera.GetEye() + Vec{100,0,10};
	Color Light{ 1,1,1 };
	int flag1 = 0;
	int flag2 = 0;
	int flag3 = 0;
	void setCamera(const Camera& camera) { this->camera = camera; }
	//向场景中添加物体
	//根据场景包围盒设置相机参数，使得整个场景都被包含在视景体内
	void addObject(const Object& object, int on) {
		//获取物体的三角网格，并添加到场景三角形列表中
		vector<Triangle> obj_triangles = object.getTriangles();
		triangles_world.insert(triangles_world.end(), obj_triangles.begin(), obj_triangles.end());

		int triangles_world_size=triangles_world.size();
		
		auto object_triangles_num_size = object_triangles_num.begin();
		while (on > 0) {
			object_triangles_num_size++;
			on--;
		}
		object_triangles_num.insert((object_triangles_num_size + 1), {triangles_world_size});
		

		//计算场景包围盒
		float xmin, xmax, ymin, ymax, zmin, zmax;
		getBBox(xmin, xmax, ymin, ymax, zmin, zmax);
		float xspan = xmax - xmin;
		float yspan = ymax - ymin;
		float zspan = zmax - zmin;

		//相机看向场景中心
		Vec lookat{ (xmin + xmax) / 2,(ymin + ymax) / 2,(zmin + zmax) / 2 };
		//相机放在z轴正方向，到场景中心距离为zmax + max(xspan,yspan)
		Vec eye = lookat + Vec{ 0,0, zmax + max(xspan,yspan) };
		Vec up{ 0,1,0 };
		//设置相机视图矩阵
		camera.setView(eye, lookat, up);

		//设置相机景深
		float f = max(xspan, yspan) + 2 * zspan;
		camera.setDepth(1, f);
		int texture_num = 0;
	}
	//修改相机的位置
	void SetCameraView(float dx,float dy,float dz,Camera &camera)
	{
		//计算场景包围盒
		float xmin, xmax, ymin, ymax, zmin, zmax;
		getBBox(xmin, xmax, ymin, ymax, zmin, zmax);
		float xspan = xmax - xmin;
		float yspan = ymax - ymin;
		float zspan = zmax - zmin;

		//相机看向场景中心
		Vec lookat{ (xmin + xmax) / 2,(ymin + ymax) / 2,(zmin + zmax) / 2 };
		//cout << lookat;
		//相机放在z轴正方向，到场景中心距离为zmax + max(xspan,yspan)
		Vec eye = camera.GetEye()+ Vec{ dx,dy,dz };
		Vec up{ 0,1,0 };
		//设置相机视图矩阵
		camera.setView(eye, lookat, up);
	}
	//修改相机的角度
	void SetCameraView(float degree,Camera &camera)
	{
		//计算场景包围盒
		float xmin, xmax, ymin, ymax, zmin, zmax;
		getBBox(xmin, xmax, ymin, ymax, zmin, zmax);
		float xspan = xmax - xmin;
		float yspan = ymax - ymin;
		float zspan = zmax - zmin;

		//相机看向场景中心
		Vec lookat{ (xmin + xmax) / 2,(ymin + ymax) / 2,(zmin + zmax) / 2 };
		//相机放在z轴正方向，到场景中心距离为zmax + max(xspan,yspan)
		Vec eye_old = camera.GetEye() - lookat;
		Vec eye_new;
		eye_new[0] = eye_old[0] * sin(degree) - eye_old[2] * cos(degree);
		eye_new[0] = eye_old[0] * cos(degree) + eye_old[2] * sin(degree);
		eye_new = lookat + eye_new;
		Vec up{ 0,1,0 };
		//设置相机视图矩阵
		camera.setView(eye_new, lookat, up);
	}
	//绘制场景
	void draw(Canvas& canvas, const Texture* tex = nullptr,int tn=0, const Object* object =nullptr);
	void drawTriangle(const Triangle& t, Canvas& canvas,
		const Texture* tex = nullptr);
	
private:
	//计算场景包围盒
	void getBBox(float& xmin, float& xmax, float& ymin, float& ymax, 
		float& zmin, float& zmax) {
		Vec p = triangles_world[0][0];
		xmin = xmax = p.x();
		ymin = ymax = p.y();
		zmin = zmax = p.z();
		for (auto tri : triangles_world) {
			for (int i = 0; i < 3; i++) {
				Vec p = tri[i];
				if (xmin > p.x())xmin = p.x();
				if (xmax < p.x())xmax = p.x();
				if (ymin > p.y())ymin = p.y();
				if (ymax < p.y())ymax = p.y();
				if (zmin > p.z())zmin = p.z();
				if (zmax < p.z())zmax = p.z();
			}
		}
	}
	vector<Triangle> triangles_world;	//场景多边形列表，定义在世界坐标系下
	vector<long int> object_triangles_num = {0};
	//判断点是否在内部
	Vec chaji(Vec p1, Vec p2)
	{
		return Vec{ p1[1] * p2[2] - p1[2] * p2[1],p1[2] * p2[0] - p1[0] * p2[2],p1[0] * p2[1] - p1[1] - p2[0] };
	}
	bool isinside(Triangle tri, Vec point)
	{
		Vec p1 = { tri[0][0] - point[0],tri[0][1] - point[1],tri[0][2] - point[2] };
		Vec p2 = { tri[1][0] - point[0],tri[1][1] - point[1],tri[1][2] - point[2] };
		Vec p3 = { tri[2][0] - point[0],tri[2][1] - point[1],tri[2][2] - point[2] };
		float angle = 0;
		float angle1_cos = ((p1[0] * p2[0] + p1[1] * p2[1] + p1[2] * p2[2]) / (sqrt(p1[0] * p1[0] + p1[1] * p1[1] + p1[2] * p1[2]) * sqrt(p2[0] * p2[0] + p2[1] * p2[1] + p2[2] * p2[2])));
		float flag1 = chaji(p1, p2)[0] / fabs(chaji(p1, p2)[0]);
		float angle1 = acosf(angle1_cos) * flag1;

		float angle2_cos = ((p2[0] * p3[0] + p2[1] * p3[1] + p2[2] * p3[2]) / (sqrt(p2[0] * p2[0] + p2[1] * p2[1] + p2[2] * p2[2]) * sqrt(p3[0] * p3[0] + p3[1] * p3[1] + p3[2] * p3[2])));
		float flag2 = chaji(p2, p3)[0] / fabs(chaji(p2, p3)[0]);
		float angle2 = acosf(angle2_cos) * flag2;

		float angle3_cos = ((p3[0] * p1[0] + p3[1] * p1[1] + p3[2] * p1[2]) / (sqrt(p3[0] * p3[0] + p3[1] * p3[1] + p3[2] * p3[2]) * sqrt(p1[0] * p1[0] + p1[1] * p1[1] + p1[2] * p1[2])));
		float flag3 = chaji(p3, p1)[0] / fabs(chaji(p3, p1)[0]);
		float angle3 = acosf(angle3_cos) * flag3;

		angle = angle1 + angle2 + angle3;
		if (fabs(angle - 2 * PI) <= 0.002)
			return true;
		else
			return false;
	}
	//求交函数
	Vec intersection_point(Vec ray_pos, Vec ray_direction, Color ray_color, Triangle tri)//返回交点
	{
		Vec e1 = { tri[1][0] - tri[0][0],tri[1][1] - tri[0][1],tri[1][2] - tri[0][2] };
		Vec e2 = { tri[2][0] - tri[0][0],tri[2][1] - tri[0][1],tri[2][2] - tri[0][2] };
		Vec p_n = { e1[1] * e2[2] - e1[2] * e2[1],e1[2] * e2[0] - e1[0] * e2[2],e1[0] * e2[1] - e1[1] * e2[0] };//平面法向量
		float D = 0 - p_n[0] * tri[0][0] - p_n[1] * tri[0][1] - p_n[2] * tri[0][2];
		float t = 0;
		p_n[0] * (ray_pos[0] + t * ray_direction[0]);
		t = (-1 * D - p_n[0] * ray_pos[0] - p_n[1] * ray_pos[1] - p_n[2] * ray_pos[2]) / (ray_direction[0] + ray_direction[1] + ray_direction[2]);
		Vec p = { ray_pos[0] + t * ray_direction[0],ray_pos[1] + t * ray_direction[1],ray_pos[2] + t * ray_direction[2] };
		Vec bc = baryCentri(tri[0], tri[1], tri[2], p);
		if (0 <= bc[0] && bc[0] <= 1 &&
			0 <= bc[1] && bc[1] <= 1 &&
			0 <= bc[2] && bc[2] <= 1)
		{
			return p;
		}
		else
			return Vec{ 0,0,0 };
	}
	Vec intersection_direction(Vec ray_pos, Vec ray_direction, Color ray_color, Triangle tri)//返回方向
	{
		Vec e1 = { tri[1][0] - tri[0][0],tri[1][1] - tri[0][1],tri[1][2] - tri[0][2] };
		Vec e2 = { tri[2][0] - tri[0][0],tri[2][1] - tri[0][1],tri[2][2] - tri[0][2] };
		Vec p_n = { e1[1] * e2[2] - e1[2] * e2[1],e1[2] * e2[0] - e1[0] * e2[2],e1[0] * e2[1] - e1[1] * e2[0] };//平面法向量
		Vec temp = { ray_direction[0] - p_n[0],ray_direction[1],ray_direction[2] - p_n[2] };
		Vec new_dir = { -temp[0] + p_n[0],temp[1],-temp[2] + p_n[2] };
		return new_dir;
	}
};


void Scene::draw(Canvas& canvas, const Texture* tex,int tn, const Object* object)
{
	int w = canvas.getW();
	int h = canvas.getH();
	//canvas.clear(WHITE);

	//设置投影窗口大小
	//保证投影窗口比例和视口比例一致
	if (w > h)
		camera.setPerspective(-0.5 * w / h, 0.5 * w / h, -0.5, 0.5);
	else
		camera.setPerspective(-0.5, 0.5, -0.5 * h / w, 0.5 * h / w);
	auto it = object_triangles_num.begin();
	//while (tn>0) {
	//	it++;
	//	tn--;
	//}
	//auto it_end = it;
	//it_end++;

	//绘制场景中的每个三角形
	for (int i = 0; i < object->getTriangles().size(); i++)
	{
		drawTriangle(object->getTriangles()[i], canvas, tex);
	}
	/*----------------------------phong 光照模型结束后的光线追踪 暂定光源位于相机位置 ，方向为（1，1，0）-----------------------------*/
	Color ray_color = { 255,255,255 };
	Vec ray_pos = camera.GetEye();
	Vec ray_direction = { 5.13343f- ray_pos.x(), 1.99786f- ray_pos.y(), -0.0795369f- ray_pos.z()};

	//for (int i = 0; i < 10; i++)
	//{
	//	ray_direction[1] += 0.5;

		for (int time = 0; time < 10; time++)
		{
			for (int i = 0; i < object->getTriangles().size(); i++)
			{
				ray_pos = intersection_point(ray_pos, ray_direction, ray_color, triangles_world[i]);//更新交点坐标;
				ray_direction = intersection_direction(ray_pos, ray_direction, ray_color, triangles_world[i]);//返回反射后光线方向
				ray_direction.normalize();
				if ((ray_pos[0] == 1) && (ray_pos[1] == 1) && (ray_pos[2] == 1))break;
				else
				{
					Vec in_p_view = camera.world2viewport(in_p_view, canvas.getW(), canvas.getH());//转为视口坐标
					if (in_p_view.z() == canvas.getDepth(in_p_view.x(), in_p_view.y()))
					{
						Color c_old = canvas.getPixel(in_p_view.x(), in_p_view.y());
						Color c_plus = ray_color;//光线追踪对该点纹理的影响值
						Color c_new = { c_old.r + c_plus.r,c_old.g + c_plus.g,c_old.b + c_plus.b };
						canvas.setPixel(in_p_view.x(), in_p_view.y(), c_new);
						ray_color = { c_new.r * 0.7f,c_new.g * 0.7f ,c_new.b * 0.7f };//每次反射后光线衰减
					}
				}
			}
		}
	//}
}

void Scene::drawTriangle(const Triangle& t, Canvas& canvas, const Texture* tex)
{
	Vec p1 = camera.world2viewport(t[0], canvas.getW(), canvas.getH()),
		p2 = camera.world2viewport(t[1], canvas.getW(), canvas.getH()),
		p3 = camera.world2viewport(t[2], canvas.getW(), canvas.getH());
	int xmin = min(min(p1.x(), p2.x()), p3.x()) + 0.5;
	int xmax = max(max(p1.x(), p2.x()), p3.x()) + 0.5;
	int ymin = min(min(p1.y(), p2.y()), p3.y()) + 0.5;
	int ymax = max(max(p1.y(), p2.y()), p3.y()) + 0.5;
	//预计算顶点深度的倒数
	float _p1z = 1 / p1.z(), _p2z = 1 / p2.z(), _p3z = 1 / p3.z();
	//顶点法向
	Vec p1n = t.getNormal(0), p2n = t.getNormal(1), p3n = t.getNormal(2);
	//读取顶点的纹理坐标
	float u1 = t.getU(0), u2 = t.getU(1), u3 = t.getU(2);
	float v1 = t.getV(0), v2 = t.getV(1), v3 = t.getV(2);
	//遍历三角形包围盒内的像素点
	for (int x = xmin; x <= xmax; x++) {
		for (int y = ymin; y <= ymax; y++) {
			//计算像素点的重心坐标
			Vec bc = baryCentri(p1, p2, p3, Vec{ float(x),float(y),1 });
			//根据重心坐标判断点是否在三角形内
			if (0 <= bc[0] && bc[0] <= 1 &&
				0 <= bc[1] && bc[1] <= 1 &&
				0 <= bc[2] && bc[2] <= 1) {
				//插值得到深度
				float z = 1 / (bc[0] * _p1z + bc[1] * _p2z + bc[2] * _p3z);
				//参考资料：
//https://www.scratchapixel.com/lessons/3d-basic-rendering/rasterization-practical-implementation/perspective-correct-interpolation-vertex-attributes.html
				//TODO:法向插值
				Vec n = z * (p1n * _p1z * bc[0] + p2n * _p2z * bc[1] + 
					p3n * _p3z * bc[2]);
				n.normalize();
				//TODO:顶点世界坐标插值
				//顶点插值后的坐标
				Vec P{ (t[0].x() + t[1].x() + t[2].x()) / 3,(t[0].y() + t[1].y() + t[2].y()) / 3,(t[0].z() + t[1].z() + t[2].z()) / 3 };
				//TODO:纹理坐标插值
				float u = z * (u1 * _p1z * bc[0] + u2 * _p2z * bc[1] + 
					u3 * _p3z * bc[2]);
				float v = z * (v1 * _p1z * bc[0] + v2 * _p2z * bc[1] +
					v3 * _p3z * bc[2]);
				//TODO:获取纹理颜色
				Vec3 tex_color = tex->getNN(u, v);
				//Vec3 tex_color_b = tex->bilinearInterpolation(u, v);
				//TODO:Phong光照颜色计算
				 
				//环境光（Ambient）
				Color ambient{ tex_color[0] * 255 * 0.3,tex_color[1] * 255 * 0.3,tex_color[2] * 255 * 0.3 };

				//漫反射（Diffuse）
				float kdr = tex_color[0], kdg = tex_color[1], kdb = tex_color[2];
				Color diffuse;
				Vec connect1 = Light1_pos - P;
				Vec connect2 = Light2_pos - P;
				Vec connect3 = Light3_pos - P;
				float nl = connect1[0] * n[0] + connect1[1] * n[1] + connect1[2] * n[2];
				float n2 = connect2[0] * n[0] + connect2[1] * n[1] + connect2[2] * n[2];
				float n3 = connect3[0] * n[0] + connect3[1] * n[1] + connect3[2] * n[2];
				diffuse.r = kdr * Light.r * max(0, fabs(nl)) * 0.7*flag1+ kdr * Light.r * max(0, fabs(n2)) * 0.7 * flag2 +kdr * Light.r * max(0, fabs(n3)) * 0.7 * flag3;
				diffuse.g = kdg * Light.g * max(0, fabs(nl)) * 0.7 * flag1 + kdg * Light.g * max(0, fabs(n2)) * 0.7 * flag2 + kdg * Light.g * max(0, fabs(n3)) * 0.7 * flag3;
				diffuse.b = kdb * Light.b * max(0, fabs(nl)) * 0.7 * flag1 + kdb * Light.b * max(0, fabs(n2)) * 0.7 * flag2 + kdb * Light.b * max(0, fabs(n3)) * 0.7 * flag3;

				//⾼光反射（Specular） 
				Color specular;
				float rv1 = connect1[0] * connect1[0] + connect1[1] * connect1[1] + connect1[2] * connect1[2];
				float rv2 = connect2[0] * connect2[0] + connect2[1] * connect2[1] + connect2[2] * connect2[2];
				float rv3 = connect3[0] * connect3[0] + connect3[1] * connect3[1] + connect3[2] * connect3[2];
				specular.r = kdr * Light.r * pow(max(0, rv1), 0.3) * flag1 + kdr * Light.r * pow(max(0, rv2), 0.3) * flag2 + kdr * Light.r * pow(max(0, rv3), 0.3) * flag3;
				specular.g = kdg * Light.g * pow(max(0, rv1), 0.3) * flag1 + kdg * Light.g * pow(max(0, rv2), 0.3) * flag2 + kdg * Light.g * pow(max(0, rv3), 0.3) * flag3;
				specular.b = kdb * Light.b * pow(max(0, rv1), 0.3) * flag1 + kdg * Light.g * pow(max(0, rv2), 0.3) * flag2 + kdg * Light.g * pow(max(0, rv3), 0.3) * flag3;

				//Combine
				Color c{ ambient.r + diffuse.r + specular.r ,ambient.g + diffuse.g + specular.g ,ambient.b + diffuse.b + specular.b };

				////Color c{ tex_color[0] * 255,tex_color[1] * 255,tex_color[2] * 255 };
				if (z < canvas.getDepth(x, y)) {
					canvas.setPixel(x, y, c);
					canvas.setDepth(x, y, z);
				}
			}
		}
	}
}