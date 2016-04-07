#include <iostream>
using namespace std;

int main()
{
	int n;						// 总输入个数
	int cur = 0;				// 当前楼层
	int next;					// 下一个停靠楼层
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