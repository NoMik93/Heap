#include <fstream>
#include <iostream>
#include <cmath>
using namespace std;

class Heap {
public:
	Heap(int n) {
		size = n + 1;
		createtree();
	}
	~Heap() {
		delete[] tree_array;
	}
	void createtree();
	void input_data(char data);
	void delete_data(char data);
	void upward(int target);
	void downward(int target);
	bool check(char a, char b);
	void swap(char& a, char& b);
	int depth();
	char get(int i);
	int getUsed() { return used; }
private:
	char* tree_array;
	int used = 1, size = 0;
};

void rotatedForm(char str[], int size, int depth);
void notRotatedForm(char str[], int size, int depth);
void hTreeform(char str[], int size, int depth);

int main() {
	char next;
	int n;
	ifstream input("input.txt");
	input >> n;
	Heap heap(n);
	while (!input.eof()) {
		input >> next;
		if (next == 'I') {
			input >> next;
			heap.input_data(next);
		}
		else if (next == 'D') {
			input >> next;
			heap.delete_data(next);
		}
	}
	input.close();

	char str[150];
	for (int i = 1; i < heap.getUsed(); i++) {
		str[i] = heap.get(i + 1);
	}

	cout << "1. rotated form\n";
	rotatedForm(str, n, (int)log2(n) + 1);

	cout << "2. not rotated form\n";
	notRotatedForm(str, n, (int)log2(n) + 1);

	cout << "3. H-tree form";
	hTreeform(str, n, (int)log2(n) + 1);
}

void Heap::createtree() {
	tree_array = new char[size];
}

void Heap::input_data(char data) {
	tree_array[++used] = data;
	upward(used);
}

void Heap::delete_data(char data) {
	int search;
	for (search = 0; search < used; search++) {
		if (tree_array[search] == data)
			break;
	}
	tree_array[search] = tree_array[used--];
	downward(search);
}

void Heap::upward(int target) {
	if (check(tree_array[target / 2], tree_array[target])) {
		swap(tree_array[target / 2], tree_array[target]);
		upward(target / 2);
	}
	else
		return;
}

void Heap::downward(int target) {
	if ((target * 2) + 1 <= used) {
		if (check(tree_array[(target * 2)], tree_array[(target * 2) + 1])) {
			if (check(tree_array[target], tree_array[(target * 2) + 1])) {
				swap(tree_array[target], tree_array[(target * 2) + 1]);
				downward((target * 2) + 1);
			}
			else
				return;
		}
		else if (check(tree_array[(target * 2) + 1], tree_array[(target * 2)])) {
			if (check(tree_array[target], tree_array[(target * 2)])) {
				swap(tree_array[target], tree_array[(target * 2)]);
				downward((target * 2));
			}
			else
				return;
		}
	}
	else if ((target * 2) <= used)
		if (check(tree_array[target], tree_array[(target * 2)])) {
			swap(tree_array[target], tree_array[(target * 2)]);
			downward((target * 2));
		}
		else
			return;
	else
		return;
}

bool Heap::check(char a, char b) {
	char str[62] = { '0','1','2','3','4','5','6','7','8','9','a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z','A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z'};
	int search1, search2;
	for (search1 = 0; search1 < 62; search1++) {
		if (str[search1] == a)
			break;
	}
	for (search2 = 0; search2 < 62; search2++) {
		if (str[search2] == b)
			break;
	}
	if (search1 < search2)
		return true;
	else if (search1 > search2)
		return false;
}


void Heap::swap(char& a, char& b) {
	char tmp = a;
	a = b;
	b = tmp;
}

int Heap::depth() {
	int d = 0, tmp = used;
	while (tmp > 1) {
		tmp = tmp / 2;
		d++;
	}
	return d;
}

char Heap::get(int i) {
	return tree_array[i];
}

void rotatedForm(char str[], int size, int depth) {
	int row, col;
	row = (int)exp2(depth) - 1;
	col = depth;
	char v[127][7];

	for (int i = 0; i < row; i++)
		for (int j = 0; j < col; j++)
			v[i][j] = ' ';

	for (int i = 0; i < size; i++) {
		int n = i + 1;
		int dep = (int)log2(n) + 1;
		v[(int)(row * (2 * ((int)exp2(dep) - n) - 1) / (int)exp2(dep))][(int)log2(n)] = str[i + 1];
	}

	for (int i = 0; i < row; i++) {
		for (int j = 0; j < col; j++)
			cout << v[i][j];
		cout << endl;
	}
}

void notRotatedForm(char str[], int size, int depth) {
	int row, col;
	row = depth;
	col = (int)exp2(depth) - 1;
	char v[7][127];

	for (int i = 0; i < row; i++)
		for (int j = 0; j < col; j++)
			v[i][j] = ' ';

	for (int i = 0; i < size; i++) {
		int n = i + 1;
		int dep = (int)log2(n) + 1;
		v[(int)log2(n)][(int)(col * (2 * (n - dep + 1) - 1) / (int)exp2(dep))] = str[i + 1];
	}

	for (int i = 0; i < row; i++) {
		for (int j = 0; j < col; j++)
			cout << v[i][j];
		cout << endl;
	}
}

void hTreeform(char str[], int size, int depth) {
	int row, col;
	row = exp2((int)((depth + 1) / 2)) - 1;
	col = exp2((int)((depth + 2) / 2)) - 1;
	char v[15][15];

	for (int i = 0; i < row; i++)
		for (int j = 0; j < col; j++)
			v[i][j] = ' ';

	for (int i = size; i > 0 ; i--) {
		int dep = (int)log2(i) + 1;
		if (i == 1)
			v[(row / 2) + 1][(col / 2) + 1] = str[i -1];
		else if (dep % 2 == 0) {

		}
		else if (dep % 2 == 1) {

		}
	}

	for (int i = 0; i < row; i++) {
		for (int j = 0; j < col; j++)
			cout << v[i][j];
		cout << endl;
	}
}