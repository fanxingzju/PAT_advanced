#include <stdio.h>
#include <algorithm>
using namespace std;

typedef struct kind
{
	float inventory;
	float totalprice;
	float price;
}kind;

kind mooncakes[1001];

bool less_than_kind(const kind &A, const kind &B)
{
	return A.price > B.price;
}

int main()
{
	int N;
	float D;
	float profit = 0;
	float demand = 0;
	int index;
	scanf("%d %f", &N, &D);
	for (int i = 0; i != N; ++i)
	{
		scanf("%f", &mooncakes[i].inventory);
	}
	for (int i = 0; i != N; ++i)
	{
		scanf("%f", &mooncakes[i].totalprice);
		mooncakes[i].price = mooncakes[i].totalprice / mooncakes[i].inventory;
	}

	sort(mooncakes, mooncakes+N, less_than_kind);

	for (index = 0; index != N; ++index)
	{
		demand += mooncakes[index].inventory;
		profit += mooncakes[index].totalprice;
		if (demand >= D)
		{
			break;
		}
	}
	
	if (demand > D)
	{
		profit -= (demand-D)*mooncakes[index].price;
	}

	printf("%0.2f\n", profit);

	system("pause");
	return 0;
}