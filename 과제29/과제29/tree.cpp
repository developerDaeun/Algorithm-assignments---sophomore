#include <iostream>
#include <fstream>
#include <vector>
using namespace std;
vector<int> in; //중위
vector<int> tvs; //전위or후위
vector<int> printer;
int temp;

void find_post(int n, vector<int> in, vector<int> pre) { //중위, 전위를 알 때 후위 구하기
	int Ls, Rs, root = pre[0];
	vector<int> L;
	vector<int> R; 
	vector<int> tvs2;
	//L.clear(), R.clear(), tvs2.clear();
	for (int i = 0; i < n; i++) { //왼쪽, 오른쪽 서브트리 크기 구하기
		if (root == in[i]) {
			Ls = i, Rs = n - Ls - 1;
			break;
		}
	}
	for (int i = 0; i < Ls; i++) {
		L.push_back(in[i]);
	}
	for (int i = 0; i < Rs; i++) {
		R.push_back(in[i+Ls+1]);
	}
	if (Ls == 0 && Rs == 0) {
		printer.push_back(root);
		return;
	}
	if (Ls != 0) {
		for (int i = 1; i < pre.size(); i++) {
			tvs2.push_back(pre[i]);
		}
		find_post(Ls, L, tvs2);
	}
	tvs2.clear();
	if (Rs != 0) {
		for (int i = Ls+1; i < pre.size(); i++) {
			tvs2.push_back(pre[i]);
		}
		find_post(Rs, R, tvs2);
	}
	printer.push_back(root);
	return;
}

void find_pre(int n, vector<int> in, vector<int> post) { //중위, 후위를 알 때 전위 구하기
	int Ls, Rs, root = post[post.size() - 1];
	vector<int> L; //중위의 L
	vector<int> R; //중위의 R
	vector<int> L2; //후위의 L
	vector<int> R2; //후위의 R
	for (int i = 0; i < n; i++) { //왼쪽, 오른쪽 서브트리 크기 구하기
		if (root == in[i]) {
			Ls = i, Rs = n - Ls - 1;
			break;
		}
	}
	for (int i = 0; i < Ls; i++)
		L.push_back(in[i]);
	for (int i = 0; i < Rs; i++)
		R.push_back(in[i + Ls + 1]);
	for (int i = 0; i < Ls; i++)
		L2.push_back(post[i]);
	for (int i = 0; i < Rs; i++)
		R2.push_back(post[i + Ls]);
	printer.push_back(root); //루트 출력
	if (Ls != 0) {
		find_pre(Ls, L, L2);
	}
	if (Rs != 0) {
		find_pre(Rs, R, R2);
	}
	return;
}

int main() {

	int n, k, num;

	ifstream input_fp("tree.inp");
	ofstream output_fp("tree.out");

	input_fp >> n;
	for (int i = 0; i < 2; i++) { //벡터 생성
		input_fp >> k;
		if (k == -1) temp = -1; else if (k == 1) temp = 1;
		for (int j = 0; j < n; j++) {
			input_fp >> num;
			if (k == 0) in.push_back(num);
			else tvs.push_back(num);
		}
	}
	for (int i = 0; i < 2; i++) {
		if (temp == -1) { //중위, 전위를 알 때
			find_post(n, in, tvs); //후위 찾기
		}
		else if (temp == 1) { //중위, 후위를 알 때
			find_pre(n, in, tvs); //전위 찾기
		}
	}
	for (int i = 0; i < n; i++)
		output_fp << printer[i] << endl;
	input_fp.close(), output_fp.close();
}