#include <stdio.h>
#include <vector>
#include <algorithm>
using namespace std;
int Cmax, N;
float D, Davg;
float maxlen;
float maxdis = 0;
float total = 0;

typedef struct node
{
	float dis;
	float price;
	float gasre;				/* remaining gas in tank while arriving this station*/
	float gasad;				/* gas added in this station*/
}node;

vector<node> stations;
bool node_less_than(const node A, const node B)
{
	return A.dis < B.dis;
}

void greedy(int index)
{
	int ni = -1;
	float minprice = 0x7fffffff;
	for (int i = index+1; i<stations.size() && stations[i].dis<=stations[index].dis+maxlen; ++i)
	{
		if (stations[i].price < stations[index].price)
		{
			ni = i;
			break;
		}
	}
	if (-1 != ni)
	{
		stations[index].gasad = (stations[ni].dis - stations[index].dis)/Davg - stations[index].gasre;
		greedy(ni);
	}
	else
	{
		if (stations[index].dis + maxlen >= D)
		{
			stations[index].gasad = (D - stations[index].dis)/Davg - stations[index].gasre;
		}
		else
		{
			ni = -1;
			for (int i = index+1; i<stations.size() && stations[i].dis<=stations[index].dis+maxlen; ++i)
			{
				if (stations[i].price < minprice)
				{
					ni = i;
					minprice = stations[i].price;
				}
			}
			if (-1 == ni)
			{
				maxdis = stations[index].dis+maxlen;
			}
			else
			{
				stations[index].gasad = Cmax - stations[index].gasre;
				stations[ni].gasre = Cmax - (stations[ni].dis - stations[index].dis)/Davg;
				greedy(ni);
			}
		}
	}
}
int main()
{
	scanf("%d %f %f %d", &Cmax, &D, &Davg, &N);
	stations.resize(N);
	maxlen = Cmax*Davg;
	for (int i = 0; i != N; ++i)
	{
		scanf("%f %f", &stations[i].price, &stations[i].dis);
		stations[i].gasad = 0;
		stations[i].gasre = 0;
	}
	sort(stations.begin(), stations.end(), node_less_than);

	if (0 != stations[0].dis)
	{
		printf("The maximum travel distance = %0.02f\n", maxdis);
		return 0;
	}
	greedy(0);

	if (0 != maxdis)
	{
		printf("The maximum travel distance = %0.02f\n", maxdis);
		return 0;
	}

	for (unsigned int i = 0; i != stations.size(); ++i)
	{
		if (0 != stations[i].gasad)
		{
			total += stations[i].gasad * stations[i].price;
		}
	}

	printf("%0.02f\n", total);

	return 0;
}


#if 0
/* 可以AC*/
#include <iostream>
#include <vector>
#include <algorithm>
#include <stdio.h>
using namespace std;

int Cmax, N;
float D, Davg;
float maxdis = 0;
float maxlen = 0;

typedef struct node
{
	float price;
	float dis;
	float gasre;				/* remaining gas in tank while arriving this station*/
	float gasad;				/* gas added in this station*/
	bool visited;				
}node;

vector<node> stations;

bool node_less_than(const node A, const node B)
{
	return A.dis < B.dis;
}

unsigned int lowestprice(unsigned int src, unsigned int &dst)
{
	unsigned int minIndex;
	float minprice = 0xffffff;
	while (src < dst)
	{
		if (!stations[src].visited && stations[src].price < minprice)
		{
			minIndex = src;
			minprice = stations[src].price;
		}
		++src;
	}
	stations[minIndex].visited = true;
	return minIndex;
}

/* 更像是在用动态规划*/
void greedy(unsigned int src, unsigned int dst)
{
	float gas_remain;
	unsigned int minIndex = lowestprice(src, dst);
	if (src != minIndex && 0 == stations[minIndex].gasre)
	{
		greedy(src, minIndex);
	}
	
	if (stations[dst].dis - stations[minIndex].dis <= maxlen)
	{
		stations[minIndex].gasad = (stations[dst].dis - stations[minIndex].dis)/Davg - stations[minIndex].gasre;
	}
	else
	{
		stations[minIndex].gasad = Cmax - stations[minIndex].gasre;
		gas_remain = static_cast<float>(Cmax);
		for (unsigned int i = minIndex+1; i < dst; ++i)
		{
			gas_remain -= (stations[i].dis - stations[i-1].dis)/Davg;
			if (gas_remain < 0)
			{
				break;
			}
			else
			{
				stations[i].gasre = gas_remain;
			}
		}
		greedy(minIndex, dst);
	}
}


int main()
{
	unsigned int index = 0;
	node temp;
	float total = 0;

	cin >> Cmax >> D >> Davg >> N;
	maxlen = Cmax*Davg;

	for (int i = 0; i != N; ++i)
	{
		cin >> temp.price >> temp.dis;
		temp.gasre = 0;
		temp.gasad = 0;
		temp.visited = false;
		if (temp.dis < D)
		{
			stations.push_back(temp);
		}
	}
	temp.price = 0xffffff;
	temp.dis = D;
	temp.gasre = 0;
	temp.gasad = 0;
	temp.visited = false;
	stations.push_back(temp);
	sort(stations.begin(), stations.end(), node_less_than);

	/* 判断是否能到达目的地*/
	while (index < stations.size())
	{
		if (maxdis < stations[index].dis)
		{
			printf("The maximum travel distance = %0.02f\n", maxdis);
			return 0;
		}
		maxdis = stations[index].dis + maxlen;
		++index;
	}

	greedy(0, stations.size()-1);

	for (unsigned int i = 0; i != stations.size(); ++i)
	{
		if (0 != stations[i].gasad)
		{
			total += stations[i].gasad * stations[i].price;
		}
	}
	
	printf("%0.02f\n", total);

	return 0;
}
#endif