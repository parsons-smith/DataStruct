#include <string>
#include<list>
#include <iostream>
#include <queue>
using namespace std;

const int M = 12;
const int N = 18;

class Point
{
public:
	Point *parent;
	double F;
	double G;
	double H;
	int X;
	int Y;
	Point(int x, int y) :parent(nullptr), F(0), G(0), H(0)
	{
		X = x;
		Y = y;
	}
	double getDistance(const Point *t) const
	{
		return sqrt((t->X - X)*(t->X - X) + (t->Y - Y)*(t->Y - Y));
	}
	Point& operator=(const Point &t) {
		F = t.F;
		G = t.G;
		H = t.H;
		X = t.X;
		Y = t.Y;
		parent = t.parent;
		return *this;
	}
};


class Maze
{
public:
	int arr[M][N]{
		{ 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5 },
		{ 5, 0, 0, 0, 0, 0, 3, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 5 },
		{ 5, 0, 0, 0, 0, 0, 3, 3, 0, 0, 3, 0, 0, 0, 0, 0, 0, 5 },
		{ 5, 0, 0, 2, 2, 0, 0, 3, 3, 3, 3, 0, 0, 2, 2, 0, 0, 5 },
		{ 5, 0, 0, 2, 2, 0, 0, 0, 0, 0, 3, 3, 3, 2, 2, 0, 0, 5 },
		{ 5, 0, 0, 0, 0, 0, 0, 0, 0, 3, 3, 0, 0, 0, 0, 0, 0, 5 },
		{ 5, 0, 0, 0, 0, 0, 0, 3, 3, 0, 0, 0, 0, 0, 0, 0, 0, 5 },
		{ 5, 0, 0, 2, 2, 3, 3, 3, 0, 0, 0, 0, 0, 2, 2, 0, 0, 5 },
		{ 5, 0, 0, 2, 2, 0, 0, 3, 3, 3, 3, 0, 0, 2, 2, 0, 0, 5 },
		{ 5, 0, 0, 0, 0, 0, 0, 3, 0, 0, 3, 3, 0, 0, 0, 0, 0, 5 },
		{ 5, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 3, 0, 0, 0, 0, 0, 5 },
		{ 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5 }
	};
	list<Point*> openList;
	list<Point*> closeList;
	Point *start;
	Point *dest;
	Point *cur;

	Maze(int sx, int sy, int ex, int ey)
	{
		start = new Point(sx, sy);
		dest = new Point(ex, ey);
		cur = nullptr;
	}
	~Maze()
	{
		for(auto &x:openList)
		{
			delete x;
		}
		for(auto &x:closeList)
		{
			delete x;
		}
	}
	Point *GetMinDis()
	{
		double F = DBL_MAX;
		Point *t = nullptr;
		for (auto &x : openList)
		{
			if (F > x->F)
			{
				F = x->F;
				t = x;
			}
		}
		openList.remove(t);
		return t;
	}

	Point *findPath(bool IgnoreCorner)
	{
		openList.push_back(start);
		while (openList.size() != 0)
		{
			cur = GetMinDis();  //获取openlist最小并移除
			closeList.push_back(cur);  //加入closelist
			if (cur == dest) return cur;
			for (int i = cur->X - 1; i <= cur->X + 1; i++)
			{
				for (int j = cur->Y - 1; j <= cur->Y + 1; j++)
				{
					if (i < 0 || i >= M || j < 0 || j >= N) continue;
					if (i == cur->X && j == cur->Y) continue;
					if (IgnoreCorner && abs(i - cur->X) + abs(j - cur->Y) > 1) continue;
					bool inopenlist = false;
					for(auto &x:openList)
					{
						if(x->X == i && x->Y == j)  //周边点已在openList中，更新
						{
							inopenlist = true;
							if(x->getDistance(cur) + cur->F < x->F)
							{
								x->parent = cur;
								x->F = x->getDistance(cur) + cur->F;
							}
						}
					}
					bool incloselist = false;
					for(auto &x:closeList)
					{
						if(x->X == i && x->Y == j)
						{
							incloselist = true;
						}
					}
					if (arr[i][j] == 0 && !incloselist && !inopenlist) { //如果可行走，且不在openlist和closelist中
						Point *next;
						if(i == dest->X && j == dest->Y)
						{
							next = dest;
						}
						else
						{
							next = new Point(i, j);
						}
						next->G = next->getDistance(start);
						next->H = next->getDistance(dest);
						next->F = next->G + next->H;
						next->parent = cur;
						openList.push_back(next);
					}
				}
			}
		}
		return nullptr;
	}
};




int main() {
	Maze maze(1, 1, 9, 9);
	Point *p = maze.findPath(false);
	while(p->parent)
	{
		cout << "(" << p->X << "," << p->Y << ")" << endl;
		p = p->parent;
	}
	getchar();
	return 0;
}