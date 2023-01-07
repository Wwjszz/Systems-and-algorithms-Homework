#include <iostream>
#include <cstring>

using namespace std;
const int MAX = 1000; // 最大加油站个数

int n, K, M, D[MAX]; // 加油站数，自驾游总路线长度，加满油可行驶公里数，加油站所在坐标
bool answer[MAX];    // 停靠序列

/**
 * @brief  贪心算法求解本问题
 * @note   None
 * @retval 序列记录在answer里，返回最小值，-1为无解
 */
int greedy()
{
    int start = 0, num = 0; // 开始节点，最小值
    answer[0] = 1;          // 初始化序列
    do
    {
        bool find = 0; // 是否能到达下一个加油站
        for (int i = n - 1; i > start; i--)
            if (D[i] <= M + D[start]) // 能到达的最远加油站
            {
                find = 1;
                num += 1;
                answer[start] = 1;
                start = i;
                break;
            }

        // 未找到则无解，返回-1
        if (!find)
            return -1;

    } while (start < n - 1);

    return num;
}

int min_num;    // 最小值，-1为无解
bool temp[MAX]; // 回溯需要的暂时序列
/**
 * @brief  回溯算法求解本问题
 * @note   None
 * @param  station: 当前加油站节点
 * @param  num: 当前序列已加油次数
 * @retval None
 */
void back_track(int station, int num)
{
    // 左剪枝
    if (num > min_num && ~min_num)
        return;

    // 得到序列，如果当前解比之前解更优，则更新。
    if (station == n - 1)
    {
        if (num < min_num || min_num == -1)
        {
            min_num = num;
            memcpy(answer, temp, n);
        }
        return;
    }

    // 记录节点
    temp[station] = 1;
    num += 1;

    // 寻找下一个可能的加油站，并递归。
    for (int i = station + 1; i < n && D[i] <= M + D[station]; i++)
    {
        back_track(i, num);
    }
}

int main()
{
    cout << "自驾游总路线长度：";
    cin >> K;

    cout << "加满油可行驶公里数：";
    cin >> M;

    cout << "沿途加油站数：";
    cin >> n;

    cout << "各加油站之间的距离数：";
    int sum = 0;
    D[0] = 0;
    for (int i = 1; i < n; i++)
    {
        cin >> sum;
        D[i] = sum + D[i - 1];
    }

    memset(answer, 0, n * sizeof(int));
    int c = greedy();

    cout << "贪心算法为：" << endl;
    if (c == -1)
    {
        cout << "无法到达目的地" << endl;
    }
    else
    {
        cout << "最少加油次数为：";
        cout << c << endl;
        cout << "加油站停靠情况：";
        for (int i = 0; i < n; i++)
            cout << answer[i] << " ";
        cout << endl;
    }

    cout << "回溯算法为：" << endl;

    min_num = -1;
    back_track(0, 0);
    c = min_num;
    if (c == -1)
    {
        cout << "无法到达目的地" << endl;
    }
    else
    {
        cout << "最少加油次数为：";
        cout << c << endl;
        cout << "加油站停靠情况：";
        for (int i = 0; i < n; i++)
            cout << answer[i] << " ";
        cout << endl;
    }

    return 0;
}