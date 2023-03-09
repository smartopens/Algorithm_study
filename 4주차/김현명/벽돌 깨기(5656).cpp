#define _CRT_SECURE_NO_WARNINGS

#include <queue>
#include <cstring>
#include <iostream>

using namespace std;

// �⺻ ������ ����
int n;
int w, h;
int board[15][15];
int tmp_board[15][15];

int visited[15][15];
vector<int> dolls;

int dr[4] = { -1,1,0,0 };
int dc[4] = { 0,0,-1,1 };

// ���� ���� ����: total_num - max_bum
// ������ ������ ���: is_maxȰ���� Ž���� ������
int max_b_num = 0;
int total_num = 0;
bool is_max = false;

struct node {
	int r;
	int c;
};

void move(int r, int c) {
	int nr = r+1;
	int nc = c;

	// ���������� Ž���ϱ�
	while (nr + 1 < h) {
		if (board[nr][nc] != 0) break;
		nr += 1;
	}

	// ������ �����̰� ����� 0�� ���
	if (nr == h-1 && board[nr][nc] == 0) {
		board[nr][nc] = board[r][c];
	}
	// ��Ͽ� ������ ���
	else if (board[nr][nc] != 0) {
		board[nr-1][nc] = board[r][c];
	}

	board[r][c] = 0;
}

void gravity() {
	// �Ʒ����� ������ Ž���ϱ�
	// �������� �������� ���δ�.
	for (int r = h - 2; r > -1; r--) {
		for (int c = 0; c < w; c++) {
			if (board[r][c] > 0 && board[r + 1][c] == 0) {
				move(r, c);
			}
		}
	}

}

int put_dolls(int sc) {
	// ���� ��ĭ���� ������ ��߽�Ų��.
	int sr = 0;
	int b_num = 0;

	// �� ���������� ������ Ž���Ѵ�.
	while (sr + 1 < h){
		if (board[sr][sc] != 0) break;
		sr += 1;
	}

	// ������ ������ ������ ���
	// ������ ������ ���ٸ� Ž���� �ʿ䰡 ����.
	if (sr == h-1 && board[sr][sc] == 0) return 0;

	memset(visited, 0, sizeof(visited));
	
	// �� �� �ִ� ���� ������ Ž���Ѵ�.
	queue<node> q = {};
	q.push({ sr,sc });

	while (!q.empty()) {
		node now = q.front();
		q.pop();

		int r, c;
		r = now.r;
		c = now.c;

		int k = board[r][c];
		visited[r][c] = 1;


		// k-1 �Ÿ���ŭ Ž���Ѵ�.
		for (int ki = 1; ki < k; ki++) {
			for (int i = 0; i < 4; i++) {
				int nr, nc;
				nr = r + dr[i] * ki;
				nc = c + dc[i] * ki;

				if (0 > nr || h <= nr || 0 > nc || w <= nc) continue;
				if (visited[nr][nc] != 0) continue;
				if (board[nr][nc] == 0) continue;

				q.push({ nr,nc });
			}
		}
	}

	// ������ ����, �� ���� ���� �����Ѵ�.
	for (int r = 0; r < h; r++) {
		for (int c = 0; c < w; c++) {
			if (visited[r][c] == 0) continue;

			board[r][c] = 0;
			b_num += 1;
		}
	}

	// ������ �߷� �ۿ��ϱ�
	gravity();

	return b_num;
}

void dfs(int a) {
	// ��� �������� �� �� �ִ� ���
	// �� �ĺ��� �� �� �ʿ䰡 ����.
	if (is_max) {
		return;
	}
	// ����� �� �ϼ�
	if (a >= n) {
		int total_b_num = 0;

		// ������ ������ ���
		// ���� �� �ִ� ���� ���� ����
		for (int i = 0; i < dolls.size(); i++) {
			total_b_num += put_dolls(dolls[i]);
		}

		// ���� ������ �����ϱ�
		for (int r = 0; r < h; r++) {
			for (int c = 0; c < w; c++) {
				board[r][c] = tmp_board[r][c];
			}
		}

		// �ִ� �������� ���� ���� �����ϱ�
		if (total_b_num > max_b_num) {
			max_b_num = total_b_num;

			if (max_b_num == total_num) {
				is_max = true;
			}
		}
		return;
	}


	// ������ ����߸��� ����� �� Ž��
	// ������ ����Ѵ�.
	for (int i = 0; i < w; i++) {
		dolls.push_back(i);
		dfs(a + 1);
		dolls.pop_back();
	}
}

int main() {
	int t = 0;
	cin >> t;

	for (int ti = 0; ti < t; ti++) {
		cin >> n >> w >> h;

		// �ʱ�ȭ
		max_b_num = 0;
		total_num = 0;
		is_max = false;

		// ������ ���� �Է�
		// ���� ������ ���� ����
		for (int r = 0; r < h; r++) {
			for (int c = 0; c < w; c++) {
				cin >> board[r][c];
				tmp_board[r][c] = board[r][c];

				if (board[r][c] > 0) {
					total_num += 1;
				}

			}
		}

		dfs(0);

		cout << "#" << ti + 1 << " " << total_num - max_b_num << endl;
	}

	return 0;
}