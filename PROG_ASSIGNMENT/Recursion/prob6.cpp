#include<iostream>
using namespace std;

const int MAX = 20;

bool is_successful(int N, int data[], int pos) {
	if (pos == N)
		return true;
	if (data[pos] == 0)
		return false;

	for (int i = 1; i <= data[pos]; i++)
		if (is_successful(N, data, pos + i))
			return true;
	return false;
}

int main() {
	int N, data[MAX];

	cin >> N;
	for (int i = 0; i < N; i++)
		cin >> data[i];

	if (is_successful(N, data, 0))
		cout << "Yes";
	else
		cout << "No";

	return 0;
}