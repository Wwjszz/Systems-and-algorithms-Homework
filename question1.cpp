#include <iostream>

using namespace std;
typedef pair<int, int> time;
const int MAX = 1000;

int n;
pair<time, time> work = {{8, 0}, {17, 0}};
pair<time, time> tasks[MAX];
bool chosen[MAX];
int max_count, answer[MAX], temp[MAX];

void dfs(int count, time end_time)
{
    // 更新
    if (count > max_count)
    {
        max_count = count;
        for (int i = 0; i < count; i++)
        {
            answer[i] = temp[i];
        }
    }

    for (int i = 0; i < n; i++)
    {
        // 剪枝
        if (!chosen[i] && tasks[i].first >= end_time && tasks[i].second <= work.second)
        {
            chosen[i] = true;
            temp[count] = i;
            dfs(count + 1, tasks[i].second);
            chosen[i] = false;
        }
    }
}

int main()
{
    printf("输入订单数:");
    scanf("%d", &n);
    printf("输入订单开始时间和结束时间（小时与分钟空格隔开）:\n");
    for (int i = 0; i < n; i++)
    {
        printf("开始时间:");
        scanf("%2d%2d", &tasks[i].first.first, &tasks[i].first.second);
        printf("结束时间:");
        scanf("%2d%2d", &tasks[i].second.first, &tasks[i].second.second);
    }

    dfs(0, {0, 0});

    printf("最大任务数：%d\n", max_count);
    printf("订单序列为:");
    for (int i = 0; i < max_count; i++)
        printf("%d ", answer[i]);

    return 0;
}