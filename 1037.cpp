#include <iostream>
#include <algorithm>
using namespace std;

int NC, NP;
int coupons[100005];
int products[100005];
unsigned long long int max_sum = 0;

int main()
{
	int index = 0;
	int min_length = 0;
	cin >> NC;
	for (int i = 0; i != NC; ++i)
	{
		cin >> coupons[i];
	}
	cin >> NP;
	for (int i = 0; i != NP; ++i)
	{
		cin >> products[i];
	}
	sort(coupons, coupons+NC);
	sort(products, products+NP);

	min_length = NC<NP? NC:NP;

	while(coupons[index] < 0 && products[index] < 0 && index < min_length)
	{
		max_sum += coupons[index]*products[index];
		++index;
	}

	index = 1;

	while(coupons[NC-index] > 0 && products[NP-index] > 0 && index <= min_length)
	{
		max_sum += coupons[NC-index]*products[NP-index];
		++index;
	}
	cout << max_sum << endl;

	system("pause");
	return 0;
}