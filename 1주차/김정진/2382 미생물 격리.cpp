#include <iostream>
 
using namespace std;

// 미생물 개개인의 움직임과 정보는 미생물의 정보를 담는 구조체에
// 각 미생물이 같은 셀에 도착했을 때의 비교를 위한 정보는 다른 구조체에

// 1이면 (상), 2이면 (하), 3이면 (좌), 4이면 (우)
const int mi[5] = {0,-1,1,0,0};
const int mj[5] = {0,0,0,-1,1};

// 빠르게 방향 전환을 위한 배열
// ex) 1(상)이면 2(하)로
const int md[5] = {0,2,1,4,3};
int T, ans;
int N,M,K,a,b;

// 미생물의 정보를 담은 구조체
struct microbe{
    bool live = true;
    int i;
    int j;
    int value;
    int dir;
};

// 셀 하나의 정보를 담은 구조체
struct area{
    int num;
    int val;
};
area map[102][102];
microbe mic[1001];
 
int main() {
    cin.tie(NULL);
    ios::sync_with_stdio(false);
    cin >> T;
    for(int tc = 1; tc <= T; tc++) {
        ans = 0;
        cin >> N >> M >> K;
        for(int i{0}; i < K; i++) {
            mic[i].live = true;
            cin >> mic[i].i >> mic[i].j >> mic[i].value >> mic[i].dir;
        }
        for(int i{1}; i <= M; i++) {
            // 매 격리 시간마다 맵 배열 초기화 시키고 시작
            for(int j{0}; j < 101; j++) {
                for(int k{0}; k < 101; k++) {
                    map[j][k] = {0,0};
                }
            }


            for(int j{0}; j < K; j++) {
                // 죽은 미생물은 검사 ㄴㄴ
                if(!mic[j].live) continue;

                // 현재 미생물 정보
                int ci = mic[j].i;
                int cj = mic[j].j;
                int cv = mic[j].value;
                int cd = mic[j].dir;

                // 다음에 이동한 미생물의 정보
                int ni = ci + mi[cd];
                int nj = cj + mj[cd];
                int nv = cv;
                int nd = cd;
                
                // 맵 끝에 도달했으면 미생물의 수량 반으로 감소 하고 방향 바꾸기
                if(ni == 0 || ni == N-1 || nj == 0 || nj == N-1) {
                    nd = md[cd];
                    nv = cv/2;
                }

                // 이동하는 셀에 미생물이 없는 경우 셀에 현재 미생물의 정보를 저장
                if(map[ni][nj].val == 0) {
                    map[ni][nj].num = j;
                    map[ni][nj].val = nv;
                    mic[j].value = nv;
                }
                // 이동하는 셀에 미생물이 있는 경우
                else {
                    // 현재 미생물이 셀에 도착한 가장 많은 수의 미생물들 보다 수가 많으므로
                    if(nv > map[ni][nj].val) {
                        // 기존 셀에 있던 미생물은 죽이고
                        mic[map[ni][nj].num].live = false;
                        // 기존 셀에 있던 미생물의 수를 합치고
                        mic[j].value = mic[map[ni][nj].num].value + nv;
                        // 셀에는 해당 미생물의 정볼르 저장
                        map[ni][nj].num = j;
                        map[ni][nj].val = nv;
                    }
                    // 현재 미생물이 셀에 도착한 가장 많은 수의 미생물 보다 수가 적으므로
                    else {
                        mic[j].live = false;    
                        mic[map[ni][nj].num].value = mic[map[ni][nj].num].value + nv;
                    }
                }
                mic[j].i = ni;
                mic[j].j = nj;
                mic[j].dir = nd;
            }
        } 
        for(int i{0}; i < K; i++) {
            if(mic[i].live) ans += mic[i].value;
        }
        cout << "#" << tc << ' ' << ans << endl;
    }
}