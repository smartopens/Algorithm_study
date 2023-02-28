#include <iostream>
#include <vector>

using namespace std;

// 구현이 복잡한 문제라 천천히 하나씩 해보기
// 하나씩 차례차례 구현하다보니 구조체나 배열이 많이 늘어남

// pmax = 맵상의 사람 수
int T, N, pmax, ans;

// 사람 및 계단의 좌표를 담을 구조체
struct pos{
    int r;
    int c;
    int val; // 계단을 내려가는데 걸리는 시간을 저장할 변수, 이 코드에선 사람 용은 아님
};
// 사람의 좌표를 담는 벡터
vector<pos>P;
// 계단의 좌표를 담는 벡터
vector<pos>S;

// dfs를 통해 각 사람들이 어떤 계단을 타고 내려갈지 모든 조합을 찾아볼 예정
// 계단은 무조건 2개, 사람은 최대 10명 --> 1024가짓수
// A와 B는 각각의 계단에 내려갈 사람을 저장할 벡터
vector<int>A;
vector<int>B;

// 계단을 내려가는 사람들의 상태를 저장할 구조체
struct state{
    int Pnum; // 내려가는 사람이 누구인지
    int lt; // 계단 내려가는데 남은 시간
};

// 각 사람별 계단까지의 거리를 담을 배열
int dist[12];

// 각 계단을 내려가는 사람의 상태를 저장할 배열
state Astair[3];
state Bstair[3];

// dfs를 통해 각 계단을 내려갈 사람의 조합을 찾고 나서 이를 통해 답을 찾는 함수
void findAns() {
    // 탈출한 사람의 수
    int escape = 0;

    // A 계단을 내려갈 사람들이 계단까지 도착하는데 걸리는 시간을 초기화
    for(int i{0}; i < A.size(); i++) {
        int cn = A[i];
        dist[cn] = abs(P[cn].r - S[0].r) + abs(P[cn].c - S[0].c);
    }

    // B 계단을 내려갈 사람들이 계단까지 도착하는데 걸리는 시간을 초기화
    for(int i{0}; i < B.size(); i++) {
        int cn = B[i];
        dist[cn] = abs(P[cn].r - S[1].r) + abs(P[cn].c - S[1].c);
    }

    // 각 계단의 상태 초기화
    for(int i{0}; i < 3; i++) {
        Astair[i] = {-1,-1};
        Bstair[i] = {-1,-1};
    }

    // 시간 측정
    int curt = 1;

    // 모두 탈출할 때 까지 while문
    while(escape < pmax) {
        // 각 계단을 내려가는 사람들의 정보 갱신
        for(int i{0}; i < 3; i++) {
            // A 계단에 내려가는 사람을 확인하고
            if(Astair[i].Pnum != -1) {
                // 내려가는데 남은 시간 1초 감소
                Astair[i].lt--;
                // 다 내려왔으면
                if(Astair[i].lt == 0) {
                    // 탈출한 사람 수 증가
                    escape++;
                    // 이건 그냥 상태 갱신용 한 줄, 이 코드에선 없어도 되는 줄
                    dist[Astair[i].Pnum] = -2;
                    // 계단에 자리 비었음
                    Astair[i] = {-1,-1};
                }
            }
            // B 계단도 마찬가지
            if(Bstair[i].Pnum != -1) {
                Bstair[i].lt--;
                if(Bstair[i].lt == 0) {
                    escape++;
                    dist[Bstair[i].Pnum] = -2;
                    Bstair[i] = {-1,-1};
                }
            }
        }
        
        // A계단으로 내려갈 사람들 계단으로 이동시키기
        for(int i{0}; i < A.size(); i++) {
            // 아직 도착 못 했으면 계단까지 남은 시간 감소
            if(dist[A[i]] > 0) {
                dist[A[i]]--;
            }
            // 도착했으면 계단 정보에 저장
            if(dist[A[i]] == 0) {
                for(int j{0}; j < 3; j++) {
                    // 계단에 자리가 비었는지 확인!
                    if(Astair[j].Pnum == -1) {
                        Astair[j] = {A[i],S[0].val};
                        // 거리를 -1로 바꿔줘야 빈 자리에 중복으로 같은 사람이 들어갈 일 없게 됨
                        dist[A[i]] = -1;
                        break;
                    }
                }
            }
        }
        // B계단도 마찬가지!
        for(int i{0}; i < B.size(); i++) {
            if(dist[B[i]] > 0) {
                dist[B[i]]--;
            }
            if(dist[B[i]] == 0) {
                for(int j{0}; j < 3; j++) {
                    if(Bstair[j].Pnum == -1) {
                        Bstair[j] = {B[i],S[1].val};
                        dist[B[i]] = -1;
                        break;
                    }
                }
            }
        }
        // 시간 갱신
        curt++;
    }

    // 최소가 되는 탈출 시간 확인
    ans = min(ans, curt);
}

// dfs로 각 계단에 내려갈 사람들의 조합을 찾는 함수
void dfs(int level) {
    // 모든 사람을 각 계단에 할당했으면 정답 찾기
    if(level == P.size()) {
        findAns();
        return;
    }
    // A 계단으로 보내보고
    A.push_back(level);
    dfs(level+1);
    A.pop_back();

    // B 계단으로도 보내보기
    B.push_back(level);
    dfs(level+1);
    B.pop_back();
}

// 메인 함수
int main() {
    cin >> T;
    for(int tc = 1; tc <= T; tc++) {
        // 전역변수 초기화 필수
        pmax = 0;
        ans = 1e9;
        cin >> N;
        P.clear();
        S.clear();

        // 맵 저보 갱신하면서
        for(int i{1}; i <= N; i++) {
            for(int j{1}; j <= N; j++) {
                cin >> M;
                // 사람이면 사람 정보 갱신
                if(M == 1) {
                    pmax++;
                    P.push_back({i,j, 0});
                }
                // 계단이면 계단 정보 갱신
                else if (M >= 2) {
                    S.push_back({i,j, M});
                }
            }
        }
        dfs(0);
        cout << '#' << tc << ' ' << ans << endl;
    }
}