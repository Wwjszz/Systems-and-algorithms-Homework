#include <iostream>
#include <math.h>

using namespace std;

int f1(int n)
{
    if (n < 1)
    {
        return 0;
    }
    else if (n == 1 || n == 2)
    {
        return 1;
    }

    return f1(n - 1) + f1(n - 2);
}

struct Matrix
{
    int mat[2][2];
};

struct Matrix matrixMultiply(struct Matrix *a, struct Matrix *b)
{
    struct Matrix c;
    for (int i = 0; i < 2; i++)
    {
        for (int j = 0; j < 2; j++)
        {
            c.mat[i][j] = (*a).mat[i][0] * (*b).mat[0][j] + (*a).mat[i][1] * (*b).mat[1][j];
        }
    }
    return c;
}

struct Matrix matrixPow(struct Matrix a, int n)
{
    struct Matrix ret;
    ret.mat[0][0] = ret.mat[1][1] = 1;
    ret.mat[0][1] = ret.mat[1][0] = 0;
    while (n > 0)
    {
        if (n & 1)
        {
            ret = matrixMultiply(&ret, &a);
        }
        n >>= 1;
        a = matrixMultiply(&a, &a);
    }
    return ret;
}

int fib3(int n)
{
    if (n < 2)
    {
        return n;
    }
    struct Matrix q;
    q.mat[0][0] = q.mat[0][1] = q.mat[1][0] = 1;
    q.mat[1][1] = 0;
    struct Matrix res = matrixPow(q, n - 1);
    return res.mat[0][0];
}

int fib2(int n)
{
    if (n < 1)
    {
        return 0;
    }
    if (n == 1 || n == 2)
    {
        return 1;
    }
    int res = 1;
    int pre = 1;
    int tmp = 0;
    for (int i = 3; i <= n; i++)
    {
        tmp = res;
        res = res + pre;
        pre = tmp;
    }
    return res;
}

int fib4(int n)
{
    double sqrt5 = sqrt(5);
    double fibN = pow((1 + sqrt5) / 2, n) - pow((1 - sqrt5) / 2, n);
    return round(fibN / sqrt5);
}

bool prime_1(int n)
{
    for (int i = 2; i < n; i++)
    {
        if (n % i == 0)
            return false; // 不是素数
    }

    return true; // 是素数
}

bool prime_2(int n)
{
    for (int i = 2; i < sqrt(n); i++)
    {
        if (n % i == 0)
            return false; // 不是素数
    }
    return true; // 是素数
}

bool prime_3(int n)
{
    for (int i = 2; i < n / 2; i++)
    {
        if (n % i == 0)
            return false; // 不是素数
    }
    return true; // 是素数
}

int main()
{

    return 0;
}