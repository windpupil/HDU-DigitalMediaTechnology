#pragma once
#include <vector>
#include <algorithm>
#include <iostream>
using namespace std;

//����ߵĽṹ
struct Edge {
	int ymax;
	float x;
	float dx;
	Edge* next;
};
//��������߱�
//���룺
//polygon������ζ�������
//y_start��et�е�0���ߵ��¶˵�y����
//�����
//et�������˱߽ṹ������߱�
void createET(const vector<pair<float, float>>& polygon,
	int y_start,
	vector<Edge*>& et) {
	//��������ε�ÿһ���ߣ���i���ߵ�����������i��i+1��
	for (int i = 0; i < polygon.size(); i++) {
		//�ҵ����¶˵�Ķ�������
		int low_index = i, up_index = (i + 1) % polygon.size();
		if (polygon[i].second > polygon[(i + 1) % polygon.size()].second) {
			swap(low_index, up_index);
		}
		
		//low_y���¶˵��y���꣬������Ӧ�÷��ڱ߱�ĵ�low_y - ystart��
		int low_y = polygon[low_index].second;
		//�ߵ����y����ymax
		int ymax = polygon[up_index].second;
		//����ˮƽ��
		if (ymax == low_y)
			continue;

		//����dx��ֵ
		float dx = (polygon[up_index].first - polygon[low_index].first)
			/ (polygon[up_index].second - polygon[low_index].second);
		//����x�������¶˵�Ϊ��ֵ��ıߣ�Ϊ�¶˵��x����
		float x = polygon[low_index].first;

		//���ڴӷǼ�ֵ�����Ϸ����ıߣ���Ҫ���ضϴ���
		//�ж϶���low_index�Ƿ��ǷǼ�ֵ��
		//����ǵĻ������Ͻض�һ�����أ�low_y++��
		//�붥��low_index���ڵ�����һ���ߵ���һ�����������
		int adj_index;
		if (low_index == i) {
			adj_index = i == 0 ? polygon.size() - 1 : i - 1;
		}
		else {
			adj_index = (i + 2) % polygon.size();
		}
		if ((polygon[up_index].second - polygon[low_index].second) *
			(polygon[adj_index].second - polygon[low_index].second) < 0) {
			//�Ǽ�ֵ�㣬���Ͻض�һ������
			low_y++;
			x += dx;
		}
		
		Edge* e = new Edge{ ymax,x,dx };
		
		if (et[low_y - y_start] != nullptr) {
			//��e���뵽�߱��е�y-y_start�У���x�����С��������
			Edge* target = et[low_y - y_start];
			//e��x����ȵ�һ���ߵ�x���껹С����Ϊͷ�ڵ����
			if (e->x < target->x || 
				e->x == target->x && e->dx < target->dx) {
				e->next = target;
				et[low_y - y_start] = e;
			}			
			else {//�ҵ���һ����e��x��Ľڵ�next�����뵽target֮��next֮ǰ
				while (target != nullptr) {
					Edge* next = target->next;					
					if (next==nullptr||(next->x > e->x ||
						next->x == e->x && next->dx > e->dx)) {
						e->next = next;
						target->next = e;
						break;	//��ɲ�����������ѭ��
					}
					else
						target = next;
				}
			}
		}
		else { //�ڿ�������Ϊͷ�ڵ�
			et[low_y - y_start] = e;
		}
	}
}
//��ӡ����߱�
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
//��new�ı��ͷŵ�
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
//�ҵ�����ζ����y�����е���Сֵ�����ֵ
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
//ɨ�����������
void fillPolygon(const vector<pair<float, float>>& polygon) {	
	int ymin, ymax;
	findMinMaxY(polygon,ymin,ymax); //�������ζ������С�����y����
	vector<Edge*> et(ymax - ymin + 1);//et�Ĵ�С������ε�y������һ��

	//1. �����߱�
	createET(polygon, ymin, et);
	printET(ymin, et);

	//2. ��ʼ�����Ա߱�
	Edge* aet = nullptr;
	int y = ymin;
	//��ymin��ʼ����ÿ��ɨ���ߣ�ֱ�����Ա߱�Ϊ��
	do {
		//1.TODO:�����±�
		if (et[y - ymin] != nullptr) {

		}
		//2.TODO:������
		//3.TODO:�Ƴ��Ѵ�����ı�
		//4.TODO:����aet�и��ߵ�x����
		y++;
	} while (aet != nullptr);
	//�ͷŶ�̬�ڴ�
	clearET(et);
}
//���Ժ���
void testFilling() {
	//��������
	vector<pair<float, float>> polygon = { {2,1},{1,7},{8,5},{7,1},{6,4} };
	fillPolygon(polygon);
}
