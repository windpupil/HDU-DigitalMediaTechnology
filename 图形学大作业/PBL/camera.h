#pragma once
#include "matrix.h"

typedef Vec Vec3;

class Camera {
public:
	//给定相机位置，相机看向的点，上方向，构造视图变换矩阵
	//参考资料：https://www.songho.ca/opengl/gl_camera.html#lookat
	Camera(const Vec3& eye, const Vec3& at, const Vec3& up) {
		mview.setView(eye, at, up);
		//setPerspective(-0.5, 0.5, -0.5, 1, 1, 6);
		//cout <<"视图变换矩阵：" <<endl<< mview << endl;
		this->eye = eye;
	}
	void setView(const Vec3& eye, const Vec3& at, const Vec3& up) {
		mview.setView(eye, at, up);
		this->eye = eye;
	}
	//获取视图变换矩阵
	Matrix4 Getmview()
	{
		return mview;
	}
	void setDepth(float n, float f) {
		this->n = n;
		this->f = f;
	}
	//设置正交投影矩阵
	void setOrtho(float l, float r, float b, float t, float n, float f) {
		mproj.setOrtho(l, r, b, t, n, f);
		this->n = n;
		this->f = f;
	}
	//设置透视投影矩阵
	//参考资料：https://www.songho.ca/opengl/gl_projectionmatrix.html
	void setPerspective(float l, float r, float b, float t, float n, float f) {
		mproj.setPerspective(l, r, b, t, n, f);
		this->n = n;
		this->f = f;
		//cout << "透视投影矩阵：" << endl << mproj << endl;
	}
	void setPerspective(float l, float r, float b, float t) {
		mproj.setPerspective(l, r, b, t, n, f);		
		//cout << "透视投影矩阵：" << endl << mproj << endl;
	}
	//世界坐标转为相机坐标
	Vec4 world2eye(const Vec3& pw) {
		return mview * Vec4{pw};
	}
	//相机坐标转为裁剪坐标
	//x=pe.x*2n/(r-l)+pe.z*(r+l)/(r-l)
	//y=pe.y*2n/(t-b)+pe.z*(t+b)/(t-b)
	//z=-pe.z*(f+n)/(f-n)-2fn/(f-n)
	//w=-pe.z
	Vec4 eye2clip(const Vec4& pe) {
		return mproj * pe;
	}	
	//裁剪坐标转为标准设备坐标
	//x: [l,r]-->[-1,1],x=-pe.x/pe.z*2n/(r-l)-(r+l)/(r-l)
	//y: [b,t]-->[-1,1], y=-pe.y/pe.z*2n/(t-b)-(t+b)/(t-b)
	//z: [-n,-f]-->[-1,1], z=(f+n)/(f-n)+2fn/pe.z/(f-n)
	Vec3 clip2ndc(const Vec4& pc) {
		return Vec3{ pc.x() / pc.w(),pc.y() / pc.w(),pc.z() / pc.w() };
	}
	//标准设备坐标转为视口坐标
	//参考资料：https://www.songho.ca/opengl/gl_transform.html
	//x: [-1,1]-->[0,w]
	//y: [-1,1]-->[0,h]
	//z: [-1,1]-->[n,f]
	Vec3 ndc2viewport(const Vec3& pn, int w, int h) {
		return Vec3{ (pn.x() + 1) * w / 2,(pn.y() + 1) * h / 2,
			-2 * f * n / (pn.z() * (f - n) - (f + n)) };
			//pn.z() * (f - n) / 2 + (f + n) / 2 };
	}
	//世界坐标变换到视口坐标
	Vec3 world2viewport(const Vec& pw, int w, int h) {
		Vec4 pc = mproj * mview * Vec4{ pw };
		Vec3 pn{ pc.x() / pc.w(),pc.y() / pc.w(),pc.z() / pc.w() };
		return Vec3{ (pn.x() + 1) * w / 2,(pn.y() + 1) * h / 2,
			-2 * f * n / (pn.z() * (f - n) - (f + n)) };
	}
	Vec3 GetEye()
	{
		return eye;
	}
private:
	//视图变换矩阵和投影矩阵
	Matrix4 mview, mproj;
	float n, f;
	Vec3 eye;
};