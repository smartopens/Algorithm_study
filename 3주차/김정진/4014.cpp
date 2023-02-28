#include <iostream>

using namespace std;

int T,N,X,ans;
int map[22][22];

// 가로 세로 탐색하면서
// 1. 지형이 같은 높이인 경우
// 2. 지형이 높아지는 경우 : 이전에 X만큼의 여유공간이 있었는가?
// 3. 지형이 낮아지는 경우 : 이제부터 X만큼의 여유공간이 있는가?
// 이렇게 세가지 때 어떻게 바뀌는지를 열심히 고려하면 해결

int main() {
    cin.tie(NULL);
    ios::sync_with_stdio(false);
    cin >> T;
    for(int tc = 1; tc <= T; tc++) {
        // 초기화
        ans = 0;
        cin >> N >> X;
        for(int i = 1; i <= N; i++) {
            for(int j = 1; j <= N; j++) {
                cin >> map[i][j];
            }
        }

        // 먼저 가로줄 부터
        for(int i = 1; i <= N; i++) {
            // 활주로 건설이 가능한지 저장하는 flag
            bool key = true;
            // 이전칸의 높이를 저장할 cnum 변수
            int cnum = map[i][1];
            // 높아지는 경우 이전까지 X만큼 공간의 여유가 있는지 체크해야 하므로 이를 세어줄 cnt 변수
            int cnt = 1;
            // 낮아지는 경우 이제 X만큼 공간의 여유가 있는지 확인해야 하므로 이를 세어줄 hnt 변수
            int hnt = 0;
            for(int j = 2; j <= N; j++) {
                // 다음 지형이 같은 높이이다.
                if(map[i][j] == cnum) {
                    // hnt가 양수라는 것은 아직 높은곳에서 내려오는 활주로가 건설 중이라는 의미이다.
                    // 그러므로 활주로를 마저 건설하기
                    if(hnt > 0) {
                        hnt--;
                    }
                    // hnt가 양수가 아니란 것은 당장 건설중인 활주로가 없다는 뜻
                    // 즉, 혹시라도 높은곳으로 올라갈 활주로를 대비한 여유공간을 세어준다.
                    else {
                        cnt++;
                    }
                }
                // 지형의 높이가 바뀌는 경우
                else {
                    // 우선 활주로를 건설 중인데 지형의 높이가 바뀌지는 않는지 체크
                    if(hnt > 0) {
                        // 건설중이였으면 flag에 false넣고 탈출
                        key = false;
                        break;
                    }
                    // 지형의 높이가 높아지는 경우
                    if(map[i][j] > cnum) {
                        // 2칸이상 높아지거나 여유공간이 X보다 모자르지는 않는지 체크
                        if(map[i][j] - cnum >= 2 || cnt < X) {
                            // 조건이 미달성이면 flag에 false 넣고 탈출
                            key = false;
                            break;
                        } 
                        // 조건이 맞으면 올라가는 활주로 건설 가능하므로 다시 여유공간 세어주기
                        // 현재 칸 부터 여유공간이니 cnt = 1
                        cnt = 1;
                    }
                    // 지형의 높이가 낮아지는 경우
                    else {
                        // 2칸 이상 낮아지는 경우 체크
                        if(cnum - map[i][j] >= 2) {
                            // 조건이 미달성이면 flag에 false 넣고 탈출 
                            key = false;
                            break;
                        }
                        // 내려오는 활주로를 지금부터 건설해야하니 hnt 초기화
                        // 단, 현재 칸은 이미 밟고 있으니 hnt엔 X-1 부여
                        // 여유공간 cnt도 초기화
                        hnt = X-1;
                        cnt = 0;
                    }
                    // 다음 칸으로 이동
                    cnum = map[i][j];
                }
            }
            // 경사로가 지형 밖까지 설치해야하는 경우 체크
            if(hnt > 0) key = false;
            // 건설이 가능하면 ans 증가
            if(key) {
                ans++;
            }
        }

        // 세로줄의 경우 가로줄 코드 복붙해서 index만 바꿔줌
        for(int j = 1; j <= N; j++) {
            bool key = true;
            int cnum = map[1][j];
            int cnt = 1;
            int hnt = 0;
            for(int i = 2; i <= N; i++) {
                if(map[i][j] == cnum) {
                    if(hnt > 0) {
                        hnt--;
                    }
                    else {
                        cnt++;
                    }
                }
                else {
                    if(hnt > 0) {
                        key = false;
                        break;
                    } 
                    if(map[i][j] > cnum) {
                        if(map[i][j] - cnum == 2 || cnt < X) {
                            key = false;
                            break;
                        } 
                        cnt = 1;
                    }
                    else {
                        if(cnum - map[i][j] >= 2) {
                            key = false;
                            break;
                        } 
                        hnt = X-1;
                        cnt = 0;
                    }
                    cnum = map[i][j];
                }
            }
            if(hnt > 0) key = false;
            if(key) {
                ans++;
            }
        }
        
        // 정답 출력
        cout << "#" << tc << " " << ans << endl;
    }
}