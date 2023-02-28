#include <iostream>
#include <cstring>
using namespace std;

// 1,3���� ������
// 2,4���� ������
int map[5][8];
int ptr[5];
int point[5] = { 0, 1, 2, 4, 8 };

void move(int num, int dir) {
	int issame[3] = { 0, }; // �� �ڼ� ������ �ؼ��� ������?
	for (int i = 0; i < 3; i++) {
		int left = map[i + 1][(ptr[i + 1] + 2) % 8]; // i�� ��ġ���� ����
		int right = map[i + 2][(ptr[i + 2] + 6) % 8]; // i�� ��ġ���� ������

		if (left == right) issame[i] = 1; // �ؼ��� ���ٸ� ǥ��
	}

	// ���� �ڼ� ȸ����Ű��
	ptr[num] = (ptr[num] - dir + 8) % 8;

	// ������ �ڼ��� ȸ����Ű��
	for (int i = num + 1; i <= 4; i++) {
		if (issame[i - 2] == 1) break; // ���� �ڼ��̶�� ���̻� ȸ�� x

		// �ٸ� �ڼ�
		// ���� �ڼ��� �����̸� ���� �������� ȸ��
		// ���� �ڼ��� ���̸� ���� �������� ȸ��
		int tmp = 0;
		if (num % 2 == i % 2) tmp = dir;
		else tmp = -dir;

		ptr[i] = (ptr[i] - tmp + 8) % 8;
	}

	// ���� �ڼ��� ȸ����Ű��
	for (int i = num - 1; i >= 1; i--) {
		if (issame[i - 1] == 1) break; // ���� �ڼ��̶�� ���̻� ȸ�� x

		int tmp = 0;
		if (num % 2 == i % 2) tmp = dir;
		else tmp = -dir;

		ptr[i] = (ptr[i] - tmp + 8) % 8;
	}
}

int main() {
	int t;
	cin >> t;

	int k;
	for (int tc = 1; tc <= t; tc++) {
		// �ʱ�ȭ
		memset(ptr, 0, sizeof(ptr));

		// �Է�
		cin >> k;

		for (int i = 1; i <= 4; i++) {
			for (int j = 0; j < 8; j++) {
				cin >> map[i][j];
			}
		}

		// 1. 1ĭ�� k�� �̵�
		int num, dir;

		for (int i = 0; i < k; i++) {
			cin >> num >> dir;

			move(num, dir);
		}

		// 2. ���� ���� �ջ�
		int ans = 0;
		for (int i = 1; i <= 4; i++) {
			// �� �ڼ��� �����Ϳ� �ִ� �ؼ��� �������� ���� ���ϱ�
			// n�� - 0��, s�� - 1,2,4,8��
			ans += map[i][ptr[i]] == 0 ? 0 : point[i];
		}

		cout << "#" << tc << " " << ans << '\n';
	}

	return 0;
}
