#include <iostream>
#include <vector>
#include <deque>
#include <algorithm>

using namespace std;

//추천받으면 반드시 게시
//자리 없으면 추천 적은 횟수 삭제 후 새롭게 추가 
//중복되는 추천횟수 적은 사람 2명이면 오래된 사람 삭제
//추천 +1 
//삭제되면 추천 횟수 0으로 변함 

vector<pair<int,int>> cand; //시간에 따라 사진틀에 있는 후보 번호 목록
vector<int> cnt; //시간에 따라 추천받은 후보들의 추천횟수
void find(int n, int num, deque<pair<int,int>> student) {
	
	
	while (!student.empty()) {
		pair<int, int> tmp = student.front();
		student.pop_front(); //추천목록에서 뺴고 사진틀에 추가하기
		cnt[tmp.second]++; //추천횟수 증가
	
		cout << '\n';
		for (int i = 0; i < cand.size(); i++) { //사진틀에 있는 후보들 중에서 
			//이미 사진틀에 있으면 추천수 +1 하고 나감
			if (cand[i].second == tmp.second) {
				cnt[cand[i].second]++;

			}

		}
		
		if (cand.size() < n) {//사진틀에 있는 수가 n보다 작으면

			cand.push_back({ tmp.first,tmp.second });//바로 추가하기
		}
		else if (cand.size() == n) {//n과 같으면 
			//추천 횟수 적은 사람 -> 오래된 사람 순으로 삭제후 추가해주기
			int min_cnt = 10000000;
			int min_flag = 10000000;
			for (int i = 0; i < cand.size(); i++) { //사진틀에 있는 후보들 중에서 
				
				if (cnt[cand[i].first] < min_cnt ) { //추천횟수 적은순, 인덱스 앞일수록 오래된 사람
					min_cnt = cnt[cand[i].first]; //추천횟수 작은 수
					min_flag = i;//추천횟수 가장 작은 인덱스
					//cout << "min:" << min_flag;
				}
				else if (cnt[cand[i].first] == min_cnt) {//추천횟수가 같으면 
					if (cand[i].second < min_flag) {//인덱스가 오래된(수가 높은)것 선택하기
						min_flag = cand[i].second;
					}
				}

			}
			
			cnt[cand[min_flag].first] = 0; //삭제되므로 0으로 추천수 바꿔주고 
			cand[min_flag] = tmp;// 해당 자리에 tmp 추가하기
		

		}
		for (int i = 0; i < cand.size(); i++) {
			cout << cand[i].second << ' ';
		}





	}
}


int main() {

	int n; //사진틀의 갯수
	int num;//총 추천 횟수
	deque<pair<int,int>> student; //추천 받은 학생 번호
	int s;
	cin >> n;
	cin >> num;
	cnt.assign(num + 1, 0);
	while (num--) {
		cin >> s;
		student.push_back({ num,s }); //입력에 빠를수록 오래됨 
	}

	find(n, num, student);

	sort(cand.begin(), cand.end()); //정렬하기 
	for (int i = 0; i < cand.size(); i++) {
		cout << cand[i].second << ' ';
	}


}
