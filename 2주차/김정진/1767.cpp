#include <iostream>
#include <vector>

using namespace std;

const int mi[4] = {-1,1,0,0};
const int mj[4] = {0,0,-1,1};

int N,T,ans,map[13][13], maxcore;
struct pos{
    int i;
    int j;
};
vector<pos>vec;

//멕시노스의 범위를 벗어나는지 확인
bool checkbound(int i, int j) {
    return i >= 0 && i < N && j >= 0 && j < N;
}

// 멕시노스의 가장자리에 위치했는지 확인
bool checkborder(int i, int j) {
    return i == 0 || i == N-1 || j == 0 || j == N-1;
}

// dfs를 통해 해결
// 각 코어가 상,하,좌,우 중 어느 방향으로 전선을 뻗을 지를 기준으로 dfs 탐색
void dfs(int level, int len, int cnt){
    // 모든 코어 탐색 완료
    if(level == vec.size()) {
        /*
        // 디버깅용
        cout << endl;
        cout << "cnt: " << cnt << endl;
        cout << "maxcore: " << maxcore << endl;
        cout << "len: " << len << endl;
        cout << "ans: " << ans << endl;
        for(int i{0}; i < N; i++) {
            for(int j{0}; j < N; j++) {
                cout << map[i][j] << ' ';
            }
            cout << endl;
        }
        */

       // 전원이 연결된 최대 코어수가 갱신 되면 그에 맞게 전선 길이의 합을 갱신
        if(cnt > maxcore) {
            maxcore = cnt;
            ans = len;
        }
        // 기존에 저장된 최대 코어수와 이번에 탐색한 최대 코어수가 같다면 전선 길이의 합만 최적화
        else if (cnt == maxcore) {
            if(len < ans) {
                ans = len;
            }
        }
        return;
    }

    // 벡터에 받아 둔 코어의 좌표값을 가져와서 상,하,좌,우 전선 설치하기
    int ci = vec[level].i;
    int cj = vec[level].j;
    for(int i{0}; i < 4; i++) {
        int ni = ci + mi[i];
        int nj = cj + mj[i];
        bool connected = true;
        int lencnt = 0;
        // 멕시노스의 범위를 벗어나기 전까지 전선을 늘리기
        while(checkbound(ni,nj)) {
            // 중간에 전선이나 코어를 만나게 된 경우
            // 불가능한 경우이므로 connected에 false값 부여
            if(map[ni][nj]) {
                ni -= mi[i];
                nj -= mj[i];
                connected = false;
                break;
            }
            map[ni][nj] = 1;
            ni += mi[i];
            nj += mj[i];
            lencnt++;
        }
        // 연결된 경우만 다음 dfs 탐색으로 진행 (가지치기)
        // 값은 위에서 설치한 전선의 길이, 코어의 개수를 갱신
        if(connected) {
            dfs(level+1, len + lencnt, cnt + 1);
        }
        // 그냥 구현상 ni,nj위치 조정용 더 스마트하게 짜면 필요없는 부분
        if(!checkbound(ni,nj)) {
            ni -= mi[i];
            nj -= mj[i];
        }
        // 다시 돌아가면서 설치해둔 전선 제거 (다음 dfs 돌리기 위해)
        while(ni != ci || nj != cj) {
            map[ni][nj] = 0;
            ni -= mi[i];
            nj -= mj[i];
        }
    }
    // 아무 전선을 설치하지 않는 경우의 dfs 탐색
    dfs(level+1, len, cnt);
}

int main() {
    cin >> T;
    for(int tc{1}; tc <= T; tc++) {
        cin >> N;
        vec.clear();
        // 가장자리에 있어서 신경 쓸 필요 없는 코어 세기
        int defcnt = 0;
        // 코어의 최대 개수 세기
        maxcore = 0;
        ans = 1e9;

        // 이중for문으로 탐색하면서 코어의 위치 파악
        // 가장자리의 코어면 개수만 체크
        // 가장자리가 아닌 코어면 좌표값을 벡터에 저장
        for(int i{0}; i < N; i++) {
            for(int j{0}; j < N; j++) {
                cin >> map[i][j];
                if(map[i][j] == 1) {
                    if(checkborder(i,j)) {
                        defcnt++;
                    }
                    else
                        vec.push_back({i,j});
                }
            }
        }

        // dfs를 통해 탐색 시작
        dfs(0,0,defcnt);
        cout << '#' << tc << ' ' << ans << endl;
    }
}