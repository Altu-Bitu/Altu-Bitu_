#include <iostream>
#include <vector>

using namespace std;
const int MOD = 1e6; //나머지 계산하여 정답 출력

int cntPassword(int n, string s) { //비밀번호 갯수 카운트
    vector<int> dp(n + 1, 0); //dp
    if (s[0] == '0') //0이면
        return 0; //리턴

    dp[0] = dp[1] = 1; //s[0]의 암호 해석 경우의 수 1로 초기화
    for (int i = 2; i <= n; i++) { //2부터 n자리 수 탐색
        if (s[i - 1] == '0' && (s[i - 2] < '1' || s[i - 2] > '2'))  //암호해석 불가
            return 0;//종료

        if (s[i - 1] != '0') //0이 아니면
            dp[i] += dp[i - 1]; //이전 dp 더하기 
        if (s[i - 2] == '1' || (s[i - 1] <= '6' && s[i - 2] == '2')) //이전 이전 dp에서
            dp[i] += dp[i - 2]; //추가하기
        dp[i] %= MOD; //나눠서 정답 출력
    }
    return dp[n];
}

/**
 * dp[i] = i인덱스까지 암호 해석할 수 있는 경우의 수 저장
 * => dp[i] = dp[i-1] + dp[i-2] (단, dp[i-1]과 dp[i-2]에서 이어서 암호 만들 수 있는 경우만)
 *
 * 1. '0' 혼자는 암호 해석 불가
 * 2. 처음 시작이 '0'인 경우 주의
 * 3. 현재 수가 '0'인데 앞의 수가 '1'이나 '2'가 아닌 경우 -> 암호 해석할 수 없음
 * 4. 두 개의 수를 하나의 알파벳으로 고려할 때, 26이하의 수인지 잘 확인해야 함
 *
 * 본 풀이는 dp 배열 인덱스를 편하게 관리하기 위해 1번 인덱스부터 시작
 */

int main() {
    string s;

    //입력
    cin >> s;

    //연산 & 출력
    cout << cntPassword(s.length(), s) << '\n';
    return 0;//종료 
}
