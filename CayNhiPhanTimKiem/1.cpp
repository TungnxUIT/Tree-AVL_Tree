#include<iostream>
#include<stack>
using namespace std;

struct Node {
	int data;
	Node* pRight;
	Node* pLeft;
};
typedef Node* Tree;
void CreateTree(Tree& T) {
	T = NULL;
}
Node* CreateNode(int x) {
	Node* p = new Node;
	p->data = x;
	p->pLeft = p->pRight = NULL;
	return p;
}
void Add(Tree& T, Node* p) {
	if (T == NULL) T = p;
	else {
		if (p->data > T->data) Add(T->pRight, p);
		else if (p->data < T->data) Add(T->pLeft, p);
	}
}
bool Find(Tree T, int x) {
	if (T == NULL) return false;
	if (T->data == x) return true;
	if (T->data > x) Find(T->pLeft, x);
	if (T->data < x) Find(T->pRight, x);

}
void Del2(Tree& p, Tree& T) {		//hàm xóa node có 2 con
	// node trái nhất của node phải
	if (T->pLeft != NULL) Del2(p, T->pLeft);
	else if (T->pLeft==NULL) {
		p->data = T->data;
		p = T;
		T = T->pRight;
	}
}
void Delete(Tree& T, int x) {
	if (T == NULL)return;
	if (T->data < x) Delete(T->pRight, x);
	else if (T->data > x) Delete(T->pLeft, x);
	else {
		Node* p = T;
		if (p->pLeft == NULL) T = T->pRight;
		else if (p->pRight == NULL) T = T->pLeft;
		else {
			Del2(p, T->pRight);
		}
		delete p;
	}
}
void Input(Tree& T) {
	int n;
	cin >> n;
	while (n != -1) {
		Add(T, CreateNode(n));
		cin >> n;
	}
}
void Output_LRN(Tree T) {
	if (T == NULL)return;
	
	Output_LRN(T->pLeft);
	Output_LRN(T->pRight);
	cout << T->data << " ";
}
void Output_NLR(Tree T) {
	if (T == NULL)return;
	cout << T->data << " ";
	Output_NLR(T->pLeft);
	Output_NLR(T->pRight);

}
void Output_LNR(Tree T) {
	if (T == NULL)return;
	
	Output_NLR(T->pLeft);
	cout << T->data << " ";
	Output_NLR(T->pRight);

}

int main() {
	Tree T;
	CreateTree(T);
	Input(T);
	Output_LNR(T);
	cout << "\n";
	Output_NLR(T);
	return 0;
}