// Longest common subsequence
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
	while (x)
		if (a[n - 1] == b[m - 1]) {
			s = a[n - 1] + s;
			--n; --m; --x;
		}
		else if (ans[n - 1][m] == x) --n;
		else --m;
	return s;
}

void ans_lcs_last(const string& a, const string& b, vector<int>& x) {
	x = vector<int>(b.size() + 1);
	vector<int> y(b.size() + 1);
	vector<vector<int>> ans(a.size() + 1, vector<int>(b.size() + 1));
	for (int i = 1; i <= a.size(); ++i, swap(x, y))
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
		string a1 = a.substr(0, a.size() / 2), a2 = a.substr(a.size() / 2);
		string a2r = a2, br = b;
		reverse(a2r.begin(), a2r.end());
		reverse(br.begin(), br.end());
		vector<int> x1, x2;
		ans_lcs_last(a1, b, x1);  // b[0..j]
		ans_lcs_last(a2r, br, x2);  // b[j+1..n-1]
		int k = 0, Max = 0;
		for (int i = 0; i <= b.size(); ++i)
		{
			int sum = x1[i] + x2[b.size() - i];
			if (sum > Max) {
				Max = sum;
				k = i;
			}
		}
		return lcs_Hirshberg(a1, b.substr(0, k)) + lcs_Hirshberg(a2, b.substr(k));
	}
}