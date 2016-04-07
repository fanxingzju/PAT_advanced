/*
http://www.nowcoder.com/discuss/391
超级麻烦的模拟题。
有乒乓球桌子，每个人来了要说玩多长时间。桌子有普通桌子和VIP桌子。可以认为普通人和VIP在两个不同的队列里，有空桌的话VIP优先，并且VIP优先进入VIP的桌子。还有一些限制每个人不能玩超过两个小时而且没有VIP的时候，普通人也可以用VIP的桌子，VIP如果没有VIP桌子可以用普通人的桌子——总之很多规则，最后看一下每个人玩多久，每个桌子支持了多少人。
我们用事件驱动的方法。
事件包括 ：
（1） 时间
（2） 人的id或者桌子的id
（3） 人的id表示人来了，桌子的id表示桌子腾空

我们看一下如何处理这些事件
我们把所有事件按照时间顺序排序，并且同一时间里优先考虑先来人，这样腾出桌子后，能使用这个桌子的人已经在等着呢。
（1） 腾空桌子比较简单
（1.1）把桌子加入到对应集合（VIP桌子和非VIP桌子）
（1.2）考虑是否能进人， 如果有VIP等并且有VIP的桌子，就给VIP分配VIP的桌子（编号最小的）
（1.3） 至此，要么没有VIP的桌子，要么没有VIP人，那么所有人“平等”分配桌子

（2） VIP人来
（2.1) 有VIP的桌子，就给他分配VIP的桌子
（2.2) 没有VIP的桌子，有普通的桌子，给他分配普通桌子
（2.3) 桌子全满，进入VIP等候队列

（3）普通人来
(3.1) 有空桌子（无论是否是VIP桌子）就分配给他——注意这是题目的坑所在，普通人只要有桌子，就可以分配给他一个编号最小的桌子，因为有空桌子一定没有人在等
(3.2) 进入普通的等候队列

关于(1.3)如何平等？
我们可以支持选一个来的最早的人，尽管有两种队列，我们从VIP人和普通人里选一个来得最早的就可以了——题目说没有两个人同时到
如何选一个编号最小的桌子？ 和选人一样，从两种桌子集合里面选一个最小的就可以了。
至于集合，可以用set<int>来做，begin就是最小的，我们可以存两种空桌子的id, 还有两种排队的人的id，注意存人的id，主要要存他什么时候来的，所以要存pair<int,int> 表示来的时间和id，因为第一维才是最重要的。

关于 分配桌子后事件的变化， 一个人被分配了一张桌子，我们知道他玩的时间，自然知道他离开桌子的时间，所以我们在事件队列里加一个腾空桌子的事件。总之，就是每满足一个人，就计算他离开的时间加入事件队列。
所以事件是动态的，需要动态按照时间顺序排序，所以自然就用堆、优先队列这种数据结构，我用了优先队列。
time, id, time表示时间,id和类型。如果类型是0，表示id是腾空桌子的id，否则type是1表示id是来的人的id。

还有一个坑就是每个人玩的时间不要超过两个小时——但是输入请求有超过两个小时的，我们需要自己把它变为两个小时（申请玩的时间和120分钟取最小值）。

代码很长： 关键还是要理解上述描述的，选人，选桌，处理时间，处理VIP的过程，理解起来就方便了。

*/
#include <iostream>
#include <queue>
#include <stdio.h>
#include <vector>
#include <set>
using namespace std;

const int close_time = 21*3600;
int N, K, M;
vector<int> play_time;	/* play time of each pair*/
vector<bool> is_vip_player;
vector<bool> is_vip_table;

set<int> ord_table;							/* table index*/
set<int> vip_table;							/* table index*/
set< pair<int, int> > vip_player;			/* arrive_time , play_time*/
set< pair<int, int> > ord_player;			/* arrive_time , play_time*/

vector<int> nums;		/* nums of pairs played on each table*/

typedef struct node
{
	int time;
	int id;
	int type;			/* 0->table free, 1->people come*/
}node;

priority_queue<node> affairs;

bool operator<(const node &A, const node &B)
{
	if (A.time != B.time)
	{
		return A.time > B.time;
	}
	else
	{
		return A.type < B.type;
	}
}

void freeTable(int index)
{
	if (is_vip_table[index])
	{
		vip_table.insert(index);
	}
	else
	{
		ord_table.insert(index);
	}
}

void printTime(int arrive_time, int serve_time)
{
	printf("%02d:%02d:%02d %02d:%02d:%02d ", arrive_time/3600, arrive_time/60%60, arrive_time%60, 
		serve_time/3600, serve_time/60%60, serve_time%60);
	printf("%d\n", (serve_time-arrive_time+30)/60);
}

pair<int, int> getPlayer()
{
	pair<int, int> ret;
	if (vip_player.empty())
	{
		ret = *ord_player.begin();
		ord_player.erase(ord_player.begin());
		return ret;
	}
	if (ord_player.empty())
	{
		ret = *vip_player.begin();
		vip_player.erase(vip_player.begin());
		return ret;
	}
	if (ord_player.begin()->first < vip_player.begin()->first)
	{
		ret = *ord_player.begin();
		ord_player.erase(ord_player.begin());
	}
	else
	{
		ret = *vip_player.begin();
		vip_player.erase(vip_player.begin());
	}
	return ret;
}

int getTable()
{
	int ret;
	if (vip_table.empty())
	{
		ret = *ord_table.begin();
		ord_table.erase(ord_table.begin());
		return ret;
	}
	if (ord_table.empty())
	{
		ret = *vip_table.begin();
		vip_table.erase(vip_table.begin());
		return ret;
	}
	if (*vip_table.begin() < *ord_table.begin())
	{
		ret = *vip_table.begin();
		vip_table.erase(vip_table.begin());
	}
	else
	{
		ret = *ord_table.begin();
		ord_table.erase(ord_table.begin());
	}
	return ret;
}

int main()
{
	int hh, mm, ss, viptag, index, nowtime;
	node temp;
	pair<int, int> tplayer;

	cin >> N;
	play_time.resize(N);
	is_vip_player.resize(N);
	for (int i = 0; i != N; ++i)
	{
		scanf("%d:%d:%d %d %d", &hh, &mm, &ss, &play_time[i], &viptag);
		is_vip_player[i] = (bool)viptag;
		play_time[i] = 60 * min(play_time[i], 120);
		temp.time = hh*3600 + mm*60 + ss;
		temp.id = i;
		temp.type = 1;
		affairs.push(temp);
	}

	cin >> K >> M;
	nums.resize(K);
	is_vip_table.resize(K);
	for (int i = 0; i != M; ++i)
	{
		cin >> index;
		is_vip_table[--index] = true;
	}
	for (int i = 0; i != K; ++i)
	{
		if (is_vip_table[i])
		{
			vip_table.insert(i);
		}
		else
		{
			ord_table.insert(i);
		}
	}

	while (!affairs.empty())
	{
		temp = affairs.top();
		affairs.pop();
		nowtime = temp.time;
		if (nowtime >= close_time)
		{
			break;
		}

		if (0 == temp.type)
		{
			freeTable(temp.id);
			/* 多个桌子可能同时释放*/
			while (!affairs.empty() && affairs.top().type == 0 && affairs.top().time == nowtime)
			{
				freeTable(affairs.top().id);
				affairs.pop();
			}

			while (!vip_table.empty() && !vip_player.empty())
			{
				temp.time = nowtime + vip_player.begin()->second;
				temp.type = 0;
				temp.id = *vip_table.begin();
				++nums[temp.id];
				printTime(vip_player.begin()->first, nowtime);
				affairs.push(temp);
				vip_table.erase(vip_table.begin());
				vip_player.erase(vip_player.begin());
			}

			while ((!ord_player.empty() || !vip_player.empty()) && (!ord_table.empty() || !vip_table.empty()))
			{
				tplayer = getPlayer();
				temp.time = nowtime + tplayer.second;
				temp.type = 0;
				temp.id = getTable();
				++nums[temp.id];
				printTime(tplayer.first, nowtime);
				affairs.push(temp);
			}
		}
		else
		{
			if (is_vip_player[temp.id])
			{
				if (!vip_table.empty())
				{
					temp.time = nowtime + play_time[temp.id];
					printTime(nowtime, nowtime);
					temp.type = 0;
					temp.id = *vip_table.begin();
					++nums[temp.id];
					affairs.push(temp);
					vip_table.erase(vip_table.begin());
				}
				else
				{
					if (!ord_table.empty())
					{
						temp.time = nowtime + play_time[temp.id];
						printTime(nowtime, nowtime);
						temp.type = 0;
						temp.id = *ord_table.begin();
						++nums[temp.id];
						affairs.push(temp);
						ord_table.erase(ord_table.begin());
					}
					else
					{
						vip_player.insert(make_pair(nowtime, play_time[temp.id]));
					}
				}
			}
			else
			{
				if (!vip_table.empty() || !ord_table.empty())
				{
					temp.time = nowtime + play_time[temp.id];
					printTime(nowtime, nowtime);
					temp.type = 0;
					temp.id = getTable();
					++nums[temp.id];
					affairs.push(temp);
				}
				else
				{
					ord_player.insert(make_pair(nowtime, play_time[temp.id]));
				}
			}
		}
	}
	
	for (unsigned int i = 0; i != nums.size(); ++i)
	{
		if (0 != i)
		{
			cout <<  ' ';
		}
		cout << nums[i];
	}
	cout << endl;
	return 0;
}