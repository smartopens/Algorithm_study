#include <iostream>
#include <vector>
#include <queue>

using namespace std;

// 순서대로... 순서대로 구현하자.
// 1. 접수 창구의 자리 비우기
// 2. 빈 접수 창구에 도착한 고객 접수시키기
// 3. 정비 창구의 자리 비우기
// 4. 빈 정비 창구에 접수 끝난 고객 접수시키기
// 주의점 추가: 접수 창구랑 정비 창구랑 고객 받는 우선순위가 다름!

int T,N,M,K,A,B,ans;
int a[12];
int b[12];
int tk[1002];

// 접수, 정비 창구의 상태를 저장할 구조체
struct state{
    int pnum = -1; // 창구를 이용하는 사람
    int remain = 0; // 창구 이용이 끝날때 까지 남은 시간
};
// astate는 접수 창구, bstate는 정비 창구의 상태를 저장
state astate[12];
state bstate[12];
// Avec은 A번 접수 창구를 이용한 고객 저장, Bvec은 B번 정비 창구를 이용한 고객 저장
vector<int>Avec;
vector<int>Bvec;
// 정비 창구는 접수 창구랑 대기 방식이 다르므로 정비 창구 대기자의 정보를 저장할 구조체
// 정비 창구는 언제부터 기다렸는지, 기다리기 시작한 시간이 같다면 이전 접수 창구의 번호가 적은 고객이 우선순위가 높다.
struct Pstate{
    int pnum = 0;
    int anum = 0; // 따라서, 접수창구의 번호와
    int wait_start; // 기다리기 시작한 시간을 저장

    // 그리고 이를 우선순위 큐에 넣어서 뽑아낼 예정
    bool operator < (Pstate next) const{
        if(wait_start != next.wait_start) {
            return wait_start > next.wait_start;
        }
        return anum > next.anum;
    }
};
// 모든 일정이 끝나고 어느 고객이 A번과 B번 창구를 모두 이용했는지 확인할 때 쓸 배열
int acheck[1001];
int bcheck[1001];


int main() {
    cin >> T;
    priority_queue<Pstate>pq;
    for(int tc = 1; tc <= T; tc++) {
        // 초기화 주의 선언한게 많아서 초기화도 길다.
        ans = 0;
        cin >> N >> M >> K >> A >> B;
        while(!pq.empty())pq.pop();
        Avec.clear();
        Bvec.clear();
        for(int i = 0; i < 12; i++) {
            astate[i] = {-1,0};
            bstate[i] = {-1,0};
        }
        for(int i = 0; i < 1002; i++) {
            acheck[i] = 0;
            bcheck[i] = 0;
        }
        for(int i = 1; i <= N; i++) {
            cin >> a[i];
        }
        for(int i = 1; i <= M; i++) {
            cin >> b[i];
        }
        for(int i = 1; i <= K; i++) {
            cin >> tk[i];
        }
        // cnt는 업무를 마친 고객 수, ct 는 현재 시간
        int cnt = 0;
        int ct = 0;
        // 모든 고객이 업무를 마치면 탐색 종료
        while(cnt < K) {
            // 1. 접수 창구의 자리 비우기
            for(int i = 1; i <= N; i++) {
                // 일단 접수 창구의 남은 시간 감소
                if(astate[i].remain > 0) {
                    astate[i].remain--;
                }
                // 접수 창구에 사람이 있었는데 접수가 끝났으면
                if(astate[i].pnum != -1 && astate[i].remain == 0) {
                    // 정비 창구 대기자를 담은 우선순위큐 pq에 고객 정보를 저장하고
                    pq.push({astate[i].pnum, i, ct});
                    // 접수 창구는 비우기
                    astate[i].pnum = -1;
                }
            }

            // 2. 빈 접수 창구에 도착한 고객 접수시키기
            for(int i = 1; i <= K; i++) {
                // 고객이 도착했으면
                if(tk[i] == 0) {
                    for(int j = 1; j <= N; j++) {
                        // 접수 창구가 비었는지 확인
                        if(astate[j].remain == 0 && astate[j].pnum == -1) {
                            // 빈 접수 창구에 고객 정보 저장
                            astate[j] = {i,a[j]};
                            // 빈 접수 창구가 A번 접수 창구면 Avec에 고객 번호 저장
                            if(A == j) {
                                Avec.push_back(i);
                            }
                            // 도착한 고객 처리
                            tk[i] = -1;
                            break;
                        }
                    }
                }
                // 고객이 도착할 때까지 남은 시간 감소
                if(tk[i] > 0) {
                    tk[i]--;
                }
            }

            // 3. 정비 창구의 자리 비우기
            for(int i = 1; i <= M; i++) {
                // 일단 정비 창구의 남은 시간 감소
                if(bstate[i].remain > 0) {
                    bstate[i].remain--;
                }
                // 정비 끝난 고객 아웃
                if(bstate[i].pnum != -1 && bstate[i].remain == 0) {
                    // 업무 마친 고객 수 늘리고 정비 창구는 비우기
                    cnt++;
                    bstate[i].pnum = -1;
                }
                
            }

            // 4. 빈 정비 창구에 접수 끝난 고객 접수시키기
            for(int i = 1; i <= M; i++) {
                // 빈 정비 창구가 있는지 확인
                if(bstate[i].pnum == -1 && bstate[i].remain == 0) {
                    // 대기 중인 고객 있는지 확인
                    if(pq.empty()) break;
                    // 대기 중인 고객 불러와서
                    Pstate npq = pq.top();
                    pq.pop();
                    // 빈 정비 창구로 보내기
                    bstate[i] = {npq.pnum, b[i]};
                    // 빈 정비 창구가 B번 정비 창구였으면 Bvec에 정보 저장
                    if(B == i) {
                        Bvec.push_back(npq.pnum);
                    }
                }
            }

            // 1초 증가
            ct++;
        }

        // A번 접수 창구 이용한 고객과 B번 정비 창구 이용한 고객들을 확인
        for(int i = 0; i < Avec.size(); i++) {
            acheck[Avec[i]] = 1;
        }
        for(int i = 0; i < Bvec.size(); i++) {
            bcheck[Bvec[i]] = 1;
        }

        // 둘 다 이용했으면 ans 증가
        for(int i = 1; i < 1001; i++) {
            if(acheck[i] && bcheck[i]) ans += i;
        }

        // ans가 0이면 A번 접수 창구와 B번 정비 창구를 동시에 이용한 고객이 없는 것이므로 예외처리
        if(ans == 0) ans = -1;
        cout << "#" << tc << ' ' << ans << endl;
    }
}