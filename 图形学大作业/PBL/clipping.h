#pragma once
#include <float.h>
#include <vector>
//二维点的坐标
struct point {
	float x;
	float y;
};

//直线段求交
//输入：线段1的起点和终点坐标s1和e1，线段2的起点和终点坐标s2和e2
//输出：交点的坐标xy，交点在线段1和线段2上的参数t1和t2
//根据返回的t1和t2的值可以判断交点是否存在，条件是0<=t1<=1,0<=t2<=1
//如果两线段平行且不重合，交点不存在，返回t1和t2为正无穷
//如果两线段重合，交点有无数个，返回t1和t2为负无穷
//比较浮点数值时需考虑误差
void IntersectLineLine(point s1, point e1, point s2, point e2,
	point xy, float& t1, float& t2) {

}
//用于WA多边形裁剪的循环链表节点
struct Node {
	//两个指针，分别指向多边形和窗口链表中的下一个节点
	Node* next_p, * next_w;
	point v;	//顶点坐标
	//标记是否为入点
	//除了交点外，多边形位于窗口内部的顶点也被标记为入点
	//遇到入点就沿多边形链表遍历，否则沿窗口链表遍历
	bool entering;	
	
	void insert_p(Node* n) {
		Node* next = this->next_p;
		this->next_p = n;
		n->next_p = next;
	}
	void insert_w(Node* n) {
		Node* next = this->next_w;
		this->next_w = n;
		n->next_w = next;
	}
};
//找到一个没有访问过的入点，如果没有则返回空
Node* findUnvisitedEntering(const vector<Node*> plist) {
	for (int i = 0; i < plist.size(); i++) {
		Node* next = plist[i];
		do {
			if (next->entering)
				return next;
			next = next->next_p;
		} while (next != plist[i]);
	}
	return nullptr;
}
//创建多边形的循环链表
//输入：多边形的顶点信息
//输出：多边形和窗口的循环链表
//把多边形位于窗口内部的点标记为入点，其余点标记为出点
//如果多边形和窗口有顶点重合，则需删除多余的重合顶点，并更新保留重合顶点的指针信息
void createList(const vector<vector<point>>& polygon,
				 vector<Node*>& list) {
	//TODO
}
//求多边形和窗口的交点，标记交点的出入状态，并把交点加入两个循环链表
//需要考虑交点与多边形或窗口顶点重合的情况
void intersetAndUpdate(vector<Node*>& plist, vector<Node*>& wlist) {
	//TODO
	//遍历多边形的每条边
	for (int i = 0; i < plist.size(); i++) {
		Node* p_start = plist[i]; //边的起点
		do {
			Node* p_end = p_start->next_p; //边的终点
			//存放交点的列表，交点按其在多边形边上参数从小到大排序
			vector<pair<point,float>> intersections;	//交点列表 			
			//遍历窗口的每条边
			for (int j = 0; j < wlist.size(); j++) {
				Node* w_start = wlist[i];
				do {
					Node* w_end = w_start->next_w;
					point xy{ 0,0 };
					float t1, t2;
					IntersectLineLine(p_start->v, p_end->v,
						w_start->v, w_end->v,
						xy, t1, t2);
					//TODO:判断交点是否存在
					//TODO:如果存在，根据交点的t1参数把交点插入交点列表
					//TODO:把交点插入到w_start和w_end之间
					w_start = w_end;
				} while (w_start != wlist[i]);
			}
			//TODO:确定交点出入状态，并把交点依序插入到p_start和p_end之间
			//由于交点是排好序的，根据p_end的出入状态可判断各交点的出入状态
			p_start = p_end;
		} while (p_start != plist[i]);
	}
}
//遍历已加入交点和标记了出入点的多边形循环链表
//输出裁剪后的多边形
void processVertices(const vector<Node*>& plist, 
					 vector<vector<point>>& output) {
	//找到一个没有访问过的入点
	Node* firstE = findUnvisitedEntering(plist);
	//外层循环，每次循环找到一个环
	while (firstE != nullptr) {
		vector<point>loop;
		Node* next = firstE;
		do {
			loop.push_back(next->v);
			//入点沿多边形遍历
			if (next->entering) {
				//把遍历过的入点的状态改为出点
				next->entering = false;
				next = next->next_p;
				
			}
			//出点沿窗口遍历
			else {
				next = next->next_w;
			}
		} while (next != firstE); //回到起点时结束内层循环
		output.push_back(loop);
		//继续找下一个环的起点
		firstE = findUnvisitedEntering(plist);
	}
}
//输入：窗口多边形和待裁剪多边形
//输出：裁剪后的的多边形
//多边形用一个vector表示，每个元素代表一个环
//多边形的环也用一个vector表示，每个元素代表环的一个顶点，并按顶点的连接顺序排列
void clipPolygon(const vector<vector<point>>& polygon,
	const vector<vector<point>>& window,
	vector<vector<point>>&output) {
	//1.建立多边形和窗口顶点循环链表
	vector<Node*>plist, wlist;
	createList(polygon, plist);
	createList(window, wlist);

	//2.计算多边形和窗口的交点，把交点插入两个链表，并判断交点的出入状态
	intersetAndUpdate(plist, wlist);

	//3.遍历链表，输出多边形顶点
	processVertices(plist, output);
}

//直线段的裁剪
//xmin,ymin：窗口左下角坐标
//xmax,ymax：窗口右上角坐标
//x0,y0：线段起点
//x1,y1：线段终点
//返回：裁剪后的线段端点坐标仍保存在x0,y0,x1,y1中
void clipLine(float xmin, float ymin, float xmax, float ymax,
	float& x0, float& y0, float& x1, float& y1) {
//TODO
}

