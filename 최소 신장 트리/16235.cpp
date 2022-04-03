#include <iostream>
#include <vector>
#include <queue>
#include <deque>
#include <tuple>
#include <algorithm>

using namespace std;
typedef vector<vector<int>> matrix; //배열 
typedef tuple<int, int, int> tp; //튜플 

queue<tp> spring(matrix &land, deque<tp> &tree, queue<pair<int, int>> &breeding_tree) { //봄 
    queue<tp> dead_tree; //죽은 나무
    int size = tree.size(); //나무 갯수 
    while (size--) { //모든 나무 검사
        int age = get<0>(tree.front()); //나이
        int row = get<1>(tree.front()); //행
        int col = get<2>(tree.front()); //열
        tree.pop_front();

        if (land[row][col] < age) { //자신의 나이만큼 양분을 먹을 수 없다면
            dead_tree.push({age, row, col}); //나무정보를 죽은 나무에 저장
            continue;//계속
        }
        land[row][col] -= age; //그 외에는 자신의 나이만큼 양분 먹기
        tree.emplace_back(age + 1, row, col); //나이+1
        if ((age + 1) % 5 == 0) //나이가 5의 배수라면
            breeding_tree.push({row, col}); //번식할 나무에 추가
    }
    return dead_tree; //죽은 나무 
}

void summer(queue<tp> &dead_tree, matrix &land) { //여름 
    while (!dead_tree.empty()) { //나무 없을때까지 계속
        int age = get<0>(dead_tree.front()); //죽은 나무의 나이
        int row = get<1>(dead_tree.front()); //죽은 나무의 행 위치
        int col = get<2>(dead_tree.front()); //죽은 나무의 열 위치
        dead_tree.pop(); //꺼내기 
        land[row][col] += (age / 2); //나이/2 소숫점 버려서 양분 추가 
    }
}

void fall(int n, deque<tp> &tree, queue<pair<int, int>> &breeding_tree) { //가을
    int dr[8] = {-1, 1, 0, 0, -1, -1, 1, 1}; //행
    int dc[8] = {0, 0, -1, 1, -1, 1, -1, 1};//열

    while (!breeding_tree.empty()) { //나무 없을때까지 계속하기 
        int row = breeding_tree.front().first; //번식할 나무의 행
        int col = breeding_tree.front().second; //번식할 나무의 열
        breeding_tree.pop(); //꺼내기 

        for (int j = 0; j < 8; j++) { //주변 탐색
            int nr = row + dr[j]; //행
            int nc = col + dc[j];//열
            if (nr < 0 || nr >= n || nc < 0 || nc >= n) //범위 내에 없으면
                continue; //다음
            tree.push_front({1, nr, nc}); //새로 생긴 나무
        }
    }
}

void winter(int n, matrix &a, matrix &land) {//겨울
    for (int i = 0; i < n; i++) //nx
        for (int j = 0; j < n; j++)//n의 장소에
            land[i][j] += a[i][j];//양분주기
}

/**
 * [문제 설명] - 단순 구현 문제
 * 봄: 하나의 칸마다 나이가 어린 나무부터 자신의 나이만큼 양분을 먹고, 나이가 1 증가함
 *    각 칸에 양분이 부족해 자신의 나이만큼 양분을 못 먹는 나무는 즉시 죽음
 * 여름: 봄에 죽은 나무가 양분으로 변함. 죽은 나무마다 나이를 2로 나눈 값이 양분으로 추가 (소수점 버림)
 * 가을: 나이가 5의 배수인 나무가 번식. 인접한 8개 칸에 나이가 1인 나무가 생김
 * 겨울: 로봇(S2D2)이 땅을 돌아다니면서 A[r][c]만큼 각 칸에 양분 추가
 *
 * K년이 지난 후 상도의 땅에 살아있는 나무의 개수
 *
 * [문제 풀이]
 * a: 로봇(S2D2)가 겨울에 주는 양분의 양
 * land: 땅의 양분
 * breeding_tree: 나이가 5의 배수인 트리 (번식할 트리)
 * tree: 땅에 심은 나무 나이, 행, 열 정보
 * -> deque 컨테이너를 활용해 번식한 나무를 앞에 넣어주면 입력 후에만 정렬해서 사용 가능
 *
 * 문제의 설명대로 계절별 연산을 진행
 */

int main() {
    int n, m, k, x, y, z; //땅 크기n, 나무 갯수 m, 시간 k , (x,y) , 나무 나이 z

    //입력
    cin >> n >> m >> k;
    matrix a(n, vector<int>(n, 0)); //배열 
    matrix land(n, vector<int>(n, 5)); //처음 양분 모든 칸에 5
    queue<pair<int, int>> breeding_tree; //번식할 트리
    deque<tp> tree; //트리 정보 
    for (int i = 0; i < n; i++) //nx
        for (int j = 0; j < n; j++)//n
            cin >> a[i][j]; //양분 정보 입력
    while (m--) { //m개 입력
        cin >> x >> y >> z; //나무 정보 
        tree.emplace_back(z, x - 1, y - 1); //(0, 0)부터 시작하도록 구현하기위해 1을 빼준 인덱스에 접근
    }

    //연산
    sort(tree.begin(), tree.end()); //어린 나이 순으로 정렬
    while (k--) { //k년이 흐르는 동안
        queue<tp> dead_tree = spring(land, tree, breeding_tree); //봄이 지나고 죽은 나무
        summer(dead_tree, land); //여름에 양분이 되는 
        fall(n, tree, breeding_tree); //나무 성장
        winter(n, a, land);//로봇이 양분 줌
    }

    //출력
    cout << tree.size();
}
