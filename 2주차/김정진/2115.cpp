#include <iostream>

using namespace std;


int T, N, M, C;
int map[12][12];
// dfs를 위해 전역변수로
int maxprofit;

// 배열에서 가능한 ㅇ모든 위치를 조합으로 생성해서 다 최대 이윤 계산인데 이게 왜 돼죠....
// si = 처음 i, sj = 처음 j, idx는 sj에서 오른쪽으로 몇 칸 확인 중인지, res = 이윤 계산값 저장, sum = 그냥 벌꿀의 합
void dfs(int si, int sj, int idx, int res, int sum) {
    // 최대 이윤이면 갱신
    if(idx == M) {
        if(res > maxprofit) {
            maxprofit = res;
        }
        return;
    }
    int ci = si;
    int cj = sj + idx;
    int mv = map[ci][cj];
    // 최대 생산 가능한 벌꿀양을 안 넘었으면 생산하는 조합 생성
    if(sum + mv <= C) {
        dfs(si,sj,idx+1,res + mv * mv, sum + mv);
    }
    // 넘기는 경우도 ㄱㄱ
    dfs(si,sj,idx+1,res,sum);
}

int main() {
    cin >> T;
    for(int tc = 1; tc <= T; tc++) {
        cin >> N >> M >> C;
        for(int i{1}; i <= N; i++) {
            for(int j{1}; j <= N; j++) {
                cin >> map[i][j];
            }
        }
        int ans = 0;
        // 일단 1명을 기준으로 모든 좌표를 탐색하고
        for(int i{1}; i <= N; i++) {
            for(int j{1}; j <= N - M + 1; j++) {
                // maxtwo는 두명 모두의 이윤 합의 최댓값 임시 저장
                int maxtwo = 0;
                maxprofit = 0;
                dfs(i,j,0,0,0);
                // 일단 1명의 현재 위치 최대 이윤 저장
                maxtwo += maxprofit;
                maxprofit = 0;
                // 이후에는 앞선 1명이 탐색한 좌표 이후의 좌표에서 2명 째의 최대 이윤 찾기
                for(int l{j + M}; l <= N - M + 1; l++) {
                    dfs(i,l,0,0,0);
                }
                for(int k{i+1}; k <= N; k++) {
                    for(int l{1}; l <= N - M + 1; l++) {
                        dfs(k,l,0,0,0);
                    }
                }
                // 최대 이윤 저장
                maxtwo += maxprofit;
                ans = max(maxtwo,ans);
            }
        }
        cout << "#" << tc << " " << ans << endl;
    }
}