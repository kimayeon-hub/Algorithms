#include<iostream>
#include<fstream>
#include<vector>
#include<algorithm>
using namespace std;

int n;
vector<pair<int, int>> points;

void read_file(string filename) {
	ifstream infile(filename);
	infile >> n;
	for (int i = 0; i < n; i++) {
		pair<int, int> p;
		infile >> p.first >> p.second;
		points.push_back(p);
	}
	infile.close();
}

vector<pair<int, int>>::iterator find_rightmost_it(vector<pair<int, int>> &vec) {	// 간접참조해서 그 벡터의 iterator를 사용해야 함 (간접 참조 안 하고 하면 복사된 벡터의 iterator로 일을 하는 것임)
	auto rightmost_it = vec.begin();
	for (auto it = vec.begin() + 1; it < vec.end(); it++)
		if (it->first > rightmost_it->first)
			rightmost_it = it;
	return rightmost_it;
}

vector<pair<int, int>>::iterator find_leftmost_it(vector<pair<int, int>> &vec) {
	auto leftmost_it = vec.begin();
	for (auto it = vec.begin() + 1; it < vec.end(); it++)
		if (it->first < leftmost_it->first)
			leftmost_it = it;
	return leftmost_it;
}

bool is_right_turn(pair<int, int> p0, pair<int, int> p1, pair<int, int> p2) {	// p0 -> p1 -> p2가 우회전인지
	return (p1.first - p0.first) * (p2.second - p0.second) - (p2.first - p0.first) * (p1.second - p0.second) < 0;
}

bool is_upper_tangent_line(pair<int, int> p0, pair<int, int> p1, pair<int, int> p2, pair<int, int> p3) {
	return !is_right_turn(p2, p1, p0) &&	// p2 -> p1 -> p0가 좌회전이고
			is_right_turn(p1, p2, p3);		// p1 -> p2 -> p3가 우회전이면 tangent line을 찾은 것

}

bool is_lower_tangent_line(pair<int, int> p0, pair<int, int> p1, pair<int, int> p2, pair<int, int> p3) {
	return is_right_turn(p2, p1, p0) &&	// p2 -> p1 -> p0가 우회전이고
		!is_right_turn(p1, p2, p3);		// p1 -> p2 -> p3가 좌회전이면 tangent line을 찾은 것

}

vector<pair<int, int>> find_convex_hull(int start, int end) {
	if (end - start == 1) {	// 점이 2개 있을 때부터 시계방향으로 convex hull을 return할 수 있음
		return vector<pair<int, int>> {points[start], points[end]};
	}

	if (end - start == 2) {
		if (points[start + 1].second > points[end].second)
			return vector<pair<int, int>> {points[start], points[start + 1], points[end]};
		else
			return  vector<pair<int, int>> {points[start], points[end], points[start + 1]};
	}

	// 분할 및 정복
	int middle = (start + end) / 2;
	vector<pair<int, int>> left = find_convex_hull(start, middle);
	vector<pair<int, int>> right = find_convex_hull(middle + 1, end);

	// 합병
	// upper tangent line 찾기
	auto q_it = find_rightmost_it(left);
	auto p_it = find_leftmost_it(right);
	auto r_it = q_it != left.begin() ? q_it - 1 : left.end() - 1;
	auto s_it = p_it != right.end() - 1 ? p_it + 1: right.begin();

	while (!is_upper_tangent_line(*r_it, *q_it, *p_it, *s_it)) {
		while (is_right_turn(*p_it, *q_it, *r_it)) {	// 왼쪽 convex hull에 대해 p -> q -> r이 우회전일 때까지 반복
			q_it = r_it;
			r_it = q_it != left.begin() ? q_it - 1 : left.end() - 1;
		}

		while (!is_right_turn(*q_it, *p_it, *s_it)) {	// 오른쪽 convex hull에 대해 q -> p -> s가 좌회전일 때까지 반복
			p_it = s_it;
			s_it = p_it != right.end() - 1 ? p_it + 1 : right.begin();
		}
	}
	auto u_it = q_it, v_it = p_it;

	// lower tangent line 찾기 (upper에서 좌우, 방향만 반대로 바꾸면 됨)
	q_it = find_rightmost_it(left);
	p_it = find_leftmost_it(right);
	r_it = q_it != left.end() - 1 ? q_it + 1 : left.begin();
	s_it = p_it != right.begin() ? p_it - 1 : right.end() - 1;
	
	while (!is_lower_tangent_line(*r_it, *q_it, *p_it, *s_it)) {
		while (!is_right_turn(*p_it, *q_it, *r_it)) {	// 왼쪽 convex hull에 대해 p -> q -> r이 좌회전일 때까지 반복
			q_it = r_it;
			r_it = q_it != left.end() - 1 ? q_it + 1 : left.begin();
		}

		while (is_right_turn(*q_it, *p_it, *s_it)) {	// 오른쪽 convex hull에 대해 q -> p -> s가 우회전일 때까지 반복
			p_it = s_it;
			s_it = p_it != right.begin() ? p_it - 1 : right.end() - 1;
		}
	}
	auto x_it = q_it, y_it = p_it;


	vector<pair<int, int>> convex_hull;
	
	// 왼쪽 convex hull에서 x에서 u까지의 점 넣기
	while (x_it != u_it) {
		convex_hull.push_back(*x_it);
		x_it = x_it != left.end() - 1 ? x_it + 1 : left.begin();
	}
	convex_hull.push_back(*u_it);

	// 오른쪽 convex hull에서 v에서 y까지의 점 넣기
	while (v_it != y_it) {
		convex_hull.push_back(*v_it);
		v_it = v_it != right.end() - 1 ? v_it + 1 : right.begin();
	}
	convex_hull.push_back(*y_it);

	return convex_hull;
}

int main() {
	read_file("input.txt");

	// x 좌표 순으로 정렬
	sort(points.begin(), points.end(), [](pair<int, int> a, pair<int, int> b) {return a.first < b.first; });

	vector<pair<int,int>> convex_hull = find_convex_hull(0, n - 1);

	for (auto p : convex_hull)
		cout << p.first << " " << p.second << endl;

	return 0;
}