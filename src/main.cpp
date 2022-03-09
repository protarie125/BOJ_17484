#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

using vi = vector<int>;
using vvi = vector<vi>;
using vvvi = vector <vvi>;

vvi space;
vvvi memo;

int solvePart(int n, int m, int y, int x, int bf) {
	if (n - 1 == y) {
		return space[y][x];
	}

	if (memo[y][x][bf + 1] < 0) {
		auto ans = space[y][x];
		auto lst = vi{};
		for (int i = -1; i <= 1; ++i) {
			if (i == bf) {
				continue;
			}

			auto x2 = x + i;
			if (x2 < 0 || m <= x2) {
				continue;
			}

			lst.push_back(solvePart(n, m, y + 1, x2, i));
		}

		ans += *(min_element(lst.begin(), lst.end()));

		memo[y][x][bf + 1] = ans;
	}

	return memo[y][x][bf + 1];
}

int solve(int n, int m) {
	auto lst = vi(m);
	for (int i = 0; i < m; ++i) {
		lst[i] = solvePart(n, m, 0, i, 2);
	}

	return *(min_element(lst.begin(), lst.end()));
}

int main() {
	ios::sync_with_stdio(false);
	std::cin.tie(nullptr);

	int n, m;
	cin >> n >> m;

	space = vvi(n, vi(m));
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < m; ++j) {
			cin >> space[i][j];
		}
	}

	memo = vvvi(n, vvi(m, vi(4, -1)));

	cout << solve(n, m);

	return 0;
}