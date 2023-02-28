#include <iostream>
using namespace std;

/*
1
2
0 0 1 0 0 1 0 0
1 0 0 1 1 1 0 1
0 0 1 0 1 1 0 0
0 0 1 0 1 1 0 1
1 1
3 -1

1
2
1 0 0 1 0 0 0 0
0 1 1 1 1 1 1 1
0 1 0 1 0 0 1 0
0 1 0 0 1 1 0 1
3 1
1 1
*/

int W[5][8];
int W_tmp[5][8];

void rotate(int num, int dir) { // Ư�� ��ȣ�� ������ ȸ����Ű�� �Լ�

    int tmp = 0;

    if (dir == 1) { // ������ �� �̻��ϴ�
        tmp = W_tmp[num][7];
        for (int i = 6; i >= 0; i--) {
            W_tmp[num][i + 1] = W_tmp[num][i];
            
        }
        W_tmp[num][0] = tmp;
    }
    int tmp_rev = 0;

    if (dir == -1) {
        tmp_rev = W_tmp[num][0];
        for (int i = 0; i < 7; i++) {
            W_tmp[num][i] = W_tmp[num][i + 1];
            
        }
        W_tmp[num][7] = tmp_rev;
    }
}

int main() {

    int T;
    cin >> T;
    for (int tc = 1; tc <= T; tc++) {

        int sum = 0;
        int K;
        cin >> K;

        for (int i = 1; i < 5; i++) {
            for (int j = 0; j < 8; j++) {
                cin >> W[i][j]; // wheel ���� �Է�
                W_tmp[i][j] = W[i][j]; // �ӽ� �迭�� �����
            } // N�� : 0, S�� : 1
        }

        int W_num;
        int W_dir;

        for (int i = 0; i < K; i++) {
            cin >> W_num; // ȸ�� ���� ��ȣ // 
            cin >> W_dir; // ȸ�� ����

            rotate(W_num, W_dir);

            int W_dir_tmp = W_dir;

            for (int j = 0; j <= 2; j++) { // ������ ��

                if (W_num + j >= 4) continue;

                if (W[W_num + j][2] != W[W_num + j + 1][6]) {
                    W_dir *= -1;
                    rotate(W_num + j + 1, W_dir); // ������ �ð� �ݴ� �������� ȸ��
                }
                else
                    break;

            }

            W_dir = W_dir_tmp;

            for (int j = 0; j <= 2; j++) { // ���� ��

                if (W_num - j <= 1) continue; // W_num�� 1���� ���� �̹Ƿ�

                if (W[W_num - j][6] != W[W_num - j - 1][2]) {
                    W_dir *= -1;
                    rotate(W_num - j - 1, W_dir); // ���� �ð� �ݴ� �������� ȸ��
                }
                else
                    break;
            }
            for (int k = 1; k < 5; k++) {
                for (int l = 0; l < 8; l++) {
                    W[k][l] = W_tmp[k][l];
                }
            }
            
        }

        for (int i = 1; i < 5; i++) {
            for (int j = 0; j < 8; j++) {
                cout << W[i][j] << " ";
            }
            cout << "\n";
        }

        /*if (W[1][0] == 1) sum += 1;
        if (W[2][0] == 1) sum += 2;
        if (W[3][0] == 1) sum += 4;
        if (W[4][0] == 1) sum += 8;

        cout << "#" << tc << " " << sum << endl;*/
        
    }



    return 0;
}