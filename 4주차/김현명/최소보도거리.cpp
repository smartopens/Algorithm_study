#define _CRT_SECURE_NO_WARNINGS

#include <algorithm>
#include <cstdlib>
#include <iostream>

using namespace std;

int sr, sc;
int tr, tc;

int min_dist = 21e8;

int main() {
    // ������ ��ġ, ��ǥ ��ġ �Է��ϱ� 
    cin >> sc >> sr;
    cin >> tc >> tr;

    int c1, r1, c2, r2, c3, r3, c4, r4;
    cin >> c1 >> r1 >> c2 >> r2 >> c3 >> r3 >> c4 >> r4;

    // dist1: �׳� �ɾ�� ��� 
    // dist2: ������ġ���� ����ö������ �ּ� ���
    // dist3: ��ǥ ��ġ���� ����ö������ �ּ� ���

    int dist1 = abs(tc - sc) + abs(tr - sr);
    int dist2 = 21e8;
    int dist3 = 21e8;

    // ����ö �������κ��� ������ġ�� ��ǥ��ġ������ �Ÿ��� ���� �����Ѵ�.

    // �Ʒ� ���� ���� Ž��
    for (int c = c1; c < c2 + 1; c++) {
        if (abs(c - sc) + abs(r1 - sr) < dist2) {
            dist2 = abs(c - sc) + abs(r1 - sr);
        }
        if (abs(c - tc) + abs(r1 - tr) < dist3) {
            dist3 = abs(c - tc) + abs(r1 - tr);
        }
    }

    // �� ���� ���� Ž��
    for (int c = c1; c < c2 + 1; c++) {
        if (abs(c - sc) + abs(r3 - sr) < dist2) {
            dist2 = abs(c - sc) + abs(r3 - sr);
        }

        if (abs(c - tc) + abs(r3 - tr) < dist3) {
            dist3 = abs(c - tc) + abs(r3 - tr);
        }
    }

    // ���� ���� ���� Ž��
    for (int r = r2; r < r3 + 1; r++) {
        if (abs(c1 - sc) + abs(r - sr) < dist2) {
            dist2 = abs(c1 - sc) + abs(r - sr);
        }

        if (abs(c1 - tc) + abs(r - tr) < dist3) {
            dist3 = abs(c1 - tc) + abs(r - tr);
        }
    }

    // ������ ���� ���� Ž��
    for (int r = r2; r < r3 + 1; r++) {
        if (abs(c3 - sc) + abs(r - sr) < dist2) {
            dist2 = abs(c3 - sc) + abs(r - sr);
        }

        if (abs(c3 - tc) + abs(r - tr) < dist3) {
            dist3 = abs(c3 - tc) + abs(r - tr);
        }
    }

    // �׳� �ȴ� ���� ����öŸ�� ��츦 ���Ѵ�.
    min_dist = min(dist1, dist2 + dist3);
    cout << min_dist << endl;

    return 0;
}