#include <iostream>
#include <cstring>
#include <vector>
using namespace std;
#define MAX_N 12
#define DIR_NUM 4

// �־��� CORE�� ��ǥ
struct CORE {
	int y;
	int x;
};

vector<CORE> cores;
int MAP[MAX_N][MAX_N];
int ydir[DIR_NUM] = { -1, 1, 0, 0 }; // �����¿�
int xdir[DIR_NUM] = { 0, 0, -1, 1 };
int N;

int connected; // ����� �ھ��� ��
int minLine; // ���� ������ �ּҰ�

int InRange(int y, int x) {
	if (y < 0 || x < 0 || y >= N || x >= N) return 0; // MAP�� �ٱ�
	else if (y == 0 || x == 0 || y == N - 1 || x == N - 1) return 1; // MAP�� �����ڸ�
	else return 2; // MAP�� ����
}

// ind��°�� CORE�� i�������� ���� �����Ѱ�?
// �����ϴٸ� ���̰� ���ΰ�?
int canConn(int ind, int dir) {
	CORE curr = cores[ind];

	int lines = 0;
	for (int i = 1; i < N; i++) {
		int ny = curr.y + ydir[dir] * i;
		int nx = curr.x + xdir[dir] * i;

		int flag = InRange(ny, nx);
		if (flag == 2 || flag == 1) {
			if (MAP[ny][nx] == 0) {
				lines++; // �� ���� ����
			}
			else {
				return -1; // MAP �����̳� �ش� ĭ�� core, line ���� �� ��ġ �Ұ�
			}
		}
		else { // ������ ���� �����ϴٰ� MAP �ܺθ� ����
			break;
		}
	}

	return lines; // lines ���̸�ŭ ���� �����ϴٰ� ���� �Ϸ�
}

// cores�� ind��° Ž���Ϸ� �Դ�
void dfs(int ind, int currCon, int currLine) {
	if (ind == cores.size()) {
		if (connected < currCon) {
			connected = currCon;
			minLine = currLine;
		}
		if (connected == currCon && minLine > currLine) {
			minLine = currLine;
		}

		return;
	}

	CORE curr = cores[ind];
	for (int i = 0; i < DIR_NUM; i++) {
		int len = canConn(ind, i); // ind��°�� CORE�� i�������� ���� �����Ѱ�?
		if (len <= 0) continue;

		int tmpMAP[MAX_N][MAX_N];
		memcpy(tmpMAP, MAP, sizeof(MAP));

		// �� ������ �����ϴٰ� ���� �Ϸ� -> �� �����ϱ�
		for (int j = 1; j <= len; j++) {
			int ny = curr.y + ydir[i] * j;
			int nx = curr.x + xdir[i] * j;

			MAP[ny][nx] = 2;
		}

		dfs(ind + 1, currCon + 1, currLine + len);

		memcpy(MAP, tmpMAP, sizeof(tmpMAP));
	}

	dfs(ind + 1, currCon, currLine); // �ش� �ھ �������� �ʴ� �͵� ���
}

int main() {
	int T;
	cin >> T;
	for (int tc = 1; tc <= T; tc++) {
		cin >> N;

		// �ʱ�ȭ
		cores.clear();
		connected = 0;
		minLine = 21e8;

		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++) {
				cin >> MAP[i][j];
				if (MAP[i][j] == 1) {
					// MAP�� �����ڸ��� ��ġ�� Core�� �̹� ���� �Ϸ� => Ž�� �ʿ� X
					if (InRange(i, j) == 1) {
						connected++;
						continue;
					}

					cores.push_back({ i,j });
				}
			}
		}

		dfs(0, connected, 0);

		cout << "#" << tc << " " << minLine << '\n';
	}

	return 0;
}