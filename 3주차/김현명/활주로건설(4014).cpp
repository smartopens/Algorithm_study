#define _CRT_SECURE_NO_WARNINGS

#include <cstring>
#include <cctype>
#include <iostream>

using namespace std;

int n;
int ground[20][20];
int visited[20][20];
int x;

// Ȱ�ַ� ���� ���� Ž��
int count_road() {
    int p_path = 0;

    // ���� ���� Ž��
    for (int r = 0; r < n; r++) {
        bool can_build = true;

        for (int c = 0; c < n - 1; c++) {
            // ���� ���̰� 1�̻��� ���
            if (abs(ground[r][c] - ground[r][c + 1]) > 1) {
                can_build = false;
                break;
            }
            // ���� ���̰� 1�� ���
            else if (abs(ground[r][c] - ground[r][c + 1]) == 1) {
                // ���� ��ġ���� �� ���� ���̰� �� Ŭ���
                if (ground[r][c] < ground[r][c + 1]) {
                    // ���븦 �Ѿ���� �Ǵ�
                    if (0 > c - x + 1) {
                        can_build = false;
                        break;
                    }

                    // ���� ���� ���� �Ǵ�
                    // 1. ���� ��ġ�� ���̰� �������� ����.
                    // 2. ������ ���θ� ��ġ�ߴ����� Ȯ���Ѵ�.
                    for (int xi = 0; xi < x; xi++) {
                        if (ground[r][c] != ground[r][c-xi] || visited[r][c - xi] == 1)
                        {
                            can_build = false;
                            break;
                        }
                    }

                    // ���� ���
                    for (int xi = 0; xi < x; xi++) {
                        visited[r][c - xi] = 1;
                    }
                }

                // ���� ��ġ���� �� ���� ���̰� �� ���� ���
                else if (ground[r][c] > ground[r][c + 1]) {
                    // ���븦 �Ѿ���� �Ǵ�
                    if (c + x > n - 1) {
                        can_build = false;
                        break;
                    }

                    // ���� ���� ���� �Ǵ�
                    // 1. ���� ��ġ�� ���̰� �������� ����.
                    for (int xi = 1; xi < x; xi++) {
                        if (ground[r][c+1] != ground[r][c + 1 + xi])
                        {
                            can_build = false;
                            break;
                        }
                    }

                    // ���� ���
                    for (int xi = 0; xi < x; xi++) {
                        visited[r][c +1+ xi] = 1;
                    }
                }

            }
            // �׳� ���� ���
        }
        if (can_build == true) {
            p_path += 1;

        }
    }

    memset(visited, 0, sizeof(visited));

    // ���� ���� Ž��
    for (int c = 0; c < n; c++) {
        bool can_build = true;

        for (int r = 0; r < n - 1; r++) {
            // ���� ���̰� 1�̻��� ���
            if (abs(ground[r][c] - ground[r+1][c]) > 1) {
                can_build = false;
                break;
            }
            // ���� ���̰� 1�� ���
            else if (abs(ground[r][c] - ground[r+1][c]) == 1) {
                if (ground[r][c] < ground[r+1][c]) {
                    // ���븦 �Ѿ���� �Ǵ�
                    if (0 > r - x + 1) {
                        can_build = false;
                        break;
                    }

                    // ���� ���� ���� �Ǵ�
                    // 1. ���� ��ġ�� ���̰� �������� ����.
                    // 2. ������ ���θ� ��ġ�ߴ����� Ȯ���Ѵ�.
                    for (int xi = 0; xi < x; xi++) {
                        if (ground[r][c] != ground[r-xi][c] || visited[r-xi][c] == 1)
                        {
                            can_build = false;
                            break;
                        }
                    }
                    // ���� ���
                    for (int xi = 0; xi < x; xi++) {
                        visited[r-xi][c] = 1;
                    }
                }
                // ���� ��ġ���� �� ���� ���̰� �� ���� ���
                else if (ground[r][c] > ground[r+1][c]) {
                    // ���븦 �Ѿ���� �Ǵ�
                    if (r + x > n - 1) {
                        can_build = false;
                        break;
                    }
                    // ���� ���� ���� �Ǵ�
                    // 1. ���� ��ġ�� ���̰� �������� ����.
                    for (int xi = 1; xi < x; xi++) {
                        if (ground[r+1][c] != ground[r+1+xi][c])
                        {
                            can_build = false;
                            break;
                        }
                    }

                    // ���� ���
                    for (int xi = 0; xi < x; xi++) {
                        visited[r+1+xi][c] = 1;
                    }
                }

            }
            // �׳� ���� ���
        }
        if (can_build == true) {
            p_path += 1;
        }
        memset(visited, 0, sizeof(visited));
    }


    return p_path;
}

int main() {
    int t = 0;
    int p_path = 0;

    cin >> t;

    for (int ti = 0; ti < t; ti++) {
        cin >> n >> x;
        memset(ground, 0, sizeof(ground));
        
        // �������� ���� �Է�
        for (int r = 0; r < n; r++) {
            for (int c = 0; c < n; c++) {
                cin >> ground[r][c];
            }
        }

        // Ȱ�ַ� ��� ���
        p_path = count_road();

        cout << "#" << ti + 1 << " " << p_path << endl;
    }
    return 0;
}