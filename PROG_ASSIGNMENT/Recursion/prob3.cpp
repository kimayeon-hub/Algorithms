#include<iostream>
using namespace std;

const int MAX = 16;

const int PATH = 0;
const int WALL = 1;

int offset[4][2] = { {-1, 0}, { 0, 1 }, { 1, 0 }, { 0, -1 } };

int N, maze[MAX][MAX], K;

int count_routes(int x, int y) {
	if (x == 0 && y == 0)
		maze[x][y] = -1;

	if (x == N - 1 && y == N - 1 && abs(maze[x][y]) <= K + 1)
		return 1;

	if (abs(maze[x][y]) > K + 1)
		return 0;

	int Count = 0;
	for (int dir = 0; dir < 4; dir++) {
		int next_x = x + offset[dir][0];
		int next_y = y + offset[dir][1];
		if (0 <= next_x && next_x < N && 0 <= next_y && next_y < N && maze[next_x][next_y] == PATH) {
			maze[next_x][next_y] = maze[x][y] - 1;
			Count += count_routes(next_x, next_y);
			maze[next_x][next_y] = PATH;
		}
	}
	return Count;
}

int main() {
	cin >> N;
	for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++)
			cin >> maze[i][j];
	cin >> K;

	cout << count_routes(0, 0) << endl;

	return 0;
}