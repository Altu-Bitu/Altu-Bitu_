#include <iostream>
#include <vector>
#include <tuple>
#include <queue>

using namespace std;
typedef tuple<int, int, int> tp; //튜플 자료구조

vector<int> parent; //부모 탐색

//Find 연산
int findParent(int node) {
    if (parent[node] < 0) //값이 음수면 루트 정점
        return node; //노드 리턴
    return parent[node] = findParent(parent[node]); //그래프 압축하며 루트 정점 찾기
}

//Union 연산
bool unionInput(int x, int y) { //유니온
    int xp = findParent(x);//x에 대하여 탐색
    int yp = findParent(y);//y에 대하여 탐색

    if (xp == yp) //같은 집합에 있다면 유니온 할 수 없음
        return false;//false 리턴
    if (parent[xp] < parent[yp]) { //새로운 루트 xp
        parent[xp] += parent[yp];//갱신
        parent[yp] = xp;//갱신
    } else { //새로운 루트 yp
        parent[yp] += parent[xp]; //갱신
        parent[xp] = yp; //갱신
    }
    return true; //true 리턴 
}

long long kruskal(int v, long long tot, priority_queue<tp, vector<tp>, greater<>> &pq) {
    int cnt = 0; //0부터 시작
    long long sum = 0; //0부터 시작 

    while (cnt < v - 1) { //사용한 간선의 수가 v-1보다 적을 동안
        if (pq.empty()) //사용한 간선이 v-1개가 안됐는데 더 이상 검사할 간선이 없다면
            return -1; //-1 리턴

        int cost = get<0>(pq.top()); //비용
        int x = get<1>(pq.top()); //건물1
        int y = get<2>(pq.top()); //건물2

        pq.pop(); //큐에서 꺼내기 
        if (unionInput(x, y)) { //유니온 했다면
            cnt++; //+1 
            sum += cost; //+비용
        }
    }
    return tot - sum; //절약비용 계산한 총 비용 리턴
}

/**
 * 기본 MST 문제에서 트리를 만들 수 없는 경우(간선이 N-1개가 아닌 경우)를 고려한 문제
 *
 * 최대 비용의 범위가 약 10^6 x 10^5 이므로 long long 자료형을 써야 함
 */

int main() {
    int n, m, a, b, c; //건물의 갯수 n, 도로의 갯수 m, 건물의 번호 a,b 비용 c
    long long tot = 0;  //초기화
    priority_queue<tp, vector<tp>, greater<>> pq; //우선순위 큐 

    //입력
    cin >> n >> m;
    parent.assign(n + 1, -1); //-1로 초기화 
    while (m--) { //m개 입력
        cin >> a >> b >> c; //a-b 비용 c
        pq.push({c, a, b}); //큐에 넣기
        tot += c; //도로를 다 설치할 때 드는 비용
    }

    //연산 & 출력
    cout << kruskal(n, tot, pq);
}
