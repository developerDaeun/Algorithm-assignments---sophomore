#include <stdio.h>
#include <iostream>
#include <fstream>
#include <algorithm>
#pragma warning (disable : 4996)
using namespace std;

typedef struct ListNode {
	int num;
	struct ListNode *next;
}ListNode;

typedef struct ListHead {
	ListNode *head;
}ListHead;

ListHead *createLinkedList() {
	ListHead *L;
	L = (ListHead*)malloc(sizeof(ListHead));
	L->head = NULL;
	return L;
}

void addNode(ListHead *L, int num) {
	ListNode *newNode = (ListNode*)malloc(sizeof(ListNode));
	newNode->num = num;
	newNode->next = NULL;
	if (L->head == NULL) { //공백 노드일때
		L->head = newNode;
		return;
	}
	ListNode *p = L->head;
	while (p->next != NULL)
		p = p->next;
	p->next = newNode;
	return;
}

void updateNode(ListHead *L, int num, int cnt) {
	ListNode *p = L->head;
	ListNode *pre, *after;
	while (p->next->num != num) { //p는 전노드
		p = p->next;
	}
	pre = p->next; //현재
	after = p->next->next; //다음
	p->next = pre->next;
	for (int i = 0; i < cnt; i++)
		p = p->next;
	pre->next = p->next;
	p->next = pre;
	return;
}

int main() {

	long long int T, n, num, cnt=0, arr[1000], result[1000];
	ListHead *L;
	ListNode *p;

	ifstream input_fp("line2.inp");
	ofstream output_fp("line2.out");

	input_fp >> T;
	for (int a = 0; a < T; a++) {
		L = createLinkedList();
		input_fp >> n;
		for (int i = 0; i < n; i++) { //처음
			input_fp >> num;
			arr[i] = num;
		}
		addNode(L, 0); //첫번째 노드
		for (int i = 0; i < n; i++) { //결과
			input_fp >> num;
			addNode(L, num);
		}
		addNode(L, 0); //끝 노드
		for (int i = n - 1; i > -1; i--) {
			p = L->head->next, cnt = 0;
			while (p != NULL) { //최종적으로 얼만큼 갔는지 찾기
				if (arr[i] == p->num) break;
				cnt++;
				p = p->next;
			}
			cnt = i - cnt;
			result[arr[i]] = cnt;
			num = arr[i];
			if(cnt!=0)
				updateNode(L, num, cnt);
		}
		for (int i = 1; i <= n; i++)
			output_fp << result[i] << ' ';
		output_fp << '\n';
	}
	input_fp.close();
	output_fp.close();
}