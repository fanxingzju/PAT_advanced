/*
http://www.nowcoder.com/discuss/391
�����鷳��ģ���⡣
��ƹ�������ӣ�ÿ��������Ҫ˵��೤ʱ�䡣��������ͨ���Ӻ�VIP���ӡ�������Ϊ��ͨ�˺�VIP��������ͬ�Ķ�����п����Ļ�VIP���ȣ�����VIP���Ƚ���VIP�����ӡ�����һЩ����ÿ���˲����泬������Сʱ����û��VIP��ʱ����ͨ��Ҳ������VIP�����ӣ�VIP���û��VIP���ӿ�������ͨ�˵����ӡ�����֮�ܶ�������һ��ÿ�������ã�ÿ������֧���˶����ˡ�
�������¼������ķ�����
�¼����� ��
��1�� ʱ��
��2�� �˵�id�������ӵ�id
��3�� �˵�id��ʾ�����ˣ����ӵ�id��ʾ�����ڿ�

���ǿ�һ����δ�����Щ�¼�
���ǰ������¼�����ʱ��˳�����򣬲���ͬһʱ�������ȿ��������ˣ������ڳ����Ӻ���ʹ��������ӵ����Ѿ��ڵ����ء�
��1�� �ڿ����ӱȽϼ�
��1.1�������Ӽ��뵽��Ӧ���ϣ�VIP���Ӻͷ�VIP���ӣ�
��1.2�������Ƿ��ܽ��ˣ� �����VIP�Ȳ�����VIP�����ӣ��͸�VIP����VIP�����ӣ������С�ģ�
��1.3�� ���ˣ�Ҫôû��VIP�����ӣ�Ҫôû��VIP�ˣ���ô�����ˡ�ƽ�ȡ���������

��2�� VIP����
��2.1) ��VIP�����ӣ��͸�������VIP������
��2.2) û��VIP�����ӣ�����ͨ�����ӣ�����������ͨ����
��2.3) ����ȫ��������VIP�Ⱥ����

��3����ͨ����
(3.1) �п����ӣ������Ƿ���VIP���ӣ��ͷ����������ע��������Ŀ�Ŀ����ڣ���ͨ��ֻҪ�����ӣ��Ϳ��Է������һ�������С�����ӣ���Ϊ�п�����һ��û�����ڵ�
(3.2) ������ͨ�ĵȺ����

����(1.3)���ƽ�ȣ�
���ǿ���֧��ѡһ������������ˣ����������ֶ��У����Ǵ�VIP�˺���ͨ����ѡһ����������ľͿ����ˡ�����Ŀ˵û��������ͬʱ��
���ѡһ�������С�����ӣ� ��ѡ��һ�������������Ӽ�������ѡһ����С�ľͿ����ˡ�
���ڼ��ϣ�������set<int>������begin������С�ģ����ǿ��Դ����ֿ����ӵ�id, ���������Ŷӵ��˵�id��ע����˵�id����ҪҪ����ʲôʱ�����ģ�����Ҫ��pair<int,int> ��ʾ����ʱ���id����Ϊ��һά��������Ҫ�ġ�

���� �������Ӻ��¼��ı仯�� һ���˱�������һ�����ӣ�����֪�������ʱ�䣬��Ȼ֪�����뿪���ӵ�ʱ�䣬�����������¼��������һ���ڿ����ӵ��¼�����֮������ÿ����һ���ˣ��ͼ������뿪��ʱ������¼����С�
�����¼��Ƕ�̬�ģ���Ҫ��̬����ʱ��˳������������Ȼ���öѡ����ȶ����������ݽṹ�����������ȶ��С�
time, id, time��ʾʱ��,id�����͡����������0����ʾid���ڿ����ӵ�id������type��1��ʾid�������˵�id��

����һ���Ӿ���ÿ�������ʱ�䲻Ҫ��������Сʱ�����������������г�������Сʱ�ģ�������Ҫ�Լ�������Ϊ����Сʱ���������ʱ���120����ȡ��Сֵ����

����ܳ��� �ؼ�����Ҫ������������ģ�ѡ�ˣ�ѡ��������ʱ�䣬����VIP�Ĺ��̣���������ͷ����ˡ�

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
			/* ������ӿ���ͬʱ�ͷ�*/
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