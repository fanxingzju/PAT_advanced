#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int N, M, S, K;
int root = -1;

typedef struct node
{
	int weight;
	int parents;
	vector<int> kids;
}node;

vector<node> tree;
vector< vector<int> > results;

bool my_cmp(const vector<int> &A, const vector<int> &B)
{
	int ni = 0;
	while (ni < A.size() && ni < B.size())
	{
		if (A[ni] != B[ni])
		{
			return A[ni] > B[ni];
		}
		++ni;
	}
	/* ? 下面这行'<' or '>'不影响结果*/
	return A.size() > B.size();
}

void level_order_tranverse(int root, vector<int> temp, int sum)
{
	temp.push_back(tree[root].weight);
	sum += tree[root].weight;
	/* leaf node*/
	if (tree[root].kids.empty())
	{
		if (sum == S)
		{
			results.push_back(temp);
		}
	}
	else
	{
		if (sum < S)
		{
			for (int i = 0; i != tree[root].kids.size(); ++i)
			{
				level_order_tranverse(tree[root].kids[i], temp, sum);
			}
		}
	}
}

void print(const vector<int> &nvec)
{
	for (int i = 0; i != nvec.size(); ++i)
	{
		if (0 != i)
		{
			cout << ' ';
		}
		cout << nvec[i];
	}
	cout << endl;
}

int main()
{
	int ni, nj, sum = 0;
	vector<int> temp;

	cin >> N >> M >> S;
	tree.resize(N);
	for (int i = 0; i != N; ++i)
	{
		cin >> tree[i].weight;
		tree[i].parents = -1;
	}

	for (int i = 0; i != M; ++i)
	{
		cin >> ni >> K;
		tree[ni].kids.resize(K);
		for (int j = 0; j != K; ++j)
		{
			cin >> nj;
			tree[ni].kids[j] = nj;
			tree[nj].parents = ni;
		}
	}

	for (int i = 0; i != N; ++i)
	{
		if (tree[i].parents == -1)
		{
			root = i;
			break;
		}
	}

	level_order_tranverse(root, temp, sum);
	sort(results.begin(), results.end(), my_cmp);
	for (int i = 0; i != results.size(); ++i)
	{
		print(results[i]);
	}
	return 0;
}

