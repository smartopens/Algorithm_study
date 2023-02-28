#include <iostream>
#include <queue>

using namespace std;

// 그냥 bfs로 미련하게 매초 마다 굴려봤다가 gg
// 우선순위큐로 최적화를 하여 해결

// 여느 때와 같은 이동 방향을 담은 배열
const int mi[4] = {-1,1,0,0};
const int mj[4] = {0,0,-1,1};
int T,N,M,K,input,ans;

// 세포의 정보를 담는 구조체
// 생성된 세포는 총 2 번의 이벤트가 발생
// 1번 이벤트 : (생성 시간 + 생명력 + 1) : 세포가 활성화되고 번식하는 이벤트 발생
// 2번 이벤트 : (생성 시간 + (생명력 * 2)) : 세포가 비활성, 활성 상태를 거쳐 사망하는 이벤트 발생
struct Cell{
    // 좌표
    int y;
    int x;
    int val;  // 세포 생명력
    int time;  // 세포의 이벤트가 발생하는 시간
    int state; // 1이면 해당 Cell에는 1번 이벤트가, 2이면 2번 이벤트가 발생

    // 최우선은 시간이 빠른 순서대로
    // 시간이 같은 경우 차선은 세포가 가진 생명력 (같은 시간, 같은 셀로의 동시 번식은 생명력 높은 세포가 이기므로)
    // 사실 해당 구현에서는 state 비교 까진 필요없음
    bool operator < (Cell next) const{
        if(next.time == time) {
            if(val == next.val) {
                return state > next.state;
            }
            return val < next.val;
        }
        return time > next.time;
    }
};
priority_queue<Cell>pq;

// K가 최대 300이고 1의 생명력을 가진 세포라도 2초가 지나야 번식을 하므로
// 세로줄과 가로줄의 최대 크기는 각각 (N + (150 * 2)), (M + (150 * 2))면 충분
int map[352][352];
int visit[352][352];

int main() {
    cin >> T;
    for(int tc = 1; tc <= T; tc++) {
        // 초기화
        cin >> N >> M >> K;
        ans = 0;
        while(!pq.empty()) pq.pop();
        for(int i = 0; i < 352; i++) {
            for(int j = 0; j < 352; j++) {
                map[i][j] = 0;
                visit[i][j] = 0;
            }
        }
        // 입력
        for(int i = 1; i <= N; i++) {
            for(int j = 1; j <= M; j++) {
                cin >> map[i+150][j+150];
            }
        }

        // 입력받은 값을 탐색하면서 세포의 경우 우선순위큐에 정보를 삽입
        for(int i = 1; i <= N; i++) {
            for(int j = 1; j <= M; j++) {
                int mij = map[i+150][j+150];
                if(mij == 0) continue;
                pq.push({i+150,j+150,mij,mij+1,1}); // 1번 이벤트
                pq.push({i+150,j+150,mij,mij*2,2}); // 2번 이벤트
                // 방문 처리
                visit[i+150][j+150] = 1;
            }
        }

        // 문제 특성상 실제로 빌 때까지 돌리는 문제는 아님
        while(!pq.empty()) {
            int cx = pq.top().x;
            int cy = pq.top().y;
            int cv = pq.top().val;
            int ct = pq.top().time;
            int cs = pq.top().state;
            // 어차피 세포 수가 증가 혹은 감소하는 이벤트가 발생하기 전까지는 세포 수는 변함이 없으므로
            // K를 현재 시간이 넘어갈 때 까지 루프 반복하면 된다.
            if(ct > K) break;
            pq.pop();
            // 2번 이벤트는 그냥 세포수를 세는데 필요한 것이므로 패스
            if(cs == 2) continue;

            // 1번 이벤트면 상하좌우 가능한 공간으로 수가 증가
            for(int i{0}; i < 4; i++) {
                int nx = cx + mj[i];
                int ny = cy + mi[i];
                // 우선순위큐로 같은 시간이면 생명력이 높은 세포가 먼저 확인 가능하므로
                // 이미 세포 정보가 들어간 칸이면 어차피 번식 가능한 칸이 아님 
                if(visit[ny][nx]) continue;
                visit[ny][nx] = 1;
                // 증가한 세포의 이벤트도 추가
                pq.push({ny,nx,cv,ct+cv+1,1});
                pq.push({ny,nx,cv,ct+cv*2,2});
            }
        }

        // 시간이 K가 넘어서 탈출
        // 남은 우선순위큐에서 2번 이벤트의 숫자만 세어준다
        // 1번이랑 2번이랑 같은 세포이므로 중복해서 세어주면 안된다.
        while(!pq.empty()) {
            int cs = pq.top().state;
            pq.pop();
            if(cs == 2) ans++;
        }
        cout << "#" << tc << " " << ans << endl;
    }
}