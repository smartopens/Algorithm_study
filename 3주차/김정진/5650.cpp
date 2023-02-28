#include <iostream>

using namespace std;

// 벽이나 블록에 부딪혔을 때 방향전환을 저장해주는 배열
// -1은 벽에 부딪혀서 경로가 완전히 돌아가는 경우
// 이 경우엔, 어차피 시작점으로 돌아가는 경로이므로 점수를 * 2 해주면 된다.
const int md[6][4] = {{0,1,2,3},{-1,3,0,-1},{3,-1,1,-1},{2,-1,-1,1},{-1,2,-1,0},{-1,-1,-1,-1}};
// 방향에 따른 이동을 저장한 배열
const int my[4] = {-1,1,0,0};
const int mx[4] = {0,0,-1,1};
int T,N,ans;
int map[102][102];
// 웜홀 좌표 저장용
struct pos{
    int y = -1;
    int x = -1;
};
pos wormhall[5][2];

int main() {
    cin >> T;
    for(int tc = 1; tc <= T; tc++) {
        // 초기화 및 입력
        ans = 0;
        cin >> N;
        for(int i = 0; i < 5; i++ ) {
            wormhall[i][0] = {-1,-1};
            wormhall[i][1] = {-1,-1};
        }
        // 범위를 가로 세로 양 옆 한 칸 씩 늘려줌
        // 이유는 어차피 범위 밖은 벽이기 때문에 5번 블록으로 때우기
        for(int i = 0; i <= N+1; i++) {
            // 벽을 5번블록으로 바꿔주기
            if(i == 0 || i == N+1) {
                for(int j = 0; j <= N+1; j++)
                    map[i][j] = 5;
            }
            else{
                for(int j = 0; j <= N+1; j++) {
                    // 벽은 5번 블록으로 바꿔주기
                    if(j == 0 || j == N+1)
                        map[i][j] = 5;
                    else {
                        // 기존 범위는 입력
                        cin >> map[i][j];
                        // 웜홀이면
                        if(map[i][j] >= 6) {
                            // 대충 웜홀 좌표 나눠서 저장해주기 (웜홀 번호는 맞춰서 저장)
                            if(wormhall[map[i][j] - 6][0].y == -1) {
                                wormhall[map[i][j] - 6][0] = {i,j};
                            }
                            else {
                                wormhall[map[i][j] - 6][1] = {i,j};
                            }
                        }
                    }        
                }
            }
        }

        // 시작점이 어딘지 모르므로 게임판 전체를 돌아야 한다.
        for(int i = 1; i <= N; i++) {
            for(int j = 1; j <= N; j++) {
                // 시작점으로 지정 가능한 위치면 시작
                if(map[i][j] == 0) {
                    // 방향도 4개 모두 지정 가능하므로
                    for(int k{0}; k < 4; k++) {
                        // cy = 핀볼의 현재 y값, cx = 핀볼의 현재 x값, cd = 핀볼의 현재 방향, cv = 핀볼이 위치한 게임판의 모양
                        int cy = i;
                        int cx = j;
                        int cd = k;
                        int cv = map[i][j];
                        int score = 0;
                        while(true) {
                            // 다음칸으로 이동 전에 현재 칸에 따라 방향부터 갱신
                            cd = md[cv][cd];
                            // 그런데 현재 부딪힌 칸이 벽이였으면 
                            if(cd == -1) {
                                // 스코어 2배하고 루프 탈출 (어차피 돌아가면서 부딪히면서 얻는 점수는 같다.)
                                score *= 2;
                                // -1 해주는건 코드 구현상 벽에 부딪힌 순간 +1을 해주도록 짜서 조정용
                                score -= 1;
                                break;
                            }
                            // 조정된 방향으로 다음칸 이동
                            cy = cy + my[cd];
                            cx = cx + mx[cd];
                            cv = map[cy][cx];
                            // 블랙홀을 만났으면 게임 종료
                            if(cv == -1) break;
                            // 시작점에 돌아왔으면 게임 종료
                            if(cy == i && cx == j) break;
                            // 벽이나 블록에 부딪혔으면 점수 1점 증가
                            if(cv >= 1 && cv <= 5) score++;
                            // 웜홀에 도착했으면
                            else if (cv >= 6) {
                                // 저장해둔 좌표로 순간이동
                                // 방향은 그대로여야하니깐 좌표랑
                                if(wormhall[cv-6][0].y == cy && wormhall[cv-6][0].x == cx){
                                    cy = wormhall[cv-6][1].y;
                                    cx = wormhall[cv-6][1].x;
                                }
                                else {
                                    cy = wormhall[cv-6][0].y;
                                    cx = wormhall[cv-6][0].x;
                                }
                                // 순간이동 후에는 평지로 이동했다고 취급하여 방향 그대로 두기
                                cv = 0;
                            }
                        }
                        //cout << i << ' ' << j << ' ' << k << ' ' << score << endl;
                        // 최대 점수 갱신
                        ans = max(ans,score);
                    }
                }
            }
        }
        // 출력
        cout << "#" << tc << " " << ans << endl;
    }
}