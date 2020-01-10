#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <algorithm>
#pragma warning (disable : 4996)
using namespace std;

struct edge {
	int end;
	int w;
};
vector<edge> graph[10000];
int DFS_sum = 0, BFS_sum = 0, visited[10000] = { 0, };

void store(int start) {
	visited[start] = 1;
	for (int i = 0; i < graph[start].size(); i++) {
		if (visited[graph[start][i].end] != 1) {
			visited[graph[start][i].end] = 1;
			DFS_sum += graph[start][i].w;
			store(graph[start][i].end);
		}
	}
}
bool cmp(edge edge1, edge edge2) {
	return edge1.end < edge2.end;
}
void bfs(int start) {
	queue<int> q;
	q.push(start);
	visited[start] = 1;
	while (!q.empty()) {
		int front = q.front();
		q.pop();
		for (int i = 0; i < graph[front].size(); i++) {
			if (!q.empty() && graph[front][i].end == q.front() && visited[graph[front][i].end] == 0)
				continue;
			if (visited[graph[front][i].end] == 0) {
				q.push(graph[front][i].end);
				BFS_sum += graph[front][i].w;
				visited[graph[front][i].end] = 1;
			}
		}
	}
}
int main() {

	int T, n, m, start, end, w, k, start_arr[10000] = { 0, }, size;

	ifstream input_fp("graph.inp");
	ofstream output_fp("graph.out");

	input_fp >> T;
	for (int a = 0; a < T; a++) {
		input_fp >> n >> m;
		for (int b = 0; b < m; b++) { //graph 구조체 배열 생성
			input_fp >> start >> end >> w;
			edge temp;
			temp.end = end, temp.w = w;
			graph[start].push_back(temp);
			temp.end = start;
			graph[end].push_back(temp);
		}
		for (int i = 0; i < n; i++) { //graph 정렬
			sort(graph[i].begin(), graph[i].end(), cmp);
		}
		input_fp >> k;
		for (int b = 0; b < k; b++) //start_arr 배열 생성
			input_fp >> start_arr[b];
		for (int b = 0; b < k; b++) {
			store(start_arr[b]); //DFS_sum 구하는 함수
			for (int i = 0; i < n; i++) { //visited 배열 초기화
				if (visited[i] != 0) visited[i] = 0;
			}
			bfs(start_arr[b]); //BFS_sum 구하는 함수
			for (int i = 0; i < n; i++) { //visited 배열 초기화
				if (visited[i] != 0) visited[i] = 0;
			}
			output_fp << "n=" << n << " m=" << m << " start=" << start_arr[b]
				<< " DFS:" << DFS_sum << " BFS:" << BFS_sum << endl;
			DFS_sum = 0, BFS_sum = 0;
		}
		for (int b = 0; b < n; b++) { //vector 초기화
			graph[b].clear();
		}
	}
	input_fp.close();
	output_fp.close();
}