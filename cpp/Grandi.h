#pragma once
#include<vector>
#include<iostream>
using namespace std;

int grandi() {
	vector<int> g(1000000 + 1);
	g[0] = 0;
	int n = 239; int x = 0;
	for (int i = 1; i <= n; ++i)
	{
		vector<int> f(i+1);
		for (int j = 1; j <= i - 1; ++j)
			f[g[j - 1] ^ g[i - j - 1]] = 1;
        int mex = 0;
		while (f[mex])
			++mex;
		g[i] = mex;
		if (g[i] == 0) {
			cout << i << ": " << g[i] << " " << i - x << endl;
			x = i;
		}
	}
}