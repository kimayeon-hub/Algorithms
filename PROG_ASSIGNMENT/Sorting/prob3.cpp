#include<iostream>
#include<cstdlib>	// ���� ������ ���� ���̺귯��
#include<ctime>	// ���� ����, �ð� ������ ���� ���̺귯��
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

	int que_size = N;	// ���� pqueue���� N���� ������ ��� ����
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
	if (2 * i > n)	// �ڽ��� ���� ���
		return;

	int k;
	if (2 * i + 1 > n ||	// ���� �ڽĸ� �ִ� ���
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
		max_heapify(i, n);	// i��°(index X) ��带 root�� �ϴ� Ʈ��. Ʈ���� ������ ���� N��° �����.
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

	// N���� ������ heap���� �����
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
	srand((unsigned int)time(NULL));	// ���� �ð��� seed������ �ֱ�
	
	int N = 100000, M = 100000;

	for (int i = 0; i < N; i++)	// N���� 0 ~ N-1 ������ ������ ���� ����
		pqueue[i] = rand() % N;
	cout << test_array(N, M) << endl;

	for (int i = 0; i < N; i++)
		pqueue[i] = rand() % N;
	cout << test_heap(N, M) << endl;

	return 0;
}