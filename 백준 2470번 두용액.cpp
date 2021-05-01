#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>

using namespace std;
int N;
vector<long long> V;
long long mininum = LLONG_MAX;

void print2Liquid() {
	int i = 0, j = N - 1;
	int idx1, idx2;
	
	while (i < j) {
		long long sum = V[i] + V[j];
		if (llabs(sum) < mininum) {
			mininum = llabs(sum);
			
			idx1 = i;
			idx2 = j;
		}
		if (sum < 0) {
			i++;
		}
		else {
			j--;
		}
	}
	cout << V[idx1] << " " << V[idx2] << endl;
	return;
}

int main() {

	cin.tie(0);
	cout.tie(0);
	ios_base::sync_with_stdio(0);
	cin >> N;

	for (int i = 0; i < N; i++)
	{
		long long temp;
		cin >> temp;
		V.push_back(temp);
	}

	sort(V.begin(), V.end());

	print2Liquid();


	
}