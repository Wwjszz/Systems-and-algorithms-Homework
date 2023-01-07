#include <iostream>
#include <cstring>

using namespace std;
const int MAX = 100;

int n;
char chess[MAX][MAX];
bool chosen[MAX][MAX];
int dx[] = {0, 0, 1, -1};
int dy[] = {1, -1, 0, 0};

// 是否合法
bool valid(int x, int y)
{
    return x >= 0 && x < n && y >= 0 && y < n;
}

// 判断是否杯包围
bool dfs(int x, int y)
{
    chosen[x][y] = true;
    bool flag = true;
    for (int i = 0; i < 4; i++)
    {
        int tx = x + dx[i], ty = y + dy[i];

        if (!valid(tx, ty))
            return false;

        if (chess[tx][ty] == 'b' || chosen[tx][ty])
            continue;

        flag = dfs(tx, ty);
    }

    return flag;
}

// 将被包围的白色变成黑色
void to_black(int x, int y)
{
    chess[x][y] = 'b';
    for (int i = 0; i < n; i++)
    {
        int tx = x + dx[i], ty = y + dy[i];
        if (valid(tx, ty) && chess[tx][ty] == 'w')
            to_black(tx, ty);
    }
}

int main()
{
    cout << "length:";
    cin >> n;

    cout << "matrix(b->black,w->white):" << endl;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            cin >> chess[i][j];

    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
        {
            if (chess[i][j] == 'w')
            {
                memset(chosen, 0, sizeof(chosen));
                if (dfs(i, j))
                    to_black(i, j);
            }
        }

    cout << endl;
    cout << "Flip to" << endl;

    for (int i = 0; i < n; i++, cout << endl)
        for (int j = 0; j < n; j++)
            cout << chess[i][j] << " ";

    return 0;
}