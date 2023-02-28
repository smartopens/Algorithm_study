#include <iostream>
#include <algorithm>
#include <vector>
 
using namespace std;
 
int T, N, maxres, minres, ans;
int S[18][18];
int f1, f2;
vector<int>food1;
vector<int>food2;
 
// 하나의 음식에 필요한 재료의 "모든" 시너지를 합쳐야 하는 문제
// dfs와 벡터를 사용해서 벡터에 각 음식에 필요한 재료를 N/2씩 나눠서 저장하기로 결정

void dfs(int level) {
    if(level > N) {
        int tmp = 0;

        for(int i{0}; i < food1.size(); i++) {
            for(int j{0}; j < food1.size(); j++) {
                tmp += S[food1[i]][food1[j]];
            }
        }
        for(int i{0}; i < food2.size(); i++) {
            for(int j{0}; j < food2.size(); j++) {
                tmp -= S[food2[i]][food2[j]];
            }
        }
        tmp = abs(tmp);
        if(tmp < ans) {
            ans = tmp;
        }
        return;
    }
    else {
        // N/2 씩 재료를 나누기
        if(f1 < N/2) {
            food1.push_back(level);
            f1++;
            dfs(level+1);
            f1--;
            food1.pop_back();
        }
        if(f2 < N/2) {
            food2.push_back(level);
            f2++;
            dfs(level+1);
            f2--;
            food2.pop_back();
        }
    }
     
}
 
int main() {
    cin.tie(NULL);
    ios::sync_with_stdio(false);
    cin >> T;
    for(int tc = 1; tc <= T; tc++) {
        cin >> N;
        // 각 음식에 넣기로 결정한 재료 개수
        f1 = 0;
        f2 = 0;
        // 그 재료를 담을 벡터 초기화
        food1.clear();
        food2.clear();
        for(int i{1}; i <= N; i++) {
            for(int j{1}; j <= N; j++) {
                cin >> S[i][j];
            }
        }
        ans = 1e9;
        dfs(1);
 
        cout << "#" << tc << ' ' << ans << endl;
    }
}