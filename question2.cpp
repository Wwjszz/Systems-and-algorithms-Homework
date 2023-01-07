#include <iostream>

using namespace std;
const int MAX = 1000;

int n;
int max_score, answer[MAX], temp[MAX], count, max_count;
pair<int, int> tasks[MAX];
bool chosen[MAX];

void dfs(int score, int end_time, int count)
{
    bool flag = false;
    for (int i = 0; i < n; i++)
    {
        if (!chosen[i] && end_time < tasks[i].first)
        {
            flag = true;
            chosen[i] = true;
            temp[count] = i;
            dfs(score + tasks[i].second, tasks[i].first + 1, count + 1);
            chosen[i] = false;
        }
    }

    // 更新
    if (!flag && score > max_score)
    {
        max_score = score;
        max_count = count;
        memcpy(answer, temp, count * sizeof(int));
    }
}

int main()
{
    printf("作业数：");
    scanf("%d", &n);

    printf("每个作业的最后提交时间：");
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &tasks[i].first);
    }

    printf("每个作业的逾期扣分数：");
    int total_score = 0;
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &tasks[i].second);
        total_score += tasks[i].second;
    }

    dfs(0, 0, 0);

    printf("完成作业的顺序为：");
    for (int i = 0; i < max_count; i++)
        printf("%d ", answer[i]);
    printf("\n");

    printf("最小逾期数为：%d\n", total_score - max_score);
    return 0;
}