#include<iostream>
#include<cstdlib>	// 난수 생성을 위한 라이브러리
#include<ctime>	// 난수 생성, 시간 측정을 위한 라이브러리
using namespace std;

const int MAX = 200000;

int pqueue[MAX];

int find_max_index(int n) {
	int max_index = 0, max = pqueue[0];
	for (int i = 1; i < n; i++)
		if (pqueue[i] > max) {
			max_index = i;
			max = pqueue[i];
		}
	return max_index;
}

double test_array(int N, int M) {
	double start = clock();

	int que_size = N;	// 현재 pqueue에는 N개의 정수가 들어 있음
	for (int i = 0; i < M; i++) {
		if (rand() % 2 == 0 || que_size == 0)	// add
			pqueue[que_size++] = rand() % N;
		else {	// delete
			int max_index = find_max_index(que_size);
			pqueue[max_index] = pqueue[que_size - 1];
			que_size--;
		}
			
	}

	double finish = clock();

	return (finish - start) / CLOCKS_PER_SEC;
}

void max_heapify(int i, int n) {
	if (2 * i > n)	// 자식이 없는 경우
		return;

	int k;
	if (2 * i + 1 > n ||	// 왼쪽 자식만 있는 경우
		(2 * i + 1 <= n && pqueue[2 * i - 1] > pqueue[2 * i]))
		k = 2 * i;
	else
		k = 2 * i + 1;

	if (pqueue[k - 1] > pqueue[i - 1]) {
		int tmp = pqueue[k - 1];
		pqueue[k - 1] = pqueue[i - 1];
		pqueue[i - 1] = tmp;

		max_heapify(k, n);
	}
}

void build_max_heap(int n) {
	for (int i = n / 2; i > 0; i--)
		max_heapify(i, n);	// i번째(index X) 노드를 root로 하는 트리. 트리의 마지막 노드는 N번째 노드임.
}

void max_heap_insert(int que_size, int N) {
	pqueue[que_size++] = rand() % N;

	int problem_node = que_size;
	while (problem_node > 1 && pqueue[(problem_node / 2) - 1] < pqueue[problem_node - 1]) {
		int tmp = pqueue[(problem_node / 2) - 1];
		pqueue[(problem_node / 2) - 1] = pqueue[problem_node - 1];
		pqueue[problem_node - 1] = tmp;
		problem_node /= 2;
	}
}

double test_heap(int N, int M) {
	double start = clock();

	// N개의 정수를 heap으로 만들기
	build_max_heap(N);

	int que_size = N;
	for (int i = 0; i < M; i++) {
		if (rand() % 2 == 0 || que_size == 0)	// add
			max_heap_insert(que_size, N);
		else {	// delete
			pqueue[0] = pqueue[que_size - 1];
			que_size--;
			max_heapify(1, que_size);
		}
	}

	double finish = clock();

	return (finish - start) / CLOCKS_PER_SEC;
}

int main() {
	srand((unsigned int)time(NULL));	// 현재 시간을 seed값으로 넣기
	
	int N = 100000, M = 100000;

	for (int i = 0; i < N; i++)	// N개의 0 ~ N-1 사이의 랜덤한 정수 삽입
		pqueue[i] = rand() % N;
	cout << test_array(N, M) << endl;

	for (int i = 0; i < N; i++)
		pqueue[i] = rand() % N;
	cout << test_heap(N, M) << endl;

	return 0;
}