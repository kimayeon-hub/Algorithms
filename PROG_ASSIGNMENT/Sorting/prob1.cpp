#include<iostream>
#include<fstream>
#include<ctime>	// �ڵ��� ����ð��� �����ϱ� ���� ���̺귯��
#include<stack> // quick sort ������ �� stack overflow�� �߻��ؼ� stack�� ���� ���
#include<algorithm>	// c++ ǥ�� ���̺귯���� �����ϴ� ���� �˰����� ����ϱ� ����
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

string sorted[MAX];	// merge sort�� ���� ������ �����͸� ������ �迭

void merge(int start, int middle, int end) {	// index�� start ~ middle, middle + 1 ~ end�� �� �迭�� merge�ϴ� �Լ�
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

	// start ~ end���� ������ ���� �迭 words�� �ֱ�
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

	while (!s.empty()) {	// ������ �� �� ���� �ݺ�
		cur = s.top();
		s.pop();

		start = cur.first, end = cur.second;
		
		if (start > end)
			continue;

		string pivot = words[end];

		// partition
		int i = start - 1;	// i: pivot���� ���� ���� ������ �ε���
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

void max_heapify(int i, int n) {	// i��° ��带 root�� �ϰ�, ������ ����� ��ȣ�� n�� ����Ʈ���� heapify�ϴ� �Լ�
	// n ��° ����� �ڽ� ��尡 ���� (leaf ���)
	if (2 * i > n)	// n�� ��ü ����� ����
		return;

	int k;	// i��° ����� �ڽ� ��� �� ū ���� ��� ��ȣ
	if (2 * i + 1 > n || // �ڽ��� 1���� ��� (���� �ڽĸ� �ִ� ���)
		(2 * i + 1 <= n && words[2 * i - 1] > words[2 * i])) // �ڽ��� 2���ε� ���� �ڽ��� �� ū ���
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
		max_heapify(i, n);	// i��°(index X) ��带 root�� �ϴ� Ʈ��. Ʈ���� ������ ���� n��° �����.
}

double measure_heap_sort() {
	double start = clock();

	// ������ �迭�� ������ �����
	build_max_heap(MAX);

	int last_node = MAX;
	while (last_node != 1) {
		// ������ �ִ�(root)�� ���� ������ ���̶� �ٲٱ�
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