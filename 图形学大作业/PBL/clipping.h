#pragma once
#include <float.h>
#include <vector>
//��ά�������
struct point {
	float x;
	float y;
};

//ֱ�߶���
//���룺�߶�1�������յ�����s1��e1���߶�2�������յ�����s2��e2
//��������������xy���������߶�1���߶�2�ϵĲ���t1��t2
//���ݷ��ص�t1��t2��ֵ�����жϽ����Ƿ���ڣ�������0<=t1<=1,0<=t2<=1
//������߶�ƽ���Ҳ��غϣ����㲻���ڣ�����t1��t2Ϊ������
//������߶��غϣ�������������������t1��t2Ϊ������
//�Ƚϸ�����ֵʱ�迼�����
void IntersectLineLine(point s1, point e1, point s2, point e2,
	point xy, float& t1, float& t2) {

}
//����WA����βü���ѭ������ڵ�
struct Node {
	//����ָ�룬�ֱ�ָ�����κʹ��������е���һ���ڵ�
	Node* next_p, * next_w;
	point v;	//��������
	//����Ƿ�Ϊ���
	//���˽����⣬�����λ�ڴ����ڲ��Ķ���Ҳ�����Ϊ���
	//���������ض������������������ش����������
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
//�ҵ�һ��û�з��ʹ�����㣬���û���򷵻ؿ�
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
//��������ε�ѭ������
//���룺����εĶ�����Ϣ
//���������κʹ��ڵ�ѭ������
//�Ѷ����λ�ڴ����ڲ��ĵ���Ϊ��㣬�������Ϊ����
//�������κʹ����ж����غϣ�����ɾ��������غ϶��㣬�����±����غ϶����ָ����Ϣ
void createList(const vector<vector<point>>& polygon,
				 vector<Node*>& list) {
	//TODO
}
//�����κʹ��ڵĽ��㣬��ǽ���ĳ���״̬�����ѽ����������ѭ������
//��Ҫ���ǽ��������λ򴰿ڶ����غϵ����
void intersetAndUpdate(vector<Node*>& plist, vector<Node*>& wlist) {
	//TODO
	//��������ε�ÿ����
	for (int i = 0; i < plist.size(); i++) {
		Node* p_start = plist[i]; //�ߵ����
		do {
			Node* p_end = p_start->next_p; //�ߵ��յ�
			//��Ž�����б����㰴���ڶ���α��ϲ�����С��������
			vector<pair<point,float>> intersections;	//�����б� 			
			//�������ڵ�ÿ����
			for (int j = 0; j < wlist.size(); j++) {
				Node* w_start = wlist[i];
				do {
					Node* w_end = w_start->next_w;
					point xy{ 0,0 };
					float t1, t2;
					IntersectLineLine(p_start->v, p_end->v,
						w_start->v, w_end->v,
						xy, t1, t2);
					//TODO:�жϽ����Ƿ����
					//TODO:������ڣ����ݽ����t1�����ѽ�����뽻���б�
					//TODO:�ѽ�����뵽w_start��w_end֮��
					w_start = w_end;
				} while (w_start != wlist[i]);
			}
			//TODO:ȷ���������״̬�����ѽ���������뵽p_start��p_end֮��
			//���ڽ������ź���ģ�����p_end�ĳ���״̬���жϸ�����ĳ���״̬
			p_start = p_end;
		} while (p_start != plist[i]);
	}
}
//�����Ѽ��뽻��ͱ���˳����Ķ����ѭ������
//����ü���Ķ����
void processVertices(const vector<Node*>& plist, 
					 vector<vector<point>>& output) {
	//�ҵ�һ��û�з��ʹ������
	Node* firstE = findUnvisitedEntering(plist);
	//���ѭ����ÿ��ѭ���ҵ�һ����
	while (firstE != nullptr) {
		vector<point>loop;
		Node* next = firstE;
		do {
			loop.push_back(next->v);
			//����ض���α���
			if (next->entering) {
				//�ѱ�����������״̬��Ϊ����
				next->entering = false;
				next = next->next_p;
				
			}
			//�����ش��ڱ���
			else {
				next = next->next_w;
			}
		} while (next != firstE); //�ص����ʱ�����ڲ�ѭ��
		output.push_back(loop);
		//��������һ���������
		firstE = findUnvisitedEntering(plist);
	}
}
//���룺���ڶ���κʹ��ü������
//������ü���ĵĶ����
//�������һ��vector��ʾ��ÿ��Ԫ�ش���һ����
//����εĻ�Ҳ��һ��vector��ʾ��ÿ��Ԫ�ش�����һ�����㣬�������������˳������
void clipPolygon(const vector<vector<point>>& polygon,
	const vector<vector<point>>& window,
	vector<vector<point>>&output) {
	//1.��������κʹ��ڶ���ѭ������
	vector<Node*>plist, wlist;
	createList(polygon, plist);
	createList(window, wlist);

	//2.�������κʹ��ڵĽ��㣬�ѽ�����������������жϽ���ĳ���״̬
	intersetAndUpdate(plist, wlist);

	//3.���������������ζ���
	processVertices(plist, output);
}

//ֱ�߶εĲü�
//xmin,ymin���������½�����
//xmax,ymax���������Ͻ�����
//x0,y0���߶����
//x1,y1���߶��յ�
//���أ��ü�����߶ζ˵������Ա�����x0,y0,x1,y1��
void clipLine(float xmin, float ymin, float xmax, float ymax,
	float& x0, float& y0, float& x1, float& y1) {
//TODO
}

