#include<iostream>
using namespace std;

int count_No_continuous_zero(int n, string sequence) {
	int len = sequence.length();
	if (len > 1 && sequence[len - 2] == '0' && sequence[len - 1] == '0')
		return 0;

	if (len == n)
		return 1;

	return count_No_continuous_zero(n, sequence + '0') + count_No_continuous_zero(n, sequence + '1');
}

int main() {
	int n;
	cin >> n;

	cout << count_No_continuous_zero(n, "");

	return 0;
}