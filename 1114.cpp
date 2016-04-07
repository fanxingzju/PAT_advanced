/* �����Ŀ�����ѵĵط���ȷ����Щ����ͬһ����ͥ, ��������Ϊһ��ͼ������, ��ĸ����Ů������ͨ·��, ����DFS����ȷ��ͼ����ͨ����, һ����ͨ����Ϊһ����ͥ*/

#include <iostream>
#include <set>
#include <vector>
#include <algorithm>
#include <cstdio>
using namespace std;

const int MAXNODE = 10010;

/* Ϊ���Ż�Ч�ʣ����ڽӱ�ķ�ʽ�洢ͼ*/
class node
{
public:
	node(): adj(), visited(true), M_estate(0), Area(0){}
	set<int> adj;
	bool visited;
	float M_estate;
	float Area;
};

int N;
node inputs[MAXNODE];

class elem
{
public:
	elem():ID(0), M(0), total_sets(0), total_area(0){}
	bool operator<(const elem& target)
	{
		if (AVG_area == target.AVG_area)
		{
			return ID < target.ID;
		}
		return AVG_area > target.AVG_area;
	}
	void clear()
	{
		ID = 0;
		M = 0;
		total_area = 0;
		total_sets = 0;
	}
	void compute_AVG()
	{
		AVG_sets = total_sets/M;
		AVG_area = total_area/M;
	}

	int ID;
	int M;
	float total_sets;
	float total_area;
	float AVG_sets;
	float AVG_area;
};
vector<elem> res;

void dfs(int index, set<int> &family)
{
	int ni;
	family.insert(index);
	inputs[index].visited = true;
	
	for (set<int>::iterator iter = inputs[index].adj.begin();
		iter != inputs[index].adj.end(); ++iter)
	{
		ni = *iter;
		if (!inputs[ni].visited)
		{
			dfs(ni, family);
		}
	}
}

int main()
{
	int ID, father, mother, k, temp;
	set<int> family;
	elem tmpres;

	cin >> N;
	for (int i = 0; i != N; ++i)
	{
		cin >> ID;
		inputs[ID].visited = false;
		cin >> father >> mother >> k;
		if (-1 != mother)
		{
			inputs[ID].adj.insert(mother);
			inputs[mother].adj.insert(ID);
			inputs[mother].visited = false;
		}
		if (-1 != father)
		{
			inputs[ID].adj.insert(father);
			inputs[father].adj.insert(ID);
			inputs[father].visited = false;
		}
		for (int j = 0; j != k; ++j)
		{
			cin >> temp;
			inputs[ID].adj.insert(temp);
			inputs[temp].visited = false;
			inputs[temp].adj.insert(ID);
		}
		cin >> inputs[ID].M_estate;
		cin >> inputs[ID].Area;
		/* ����ͼ, ֻ����Ŀ�������漰����ID��Ҫȫ������, ���ֻ�����ǵ�visitedλ��Ϊfalse*/
	}

	for (int i = 0; i != MAXNODE; ++i)
	{
		if (!inputs[i].visited)
		{
			family.clear();
			tmpres.clear();
			dfs(i, family);
			tmpres.ID = *family.begin();
			for (set<int>::iterator iter = family.begin(); iter != family.end(); ++iter)
			{
				++tmpres.M;
				tmpres.total_area += inputs[*iter].Area;
				tmpres.total_sets += inputs[*iter].M_estate;
			}
			tmpres.compute_AVG();
			res.push_back(tmpres);
		}
	}
	sort(res.begin(), res.end());
	cout << res.size() << endl;

	for (int i = 0; i != res.size(); ++i)
	{
		printf("%04d %d %0.03f %0.03f\n", res[i].ID, res[i].M, res[i].AVG_sets, res[i].AVG_area);
	}

	return 0;
}
