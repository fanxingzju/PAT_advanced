/*
��case2���˺ܾ�, �Ա������Ͽ���AC�ĳ���, �ж�case2Ӧ���������������
Input:
10
3 1 2 8 7 5 9 4 6 0
1 2 3 7 8 5 9 4 6 0
Output:
Insertion Sort
1 2 3 5 7 8 9 4 6 0

������������
Input:
10
3 1 2 8 7 5 9 4 6 0
1 2 3 5 7 8 9 4 6 0
��ȷ�����Ӧ����
Output:
Insertion Sort
1 2 3 4 5 7 8 9 6 0
������
Output:
Insertion Sort
1 2 3 5 7 8 9 4 6 0
*/

#include <iostream>
#include <algorithm>
using namespace std;

int N;
int initial[105];
int sequence[105];
int pos = 0;

void swap_sequence(int pos_a, int pos_b)
{
	int temp = sequence[pos_a];
	sequence[pos_a] = sequence[pos_b];
	sequence[pos_b] = temp;
	return ;
}

/* �������ִ��֮�� pos >= 1*/
bool isInsertionSort()
{
	pos = N-1;
	while (pos != 0 && sequence[pos] == initial[pos])		/* �������û��pos != 0, case2Ҳ����ͨ��*/
	{
		--pos;
	}
	++pos;
	for (int i = 1; i < pos; ++i)
	{
		if (sequence[i-1] > sequence[i])
		{
			return false;
		}
	}
	return true;
}

bool isSame()
{
	for (int i = 0; i != N; ++i)
	{
		if (sequence[i] != initial[i])
		{
			return false;
		}
	}
	return true;
}

/* ���merge���ԸĽ�*/
void merge_len(int *narray, int len)
{
	int i = 0;
	int j = len;

	for (i = 0; (i+1)*j <= N; ++i)
	{
		sort(narray + i*j, narray + (i+1)*j);

	}
	if (N > i*j)
	{
		sort(narray + i*j, narray + N);
	}
}

int main()
{
	int len = 2;

	cin >> N;
	for (int i = 0; i != N; ++i)
	{
		cin >> initial[i];
	}
	for (int i = 0; i != N; ++i)
	{
		cin >> sequence[i];
	}

	if (isInsertionSort())
	{
		cout << "Insertion Sort" << endl;
		/* ���û���������whileѭ��, case2ͨ����*/
		while (pos != N-1 && sequence[pos] > sequence[pos-1])
		{
			++pos;
		}
		while (pos != 0 && sequence[pos] < sequence[pos-1])
		{
			swap_sequence(pos, pos-1);
			--pos;
		} 
	}
	else
	{
		cout << "Merge Sort" << endl;
		while (!isSame())
		{
			merge_len(initial, len);
			len *= 2;
		}
		merge_len(sequence, len);
	}

	cout << sequence[0];
	for (int i = 1; i != N; ++i)
	{
		cout << ' ' << sequence[i];
	}
	cout << endl;
	system("pause");
	return 0;
}










