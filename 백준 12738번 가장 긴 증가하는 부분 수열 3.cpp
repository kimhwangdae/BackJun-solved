#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;
int main() {
	cin.tie(0);
	cout.tie(0);
	ios_base::sync_with_stdio(0);
	vector<long long>v;
	int N;
	cin >> N;

	
	for (int i = 0; i < N; i++) {
		long long temp;
		cin >> temp;
		if (i == 0) {
			v.push_back(temp);
			continue;
		}

		if (v.back() >= temp) {
			
			auto it = lower_bound(v.begin(), v.end(), temp);
			*it = temp;
		}
		else {
			v.push_back(temp);
		}
		
	}

	cout << v.size() << "\n";
}