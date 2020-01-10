#include <stdio.h>
#include <stdlib.h>
#pragma warning (disable : 4996)

typedef struct rankNode {
	int teamNum; //���ѹ�
	int score; //����
	int goal; //���� �� ��
	int lost; //���� �� ��
	int goal_lost; //���� �� �� - ���� �� ��
	int awayGoal; //away���� ���� �� ��
	int rank;
	struct rankNode *next;
}rankNode;

typedef struct rankHead {
	rankNode *head;
}rankHead;

rankHead* createdlinkedlist(void){
	rankHead *L;
	L = (rankHead*)malloc(sizeof(rankHead));
	L->head = NULL;
	return L;
}

void insertNode(rankHead *L, int teamNum, int score, int goal, int lost, int awayGoal) {
	rankNode *newNode;
	rankNode *p;
	
	if (L->head == NULL) { //���� ����Ʈ �϶�
		newNode = (rankNode *)malloc(sizeof(rankNode));
		newNode->teamNum = teamNum, newNode->score = score, newNode->goal = goal, newNode->lost = lost, newNode->awayGoal = awayGoal;
		newNode->next = NULL;
		L->head = newNode;
		return;
	}
	else{ //�� �� �̻� ���� ��
		p = L->head;
		while (p != NULL) {
			if (p->teamNum == teamNum) { //���ѹ��� ��ġ�� ��
				p->score = p->score + score, p->goal = p->goal + goal, p->lost = p->lost + lost, p->awayGoal = p->awayGoal + awayGoal;
				return;
			}
			else if (p->teamNum != teamNum && p->next == NULL) { //���ѹ��� ��ġ���� �ʰ� ������尡 ���� ��
				newNode = (rankNode *)malloc(sizeof(rankNode));
				newNode->teamNum = teamNum, newNode->score = score, newNode->goal = goal, newNode->lost = lost, newNode->awayGoal = awayGoal;
				newNode->next = NULL;
				p->next = newNode;
				return;
			}
			else if (p->teamNum != teamNum && p->next != NULL)    //���ѹ��� ��ġ���� �ʰ� ������尡 ���� ��
				p = p->next;
		}
	}
}

int compareNode(rankHead *L, int n, int i) { //���� �ű�� �Լ�
	rankNode *p;
	int max = -1, max2 = -1, cnt = 0;
	int temp = 0, teamNum = 0; //���� �� �� - ���� �� ��

	cnt = 0;
	p = L->head;
	max = -1;
	while (p != NULL) { //�ִ� ���� ã��
		if ((p->score > max) && !(p->rank>0 && p->rank < i))
			max = p->score;
		p = p->next;
	}
	while (1) {
		p = L->head;
		while (p != NULL) { //���� ������ ���� ���� � �ִ��� Ȯ��
			if (p->score == max && !(p->rank>0 && p->rank < i))
				cnt++;
 			p = p->next;
		}
		if (cnt == 1) { //�ִ� ������ �� ���� ��
			p = L->head;
			while (p != NULL) {
				if (p->score == max && !(p->rank > 0 && p->rank < i)) {
					p->rank = i;
					break;
				}
				p = p->next;
			}
			break;
		}
		else { //�ִ� ������ �� �� �̻� ���� ��
			p = L->head;
			while (p != NULL) { // ���� �� �� - ���� �� �� �� �ֱ�
				p->goal_lost = p->goal - p->lost;
				p = p->next;
 			}
			p = L->head;
			while (p != NULL) { // �ִ� goal_lost�� ã��1
				if (p->score == max && !(p->rank>0 && p->rank<i)) {
					temp = p->goal_lost;
					teamNum = p->teamNum;
					break;
				}
				p = p->next;
			}
			p = L->head;
			while (p != NULL) { //�ִ� goal_lost�� ã��2
				if (p->score == max && !(p->rank > 0 && p->rank < i) && (temp < p->goal_lost)) {
					temp = p->goal_lost;
					teamNum = p->teamNum;
				}
				p = p->next;
			}
			p = L->head;
			cnt = 0;
			while (p != NULL) { // 1. (���� �� �� - ���� �� ��) �� ���ϱ�
				if (p->score == max && !(p->rank > 0 && p->rank < i) && temp == p->goal_lost)
						cnt++;
				p = p->next;
			}
			if (cnt == 1) { //1�� �������� ������ �Ű����� ��
				p = L->head;
				while (p != NULL) {
					if (p->goal_lost == temp && teamNum == p->teamNum) {
						p->rank = i;
						break;
					}
					p = p->next;
				}
				break;
			}
			if (cnt > 1) { //2�� ���� ���� (�ٲ�� ���� ��)
				cnt = 0;
				p = L->head;
				max2 = -1;
				while (p != NULL) { //�ִ� awayGoal ã��
					if (p->score == max && (p->goal_lost == temp) && (p->awayGoal > max2) && !(p->rank >0 && p->rank<i)) {
						max2 = p->awayGoal;
						teamNum = p->teamNum;
					}
					p = p->next;
				}
				p = L->head;
				while (p != NULL) { //���� awayGoal�� ���� ���� � �ִ��� Ȯ��
					if (p->score == max && (p->goal_lost == temp) && (p->awayGoal == max2) && !(p->rank > 0 && p->rank < i))
						cnt++;
					p = p->next;
				}
				if (cnt == 1) { //�ִ� awayGoal�� �� ���� ��
					p = L->head;
					while (p != NULL) {
						if (p->teamNum == teamNum) {
							p->rank = i;
							break;
						}
						p = p->next;
					}
					break;
				}
				else { //�׷��� ������ �ȵǸ� ������ ��� �ο�
					p = L->head;
					while (p != NULL) {
						if (p->score == max && (p->goal_lost == temp) && (p->awayGoal == max2) && !(p->rank > 0 && p->rank < i))
							p->rank = i;
						p = p->next;
					}
					i = i + cnt - 1;
					break;
				}
			}
		}
	}
	return i;
}

int main() {

	int T, n, k, temp=0;
	int awayNum, homeNum, awayScore, homeScore;
	char c;

	rankHead *L;
	rankNode *p;

	FILE *input_fp = fopen("soccer.inp", "rt");
	FILE *output_fp = fopen("soccer.out", "wt");

	fscanf(input_fp, "%d", &T);
	for (int a = 1; a <= T; a++) {
		L = createdlinkedlist();
		fscanf(input_fp, "%d %d", &n, &k);
		for (int i = 0; i < k * 2 * (n - 1); i++) { //��� ����
			for (int j = 0; j < n/2; j++) {
				fscanf(input_fp, "%d %d %d %d", &awayNum, &homeNum, &awayScore, &homeScore);
				if(homeNum<0)
					homeNum = -homeNum;
				if (awayScore > homeScore) { //away�� �̱��
					insertNode(L, awayNum, 3, awayScore, homeScore, awayScore);
					insertNode(L, homeNum, 0, homeScore, awayScore, 0);
				}
				else if (awayScore < homeScore) { //home�� �̱��
					insertNode(L, awayNum, 0, awayScore, homeScore, awayScore);
					insertNode(L, homeNum, 3, homeScore, awayScore, 0);
 				}
				else { //����
					insertNode(L, awayNum, 1, awayScore, homeScore, awayScore);
					insertNode(L, homeNum, 1, homeScore, awayScore, 0);
				}
			}
		}
		p = L->head;
		while (p != NULL) {
			p->rank = -1;
			p = p->next;
		}
		
		for (int i = 1; i < n; i++) {
			i = compareNode(L, n, i); //���� ��
		}

		p = L->head;
		while (p != NULL) { //������ ��� ã��
			if (p->rank == -1) {
				p->rank = n;
				break;
			}
			p = p->next;
		}
		
		fprintf(output_fp, "Test Case #%d: ", a); 
		
		for (int i = 1; i <= n; i++) { //1�� ������ ��� ���
			p = L->head;
			while (p != NULL) {
				if (p->teamNum == i) {
					fprintf(output_fp, "%d ", p->rank);
					break;
				}
				p = p->next;
			}
		}
		fprintf(output_fp, "\n");
	}
	fclose(input_fp);
	fclose(output_fp);
}