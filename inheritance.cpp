#include <iostream>
#include <math.h>
#include <cstring>
#include <stdlib.h>
#include <time.h>

using namespace std;

#define Accuracy 99        // 保留2位小数
#define GENE_LENGTH 25     // 基因编码长度
#define GROUP 1000         // 种群数量
#define X_BEGIN (-1.57)    // X 最小
#define X_END 20.18        // X 最大、
#define MUTATION_RATE 0.01 // 变异概率
#define CROSS_NUMBER 10    // 交叉次数
#define ITERATIONS 10000   // 迭代次数
#define MAX_FITNESS 15625  // 适应度最大值不超过 MAX_FITNESS（用于轮盘赌）

const int GENE_MAX_NUMBER = pow(2.0, GENE_LENGTH) - 1;

double random(int N = 1) // 生成随机数 0 ~ N
{
    return N == 1 ? rand() % (Accuracy + 1) / (float)(Accuracy + 1) : rand() % N;
}

struct Individual // 个体
{
    char gene[GENE_LENGTH];
    float x;
    float rate;
    float fitness;

    void cal_fit() // 计算适应度
    {
        x = decode();
        fitness = x * x * x * cos(x);
    }

    float decode() // 解码
    {
        int dec = 0, i, temp = 1;
        for (i = 0; i < GENE_LENGTH; i++) // 二进制转十进制
        {
            if (gene[i] != '0')
                dec += temp;
            temp *= 2;
        }

        return (X_END - X_BEGIN) * ((float)dec / (GENE_MAX_NUMBER)) + X_BEGIN;
    }

    void cal_random() // 生成随机基因
    {
        int i;
        for (i = 0; i < GENE_LENGTH; i++)
            gene[i] = random() < 0.5 ? '1' : '0';
    }

    void cal_mutate() // 变异
    {
        int node = random(GENE_LENGTH); // 选择节点

        if (gene[node] == '0') // 变异
            gene[node] = '1';
        else
            gene[node] = '0';
    }

    void cal_cross(Individual &partner) // 交叉
    {
        int node = random(GENE_LENGTH); // 选择节点

        for (int i = node; i < GENE_LENGTH; i++) // 从节点之后开始交叉
            swap(gene[i], partner.gene[i]);
    }

    void output()
    {
        for (int i = 0; i < GENE_LENGTH; i++)
        {
            cout << gene[i];
        }
        cout << " ";
        cout << "适应度：" << fitness << " "
             << "rate：" << rate << " "
             << "x：" << x << endl;
    }
};

Individual group[GROUP];

int select(float rate)
{
    int i;
    for (i = 0; i < GROUP; i++) // 通过累积概率选择个体
        if (group[i].rate >= rate)
            return i;
    return i - 1;
}

void roulette_wheel_selection() // 轮盘赌进行交叉个体
{
    float sum = 0, temp = 0;
    int i;

    for (i = 0; i < GROUP; i++) // 计算适应度之和
        sum += (MAX_FITNESS - group[i].fitness);

    for (i = 0; i < GROUP; i++) // 计算个体的累积概率
    {
        temp += (MAX_FITNESS - group[i].fitness) / sum;
        group[i].rate = temp;
    }

    for (i = 0; i < CROSS_NUMBER; i++) // 选择交叉
    {
        float a = random(), b = random();
        int p1 = select(a), p2 = select(b);
        group[p1].cal_cross(group[p2]);
    }
}

void mutate()
{
    int i;
    for (i = 0; i < GROUP; i++)
    {
        if (random() < MUTATION_RATE)
            group[i].cal_mutate();
    }
}

pair<float, float> find_min() // 寻找种群中适应度最好的个体
{
    int i, min_fitness = INT_MAX, min_id = 0;
    for (i = 0; i < GROUP; i++)
    {
        if (min_fitness >= group[i].fitness)
            min_fitness = group[i].fitness, min_id = i;
    }

    return {min_fitness, group[min_id].x};
}

int main()
{
    srand(time(NULL));

    for (int i = 0; i < GROUP; i++) // 生成初始种群
    {
        group[i].cal_random();
        group[i].cal_fit();
        group[i].output();
    }

    int i, min_result = INT_MAX;
    float min_x;
    for (i = 0; i < ITERATIONS; i++)
    {
        cout << "迭代次数：" << i << " ";
        roulette_wheel_selection(); // 交叉产生新种群

        mutate(); // 种群间产生变异

        int j;
        for (j = 0; j < GROUP; j++) // 重新计算适应度
        {
            group[j].cal_fit();
        }

        pair<float, float> cur_best = find_min(); // 寻找最优解

        if (cur_best.first <= min_result)
        {
            min_result = cur_best.first;
            min_x = cur_best.second;
        }
        cout << "最优适应度：" << cur_best.first << " "
             << "x为：" << cur_best.second << endl;
    }

    cout << "end" << endl;
    cout << min_result << endl;
    cout << min_x << endl;
}