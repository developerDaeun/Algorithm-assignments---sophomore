#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#pragma warning (disable : 4996)
using namespace std;

struct edge {
	int end;
	int w;
	int rank;
};
vector<edge> graph[10000];
vector<int> stack;
int visited[10000], dist[10000], rank_[10000], i;
queue<int> que;
int main() {

	int n, m, start, end, w;

	ifstream input_fp("dijkstra.inp");
	ofstream output_fp("dijkstra.out");

	input_fp >> n >> m;
	for (int i = 0; i < m; i++) { //graph 구조체 벡터 생성
		input_fp >> start >> end >> w;
		edge temp;
		temp.end = end, temp.w = w, temp.rank = i;
		graph[start].push_back(temp);
	}
	for (int i = 0; i < n; i++)
		visited[i] = -1;
	que.push(0);
	while(!que.empty()) {
		i = que.front();
		for (int j = 0; j < graph[i].size(); j++) {
			if (visited[graph[i][j].end] == -1) {
				visited[graph[i][j].end] = i;
				dist[graph[i][j].end] = graph[i][j].w + dist[i];
				rank_[graph[i][j].end] = graph[i][j].rank;
				que.push(graph[i][j].end);
			}
			else if (dist[graph[i][j].end] > graph[i][j].w + dist[i]) {
				dist[graph[i][j].end] = graph[i][j].w + dist[i];
				visited[graph[i][j].end] = i;
				rank_[graph[i][j].end] = graph[i][j].rank;
				que.push(graph[i][j].end);
			}
			else if ((dist[graph[i][j].end] == graph[i][j].w + dist[i]) && (graph[i][j].rank > rank_[graph[i][j].end])) {
				rank_[graph[i][j].end] = graph[i][j].rank;
				visited[graph[i][j].end] = i;
				que.push(graph[i][j].end);
			}
		}
		que.pop();
	}
	int ptr;
	for (int i = 1; i < n; i++) {
		ptr = i;
		output_fp << "V0 ";
		if (visited[ptr] != -1) {
			while (visited[ptr] != 0) {
				ptr = visited[ptr];
				stack.push_back(ptr);
			}
			for (int j = stack.size() - 1; j >= 0; j--) {
				output_fp << "V" << stack[j] << " ";
			}
			output_fp << "V" << i << " (" << dist[i] << ")" << endl;
		}
		else
			output_fp << "V" << i << " (-1)" << endl;
		stack.clear();
	}

	input_fp.close();
	output_fp.close();
}