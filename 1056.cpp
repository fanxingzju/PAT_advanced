#include <iostream>
using namespace std;

typedef struct node
{
	int index;
	int weight;
	int rank;
}node;

node records[1005];
int order[1005];					// ��¼ÿ�ַ�����Ϣ
int length[100];					// ��¼ÿ�ֱ�������
int match = 1;
int orderlength = 0;
int NP, NG;

int winner_in_group(int startpos, int endpos)
{
	int winner = order[startpos];
	for (int i = startpos+1; i != endpos; ++i)
	{
		if (records[order[i]].weight > records[winner].weight)
		{
			winner = order[i];
		}
	}
	return winner;
}

// ��������
void process_match()
{
	int newOrderlength;
	int i, j;
	while (1 != orderlength)
	{
		newOrderlength = 0;
		for (i = 0; NG*(i+1) <= orderlength; ++i)
		{
			j = winner_in_group(NG*i, NG*(i+1));
			order[newOrderlength++] = j;
		}
		if (NG*i < orderlength)
		{
			j = winner_in_group(NG*i, orderlength);
			order[newOrderlength++] = j;
		}

		orderlength = newOrderlength;
		length[++match] = orderlength;
		for (i = 0; i != orderlength; ++i)
		{
			records[order[i]].rank = match;
		}
	}
}

int main()
{	
	cin >> NP >> NG;
	for (int i = 0; i != NP; ++i)
	{
		cin >> records[i].weight;
		records[i].index = i;
		records[i].rank = match;
	}
	orderlength = NP;
	length[match] = orderlength;
	for (int i = 0; i != NP; ++i)
	{
		cin >> order[i];
	}
	
	process_match();

	for (int i = 0; i != NP; ++i)
	{
		cout << length[records[i].rank+1]+1;
		if (i != NP-1)
		{
			cout << ' ';
		}
		else
		{
			cout << endl;
		}
	}

	system("pause");
	return 0;
}



