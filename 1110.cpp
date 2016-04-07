#include <iostream>
#include <vector>
#include <string>
#include <queue>
using namespace std;

class node
{
public:
	node():parent(-1), level(-1), lchild(-1), rchild(-1), index(-1){}
	int parent;
	int level;
	int lchild;
	int rchild;
	int index;
};

vector<node> bitree;

int str_to_n(const string &str)
{
	int ret = 0;
	if ("-" == str)
	{
		return -1;
	}
	for (int i = 0; i != str.size(); ++i)
	{
		ret = ret*10 + str[i] - '0';
	}
	return ret;
}

void set_level_index(int root)
{
	if (bitree[root].lchild != -1)
	{
		bitree[bitree[root].lchild].level = bitree[root].level + 1;
		bitree[bitree[root].lchild].index = 2*bitree[root].index + 1;
		set_level_index(bitree[root].lchild);
	}

	if (bitree[root].rchild != -1)
	{
		bitree[bitree[root].rchild].level = bitree[root].level + 1;
		bitree[bitree[root].rchild].index = 2*bitree[root].index + 2;
		set_level_index(bitree[root].rchild);
	}
}

bool level_order_tranverse(int root, int &lastnode)
{
	int count = 0;;
	queue<int> nque;
	nque.push(root);
	while (!nque.empty())
	{
		lastnode = nque.front();
		nque.pop();
		if (bitree[lastnode].index != count++)
		{
			return false;
		}
		if (-1 != bitree[lastnode].lchild)
		{
			nque.push(bitree[lastnode].lchild);
		}
		if (-1 != bitree[lastnode].rchild)
		{
			nque.push(bitree[lastnode].rchild);
		}
	}
	return true;
}

int main()
{
	string lstr, rstr;
	int root, lastnode;
	int N;

	cin >> N;
	bitree.resize(N);

	for (int i = 0; i != N; ++i)
	{
		cin >> lstr >> rstr;
		bitree[i].lchild = str_to_n(lstr);
		bitree[i].rchild = str_to_n(rstr);
		if (-1 != bitree[i].lchild)
		{
			bitree[bitree[i].lchild].parent = i;
		}
		if (-1 != bitree[i].rchild)
		{
			bitree[bitree[i].rchild].parent = i;
		}
	}

	for (int i = 0; i != N; ++i)
	{
		if (bitree[i].parent == -1)
		{
			root = i;
			break;
		}
	}

	bitree[root].index = 0;
	bitree[root].level = 0;
	
	set_level_index(root);

	if (level_order_tranverse(root, lastnode))
	{
		cout << "YES" << ' ' << lastnode << endl;
	}
	else
	{
		cout << "NO" << ' ' << root << endl;
	}

	return 0;
};