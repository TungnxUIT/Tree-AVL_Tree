#include<iostream>
using namespace std;
#define LH -1 //cây con trái cao hơn
#define EH 0 //cây con trái bằng cây con phải
#define RH 1 //cây con phải cao hơn

struct Node {
	char balFactor;		//chi so can bang
	int data;
	Node* pRight;
	Node* pLeft;
};
typedef Node* Tree;

void LL(Tree& T) {
	Node* T1 = T->pLeft;
	T->pLeft = T1->pRight;
	T1->pRight = T;
	switch (T1->balFactor){
	case LH: 	T->balFactor = EH;
				T1->balFactor = EH; break;
	case EH:	T->balFactor = LH;
				T1->balFactor = RH; break;
	}
	T = T1;
}
void RR(Tree& T) {
	Node* T1 = T->pRight;
	T->pRight = T1->pLeft;
	T1->pLeft = T;
	switch (T1->balFactor) {
	case RH:	T->balFactor = EH;
				T1->balFactor = EH; break;
	case EH:	T->balFactor = RH;
				T1->balFactor = LH; break;
	}
	T = T1;
}
void LR(Tree& T) {
	Node* T1 = T->pLeft;
	Node* T2 = T1->pRight;
	T->pLeft = T2->pRight;
	T2->pRight = T;
	T1->pRight = T2->pLeft;
	T2->pLeft = T1;
	switch (T2->balFactor) {
	case LH:	T->balFactor = RH;
				T1->balFactor = EH; break;
	case EH:	T->balFactor = EH;
				T1->balFactor = EH; break;
	case RH:	T->balFactor = EH;
				T1->balFactor = LH; break;
	}T2->balFactor = EH; T = T2;
}
void RL(Tree& T) {
	Node* T1 = T->pRight;
	Node* T2 = T1->pLeft;
	T->pRight = T2->pLeft;
	T2->pLeft = T;
	T1->pLeft = T2->pRight;
	T2->pRight = T1;
	switch (T2->balFactor) {
	case RH:	T->balFactor = LH;
				T1->balFactor = EH; break;
	case EH:	T->balFactor = EH;
				T1->balFactor = EH; break;
	case LH:	T->balFactor = EH;
				T1->balFactor = RH; break;
	}T2->balFactor = EH; T = T2;
}
int balanceLeft(Tree& T) {
	switch (T->balFactor)
	{
	case LH: LL(T); return 2;		//lệch trái của trái
	case RH: LR(T); return 2;		//lệch phải của trái
	case EH: LL(T); return 1;		
	}
	return 0;
}
int balanceRight(Tree& T) {
	switch (T->balFactor)
	{
	case LH: RL(T); return 2;		//lệch trái của phải
	case RH: RR(T); return 2;		//lệch phải của phải
	case EH: RR(T); return 1;
	}
	return 0;
}
int insertNode(Tree& T, int x) {
	int res;
	if (T) {
		if (x == T->data) return 0;		//đã có
		if (x < T->data) {				//thêm trái
			res = insertNode(T->pLeft, x);
			if (res < 2) return res;				//nếu res < 2, tức là node đó chưa bị lệch, bỏ qua phần dưới
			switch (T->balFactor)					//phần dưới là phần điểu chỉnh lại node cho cân bằng
			{
			case EH: T->balFactor = LH; return 2;	//res = 1 là sau khi thêm node thì node cha cân bằng
			case RH: T->balFactor = EH; return 1;	//res = 2 là sau khi thêm node thì node cha bị lệch trái hoặc phải
			case LH: balanceLeft(T);	return 2;
			}
		}
		else if (x > T->data) {			//thêm phải
			res = insertNode(T->pRight, x);
			if (res < 2) return res;
			switch (T->balFactor)
			{
			case EH: T->balFactor = RH; return 2;
			case LH: T->balFactor = EH; return 1;
			case RH: balanceRight(T);	return 2;
			}
		}
	}
	else {
		T = new Node;
		T->data = x;
		T->pLeft = T->pRight = NULL;
		T->balFactor = EH;
		return 2;								//mặc định node đầu tiên res = 2
	}
}
int Del2(Tree& p, Tree& T) {		//hàm xóa node có 2 con
	// node trái nhất của node phải
	int res;
	if (T->pLeft != NULL) {
		res = Del2(p, T->pLeft);
		if (res < 2) return res;
		switch (T->balFactor)
		{
		case EH: T->balFactor = RH; return 2;
		case LH: T->balFactor = EH; return 1;
		case RH: balanceRight(T);	return 2;
		}
	}
	else if (T->pLeft == NULL) {
		p->data = T->data;
		p = T;
		T = T->pRight;
		return 2;
	}
	
}
int Delete(Tree& T, int x) {
	int res;
	if (T == NULL) return 0;
	else if (x < T->data) {
		res = Delete(T->pLeft, x);			// xóa xong node trái thì cây sẽ lệch phía phải, nên ta cần balanceRight
		if (res < 2) return res;
		switch (T->balFactor)
		{
		case EH: T->balFactor = RH; return 2;
		case LH: T->balFactor = EH; return 1;
		case RH: balanceRight(T);	return 2;
		}
	}
	else if (x > T->data) {					// xóa xong node phải thì cây lệch phía trái, nên ta cần balanceLeft
		res = Delete(T->pRight, x);
		if (res < 2) return res;
		switch (T->balFactor)
		{
		case EH: T->balFactor = LH; return 2;
		case RH: T->balFactor = EH; return 1;
		case LH: balanceLeft(T);	return 1;
		}
	}
	else {
		Node* p = T;
		if (p->pLeft == NULL) {				// xóa xong thì sẽ bị lệch, ta return 2
			T = T->pRight;
			return 2;
		}
		else if (p->pRight == NULL) {
			T = T->pLeft;
			return 2;
		}
		else {
			res = Del2(p, T->pRight);		// tìm node thế mạng
			if (res < 2) return res;
			switch (T->balFactor)
			{
			case EH: T->balFactor = LH; return 1;	
			case RH: T->balFactor = EH; return 1;
			case LH: balanceLeft(T);	return 1;
			}
		}
		delete p;
		return res;
	}
}
void Output_NLR(Tree T) {
	if (T == NULL)return;
	cout << T->data << " ";
	Output_NLR(T->pLeft);
	Output_NLR(T->pRight);
	
}
void Output_LRN(Tree T) {
	if (T == NULL)return;

	Output_LRN(T->pLeft);
	Output_LRN(T->pRight);
	cout << T->data << " ";
}

int main() {
	Tree T = NULL;
	int n; cin >> n;
	while (n != -1) {
		insertNode(T, n);
		cin >> n;
	}
	Delete(T, 10);
	Output_NLR(T);
}