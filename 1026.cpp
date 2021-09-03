#include<iostream>
#include<algorithm>
#define MAX 51

using namespace std;

int a[MAX] = { 0 };
int b[MAX] = { 0 };
int main() {
	//백준 1026번
	int n;
	cin >> n;
	for (int i = 0; i < n; i++) {
		cin >> a[i];
	}
	for (int i = 0; i < n; i++) {
		cin >> b[i];
	}
	//a,b 각 인덱스의 곱의 합이 최소가 되어야 함
	sort(a,a+n);
	sort(b,b+n, greater<>());
	
	int answer = 0;
	for (int i = 0; i < n; i++) {
		answer += a[i] * b[i];
	}
	cout << answer;
}
