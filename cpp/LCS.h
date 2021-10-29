#pragma once
#include "Std.h"
void ans_lcs(const string& a, const string& b, vector<vector<int>>& ans) {
	ans = vector<vector<int>>(a.size() + 1, vector<int>(b.size() + 1));
	for (int i = 1; i <= a.size(); ++i)
		for (int j = 1; j <= b.size(); ++j)
			if (a[i - 1] == b[j - 1])
				ans[i][j] = ans[i - 1][j - 1] + 1;
			else
				ans[i][j] = max(ans[i - 1][j], ans[i][j - 1]);
}

string lcs(const string& a, const string& b) {
	size_t n = a.size(), m = b.size();
	vector<vector<int>> ans;
	ans_lcs(a, b, ans);
	int x = ans[n][m];
	string s = "";
	while (x) {
		if (a[n - 1] == b[m - 1]) {
			s = a[n - 1] + s;
			--n; --m; --x;
		}
		else if (ans[n - 1][m] == x) --n;
		else --m;
	}
	return s;
}

void ans_lcs_last(const string& a, const string& b, vector<int>& x) {
	x = vector<int>(b.size() + 1);
	vector<int> y(b.size() + 1);
	vector<vector<int>> ans(a.size() + 1, vector<int>(b.size() + 1));
	for (int i = 1; i <= a.size(); ++i, swap(x,y))
		for (int j = 1; j <= b.size(); ++j)
			if (a[i - 1] == b[j - 1])
				y[j] = x[j - 1] + 1;
			else
				y[j] = max(x[j], y[j - 1]);
}

string lcs_Hirshberg(const string& a, const string& b) {
	if (a.size() == 0)
		return "";
	else if (a.size() == 1) {
		for (int i = 0; i < b.size(); ++i)
			if (a[0] == b[i])
				return a;
		return "";
	}
	else {
		int n = a.size(), m = b.size();
		string a1, a2, a2r, br;
		copy(a.begin(), a.begin() + n / 2, a1);
		copy(a.begin() + n / 2, a.end(), a2);
		reverse_copy(a2.begin(), a2.end(), a2r);
		reverse_copy(b.begin(), b.end(), br);
		int k = 0, max_sum = 0;
		vector<int> x1, x2; 
		ans_lcs_last(a1, b, x1);
		ans_lcs_last(a2r, br, x2);
		for (int i = 0; i <= n; ++i)
		{
			//int sum = 
		}
	}
}