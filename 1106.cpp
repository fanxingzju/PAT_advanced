#include <iostream>
#include <vector>
#include <queue>
#include <cstdio>
#include <cmath>
using namespace std;

class node
{
public:
	node(): level(-1), kids(){}
	int level;
	vector<int> kids;
};

vector<node> tree;
int N, K;
/*P, r必须定义为double，否则会有case通不过*/
double P, r;

void set_level(int index)
{
	int ni;
	for (int i = 0; i != tree[index].kids.size(); ++i)
	{
		ni = tree[index].kids[i];
		tree[ni].level = tree[index].level + 1;
		set_level(ni);
	}
	return ;
}

void level_order_tranverse(int &minlevel, int &ncount)
{
	queue<int> nque;
	int ni, nj;

	minlevel = -1;
	ncount = 0;
	nque.push(0);
	while (!nque.empty())
	{
		ni = nque.front();
		nque.pop();
		if (-1 == minlevel && tree[ni].kids.empty())
		{
			minlevel = tree[ni].level;
		}

		if (tree[ni].level == minlevel && tree[ni].kids.empty())
		{
			++ncount;
		}

		if (-1 != minlevel && tree[ni].level > minlevel)
		{
			break;
		}

		for (int i = 0; i != tree[ni].kids.size(); ++i)
		{
			nj = tree[ni].kids[i];
			nque.push(nj);
		}
	}
	return ;
}

int main()
{
	cin >> N >> P >> r;
	int minlevel, ncount;
	tree.resize(N);
	for (int i = 0; i != N; ++i)
	{
		cin >> K;
		tree[i].kids.resize(K);
		for (int j = 0; j != K; ++j)
		{
			cin >> tree[i].kids[j];
		}
	}

	tree[0].level = 0;
	set_level(0);

	level_order_tranverse(minlevel, ncount);

	r = 1 + r*0.01;
	printf("%0.04lf %d\n", P*pow(r,minlevel), ncount);
	return 0;
}

