#include <iostream>
#include <string>
using namespace std;

string poison[20]; // ���ع� ����

int N, K;
int cnt; // ������ �๰�� ������ �� (��)

// ���ع��� ���ԵǾ� �ִ� �����ΰ��� �Ǵ�
// true: ������ ����, false: ������ ����
bool isUnsafe(string medi) {
	bool isFound = true;

	// �Է¹��� ���ع��� ��� Ž��
	for (int i = 0; i < K; i++) {
		isFound = true;

		// i��° ���ع�
		string now = poison[i];
		int len = now.length();

		// �����Ϸ��� ���պ��� ���̰� �۴ٸ� ���� -> �ش� ������ ���� ���� X
		if (len > medi.length()) continue;

		// ���� ã�� ���տ� ���ع��� �� ������ ���ԵǾ� �ִ��� Ȯ��
		for (int j = 0; j < len; j++) {
			if (medi.find(now[j]) == -1) { // j��° �๰�� ���ٸ�
				// medi�� i��° ���ع��� ������ -> �������� ����
				isFound = false;
				break;
			}
		}

		// ������ �����ϴٰ� �Ǵܵ��� �ʾҴٸ�
		// ��, ���ع��� �๰ ������ ���� ���ԵǾ��ٸ�
		// �ش� ������ �����ϴ�
		if (isFound) return true;
	}

	// ������ return���� �ʾҴٸ�
	// ��� ���ع��� ���ԵǾ� ���� �ʴ�
	// ��, �ش� ������ �����ϴ�
	isFound = false;

	return isFound;
}

// lev: ������� ã�� ������ ���ڼ�
// medi: ������� ã�� ����
void dfs(int lev, string medi) {
	if (lev > N) return; // N ���� �ʰ��� ���̻� Ž�� X

	// ���ؿ� ������ �����ϴٸ� cnt ī����
	if (lev > 0 && lev <= N) {
		if (!isUnsafe(medi)) {
			cnt++;
		}
	}

	// �ߺ� ���Ÿ� ���� ������ ã�� �๰���� ū������ Ž���ϱ�
	int prev = lev == 0 ? 0 : (medi[lev - 1] - '0');
	for (int i = prev + 1; i <= N; i++) {
		dfs(lev + 1, medi + to_string(i));
	}
}

int main() {
	// input
	cin >> N >> K;
	for (int i = 0; i < K; i++) {
		cin >> poison[i];
	}

	// dfs�� ��� ������ ���� ã��
	dfs(0, "");

	// ������ �๰�� ���� ����ϱ�
	cout << cnt << "\n"; 

	return 0;
}

/* 2�� ���� - 31 �� ��
1 2 3 4 5
12 13 14 15 23 24 25 34 35 45
123 124 125 134 135 145 234 345
1234 1345

235 245 1235 1245 2345 12345
*/