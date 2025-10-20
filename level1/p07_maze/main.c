#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>

#define WIDTH 15
#define HEIGHT 15

// 迷宫元素定义
#define WALL '#'
#define PATH ' '
#define PLAYER 'P'
#define EXIT 'E'

char map[HEIGHT][WIDTH] = {
    "###############",
    "#P            #",
    "### ###  ######",
    "#     #       #",
    "# ########### #",
    "#           # #",
    "# ##### ##### #",
    "#   #   #     #",
    "##### # #######",
    "#     #       #",
    "# ########### #",
    "# # # #       #",
    "# # # # #######",
    "#     #      E#",
    "###############"
};  // Map
int playerX, playerY;      // 玩家位置
int exitX, exitY;          // 出口位置


// 初始化迷宫
void initMaze()
{
    // Init player pos
    playerX = playerY = 1;

    // Set exit pos
    exitX = exitY = 13;
}

char getDirectionInput() {
    int ch = _getch();

    if (ch == 0 || ch == 224) {
        ch = _getch();

        switch(ch) {
        case 72: return 'W';  // 上箭头
        case 80: return 'S';  // 下箭头
        case 75: return 'A';  // 左箭头
        case 77: return 'D';  // 右箭头
        }
    }

    // return if not direction keys
    return ch;
}

// 显示迷宫
void displayMaze() {
    system("cls");
    for(int i = 0; i < HEIGHT; i++) {
        for(int j = 0; j < WIDTH; j++) {
            printf("%c", map[i][j]);
        }
        printf("\n");
    }
}

// 处理玩家移动
int movePlayer(int dx, int dy) {
    int newX = playerX + dx;
    int newY = playerY + dy;

    // 检查是否可以移动（不是墙壁）
    if(map[newY][newX] != WALL) {
        // 更新玩家位置
        map[playerY][playerX] = PATH;
        playerX = newX;
        playerY = newY;
        map[playerY][playerX] = PLAYER;

        // 检查是否到达出口
        if(playerX == exitX && playerY == exitY) {
            return 1; // 游戏胜利
        }
    }
    return 0;
}

// Main loop
void gameLoop() {
    // define gameOver flag
    int gameOver = 0;
    char input;

    while(!gameOver) {
        displayMaze();
        input = getDirectionInput();

        switch(input) {
        case 'w': case 'W':
            gameOver = movePlayer(0, -1); break;
        case 's': case 'S':
            gameOver = movePlayer(0, 1); break;
        case 'a': case 'A':
            gameOver = movePlayer(-1, 0); break;
        case 'd': case 'D':
            gameOver = movePlayer(1, 0); break;
        case 'q': case 'Q':
            return; // 退出游戏
        }
    }

    displayMaze(); // update to show that player went to exit
    printf("恭喜你成功走出迷宫！\n");
    system("pause");
}

int main() {
    SetConsoleOutputCP(65001);
    initMaze();
    gameLoop();
    return 0;
}