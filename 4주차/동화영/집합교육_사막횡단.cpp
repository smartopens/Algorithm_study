/* �縷Ⱦ�� */
#include <iostream>
#include <vector>
using namespace std;

struct store {
	int loc; // ������ ��ġ
	int cnt; // �Ǹ� ���� ������ ����
};

vector<store> stores;
vector<store> history; // ������ �Ǹ��� �̷�
int N, M, K;

vector<store> minHis; // �ּ� �Ҹ� ü���� ����� �̷� (��)
int minAcc; // �ּ� �Ҹ� ü�� (��)

// ind : stores[ind]�� �̹��� �߰��� ������ ��ġ
// water : ���� ������ ���� ����
// acc : ������� �Ҹ��� ü��
void dfs(int ind, int water, int acc) {
	if (stores[ind].loc == M) {
		if (acc < minAcc) {
			minAcc = acc;
			minHis = history;
		}
		return;
	}

	// 1. ����(ind) ~ ����(ind+1) ������ �Ҹ� ü�� ���
	int st = stores[ind].loc;
	int en = stores[ind + 1].loc;
	int nDist = en - st;
	
	int tmp = 0; // ind ~ (ind+1) ���� �Ҹ�Ǵ� ü��
	for (int pos = 0; pos < nDist; pos++) {
		tmp += (water - pos);
	}

	// 2. �������� �� �� �ִ� ���� ���� ��츦 ��� ���� �������� ����
	for (int i = stores[ind].cnt; i >= 0; i--) {
		if (nDist > water + i) break;

		history.push_back({ ind, i });
		dfs(ind + 1, water - nDist + i, acc + tmp);
		history.pop_back();
	}
}

int main() {
	// input
	cin >> N >> M >> K;
	stores.push_back({ 0, 0 });
	int loc, cnt;
	for (int i = 0; i < K; i++) {
		cin >> loc >> cnt;
		stores.push_back({ loc, cnt });
	}
	stores.push_back({ M, 0 });

	// solve
	dfs(0, N, 0);

	// output
	for (int i = 1; i < minHis.size() - 1; i++) {
		cout << minHis[i].loc << " " << minHis[i].cnt << '\n';
	}

	return 0;
}