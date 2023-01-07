#include <iostream>
#include <queue>
#include <string.h>
using namespace std;
const int INF = 1e9;

int dx[] = {1, -1, 0, 0}, dy[] = {0, 0, 1, -1}; // 四个方向

char dir[] = {"durl"}; // 如何移动x down up right left

inline int ABS(int x) // 绝对值
{
	return x < 0 ? -x : x;
}

const int Max = 370000;

int fc[] = {1, 1, 2, 6, 24, 120, 720, 5040, 40320}; // 康托展开所需要
int pr[Max];										// 记录当前状态之前的状态
char way[Max];										// 记录如何从 之前的状态 到 现在的状态

struct node
{
	// h：从当前状态到结果的曼哈顿距离 f：从起点到当前状态的距离 g：h+f num：空格所在的位置（0-8）
	// id：当前状态的id
	int g, h, num, id, f;
	int a[9]; // 存储八数码数组数组

	void get_id() // 康托展开 将每一个八数码的状态转换为id
	{
		int cnt;
		id = 0;
		for (int i = 0; i < 9; i++)
		{
			cnt = 0;
			for (int j = i + 1; j < 9; j++)
			{
				cnt += a[i] > a[j];
			}
			id += cnt * fc[8 - i];
		}
	}

	void get_h() // A* 计算 曼哈顿距离加已走距离
	{
		h = 0;
		int pos, x, y, cx, cy;
		for (int i = 0; i < 9; i++)
		{
			if (!a[i])
				continue;
			x = (a[i] - 1) / 3, y = (a[i] - 1) % 3;
			cx = i / 3, cy = i % 3;
			h += ABS(x - cx) + ABS(y - cy);
		}
		g = h + f;
	}
	bool operator<(const node &p) const // 重载小于号 以便后续算法
	{
		/*if (g == p.g)return f > p.f;
		return g > p.g;*/
		if (p.h != h)
			return p.h < h;
		else
			return p.f < f;
	}
};

/*
 * 八数码问题的有解无解的结论：
 * 一个状态表示成一维的形式，求出除0之外所有数字的逆序数之和，
 * 也就是每个数字前面比它大的数字的个数的和，称为这个状态的逆序。
 * 若两个状态的逆序奇偶性 相同，则可相互到达，否则不可相互到达。
 * */
int result_count;
void cal_judge(int a[9])
{
	int count = 0;
	for (int i = 0; i < 9; i++)
		for (int j = i + 1; j < 9; j++)
			if (a[i] && a[j] && a[i] > a[j])
				count++;
	result_count = count & 1;
}

bool judge(int a[9]) // 判断是否无解
{
	int count = 0;
	for (int i = 0; i < 9; i++)
		for (int j = i + 1; j < 9; j++)
			if (a[i] && a[j] && a[i] > a[j])
				count++;
	return (count & 1) != result_count;
}

node temp, result;
void bfs() // bfs 求最短路
{
	priority_queue<node> q; // 优先队列 将 g 最小的排在前面
	q.push(temp);
	while (!q.empty())
	{
		node p = q.top();
		q.pop();
		if (p.id == result.id)
		{
			return;
		}
		int x = p.num / 3, y = p.num % 3;
		int tx, ty, nnum;
		for (int i = 0; i < 4; i++)
		{
			tx = x + dx[i], ty = y + dy[i];
			if (tx < 0 || tx >= 3 || ty < 0 || ty >= 3)
				continue;
			nnum = tx * 3 + ty;
			node t = p;
			t.f += 1;
			t.num = nnum;
			swap(t.a[nnum], t.a[p.num]);
			t.get_h();
			t.get_id();
			if (pr[t.id] == -1)
			{
				pr[t.id] = p.id;
				way[t.id] = dir[i];
				if (t.id == result.id)
				{
					return;
				}
				q.push(t);
			}
		}
	}
}
char c;

int main()
{

	memset(pr, -1, sizeof(pr));
	printf("请输入结果矩阵\n");
	for (int i = 0; i < 9; i++) // 输入结果矩阵
	{
		cin >> c;
		if (c == '0')
		{
			result.num = i;
			result.a[i] = 0;
		}
		else
		{
			result.a[i] = c - '0';
		}
	}

	printf("请输入开始矩阵\n");
	for (int i = 0; i < 9; i++) // 输入开始矩阵
	{
		cin >> c;
		if (c == '0')
		{
			temp.num = i;
			temp.a[i] = 0;
		}
		else
		{
			temp.a[i] = c - '0';
		}
	}

	temp.get_id();
	temp.get_h();
	temp.f = 0;
	result.get_id();

	pr[temp.id] = temp.id;
	cal_judge(result.a);
	if (judge(temp.a))
	{
		printf("unsolvable\n");
		return 0;
	}

	bfs();

	string str;
	str.clear();
	int start = result.id;
	while (start != temp.id)
	{
		str += way[start];
		start = pr[start];
	}
	for (int i = str.size() - 1; i >= 0; i--) // 输出结果
		cout << str[i];
	cout << endl;

	return 0;
}