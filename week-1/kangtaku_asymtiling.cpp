#include<iostream>
#include<algorithm>
#define M 101
#define MOD 1000000007
using namespace std;

int64_t tiling[M], result;

int main()
{
	int cases, n;
	tiling[0] = 1;
	tiling[1] = 1;
	for (int i = 2; i < M; i++) {
		tiling[i] = (tiling[i - 1] + tiling[i - 2]) % MOD;
	}

	ifstream in("input.txt");
	in >> cases;
	while (cases--) {
		in >> n;
		result = (tiling[n] + MOD*2 - ((n % 2 == 0) ? tiling[(n - 2) / 2] + tiling[n / 2] : tiling[(n - 1) / 2])) % MOD;
		cout << result << endl;
	}
}