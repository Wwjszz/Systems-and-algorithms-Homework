#include <iostream>

using namespace std;

struct CPU;

CPU *cpu;

// 线程
struct Thread
{
    int x, y, width, height; // 用于画图，x坐标 y坐标 宽度width 高度height
    int wait_time;           // 等待时间
    enum
    {
        RUNNING,   // 正在CPU中被处理
        NOTARRIVE, // 未到达
        ARRIVE,    // 到达
        WAITTING,  // 到达但是在等待
    } status;      // 进程的状态

    // 初始化
    void init(int x, int y, int width, int height)
    {
        this->x = x;
        this->y = y;
        this->width = width;
        this->height = height;
        this->status = NOTARRIVE;
        this->wait_time = 0;
    }

    // 运行
    void run()
    {
        if (status == NOTARRIVE)
        {
            x += 1; // 前进
        }
        else if (status == ARRIVE || status == WAITTING)
        {
            wait_time += 1;
        }
        else
        {
            add_to_cpu(this, cpu);
        }
    }

    // 画图
    void draw()
    {
        drawRectangle(this);
    }
};

// CPU
struct CPU
{
    int x, y, width, height; // 用于画图，x坐标 y坐标 宽度width 高度height
    Thread *cur_thread;

    // 初始化
    void init(int x, int y, int width, int height)
    {
        this->x = x;
        this->y = y;
        this->width = width;
        this->height = height;
        cur_thread = NULL;
    }

    // 处理进程
    void process()
    {
        if (cur_thread)
        {
            cur_thread->x += 1;
            if (cur_thread->x >= x)
            {
                cur_thread = NULL;
            }
        }
    }

    // 画图
    void draw()
    {
        drawRectangle(this);
    }
};

void add_to_cpu(Thread *thread, CPU *cpu)
{
}

void drawRectangle(void *thread) {}

int main()
{

    return 0;
}