#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cmath>
#include <cassert>
#include <iostream>
#include <sstream>
#include <algorithm>
#include <string>
#include <vector>
#include <set>
#include <map>
#include <queue>
#include <stack>
#include <bitset>
#include <deque>
#include <iomanip>
#include <unordered_map>
#include <unordered_set>
#include <fstream>
using namespace std;
typedef long long LL;
typedef pair<int, int> PII;

#define PB push_back
#define MP make_pair
#define AA first
#define BB second
#define SZ size()
#define BG begin()
#define OP begin()
#define ED end()
#define SQ(x) ((x)*(x))
#define cmax(x, y) x = max(x, y)
#define cmin(x, y) x = min(x, y)

const int MAXN = 200 + 5;
const int MAXH = 2500 + 5;

const int dirs[4][2] = {{-1, 0}, {1, 0}, {0, 1}, {0, -1}};

int rows, cols, height;
int heights[MAXN][MAXN];

int whenActive[MAXN][MAXN];
bool inqueue[MAXN][MAXN];

vector<PII> covered[MAXH];
bool active[MAXN][MAXN];

int above[MAXN];

void solve()
{
	int i, j, k;

	// clear everything
	for (i = 0; i < MAXN; ++i)
		above[i] = 0;
	for (i = 0; i < MAXH; ++i)
		covered[i].clear();
	for (i = 0; i < MAXN; ++i)
		for (j = 0; j < MAXN; ++j)
		{
			heights[i][j] = 0;
			whenActive[i][j] = 0;
			inqueue[i][j] = false;
			active[i][j] = false;
		}

	// input, make an artificial barrier 
	cin >> rows >> cols >> height;
	for (i = 0; i < rows + 2; i += rows + 1)
		for (j = 0; j < cols + 2; j += cols + 1)
		{
			heights[i][j] = MAXH;
		}

	for (i = 1; i <= rows; ++i)
		for (j = 1; j <= cols; ++j)
		{
			cin >> heights[i][j];
			whenActive[i][j] = MAXH - 1;
		}

	// get midpoint
	int midx = (rows >> 1) + 1;
	int midy = (cols >> 1) + 1;

	// run a basic spfa to figure out at which h is each block active
	deque<PII> next;
	next.PB(PII(midx, midy));
	inqueue[midx][midy] = true;
	whenActive[midx][midy] = heights[midx][midy];

	while (!next.empty())
	{
		PII front = next[0];
		next.pop_front();
		int r = front.first, c = front.second;

		for (i = 0; i < 4; ++i)
		{
			int r2 = r + dirs[i][0];
			int c2 = c + dirs[i][1];

			if (heights[r2][c2] == MAXH)
				continue;

			if (whenActive[r2][c2] > whenActive[r][c])
			{
				if (heights[r2][c2] > heights[r][c])
				{
					if (whenActive[r2][c2] > heights[r2][c2])
					{
						whenActive[r2][c2] = heights[r2][c2];

						if (!inqueue[r2][c2])
						{
							next.push_back(PII(r2, c2));
							inqueue[r2][c2] = true;
						}
					}
				}
				else
				{
					whenActive[r2][c2] = whenActive[r][c];

					if (!inqueue[r2][c2])
					{
						next.push_back(PII(r2, c2));
						inqueue[r2][c2] = true;
					}
				}
			}
		}
	}

	// go through each point and bucket sort
	for (i = 1; i <= rows; ++i)
		for (j = 1; j <= cols; ++j)
		{
			covered[whenActive[i][j]].PB(PII(i, j));
		}

	// now we iterate through all heights and find largest rectangle
	for (int h = 0; h <= height; ++h)
	{
		for (i = 0; i < covered[h].SZ; ++i)
			active[covered[h][i].first][covered[h][i].second] = true;

		for (i = 0; i <= cols; ++i)
			above[i] = 0;

		int best = 0;
		for (i = 1; i <= rows; ++i)
		{
			vector<PII> inc;
			for (j = 1; j <= cols; ++j)
			{
				above[j] = active[i][j] ? (above[j] + 1) : 0;

				if (inc.size() == 0)
				{
					inc.PB(PII(j, above[j]));
					continue;
				}

				int low = j;
				while (!inc.empty() && inc.back().second > above[j])
				{
					PII back = inc.back();
					int area = (j - back.AA) * back.BB;
					inc.pop_back();

					if (area > best)
						best = area;
					low = back.AA;
				}

				inc.PB(PII(low, above[j]));
			}

			while (!inc.empty())
			{
				PII back = inc.back();
				int area = (cols - back.AA + 1) * back.BB;
				inc.pop_back();

				if (area > best)
					best = area;
			}
		}

		cout << best << endl;
	}
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	//freopen("", "r", stdin);
	//freopen("", "w", stdout);

	solve();

	return 0;
}