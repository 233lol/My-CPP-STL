#include <iostream>
#include "vector.hpp"
#include "queue.hpp"
using namespace std;
int n, m, s, t, a[51][51];
Queue<int> q;
Vector<int> ans;
bool vis[52];
void bfs(int x)
{
	q.push(x);
	while (!q.empty())
	{
		int now = q.get_front();
		q.pop();
		for (int i = 1; i <= n; ++i)
		{
			if (a[now][i] && !vis[i])
			{
				vis[i] = true;
				q.push(i);
			}
		}
		ans.push_back(now);
	}
	return;
}
int main()
{
	cin >> n;
	for (int i = 1; i <= n; ++i)
	{
		for (int j = 1; j <= n; ++j)
		{
			cin >> a[i][j];
		}
	}
	for (int i = 1; i <= n; ++i)
	{
		if (!vis[i])
		{
			vis[i] = true;
			bfs(i);
		}
	}
	for (int i = 1; i <= n; ++i)
	{
		cout<<ans[i - 1] - 1<<" ";
	}
	cout<<endl;
	return 0;
}