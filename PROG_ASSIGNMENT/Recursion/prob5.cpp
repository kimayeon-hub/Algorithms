#include<iostream>
#include<fstream>
#include<queue>
using namespace std;

const int MAX = 20;

const int PATH = 0;
const int WALL = 1;

int offset[4][2] = { {-1, 0}, {0, 1}, {1, 0}, {0, -1} };

int N, maze[MAX][MAX], k;

void read_maze(string filename) {
	ifstream mazefile(filename);
	mazefile >> N;
	for (int x = 0; x < N; x++)
		for (int y = 0; y < N; y++)
			mazefile >> maze[x][y];
	mazefile >> k;
	mazefile.close();
}

bool is_movable(int x, int y, int dir, int i) {
	int next_x = x + offset[dir][0] * i;
	int next_y = y + offset[dir][1] * i;
	return 0 <= next_x && next_x < N && 0 <= next_y && next_y < N && maze[next_x][next_y] != WALL;
}

pair<int, int> move(int x, int y, int dir, int i) {
	pair<int, int> pos;
	pos.first = x + offset[dir][0] * i;
	pos.second = y + offset[dir][1] * i;
	return pos;
}

int find_min_restCount() {
	queue<pair<int, int>> que;
	pair<int, int> cur(0, 0);
	que.push(cur);
	maze[cur.first][cur.second] = -1;

	while (!que.empty()) {
		cur = que.front();
		que.pop();

		if (cur.first == N - 1 && cur.second == N - 1)
			return abs(maze[cur.first][cur.second]) - 1;

		for (int dir = 0; dir < 4; dir++)
			for (int i = 1; i <= k; i++) {
				if (is_movable(cur.first, cur.second, dir, i)) {
					pair<int, int> next_pos = move(cur.first, cur.second, dir, i);
					if (maze[next_pos.first][next_pos.second] == PATH) {
						que.push(next_pos);
						maze[next_pos.first][next_pos.second] = maze[cur.first][cur.second] - 1;
					}
				}
				else
					break;
			}
	}
	return -1;
}

int main() {
	read_maze("maze.txt");

	cout << find_min_restCount();

	return 0;
}