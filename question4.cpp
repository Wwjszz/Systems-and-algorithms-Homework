#include <iostream>
#include <algorithm>

using namespace std;
const int MAX = 1000;

int n;
int W[MAX][MAX], M[MAX][MAX];
int a[MAX], b[MAX];
long long sum, temp;
int answer1[MAX], answer2[MAX];

int main()
{
    printf("男女老师人数：");
    cin >> n;

    printf("女左男右：\n");
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            cin >> W[i][j];

    printf("男左女右：\n");
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            cin >> M[i][j];

    for (int i = 0; i < n; i++)
        a[i] = b[i] = i;

    // 女老师全排列
    do
    {
        for (int i = 0; i < n; i++)
            b[i] = i;

        // 男老师全排列
        do
        {
            temp = 0;
            for (int i = 0; i < n; i++)
                temp += W[a[i]][b[i]] * M[b[i]][a[i]];

            if (temp > sum)
            {
                for (int i = 0; i < n; i++)
                {
                    answer1[i] = a[i];
                    answer2[i] = b[i];
                }

                sum = temp;
            }

        } while (next_permutation(b, b + n));
    } while (next_permutation(a, a + n));

    cout << "混双最大优势值：" << sum << endl;
    cout << "最大优势值下的男女老师安排情况：" << endl;
    for (int i = 0; i < n; i++)
    {
        cout << "女：" << answer1[i] << " 男：" << answer2[i] << endl;
    }

    return 0;
}