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

/* ��������*/
void max_heapify(int pos, int size)
{
	int l = pos*2+1;
	int r = pos*2+2;
	int largest;

	if (l < size && sequence[l] > sequence[pos])
	{
		largest = l;
	}
	else
	{
		largest = pos;
	}

	if (r < size && sequence[r] > sequence[largest])
	{
		largest = r;
	}

	if (largest != pos)
	{
		swap_sequence(pos, largest);
		max_heapify(largest, size);
	}
}

/* �������ִ��֮�� pos >= 1*/
bool isInsertionSort()
{
	pos = N-1;
	while (pos != 0 && sequence[pos] == initial[pos])			/* �������û��pos != 0, case2Ҳ����ͨ��*/
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

int main()
{
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
		cout << "Heap Sort" << endl;
		pos = N-1;
		while (sequence[0] < sequence[pos] && sequence[pos-1] < sequence[pos])
		{
			--pos;
		}
		swap_sequence(0, pos);
		max_heapify(0, pos);
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