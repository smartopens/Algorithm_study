#include <iostream>

using namespace std;

int T,K,ans;
// gn은 회전시키려는 자석의 번호,  dir은 회전방향
int gn, dir;
// gear는 자석의 자성 정보 저장
// 단, gear 8칸에 배열이니까 따로 리스트를 만들어줄게 아닌 한 해당 배열의 숫자를 직접 이동시키는 것은 낭비이다.
int gear[5][8];
// 따라서, 해당 배열의 값을 이동시키기 보다는 직접적으로 사용되는 세개의 위치 값만 변화시키는 방향으로 구현
struct state {
    // ap는 빨간 화살표가 가리키는 index, lc는 왼쪽 자석과 붙어있는 값을 가리키는 인덱스, rc는 오른쪽 자석과 붙어있는 값을 가리키는 인덱스
    int ap = 0;
    int lc = 6;
    int rc = 2;
};
// 위의 정보를 저장할 gs배열
state gs[5];
// 각 자석들의 이번 회전정보를 저장할 rot 배열
int rot[5];

int main() {
    cin >> T;
    for(int tc = 1; tc <= T; tc++) {
        // 초기화 및 입력
        ans = 0;
        cin >> K;
        for(int i = 1; i <= 4; i++) {
            for(int j = 0; j < 8; j++) {
                cin >> gear[i][j];
            }
            gs[i] = {0,6,2};
        }

        // 회전 시작
        for(int i = 1; i <= K; i++) {
            // 먼저, 이번 턴의 회전정보를 저장할 rot 배열 초기화
            for(int j = 1; j <= 4; j++) {
                rot[j] = 0;
            }
            // 회전 시키는 기준이 되는 자석 정보 입력
            cin >> gn >> dir;
            // 그 정보 저장
            rot[gn] = dir;

            // 이제 기준이 되는 자석으로부터 오른쪽, 왼쪽으로 이동하면서 다른 자석이 회전할지 안 할지를 판단하고 정보를 저장할 예정
            int cn = gn;
            // 우선 오른쪽으로
            while(cn < 4) {
                // 현재 자석과 오른쪽 자석이 서로 붙어 있는 날의 자성이 다른 경우
                if(gear[cn][gs[cn].rc] != gear[cn+1][gs[cn+1].lc]) {
                    // 현재 자석의 회전방향과 반대방향으로 회전함을 저장
                    rot[cn+1] = -rot[cn];
                }
                // 같은 경우는 오른쪽 자석은 회전 안 하므로 더 오른쪽 자석들까진 볼 필요가 없다.
                else {
                    break;
                }
                cn++;
            }
            // 다음은 왼쪽으로 마찬가지
            cn = gn;
            while(cn > 1) {
                if(gear[cn][gs[cn].lc] != gear[cn-1][gs[cn-1].rc]) {
                    rot[cn-1] = -rot[cn];
                }
                else {
                    break;
                }
                cn--;
            }

            // 모든 자석이 이번턴에 어떻게 회전할지를 정했으므로 이를 가지고 빨간화살표와 왼쪽 오른쪽 날의 위치를 갱신
            for(int j = 1; j <= 4; j++) {
                // 자석의 날은 0~7 위치이므로 +8 해주고 8로 나머지를 찾으면
                // 계산결과 -1로 내려가면 자동으로 7 index로
                // 계산결과 8로 올라가버리면 자동으로 0 index로 저장
                gs[j].ap = (gs[j].ap - rot[j] + 8) % 8;
                gs[j].lc = (gs[j].lc - rot[j] + 8) % 8;
                gs[j].rc = (gs[j].rc - rot[j] + 8) % 8;
            }
        }
        // 마지막으로 점수계산 i번 자석의 빨간 화살표가 가리키는 정보가 S이면 2^(i-1)만큼 점수 증가
        int d = 1;
        for(int i = 1; i <= 4; i++) {
            ans += gear[i][gs[i].ap] * d;
            d *= 2; 
        }
        // 출력
        cout << "#" << tc << " " << ans << endl;
    }
}