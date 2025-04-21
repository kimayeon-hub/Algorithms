#include<iostream>
using namespace std;

const int MAX = 16;

int N, W, weights[MAX], prices[MAX];

int calc_max_price(int current_weight, int current_price, int pos) {
	if (current_weight > W)
		return 0;
	if (pos == N - 1)
		return current_price;

	return max(calc_max_price(current_weight + weights[pos + 1], current_price + prices[pos + 1], pos + 1),
		calc_max_price(current_weight, current_price, pos + 1));
}

int main() {
	cin >> N >> W;
	for (int i = 0; i < N; i++)
		cin >> weights[i];
	for (int i = 0; i < N; i++)
		cin >> prices[i];

	cout << calc_max_price(0, 0, -1);

	return 0;
}