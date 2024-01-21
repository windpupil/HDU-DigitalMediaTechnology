#pragma once
#include "matrix.h"
#include "camera.h"
//给定三角形三个顶点A、B、C的坐标，计算一点p的重心坐标
Vec baryCentri(const Vec& A, const Vec& B, const Vec& C, const Vec& p)
{
	float x = p.x(), y = p.y(), z = p.z();
	float xA = A.x(), yA = A.y(), zA = A.z();
	float xB = B.x(), yB = B.y(), zB = B.z();
	float xC = C.x(), yC = C.y(), zC = C.z();

	float a, b;
	a = (-(x - xB) * (yC - yB) + (y - yB) * (xC - xB)) /
		(-(xA - xB) * (yC - yB) + (yA - yB) * (xC - xB));
	b = (-(x - xC) * (yA - yC) + (y - yC) * (xA - xC))
		/ (-(xB - xC) * (yA - yC) + (yB - yC) * (xA - xC));

	return Vec{ a,b,1 - a - b };
}

