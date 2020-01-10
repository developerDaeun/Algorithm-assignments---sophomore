#include <stdio.h>
#include <stdlib.h>
#pragma warning (disable : 4996)

typedef struct rankNode {
	int teamNum; //팀넘버
	int score; //승점
	int goal; //넣은 골 수
	int lost; //잃은 골 수
	int goal_lost; //넣은 골 수 - 잃은 골 수
	int awayGoal; //away에서 넣은 골 수
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
	
	if (L->head == NULL) { //공백 리스트 일때
		newNode = (rankNode *)malloc(sizeof(rankNode));
		newNode->teamNum = teamNum, newNode->score = score, newNode->goal = goal, newNode->lost = lost, newNode->awayGoal = awayGoal;
		newNode->next = NULL;
		L->head = newNode;
		return;
	}
	else{ //한 개 이상 있을 때
		p = L->head;
		while (p != NULL) {
			if (p->teamNum == teamNum) { //팀넘버가 일치할 때
				p->score = p->score + score, p->goal = p->goal + goal, p->lost = p->lost + lost, p->awayGoal = p->awayGoal + awayGoal;
				return;
			}
			else if (p->teamNum != teamNum && p->next == NULL) { //팀넘버가 일치하지 않고 다음노드가 없을 때
				newNode = (rankNode *)malloc(sizeof(rankNode));
				newNode->teamNum = teamNum, newNode->score = score, newNode->goal = goal, newNode->lost = lost, newNode->awayGoal = awayGoal;
				newNode->next = NULL;
				p->next = newNode;
				return;
			}
			else if (p->teamNum != teamNum && p->next != NULL)    //팀넘버가 일치하지 않고 다음노드가 있을 때
				p = p->next;
		}
	}
}

int compareNode(rankHead *L, int n, int i) { //순위 매기는 함수
	rankNode *p;
	int max = -1, max2 = -1, cnt = 0;
	int temp = 0, teamNum = 0; //넣은 골 수 - 잃은 골 수

	cnt = 0;
	p = L->head;
	max = -1;
	while (p != NULL) { //최대 승점 찾기
		if ((p->score > max) && !(p->rank>0 && p->rank < i))
			max = p->score;
		p = p->next;
	}
	while (1) {
		p = L->head;
		while (p != NULL) { //같은 승점을 가진 팀이 몇개 있는지 확인
			if (p->score == max && !(p->rank>0 && p->rank < i))
				cnt++;
 			p = p->next;
		}
		if (cnt == 1) { //최대 승점이 한 팀일 때
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
		else { //최대 승점이 두 개 이상 팀일 때
			p = L->head;
			while (p != NULL) { // 넣은 골 수 - 잃은 골 수 값 넣기
				p->goal_lost = p->goal - p->lost;
				p = p->next;
 			}
			p = L->head;
			while (p != NULL) { // 최대 goal_lost값 찾기1
				if (p->score == max && !(p->rank>0 && p->rank<i)) {
					temp = p->goal_lost;
					teamNum = p->teamNum;
					break;
				}
				p = p->next;
			}
			p = L->head;
			while (p != NULL) { //최대 goal_lost값 찾기2
				if (p->score == max && !(p->rank > 0 && p->rank < i) && (temp < p->goal_lost)) {
					temp = p->goal_lost;
					teamNum = p->teamNum;
				}
				p = p->next;
			}
			p = L->head;
			cnt = 0;
			while (p != NULL) { // 1. (넣은 골 수 - 잃은 골 수) 값 비교하기
				if (p->score == max && !(p->rank > 0 && p->rank < i) && temp == p->goal_lost)
						cnt++;
				p = p->next;
			}
			if (cnt == 1) { //1번 조건으로 순위가 매겨졌을 때
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
			if (cnt > 1) { //2번 조건 시작 (바뀐게 없을 때)
				cnt = 0;
				p = L->head;
				max2 = -1;
				while (p != NULL) { //최대 awayGoal 찾기
					if (p->score == max && (p->goal_lost == temp) && (p->awayGoal > max2) && !(p->rank >0 && p->rank<i)) {
						max2 = p->awayGoal;
						teamNum = p->teamNum;
					}
					p = p->next;
				}
				p = L->head;
				while (p != NULL) { //같은 awayGoal을 가진 팀이 몇개 있는지 확인
					if (p->score == max && (p->goal_lost == temp) && (p->awayGoal == max2) && !(p->rank > 0 && p->rank < i))
						cnt++;
					p = p->next;
				}
				if (cnt == 1) { //최대 awayGoal이 한 팀일 때
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
				else { //그래도 구별이 안되면 동일한 등수 부여
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
		for (int i = 0; i < k * 2 * (n - 1); i++) { //노드 생성
			for (int j = 0; j < n/2; j++) {
				fscanf(input_fp, "%d %d %d %d", &awayNum, &homeNum, &awayScore, &homeScore);
				if(homeNum<0)
					homeNum = -homeNum;
				if (awayScore > homeScore) { //away가 이기면
					insertNode(L, awayNum, 3, awayScore, homeScore, awayScore);
					insertNode(L, homeNum, 0, homeScore, awayScore, 0);
				}
				else if (awayScore < homeScore) { //home이 이기면
					insertNode(L, awayNum, 0, awayScore, homeScore, awayScore);
					insertNode(L, homeNum, 3, homeScore, awayScore, 0);
 				}
				else { //비기면
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
			i = compareNode(L, n, i); //순위 비교
		}

		p = L->head;
		while (p != NULL) { //마지막 등수 찾기
			if (p->rank == -1) {
				p->rank = n;
				break;
			}
			p = p->next;
		}
		
		fprintf(output_fp, "Test Case #%d: ", a); 
		
		for (int i = 1; i <= n; i++) { //1번 팀부터 등수 출력
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