#include <stdio.h>
#include <string.h>
#include <stdlib.h>

const int values[7] = {30,45,60,50,65,70,35};
const int price[7] = {2,3,5,4,6,8,1};
const char mapName[7][25] = {"蔬菜","鸡蛋","鱼","牛奶","猪肉","牛肉","米饭"};
const int MAX_VALUES = 200;
const int MIN_VALUES = 180;

static int food_numbers[7];
static int max_types;

//回溯得出所有解决方案
void dfs(int i,int cur_value,int cur_price,int type){
    //剪枝
    if(cur_value > 200 || (cur_value < 180 && i == 7))
        return;
    //得到结果
    if(i == 7){
        if(max_types > type)return;
        max_types = type;
        for(int j = 0;j < i;j++){
            if(food_numbers[j]){
                printf("%d个%s ",food_numbers[j],mapName[j]);
            }
        }
        printf("总花费为:%d 营养价值为:%d 种类数为:%d\n",cur_price,cur_value,type);
        return;
    }

    //dfs
    int max_number = (200 - cur_value) /  price[i];
    for(int n = max_number;~n;n--){
        food_numbers[i] = n;
        dfs(i+1,cur_value + values[i] * n,cur_price + price[i] * n,type + !!n);
    }
}

int ans[7];
int ans_price = -1;

//寻找最优解
void dfs_price(int i,int cur_value,int cur_price,int type){
    //剪枝
    if(cur_value > 200 || (cur_value < 180 && i == 7))
        return;
    //得到结果
    if(i == 7){
        if(max_types > type)return;
        if((cur_price > ans_price && ans_price != -1))return;
        ans_price = cur_price;
        memcpy(ans,food_numbers,sizeof(int) * 7);
        return;
    }

    //dfs
    int max_number = (200 - cur_value) /  price[i];
    for(int n = max_number;~n;n--){
        food_numbers[i] = n;
        dfs_price(i+1,cur_value + values[i] * n,cur_price + price[i] * n,type + !!n);
    }
}


int main()
{
    printf("满足条件的方案如下:\n");
    dfs(0,0,0,0);

    puts("");

    printf("最优方案如下（花费最小）:\n");
    dfs_price(0,0,0,0);
    
    int value = 0;
    for(int j = 0;j < 7;j++)
        if(ans[j]){
            printf("%d个%s ",ans[j],mapName[j]);
            value += ans[j] * values[j];
        }
    printf("总花费为:%d 总营养为:%d 种类数为:%d\n",ans_price,value,max_types);

    return 0;
}