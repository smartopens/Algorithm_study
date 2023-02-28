#include <iostream>
#include <algorithm>
#include <vector>
 
using namespace std;
 
 // 이동 하는 움직임 저장
const int mi[5] = {0,-1,0,1,0};
const int mj[5] = {0,0,1,0,-1};
int T, M, BC, bci, bcj, C, P, ans;
int A[101];
int B[101];
struct pos{
    int i;
    int j;
};
pos Apos, Bpos;
vector<int>map[12][12];
int bcp[9];
int bca[8];
int bcb[8];
 
 // 범위 안 넘어가게
bool checkbound(int mini, int minj, int maxi, int maxj, int curi, int curj) {
    return (curi >= mini && curi <= maxi && curj >= minj && curj <= maxj);
}
 
int main() {
    cin.tie(NULL);
    ios::sync_with_stdio(false);
    cin >> T;
    for(int tc = 1; tc <= T; tc++) {
        cin >> M >> BC;
        ans = 0;
        A[0] = 0;
        for(int i{1}; i <= 10; i++) {
            for(int j{1}; j <= 10; j++) {
                map[i][j].clear();
                map[i][j].push_back(0);
            }
        }
        // A의 움직임 저장
        for(int i{1}; i <= M; i++) {
            cin >> A[i];
        }

        // B의 움직임 저장
        B[0] = 0;
        for(int i{1}; i <= M; i++) {
            cin >> B[i];
        }

        // 베터리 저장 및 map 배열에 각 배터리의 정보를 저장
        for(int i{1}; i <= BC; i++) {
            cin >> bcj >> bci >> C >> P;
            // 베터리의 범위를 이중 for문으로 처리
            for(int j{-C}; j <= C; j++) {
                for(int k{- C + abs(j)}; k <= C - abs(j); k++) {
                    if(!checkbound(1,1,10,10,bci + j,bcj + k)) continue;
                    map[bci + j][bcj + k].push_back(i);
                }
            }
            bcp[i] = P;
        }
        Apos = {1,1};
        Bpos = {10,10};
        // 저장해둔 이동 경로에 따라 이동
        for(int i{0}; i <= M; i++) {
            Apos.i = Apos.i + mi[A[i]];
            Apos.j = Apos.j + mj[A[i]];
            Bpos.i = Bpos.i + mi[B[i]];
            Bpos.j = Bpos.j + mj[B[i]];
            int tmp = 0;
            int sum = 0;

            // A가 접촉한 충전기와
            for(int j{0}; j < map[Apos.i][Apos.j].size(); j++) {
                int abc = map[Apos.i][Apos.j][j]; 
                // B가 접촉중인 충전기를 이중for문으로 완전탐색하여 가장 최고의 조합을 찾기
                for(int k{0}; k < map[Bpos.i][Bpos.j].size(); k++) {
                    int bbc = map[Bpos.i][Bpos.j][k];
                    // 서로 다른 충전기인 경우의 조합
                    if(abc != bbc) {
                        tmp = bcp[abc] + bcp[bbc];
                    }
                    // 같은 충전기인 경우의 조합
                    else {
                        tmp = max(bcp[abc],bcp[bbc]);
                    }
                    // 그 중 최고의 조합을 저장
                    if(tmp > sum) {
                        sum = tmp;
                    }
 
                }
 
            }
            //결과에 반영
            ans += sum;
        }
 
        cout << "#" << tc << ' ' << ans << endl;
    }
}