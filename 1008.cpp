#include <iostream>
using namespace std;

int main()
{
	int n;						// ���������
	int cur = 0;				// ��ǰ¥��
	int next;					// ��һ��ͣ��¥��
	unsigned int time = 0;
	cin >> n;
	time += 5*n;
	while(n--)
	{
		cin >> next;
		if (next > cur)
		{
			time += 6*(next-cur);
		}
		if (next < cur)
		{
			time += 4*(cur-next);
		}
		cur = next;
	}
	cout << time << endl;
	system("pause");
	return 0;
}