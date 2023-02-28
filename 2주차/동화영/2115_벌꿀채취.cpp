// 1. ���� �� ��ġ���� �����ϸ� ���� ä�밡 �Ǵ��� ����
// 2. 1���� ���� ���鼭(M��ŭ ��ġ�� �ʰ�) �ּ��� ������ Ž��
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;
#define MAX_N 10

int MAP[MAX_N][MAX_N];

int picked[MAX_N][MAX_N]; // �� ������ �������� M��ŭ�� �������� ä���� �� �ִ� ���� �ִ� ����
vector<int> myV; // picked�� Ž���ϱ� ���� ��ǥ�� ���� ���
int vMax; // dfs���� ���� �ִ�

int N, M, C; // N: ������, M: �ѹ��� ä�����, C: ����� ��

void dfs(int pInd, int sum, int profit) {
	if (profit > vMax) {
		vMax = profit;
	}

	if (pInd == M) {
		return;
	}

	for (int i = pInd; i < M; i++) {
		int nSum = sum + myV[i];

		if (nSum > C) continue; // vector�� ���ĵ� �����̹Ƿ� ���̻� Ž�� �Ұ�

		dfs(i + 1, nSum, profit + myV[i] * myV[i]);
	}
}

// ��ǥ �� ��� ������������ M��ŭ�� ������ ä���Ѵٰ� ����
// �� �� ������ ���� �ִ� ����
void pickMAP() {
	int maxH = 0;
	for (int i = 0; i < N; i++) { // �� ��
		for (int j = 0; j <= N - M; j++) { // �� �࿡�� ������ ���� ����(��)
			myV.clear();

			for (int k = 0; k < M; k++) {
				myV.push_back(MAP[i][j + k]);
			}

			sort(myV.begin(), myV.end(), greater<int>());

			vMax = 0;
			dfs(0, 0, 0);

			picked[i][j] = vMax;

		}
	}
}

int findMore(int y, int x) {
	int tmpMax = 0;
	for (int i = x + M; i <= N - M; i++) {
		if (picked[y][i] > tmpMax) tmpMax = picked[y][i];
	}

	for (int i = y + 1; i < N; i++) {
		for (int j = 0; j <= N - M; j++) {
			if (picked[i][j] > tmpMax) tmpMax = picked[i][j];
		}
	}

	return tmpMax;
}

int main() {
	//freopen("input2115.txt", "r", stdin);

	int T;
	cin >> T;
	for (int tc = 1; tc <= T; tc++) {
		cin >> N >> M >> C;

		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++) {
				cin >> MAP[i][j];
			}
		}

		pickMAP();

		int maxHoney = 0;
		for (int i = 0; i < N; i++) {
			for (int j = 0; j <= N - M; j++) {
				int honey = findMore(i, j) + picked[i][j];
				if (honey > maxHoney) maxHoney = honey;
			}
		}

		cout << "#" << tc << " " << maxHoney << '\n';
	}

	return 0;
}
