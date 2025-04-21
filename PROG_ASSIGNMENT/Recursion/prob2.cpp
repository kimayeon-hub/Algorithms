#include<iostream>
using namespace std;

const int MAX = 1000;

int Nearest(int begin, int end, int data[], int target) {
	if (begin - end == 0)	// 원소가 하나만 있는 경우
		return data[begin];
	if (begin - end == 1)	// 원소가 두 개인 경우
		return abs(data[begin] - target) < abs(data[end] - target) ? data[begin] : data[end];

	int middle = (begin + end) / 2;

	int nearest = data[middle];
	if (data[middle] < target)
		nearest = Nearest(middle + 1, end, data, target);
	else if (data[middle] > target)
		nearest = Nearest(begin, middle - 1, data, target);

	return (abs(data[middle] - target) < abs(nearest - target)) ? data[middle] : nearest;
}

int main() {
	int N, data[MAX], K;

	cin >> N;
	for (int i = 0; i < N; i++)
		cin >> data[i];
	cin >> K;

	cout << Nearest(0, N - 1, data, K);

	return 0;
}