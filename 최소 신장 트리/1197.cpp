#include <iostream>
#include <vector>
#include <tuple>
#include <queue>

using namespace std;
typedef tuple<int, int, int> tp; //튜플 형식 자료구조

vector<int> parent; //parent 탐색 벡터

//Find 연산
int findParent(int node) {
    if (parent[node] < 0) //값이 음수면 루트 정점
        return node; //노드 리턴
    return parent[node] = findParent(parent[node]); //그래프 압축하며 루트 정점 찾기
}

//Union 연산
bool unionInput(int x, int y) { //유니온
    int xp = findParent(x); //x에 대하여 부모 탐색
    int yp = findParent(y); //y에 대하여 부모 탐색

    if (xp == yp) //같은 집합에 있다면 유니온 할 수 없음
        return false; //false 리턴
    if (parent[xp] < parent[yp]) { //새로운 루트 xp
        parent[xp] += parent[yp]; //갱신
        parent[yp] = xp; //갱신
    } else { //새로운 루트 yp
        parent[yp] += parent[xp]; //갱신
        parent[xp] = yp; //갱신
    }
    return true; //true 리턴
}

//kruskal
int kruskal(int v, priority_queue<tp, vector<tp>, greater<>> &pq) {
    int cnt = 0, sum = 0; //0부터 시작

    while (cnt < v - 1) { //사용한 간선의 수가 v-1보다 작을 동안
        int weight = get<0>(pq.top());//큐 맨위의 가중치값
        int x = get<1>(pq.top());//큐 맨위의 정점
        int y = get<2>(pq.top());//큐 맨 위의 정점
        pq.pop();//큐에서 꺼내기

        if (unionInput(x, y)) { //유니온 했다면
            cnt++; //+1
            sum += weight; //가중치 더하기
        }
    }
    return sum; //최종 리턴
}

int main() {
    int v, e, a, b, c; //정점의 갯수, 간선의 갯수, a-b정점 가중치 c로 연결
    priority_queue<tp, vector<tp>, greater<>> pq; //우선순위 큐

    //입력
    cin >> v >> e;
    parent.assign(v + 1, -1); //초기값 -1
    while (e--) { //e개 입력
        cin >> a >> b >> c; //a-b정점 가중치 c
        pq.push({c, a, b}); //큐에 입력
    }

    //연산 & 출력
    cout << kruskal(v, pq);
}
