#include <iostream>
#include <algorithm>
using namespace std;

struct Node {
	int y;
	int x;
};

Node subway[4]; // ����ö�� 4���� ������ (����, ����, ���, �»�)

int findY(Node st, int xInd) {
	int retY = 0;
	if (st.y > subway[3].y) { // ����ö���� ���� ��
		retY = abs(st.y - subway[3].y);
	}
	else if (st.y < subway[0].y) { // ����ö���� �Ʒ��� ��
		retY = abs(st.y - subway[0].y);
	}
	else { // ����ö y�� ����
		retY = 0;
	}
	return retY;
}

// st: ���� Ȥ�� ������
// st�� ����ö���� �Ÿ� ���ϱ�
int findDist(Node st) {
	int ret = 0;

	if (st.x < subway[3].x) { // ����ö���� ���� ��
		ret = abs(st.x - subway[3].x) + findY(st, 0);
		
	}
	else if (st.x > subway[2].x) { // ����ö���� ������ ��
		ret = abs(st.x - subway[2].x) + findY(st, 2);
	}
	else { // ����ö x�� ����
		ret = 0 + findY(st, 1);

		// ����ö �뼱�� ���� �ִ� ��� (4������� �Ÿ� �� �ּ�)
		if (ret == 0) {
			int tmp1 = min(abs(st.x - subway[3].x), abs(st.x - subway[2].x));
			int tmp2 = min(abs(st.y - subway[3].y), abs(st.y - subway[0].y));
			ret = min(tmp1, tmp2);
		}
	}

	return ret;
}

int main() {
	Node coco; // ������ �ʱ� ��ġ
	Node dest; // �������� ��ġ

	cin >> coco.x >> coco.y
		>> dest.x >> dest.y;

	for (int i = 0; i < 4; i++) {
		cin >> subway[i].x >> subway[i].y;
	}

	// 1. ����ö �̿� ���� ������ �̵��� �Ÿ� -> �ʱⰪ
	int dist = abs(coco.y - dest.y) + abs(coco.x - dest.x);

	// 2. ����ö �̿��Ͽ� �ɸ��� ���� �Ÿ�
	int cocoD = findDist(coco);
	int destD = findDist(dest);
	dist = min(dist, cocoD + destD); // 1�� 2 �� ���� ��

	cout << dist << '\n';

	return 0;
}