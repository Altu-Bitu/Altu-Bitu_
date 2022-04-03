#include <iostream>
#include <vector>
#include <queue>
#include <cmath>

using namespace std;
const double INF = 1e3; //최댓값
typedef pair<double, int> ci; //pair형 자료구조 

double prim(int v, int start, vector<vector<ci>> &graph) {
    double sum = 0; //0부터 시작
    vector<double> dist(v, INF); //각 정점까지의 비용
    vector<bool> visited(v, false); //정점 방문 여부
    priority_queue<ci, vector<ci>, greater<>> pq; //우선 순위 큐 

    //초기화
    dist[start] = 0;
    pq.push({0, start}); //큐에 시작점 넣기
    while (!pq.empty()) { //큐가 빌때까지 계속
        double weight = pq.top().first; //간선 가중치
        int node = pq.top().second; //현재 정점
        pq.pop();//큐에서 꺼내기 

        if (visited[node]) //이미 확인했던 정점
            continue; //계속하기 
        sum += weight; //MST 간선 가중치 총합
        visited[node] = true; //방문 처리

        for (int i = 0; i < graph[node].size(); i++) { //연결된 모든 점 탐색
            double next_weight = graph[node][i].first;//다음 가중치 
            int next_node = graph[node][i].second;//다음 정점
            if (!visited[next_node] && next_weight < dist[next_node]) { //미방문 정점이면서 더 짧은 간선을 통해 갈 수 있다면
                dist[next_node] = next_weight; //갱신
                pq.push({dist[next_node], next_node});//큐에 넣기
            }
        }
    }
    return sum; //최종값 리턴
}

int main() {
    int n; //별의 갯수 n

    //입력
    cin >> n;
    vector<pair<double, double>> stars(n); //별의 갯수 n만큼 생성
    vector<vector<ci>> graph(n, vector<ci>(0)); //그래프
    for (int i = 0; i < n; i++) //n개 입력받기
        cin >> stars[i].first >> stars[i].second; //좌표

    //연산
    //임의의 두 별에 대한 거리(간선) 모두 구하기
    for (int i = 0; i < n - 1; i++) {//좌표1
        for (int j = i + 1; j < n; j++) {//좌표2
            double xd = stars[i].first - stars[j].first; //x좌표 차이
            double yd = stars[i].second - stars[j].second;//y좌표 차이
            double dist = sqrt(xd * xd + yd * yd); //거리 구하기
            graph[i].emplace_back(dist, j); //거리 저장하기 
            graph[j].emplace_back(dist, i); //거리 저장하기 
        }
    }

    //연산 & 출력
    cout << fixed;
    cout.precision(2); //소숫점 2자리로 고정
    cout << prim(n, 1, graph); //별자리 최소 비용 구하기
}
