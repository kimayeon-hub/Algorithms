#include<iostream>
using namespace std;

const int MAX = 10;

const int PATH = 0;
const int WALL = 1;
const int BOMB = 2;
const int VISITED = 3;

int offset[4][2] = { {-1, 0}, {0, 1}, {1, 0}, {0, -1} };

int N, maze[MAX][MAX], K;

bool check_escape(int x, int y, int HP) {
	if (HP < 0)
		return false;
	if (x == N - 1 && y == N - 1)
		return true;

	maze[x][y] = VISITED;

	for (int dir = 0; dir < 4; dir++) {
		int next_x = x + offset[dir][0];
		int next_y = y + offset[dir][1];
		if (0 <= next_x && next_x < N && 0 <= next_y && next_y < N && 
			((maze[next_x][next_y] == PATH && check_escape(next_x, next_y, HP)) ||
			(maze[next_x][next_y] == BOMB && check_escape(next_x, next_y, HP - 1))))
			return true;
	}

	maze[x][y] = PATH;

	return false;
}

int main() {
	cin >> N;
	for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++)
			cin >> maze[i][j];
	cin >> K;

	if (check_escape(0, 0, K))
		cout << "Yes";
	else
		cout << "No";

	return 0;
}