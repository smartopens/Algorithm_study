#include <iostream>
#include <algorithm>
 
using namespace std;
 
// 연산자를 기준으로 dfs를 돌리면 가능한 모든 수식을 탐색 가능

int T, N, maxres, minres;
int card[13];
// 최대 사용가능한 연산자의 개수가 정해져 있기 때문에 이를 저장하기 위한 배열
int oper[4];
 
void dfs(int level, long long result) {
    if(level == N) {
        // 수식이 완성되면 비교를 통해 최댓값과 최솟값을 찾기
        if(result < minres) {
            minres = result;
        }
        if(result > maxres) {
            maxres = result;
        }
        return;
    }
    // 더하기
    if(oper[0] > 0) {
        oper[0]--;
        dfs(level+1,result + card[level]);
        oper[0]++; // 백트래킹 돌아올 때 사용햇던 연산자 반납하기
    }
    // 빼기
    if(oper[1]) {
        oper[1]--;
        dfs(level+1,result - card[level]);
        oper[1]++;
    }
    //곱하기
    if(oper[2]) {
        oper[2]--;
        dfs(level+1,result * card[level]);
        oper[2]++;
    }
    // 나누기
    if(oper[3]) {
        oper[3]--;
        dfs(level+1,result / card[level]);
        oper[3]++;
    }
}
 
int main() {
    cin.tie(NULL);
    ios::sync_with_stdio(false);
    cin >> T;
    for(int tc = 1; tc <= T; tc++) {
        cin >> N;
        for(int i{0}; i < 4; i++) {
            cin >> oper[i];
        }
        for(int i{0}; i < N; i++) {
            cin >> card[i]; 
        }
        maxres = -1e9;
        minres = 1e9;
        dfs(1,card[0]); 
        cout << "#" << tc << ' ' << maxres - minres << endl;
    }
}