#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
using namespace std;
#define COST_NUM 4
#define MONTH_NUM 12

int minCost, currCost;
int cost[COST_NUM]; // 1�� 1�� 3�� 1��
int inter[COST_NUM] = { 0, 1, 3, 12 };
int days[MONTH_NUM];

// �� ���̽��� ������ �ʱ�ȭ
void init() {
	// 1����� 1�� 1�� ��ϸ� ����
	minCost = cost[COST_NUM - 1];
	currCost = 0;
}

void dfs(int lev) {
	if (lev >= 12) { // 12������ Ž�� �Ϸ��
		if (currCost < minCost) { // �ּ� ��� �߰� ���� Ȯ��
			minCost = currCost; // �ּ� ��� ����
		}
		return;
	}

	// �ݹ��� Ž���� �� �̿��ϼ��� 0���� ���, �ٷ� ������ Ž�� �� return;
	if (days[lev] == 0) {
		dfs(lev + 1);
		return;
	}

	// 3�����Ǻ��� Ž��
	for (int i = COST_NUM - 2; i >= 0; i--) {
		// i == 0 : �ش� ���� 1�ϱ� �̿�
		int currC = i == 0 ? cost[i] * days[lev] : cost[i];
		int currM = i == 0 ? 1 : inter[i]; // int inter[COST_NUM] = { 0, 1, 3, 12 };

		// �̹� ��� �߰�
		currCost += currC;

		// ��� ���� ���� �� Ž��
		dfs(lev + currM);

		// ��� ����
		currCost -= currC;
	}
}

int main() {
	freopen("input1952.txt", "r", stdin);

	int T;
	cin >> T;
	for (int tc = 1; tc <= T; tc++) {
		// 1. �Է�
		for (int i = 0; i < COST_NUM; i++) {
			cin >> cost[i];
		}

		for (int i = 0; i < MONTH_NUM; i++) {
			cin >> days[i];
		}

		// 2. �ʱ�ȭ
		init();

		// 3. ���� - 1������ Ž�� ����
		dfs(0);

		// 4. ���
		cout << "#" << tc << " " << minCost << '\n';
	}

	return 0;
}

/*
1
10 40 100 300
0 0 2 9 1 5 0 0 0 0 0 0
*/