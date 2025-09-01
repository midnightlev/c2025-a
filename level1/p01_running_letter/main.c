#include <stdio.h>
#include <windows.h>

// 我对C与C++一窍不通……代码复用差了点关键知识
// API我查的

// 获取控制台窗口的宽度
int getConsoleWidth() {
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    int columns;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
    columns = csbi.srWindow.Right - csbi.srWindow.Left + 1;
    return columns;
}

// 清空当前行
void clearLine(int length, int position) {
    COORD coord;
    coord.X = 0;
    coord.Y = 0;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);

    for (int i = 0; i < length; i++) {
        printf(" ");
    }

    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void move_forward(int end_pos, int target_pos)
{
    for (int pos = 0; pos < end_pos; pos++)
    {
        // each frame:
        if (target_pos == pos)
        {
            printf("A");
        }
        else
        {
            printf(" ");
        }
    }
    Sleep(50);
    clearLine(end_pos, end_pos);
}

void move_backwards(int end_pos, int target_pos)
{
    for (int pos = 0; pos < end_pos; pos++)
    {
        // each frame:
        if (target_pos == pos)
        {
            printf("A");
        }
        else
        {
            printf(" ");
        }
    }
    Sleep(50);
    clearLine(end_pos, end_pos);
}

int main() {
    int end_pos = getConsoleWidth();
    const int TOTAL_STEPS = 5;
    int this_step = 0;
    while (this_step < TOTAL_STEPS)
    {
        for (int target_pos = 0; target_pos < end_pos; target_pos++)
        {
            move_forward(end_pos, target_pos);
        }
        for (int target_pos = end_pos; target_pos > 0; target_pos--)
        {
            move_backwards(end_pos, target_pos);
        }
        this_step++;
    }
    return 0;
}