// 借鉴哈希表的思想,将每张卡牌和一个数字一一对应
#include <iostream>
#include <algorithm>
using namespace std;

char card_kind[5] = {'S', 'H', 'C', 'D', 'J'};

typedef struct card
{
	int card_index;
	int shuffle_index;
}card;

card records[54];
int shuffle_order[54];

bool card_less_than(const card &A, const card &B)
{
	return A.shuffle_index < B.shuffle_index;
}

void shuffle_cards()
{
	for (int i = 0; i != 54; ++i)
	{
		records[i].shuffle_index = shuffle_order[i];
	}
	sort(records, records+54, card_less_than);
}

void rHash_print_card(int index)
{
	int kind = index/13;
	int number = index%13+1;
	cout << card_kind[kind] << number;
}

int main()
{
	int N;
	cin >> N;
	
	// initial card
	for (int i = 0; i != 54; ++i)
	{
		records[i].card_index = i;
	}

	for (int i = 0; i != 54; ++i)
	{
		cin >> shuffle_order[i];
	}

	for (int i = 0; i != N; ++i)
	{
		shuffle_cards();
	}
	
	rHash_print_card(records[0].card_index);
	for (int i = 1; i != 54; ++i)
	{
		cout << ' ';
		rHash_print_card(records[i].card_index);
	}
	cout << endl;
	system("pause");
	return 0;
}

