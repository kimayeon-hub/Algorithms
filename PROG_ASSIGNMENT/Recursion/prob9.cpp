#include<iostream>
#include<fstream>
using namespace std;

const int MAX = 16;

int N, A[MAX][MAX], k;

void read_file(string filename) {
	ifstream infile(filename);
	infile >> N;
	for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++)
			infile >> A[i][j];
	infile >> k;
	infile.close();
}

int players[MAX];

int find_max_ability(int n, int pos) {
	if (N - (pos + 1) < k - n)
		return INT_MIN;
	if (n == k) {
		int ability = 0;
		for (int i = 0; i < k; i++)
			for (int j = 0; j < k;  j++)
				ability += A[players[i]][players[j]];
		return ability;
	}

	// ���� ��ġ ���� ����� ������ �̴� ���
	players[n] = pos + 1;	// ���� ��ܿ� ������ ���� ����� ��ȣ �ֱ�
	int ability_1 = find_max_ability(n + 1, pos + 1);
	players[n] = 0;	// �ٽ� ������� ��������

	// ���� ��ġ ���� ����� ������ ���� �ʴ� ���
	int ability_2 = find_max_ability(n, pos + 1);

	return max(ability_1, ability_2);
}

int main() {
	read_file("input9.txt");

	cout << find_max_ability(0, -1);

	return 0;
}