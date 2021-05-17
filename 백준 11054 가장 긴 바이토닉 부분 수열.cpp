#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int DP[1001];
int DP2[1001];
int N;
vector<int>Input_vector;
void first_lis() {
	vector<int>v;
	for (int i = 0; i < N; i++) {
		if (i == 0) {
			v.push_back(Input_vector[i]);
			DP[i] = v.size();
			continue;
		}
		if (v.back() < Input_vector[i]) {
			v.push_back(Input_vector[i]);
		}
		else {
			auto it = lower_bound(v.begin(), v.end(), Input_vector[i]);
			*it = Input_vector[i];

		}
		DP[i] = v.size();
	}
}

void second_lis() {
	vector<int>v;
	for (int i = N - 1; i >= 0; i--) {
		if (i == N-1) {
			v.push_back(Input_vector[i]);
			DP2[i] = v.size();
			continue;
		}
		if (v.back() < Input_vector[i]) {
			v.push_back(Input_vector[i]);
		}
		else {
			auto it = lower_bound(v.begin(), v.end(), Input_vector[i]);
			*it = Input_vector[i];
		}
		DP2[i] = v.size();
	}
	
}
int main() {

	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);

	cin >> N;
	for (int i = 0; i < N; i++) {
		int temp;
		cin >> temp;
		Input_vector.push_back(temp);
	}
	first_lis();
	second_lis();

	int result = 0;
	for (int i = 0; i < N; i++) {
		result = max(result, (DP[i] + DP2[i]));
	}
	cout << result-1 << endl;
}