#include <iostream>
#include <iomanip>
using namespace std;

typedef struct node
{
	int exp;
	float coe;
	struct node *next;
}node, *myqueue;

void inputdata(int length, myqueue &Q)
{
	Q = new node;
	node *pre = Q;
	while (0 != length)
	{
		node *temp = new node;
		cin >> temp->exp >> temp->coe;
		temp->next = NULL;
		pre->next = temp;
		pre = temp;
		--length;
	}
}

// merge Q2 into Q1
void merge(myqueue &Q1, myqueue &Q2, int L1, int L2)
{
	node* p1 = Q1->next;
	node* p2 = Q2->next;
	node* pre = Q1;
	node* temp;
	delete Q2;
	while (NULL != p1 && NULL != p2)
	{
		if (p1->exp > p2->exp)
		{
			pre->next = p1;
			pre = pre->next;
			p1 = p1->next;
		}
		else
		{
			if (p1->exp == p2->exp)
			{
				p1->coe += p2->coe;
				temp = p2;
				p2 = p2->next;
				delete temp;
				if (0 != p1->coe)
				{
					pre->next = p1;
					pre = pre->next;
					p1 = p1->next;
				}
				else
				{
					temp = p1;
					p1 = p1->next;
					delete temp;
				}
			}
			else
			{
				pre->next = p2;
				p2 = p2->next;
				pre = pre->next;
			}
		}
	}
	pre->next = NULL;
	if (p1 != NULL)
	{
		pre->next = p1;
	}
	if (p2 != NULL)
	{
		pre->next = p2;
	}
}

int main()
{
	myqueue Q1, Q2;
	int L1, L2;
	int length = 0;
	node *temp;
	cin >> L1;
	inputdata(L1, Q1);
	cin >> L2;
	inputdata(L2, Q2);
	merge(Q1, Q2, L1, L2);
	temp = Q1->next;
	while (NULL != temp)
	{
		++length;
		temp = temp->next;
	}
	cout << length;
	if (0 != length)
	{
		cout << ' ';
	}
	temp = Q1->next;
	delete Q1;
	for (int i = 0; i != length; ++i)
	{
		cout << temp->exp << ' ';
		cout << fixed << setprecision(1) << temp->coe;
		if (i != length - 1)
		{
			cout << ' ';
		}
		node *pre = temp;
		temp = temp->next;
		delete pre;
	}
	// system("pause");
	return 0;
}