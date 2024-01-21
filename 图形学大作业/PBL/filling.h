#pragma once
#include <vector>
#include <algorithm>
#include <iostream>
using namespace std;

//定义边的结构
struct Edge {
	int ymax;
	float x;
	float dx;
	Edge* next;
};
//建立有序边表
//输入：
//polygon：多边形顶点数组
//y_start：et中第0条边的下端点y坐标
//输出：
//et：加入了边结构的有序边表
void createET(const vector<pair<float, float>>& polygon,
	int y_start,
	vector<Edge*>& et) {
	//遍历多边形的每一条边，第i条边的两个顶点是i和i+1。
	for (int i = 0; i < polygon.size(); i++) {
		//找到上下端点的顶点索引
		int low_index = i, up_index = (i + 1) % polygon.size();
		if (polygon[i].second > polygon[(i + 1) % polygon.size()].second) {
			swap(low_index, up_index);
		}
		
		//low_y是下端点的y坐标，这条边应该放在边表的第low_y - ystart行
		int low_y = polygon[low_index].second;
		//边的最大y坐标ymax
		int ymax = polygon[up_index].second;
		//跳过水平边
		if (ymax == low_y)
			continue;

		//计算dx的值
		float dx = (polygon[up_index].first - polygon[low_index].first)
			/ (polygon[up_index].second - polygon[low_index].second);
		//计算x，对于下端点为极值点的边，为下端点的x坐标
		float x = polygon[low_index].first;

		//对于从非极值点向上发出的边，需要做截断处理
		//判断顶点low_index是否是非极值点
		//如果是的话，向上截断一个像素，low_y++。
		//与顶点low_index相邻的另外一条边的另一个顶点的索引
		int adj_index;
		if (low_index == i) {
			adj_index = i == 0 ? polygon.size() - 1 : i - 1;
		}
		else {
			adj_index = (i + 2) % polygon.size();
		}
		if ((polygon[up_index].second - polygon[low_index].second) *
			(polygon[adj_index].second - polygon[low_index].second) < 0) {
			//非极值点，向上截断一个像素
			low_y++;
			x += dx;
		}
		
		Edge* e = new Edge{ ymax,x,dx };
		
		if (et[low_y - y_start] != nullptr) {
			//把e插入到边表中第y-y_start行，按x坐标从小到大排序
			Edge* target = et[low_y - y_start];
			//e的x坐标比第一条边的x坐标还小，作为头节点插入
			if (e->x < target->x || 
				e->x == target->x && e->dx < target->dx) {
				e->next = target;
				et[low_y - y_start] = e;
			}			
			else {//找到第一个比e的x大的节点next，插入到target之后，next之前
				while (target != nullptr) {
					Edge* next = target->next;					
					if (next==nullptr||(next->x > e->x ||
						next->x == e->x && next->dx > e->dx)) {
						e->next = next;
						target->next = e;
						break;	//完成插入任务，跳出循环
					}
					else
						target = next;
				}
			}
		}
		else { //在空行中作为头节点
			et[low_y - y_start] = e;
		}
	}
}
//打印有序边表
void printET(int y_start, const vector<Edge*>& et) {
	for (int i = 0; i < et.size(); i++) {
		if (et[i] != nullptr) {
			cout << "y=" << y_start + i << ":" << endl;
			Edge* e = et[i];
			while (e != nullptr) {
				cout << "{" << e->ymax << ", " << e->x << ", " << e->dx << "}" << endl;
				e = e->next;
			}
			cout << endl;
		}
	}
}
//把new的边释放掉
void clearET(const vector<Edge*>& et) {
	for (int i = 0; i < et.size(); i++) {
		if (et[i] != nullptr) {
			Edge* e = et[i];
			while (e != nullptr) {
				Edge* tmp = e;
				e = e->next;
				delete tmp;
			}
		}
	}
}
//找到多边形顶点的y坐标中的最小值和最大值
void findMinMaxY(const vector<pair<float, float>>& polygon, 
	int& ymin, int& ymax) {
	ymin = ymax = polygon[0].second;
	for (int i = 1; i < polygon.size(); i++) {
		if (polygon[i].second < ymin)
			ymin = polygon[i].second;
		if (polygon[i].second > ymax)
			ymax = polygon[i].second;
	}
}
//扫描线填充多边形
void fillPolygon(const vector<pair<float, float>>& polygon) {	
	int ymin, ymax;
	findMinMaxY(polygon,ymin,ymax); //计算多边形顶点的最小和最大y坐标
	vector<Edge*> et(ymax - ymin + 1);//et的大小跟多边形的y坐标跨度一样

	//1. 创建边表
	createET(polygon, ymin, et);
	printET(ymin, et);

	//2. 初始化活性边表
	Edge* aet = nullptr;
	int y = ymin;
	//从ymin开始遍历每条扫描线，直到活性边表为空
	do {
		//1.TODO:加入新边
		if (et[y - ymin] != nullptr) {

		}
		//2.TODO:配对填充
		//3.TODO:移除已处理完的边
		//4.TODO:更新aet中各边的x坐标
		y++;
	} while (aet != nullptr);
	//释放动态内存
	clearET(et);
}
//测试函数
void testFilling() {
	//定义多边形
	vector<pair<float, float>> polygon = { {2,1},{1,7},{8,5},{7,1},{6,4} };
	fillPolygon(polygon);
}
