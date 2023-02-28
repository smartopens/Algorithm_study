#define _CRT_SECURE_NO_WARNINGS
#include <cstring>
#include <iostream>

using namespace std;

// �ڼ� ����
int n;
int magnetics[5][8];

int main() {
    int t = 0;
    int k = 0;

    cin >> t;
    for (int ti = 0; ti < t; ti++) {
        cin >> k;
        int scores = 0;

        // �ڼ� ���� �Է�
        for (int i = 1; i < 5; i++) {
            for (int j = 0; j < 8; j++) {
                cin >> magnetics[i][j];
            }
        }

        for (int ki = 0; ki < k; ki++) {

            // ȸ�� ���� 
            int cycles[5] = {};
            int idx, c;
            cin >> idx >> c;

            // �ڼ� ����
            // ��:6 ��:2

            // ó�� �ڼ� ȸ��
            cycles[idx] = c;

            // ù �ڼ� ���� ���� ���� ȸ�� ���� ����
            int ori_c = c;
            for (int i = idx; i < 4; i++) {
                if (magnetics[i][2] != magnetics[i + 1][6]) {
                    if (c == -1) {
                        cycles[i + 1] = 1;
                        c = 1;
                    }
                    else if (c == 1) {
                        cycles[i + 1] = -1;
                        c = -1;
                    }
                }
                else {
                    break;
                }
            }

            c = ori_c;

            // ù �ڼ� ���� ���� ���� ȸ�� ���� ����
            for (int i = idx; i > 1; i--) {
                if (magnetics[i][6] != magnetics[i - 1][2]) {
                    if (c == -1) {
                        cycles[i - 1] = 1;
                        c = 1;
                    }
                    else if (c == 1) {
                        cycles[i - 1] = -1;
                        c = -1;
                    }
                }
                else {
                    break;
                }
            }

            // ȸ�� ������ �°� �ڼ��� ȸ����Ű��
            for (int i = 1; i < 5; i++) {
                // �ð� 
                if (cycles[i] == -1) {
                    int tmp = magnetics[i][0];

                    for (int j = 0; j < 7; j++) {
                        magnetics[i][j] = magnetics[i][j + 1];
                    }
                    magnetics[i][7] = tmp;

                }
                // �ݽð� 
                else if (cycles[i] == 1) {
                    int tmp = magnetics[i][7];

                    for (int j = 7; j > 0; j--) {
                        magnetics[i][j] = magnetics[i][j - 1];
                    }
                    magnetics[i][0] = tmp;

                }
            }
        }

        // ���� ���� ���
        for (int i = 1; i < 5; i++) {
            if (magnetics[i][0] == 1) {
                int score = 1;
                for (int j = 0; j < i - 1; j++) {
                    score *= 2;
                }
                scores += score;
            }
        }

        cout << "#" << ti+1 << " " << scores << endl;
    }

    return 0;
}