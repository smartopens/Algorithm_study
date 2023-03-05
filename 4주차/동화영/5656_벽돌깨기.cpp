#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstring>
#include <queue>
using namespace std;
#define MAX_WH 20
#define DIR_NUM 4

struct Node {
	int y;
	int x;
};

int ydir[DIR_NUM] = { -1, 1, 0, 0 }; // �����¿�
int xdir[DIR_NUM] = { 0, 0, -1, 1 };

int MAP[MAX_WH][MAX_WH];
int N; // ���� ��� Ƚ��
int H, W; // ������ ������ H*W

int brick; // ������ �� ����
int curCnt; // �� ���� ���� ����
int ans; // ���� ������ ��

bool InRange(int y, int x) {
	return y >= 0 && x >= 0 && y < H && x < W;
}

void breakBrick(int ind) {
	// ������ ã�� - ���������� ���� ���� ã�� ������ ��ġ
	Node start = { 0,0 };
	for (int i = 0; i < H; i++) {
		if (MAP[i][ind] != 0) {
			start = { i, ind };
			break;
		}
	}

	queue<Node> q;
	q.push(start);

	// �� �� �ִ� ��� ���� ���� => MAP�� ���� 0���� ǥ��
	while (!q.empty()) {
		Node now = q.front();
		q.pop();

		int num = MAP[now.y][now.x];

		if (num == 0) continue; // �̹� ���� ���̶�� ����

		// ���� ���߸���
		MAP[now.y][now.x] = 0;
		curCnt--;

		// �ش� �����κ��� ����޴� ������ queue�� �־��ֱ�
		for (int i = 0; i < DIR_NUM; i++) {
			for (int j = 1; j < num; j++) {
				int ny = now.y + ydir[i] * j;
				int nx = now.x + xdir[i] * j;

				if (!InRange(ny, nx)) continue;
				if (MAP[ny][nx] == 0) continue;

				q.push({ ny, nx });
			}
		}
	}
}

// ������ �Ʒ��� �������
void cleanBrick() {
	queue<int> q; // ������ �ִ� ĭ�� ���ڵ�

	for (int i = 0; i < W; i++) { // �� ���� ����
		for (int j = H - 1; j >= 0; j--) { // �Ʒ���������
			if (MAP[j][i] != 0) { // ������ �ִٸ�
				q.push(MAP[j][i]); // queue�� �ֱ�
				MAP[j][i] = 0; // �ش� ĭ�� ���� 0���� ����
			}
		}

		int ind = H - 1; // �� �Ʒ� �����
		while (!q.empty()) {
			MAP[ind][i] = q.front(); // ������ �־��ֱ�
			q.pop();
			ind--; // index ���� �Ű��ֱ�
		}
	}
}

// lev��° ������ ���� �� ã��
void selectLine(int lev) {
	// N�� ������ �����ٸ� ����
	if (lev == N) {
		if (curCnt < ans) {
			ans = curCnt;
		}

		return;
	}

	// ��ü �� �� ����
	for (int i = 0; i < W; i++) {
		if (MAP[H - 1][i] == 0) continue; // �̹� �� ���� ���� ����

		// ������ MAP �����صα�
		int tmp[MAX_WH][MAX_WH] = { 0, };
		memcpy(tmp, MAP, sizeof(MAP));
		// ������ ���� ������ ���� �����صα�
		int tmpCnt = curCnt;

		breakBrick(i); // �� �� �ִ� ���� ��� ���� => bfs
		cleanBrick(); // ���� �Ʒ��� �������

		// lev��° ������ ��Ҵ��� ���� ������ ���ٸ�
		if (curCnt == 0) {
			ans = 0;
			return;
		}

		selectLine(lev + 1); // ���� ���� ��� ������ ã���� ����

		// ����
		memcpy(MAP, tmp, sizeof(tmp));
		curCnt = tmpCnt;
	}
}

int main() {
	freopen("input5656.txt", "r", stdin);
	int T;
	cin >> T;

	for (int tc = 1; tc <= T; tc++) {
		// reset
		ans = 21e8;
		brick = 0;
		curCnt = 0;

		// input
		cin >> N >> W >> H;

		for (int i = 0; i < H; i++) {
			for (int j = 0; j < W; j++) {
				cin >> MAP[i][j];

				if (MAP[i][j] != 0) brick++; // ���� ���� ����
			}
		}

		// solve
		curCnt = brick;
		selectLine(0);

		// output
		cout << "#" << tc << " " << ans << '\n';
	}

	return 0;
}

/*
2
3 10 10
0 0 0 0 0 0 0 0 0 0
1 0 1 0 1 0 0 0 0 0
1 0 3 0 1 1 0 0 0 1
1 1 1 0 1 2 0 0 0 9
1 1 4 0 1 1 0 0 1 1
1 1 4 1 1 1 2 1 1 1
1 1 5 1 1 1 1 2 1 1
1 1 6 1 1 1 1 1 2 1
1 1 1 1 1 1 1 1 1 5
1 1 7 1 1 1 1 1 1 1
2 9 10
0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0 0
0 1 0 0 0 0 0 0 0
0 1 0 0 0 0 0 0 0
1 1 0 0 1 0 0 0 0
1 1 0 1 1 1 0 1 0
1 1 0 1 1 1 0 1 0
1 1 1 1 1 1 1 1 0
1 1 3 1 6 1 1 1 1
1 1 1 1 1 1 1 1 1
*/

/*
1
4 12 15 
9 9 9 9 9 9 9 9 9 9 9 9	 
9 9 9 9 9 9 9 9 9 9 9 9	 
9 9 9 9 9 9 9 9 9 9 9 9	 
9 9 9 9 9 9 9 9 9 9 9 9	 
9 9 9 9 9 9 9 9 9 9 9 9	 
9 9 9 9 9 9 9 9 9 9 9 9	 
9 9 9 9 9 9 9 9 9 9 9 9	 
9 9 9 9 9 9 9 9 9 9 9 9	 
9 9 9 9 9 9 9 9 9 9 9 9	 
9 9 9 9 9 9 9 9 9 9 9 9	 
9 9 9 9 9 9 9 9 9 9 9 9	 
9 9 9 9 9 9 9 9 9 9 9 9	 
9 9 9 9 9 9 9 9 9 9 9 9	 
9 9 9 9 9 9 9 9 9 9 9 9	 
9 9 9 9 9 9 9 9 9 9 9 9	 
*/