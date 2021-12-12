#pragma once
#include<deque>
#include<vector>
#include<sort>
using namespace std;

vector<bool> used;
vector<vector<int>> edges;
int t;
vector<int> tin, tout;

void dfs(int n, vector<bool>& edges)
{
	used[n] = true;
	tin[n] = t++;
	for (auto v : edges[n])
		if (!used[v])
			dfs(v);
	tout[n] = t++;
}

deque<int> dq;

void bfs(int n)
{
	dq.push_back(n);
	d[n] = 0;
	while (!dq.empty())
	{
		int v = dq.front();
		dq.pop_front();
		used[v] = true;
		for (auto w : edges[v])
			if (!used[w])
			{
				dq.push_back(w);
				d[w] = d[v] + 1;
			}
	}
}

void strong_conn_s() {
	int n = 1000;
	for (int i = 1; i <= n; ++i)
		if (!used[i])
			dfs(i, edges);
	vector<vector<int>> edgesR(n + 1);
	for (int i = 1; i <= n; ++i)
		for (auto v : edges[i])
			edgesR[v].push_back(i);
	used = vector<bool>(n + 1);
	vector<int> V(n + 1);
	sort(V.begin() + 1, V.end(), [](int a, int b) {return tin[a] > tout[b]; });
	int cnt = 0;
	for (int i = 1; i <= n; ++i)
		if (!used[i])
			dfs(i, edgesR), ++cnt;
}