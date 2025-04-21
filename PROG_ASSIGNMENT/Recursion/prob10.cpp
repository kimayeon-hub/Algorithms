#include<iostream>
#include<fstream>
using namespace std;

const int MAX = 20;

int N, items_info[MAX][3], W;

void read_file(string filename) {
	ifstream infile(filename);
	infile >> N;
	for (int i = 0; i < N; i++)
		infile >> items_info[i][0] >> items_info[i][1] >> items_info[i][2];
	infile >> W;
	infile.close();
}

int calc_max_gain(int current_volume, int current_price, int current_disposal, int pos) {
	if (current_volume > W)
		return 0;

	if (pos == N - 1)
		return current_price - current_disposal;

	return max(calc_max_gain(current_volume + items_info[pos + 1][0], current_price + items_info[pos + 1][1], current_disposal, pos + 1),
		calc_max_gain(current_volume, current_price, current_disposal + items_info[pos + 1][2], pos + 1));
}

int main() {
	read_file("input10.txt");

	cout << calc_max_gain(0, 0, 0, -1);

	return 0;
}