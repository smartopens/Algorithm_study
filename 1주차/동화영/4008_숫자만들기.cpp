#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
using namespace std;
#define max_n 12

int nums[max_n]; // ���ڵ�
int oper[4]; // + - * / ����
int visited[4]; // �� ��ȣ���� ��� Ƚ��
int n; // �Է¹޴� ������ ����

int sum; // ������ �����
int maxans, minans; // �ִ�, �ּҰ�

void dfs(int lev) {
	if (lev == n - 1) { // n-1���� ��ȣ�� ��� Ž����
		// �ִ�, �ּҰ� ����
		if (sum > maxans) maxans = sum;
		if (sum < minans) minans = sum;

		return;
	}

	for (int i = 0; i < 4; i++) {
		// �̹� ������ ��ȣ�� ��� �Ұ�
		if (visited[i] >= oper[i]) continue;

		int tmp = sum;

		sum = i == 0 ? sum + nums[lev + 1] : i == 1 ? sum - nums[lev + 1] : i == 2 ? sum * nums[lev + 1] : sum / nums[lev + 1]; // �ݹ��� ��ȣ ������� ���� ���
		visited[i]++; // ��ȣ ��� ǥ��
		
		dfs(lev + 1); // ���� ��ȣ ã���� ����

		// ����
		visited[i]--;
		sum = tmp;
	}

}

int main() {
	freopen("input4008.txt", "r", stdin);

	int t;
	cin >> t;

	for (int tc = 1; tc <= t; tc++) {
		// �Է�
		cin >> n;
		for (int i = 0; i < 4; i++) {
			cin >> oper[i];
		}
		for (int i = 0; i < n; i++) {
			cin >> nums[i];
		}
		
		// �ʱ�ȭ
		maxans = -21e8;
		minans = 21e8;
		sum = nums[0]; // ù��° ���ڷ� �ʱ�ȭ
		
		// ����
		dfs(0);

		// ���
		cout << "#" << tc << " " << (maxans - minans) << "\n";
	}

	return 0;
}

/*
2
5
2 1 0 1
3 5 3 7 9
6
4 1 0 0
1 2 3 4 5 6
*/