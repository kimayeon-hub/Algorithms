#include<iostream>
using namespace std;

const int MAX = 1000;

int Rank(int n, int data[], int K) {
	if (n == 0)
		return 1;

	if (data[n - 1] < K)
		return 1 + Rank(n - 1, data, K);
	return Rank(n - 1, data, K);
}

int main() {
	int N, data[MAX], K;

	cin >> N;
	for (int i = 0; i < N; i++)
		cin >> data[i];
	cin >> K;

	cout << Rank(N, data, K);

	return 0;
}
