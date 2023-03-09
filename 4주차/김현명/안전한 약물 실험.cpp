#define _CRT_SECURE_NO_WARNINGS

#include <string>
#include <iostream>

using namespace std;

int n, k;
int nums[10];
string poison[10];
int path[10];
int safe_num;

void dfs(int depth, int max_depth, int idx) {
    // Ž���Ϸ��� ��ǰ ������ �Ǿ��� ���
    if (depth >= max_depth) {

        // ��ǰ�� ���������� ����.
        bool is_safe = true;

        // k���� ���ع��� Ž���Ѵ�.
        for (int i = 0; i < k; i++) {
            int p_num = 0;

            // ���ع��� �� ��Ұ� ��ǰ����(path)�� ������ ��� p_num += 1�� ���ش�.
            for (int s = 0; s < poison[i].length(); s++) {
                for (int j = 0; j < max_depth; j++) {
                    if ((int)(poison[i][s]-'0') == path[j]) {
                        p_num += 1;
                        break;
                    }
                }
            }
            // ���ع��� ������ �ִ� ��� �������� �ʴ�.
            if (p_num == poison[i].length()) {
                is_safe = false;
            }
        }

        // �����ϴٸ� ������ ����.
        if (is_safe) {
            safe_num += 1;
        }

        return;
    }

    // 3 5 7

    // �๰ ���� �����
    for (int i = idx; i < n; i++) {
        path[depth] = nums[i];
        dfs(depth + 1, max_depth, i + 1);
    }
}

int main() {
    cin >> n;

    // �๰ ���� �Է��ϱ�
    for (int i = 0; i < n; i++) {
        nums[i] = i+1;
    }

    cin >> k;

    // �� ���� �Է��ϱ�
    for (int i = 0; i < k; i++) {
        string tmp;
        cin >> tmp;
        poison[i] = tmp;
    }

    // �������� Ž���ϱ�
    // ��ǰ����: 1 ~ n ��
    // ��� �๰ ������ ��츦 ����.
    for (int i = 1; i < n + 1; i++) {
        dfs(0,i,0);
    }

    cout << safe_num << endl;

    return 0;
}