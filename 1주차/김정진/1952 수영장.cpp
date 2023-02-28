#include <iostream>
 
using namespace std;
 
int T, ans;
int odc,omc,tmc,oyc; // odc = 1일 이용권, omc = 1달 이용권, tmc = 3달 이용권, oyc = 1년 이용권
int plan[12];
 
void dfs(int month, int cost) {
    // 1년이 지나고 비용과 기존의 최댓값과의 비교
    // 3달 이용권이 있기 때문에 >= 으로 범위 잡기
    if(month >= 12) {
        if(cost < ans) {
            ans = cost;
        }
        return;
    }
    // 이번달에 1일 이용권을 산 경우
    // 해당 달의 수영장을 이용한 날의 수를 곱해서 저번달까지의 비용과 합치기
    int ncost = cost + odc * plan[month];
    if(ncost < ans) // ans보다 비용이 커지면 더 검색할 필요가 없으므로 가지치기
        dfs(month+1,ncost);
    
    // 이번달에 1달 이용권을 산 경우
    ncost = cost + omc;
    if(ncost < ans) // 가지치기
        dfs(month+1,ncost);

    // 이번달에 3달 이용권을 산 경우
    ncost = cost + tmc;
    if(ncost < ans) // 가지치기
        dfs(month+3,ncost); // 3달 이용권이므로 month도 3 증가
}
 
int main() {
    cin.tie(NULL);
    ios::sync_with_stdio(false);
    cin >> T;
    for(int tc = 1; tc <= T; tc++) {
        cin >> odc >> omc >> tmc >> oyc;
        for(int i{0}; i < 12; i++) {
            cin >> plan[i];
        }
        // 어차피 한 번 사면 갱신 필요 없는 1년 이용권을 디폴트 값으로
        ans = oyc;
        dfs(0,0); 
        cout << "#" << tc << ' ' << ans << endl;
    }
}