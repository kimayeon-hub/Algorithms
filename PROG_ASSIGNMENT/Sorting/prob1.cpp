#include<iostream>
#include<fstream>
#include<ctime>	// 코드의 실행시간을 측정하기 위한 라이브러리
#include<stack> // quick sort 구현할 때 stack overflow가 발생해서 stack을 만들어서 사용
#include<algorithm>	// c++ 표준 라이브러리가 제공하는 정렬 알고리즘을 사용하기 위해
using namespace std;

const int MAX = 125553;

string words[MAX];

void read_file(string filename) {
	ifstream infile(filename);
	string str;
	int i = 0;
	while (infile >> words[i])
		i++;
	infile.close();
}

double measure_bubble_sort() {
	double start = clock();

	for (int i = MAX - 1; i > 0; i--)
		for (int j = 0; j < i; j++)
			if (words[j] > words[j + 1]) {
				string tmp = words[j];
				words[j] = words[j + 1];
				words[j + 1] = tmp;
			}

	double finish = clock();

	return (finish - start) / CLOCKS_PER_SEC;
}

double measure_insertion_sort() {
	double start = clock();

	for (int i = 1; i < MAX; i++) {
		int insert_index = i;
		string tmp = words[i];
		while (insert_index > 0 && tmp < words[insert_index - 1]) {
			words[insert_index] = words[insert_index - 1];
			insert_index--;
		}
		words[insert_index] = tmp;
	}

	double finish = clock();

	return (finish - start) / CLOCKS_PER_SEC;
}

string sorted[MAX];	// merge sort를 통해 정렬한 데이터를 저장할 배열

void merge(int start, int middle, int end) {	// index가 start ~ middle, middle + 1 ~ end인 두 배열을 merge하는 함수
	int i = start, j = middle + 1, k = start;
	while (i < middle + 1 && j < end + 1) {
		if (words[i] < words[j])
			sorted[k++] = words[i++];
		else if (words[j] < words[i])
			sorted[k++] = words[j++];
		else {
			sorted[k++] = words[i++];
			sorted[k++] = words[j++];
 		}
	}
	if (i < middle + 1)
		while (i < middle + 1)
			sorted[k++] = words[i++];
	else if (j < end + 1)
		while (j < end + 1)
			sorted[k++] = words[j++];

	// start ~ end까지 정렬한 값을 배열 words에 넣기
	for (int i = start; i <= end; i++)
		words[i] = sorted[i];
}

void merge_sort(int start, int end) {
	if (start >= end)
		return;

	int middle = (start + end) / 2;
	merge_sort(start, middle);
	merge_sort(middle + 1, end);
	merge(start, middle, end);
}

double measure_merge_sort() {
	double start = clock();

	merge_sort(0, MAX - 1);

	double finish = clock();

	return (finish - start) / CLOCKS_PER_SEC;
}

void quick_sort(int start, int end) {
	stack<pair<int, int>> s;
	pair<int, int> cur(start, end);
	s.push(cur);

	while (!s.empty()) {	// 스택이 빌 때 동안 반복
		cur = s.top();
		s.pop();

		start = cur.first, end = cur.second;
		
		if (start > end)
			continue;

		string pivot = words[end];

		// partition
		int i = start - 1;	// i: pivot보다 작은 값의 마지막 인덱스
		for (int j = start; j < end; j++)
			if (words[j] < pivot) {
				string tmp = words[++i];
				words[i] = words[j];
				words[j] = tmp;
			}
		words[end] = words[++i];
		words[i] = pivot;

		s.push(pair<int, int> (start, i - 1));
		s.push(pair<int, int> (i + 1, end));
	}
}

double measure_quick_sort() {
	double start = clock();

	quick_sort(0, MAX - 1);

	double finish = clock();

	return (finish - start) / CLOCKS_PER_SEC;
}

void max_heapify(int i, int n) {	// i번째 노드를 root로 하고, 마지막 노드의 번호가 n인 서브트리를 heapify하는 함수
	// n 번째 노드의 자식 노드가 없음 (leaf 노드)
	if (2 * i > n)	// n은 전체 노드의 개수
		return;

	int k;	// i번째 노드의 자식 노드 중 큰 값의 노드 번호
	if (2 * i + 1 > n || // 자식이 1명인 경우 (왼쪽 자식만 있는 경우)
		(2 * i + 1 <= n && words[2 * i - 1] > words[2 * i])) // 자식이 2명인데 왼쪽 자식이 더 큰 경우
		k = 2 * i;
	else
		k = 2 * i + 1;
	
	if (words[i - 1] < words[k - 1]) {
		string tmp = words[k - 1];
		words[k - 1] = words[i - 1];
		words[i - 1] = tmp;
	}

	max_heapify(k, n);
}

void build_max_heap(int n) {
	for (int i = n / 2; i > 0; i--)
		max_heapify(i, n);	// i번째(index X) 노드를 root로 하는 트리. 트리의 마지막 노드는 n번째 노드임.
}

double measure_heap_sort() {
	double start = clock();

	// 정렬할 배열을 힙으로 만들기
	build_max_heap(MAX);

	int last_node = MAX;
	while (last_node != 1) {
		// 힙에서 최댓값(root)을 가장 마지막 값이랑 바꾸기
		string tmp = words[0];
		words[0] = words[last_node - 1]; 
		words[last_node - 1] = tmp;

		max_heapify(1, --last_node);
	}

	double finish = clock();

	return (finish - start) / CLOCKS_PER_SEC;
}

double measure_library() {
	double start = clock();

	sort(words, words + MAX);

	double finish = clock();

	return (finish - start) / CLOCKS_PER_SEC;
}

int main() {
	read_file("harry_full.txt");
	cout << measure_bubble_sort() << endl;

	read_file("harry_full.txt");
	cout << measure_insertion_sort() << endl;

	read_file("harry_full.txt");
	cout << measure_merge_sort() << endl;

	read_file("harry_full.txt");
	cout << measure_quick_sort() << endl;

	read_file("harry_full.txt");
	cout << measure_heap_sort() << endl;

	read_file("harry_full.txt");
	cout << measure_library() << endl;

	return 0;
}