#include <iostream>
#include <time.h>

#define Accuracy 99 // 保留2位小数

using namespace std;

const float max_x = 5.0;
const float min_x = -5.0;
const float inertial_param = 0.8;
const float self_param = 0.5;
const float group_param = 0.5;

double random(int N = 1) // 生成随机数 0 ~ N
{
    return N == 1 ? rand() % (Accuracy + 1) / (float)(Accuracy + 1) : rand() % N;
}

struct Pos
{
    float x1, x2, x3, x4;
};

struct Speed
{
    float v1, v2, v3, v4;

    float cal_v(const float x, const float self_goat_x, const float group_goat_x)
    {
        return x * inertial_param + self_param * random() * (self_goat_x - x) +
               group_param * random() * (group_goat_x - x);
    }

    float cal_speed(const Pos &cur, const Pos &self_goat, const Pos &group_goat)
    {
        v1 = cal_v(cur.x1, self_goat.x1, group_goat.x1);
        v2 = cal_v(cur.x2, self_goat.x2, group_goat.x2);
        v3 = cal_v(cur.x3, self_goat.x3, group_goat.x3);
        v4 = cal_v(cur.x4, self_goat.x4, group_goat.x4);
    }
};

struct Individual
{
    Pos cur, goat_pos;
    Speed speed;
    float fitness;

    void cal_speed(const Pos &group_goat)
    {
        speed.cal_speed(cur, goat_pos, group_goat);
    }

    void cal_fitness()
    {
        fitness = cur.x1 * cur.x1 + cur.x2 * cur.x2 +
                  cur.x3 * cur.x3 + cur.x4 * cur.x4 + 1;
    }
};

int main()
{
    srand(time(NULL));

    return 0;
}