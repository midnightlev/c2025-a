#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>
#include <time.h>
#include <string.h>

#define WIDTH 15
#define HEIGHT 15

// Map element definitions
#define WALL '#'
#define PATH ' '
#define PLAYER 'P'
// #define EXIT 'E'
#define GOAL '*'
#define BOX '@'


typedef struct {
    char map[HEIGHT][WIDTH];
    char original_map[HEIGHT][WIDTH];
    int rows, cols;
    int playerX, playerY;
    int boxCount;           // 箱子数量
    int targetsFilled;      // 已填满的目标点数量
    int steps;              // 步数计数器
} GameState;


int loadMap(GameState *game, const char *filename) {
    FILE *file = fopen(filename, "r");
    if (!file) return 0;

    // 读取地图尺寸
    if (fscanf(file, "%d %d", &game->rows, &game->cols) != 2) {
        fclose(file);
        return 0;
    }

    // 跳过行尾的换行符
    int c;
    while ((c = fgetc(file)) != '\n' && c != EOF);

    // 检查地图尺寸是否合法
    if (game->rows > HEIGHT || game->cols > WIDTH) {
        fclose(file);
        return 0;
    }

    char buffer[WIDTH + 2];  // 缓冲区大小至少为列数+2
    game->boxCount = 0;
    game->targetsFilled = 0;

    for (int i = 0; i < game->rows; i++) {
        if (fgets(buffer, sizeof(buffer), file) == NULL) {
            break;
        }

        // 去除换行符
        buffer[strcspn(buffer, "\r\n")] = '\0';

        for (int j = 0; j < game->cols; j++) {
            // 如果缓冲区中字符不足，则用空格填充
            if (j < strlen(buffer)) {
                game->map[i][j] = buffer[j];
            } else {
                game->map[i][j] = PATH;
            }

            // 记录玩家位置
            if (game->map[i][j] == PLAYER) {
                game->playerX = j;
                game->playerY = i;
            }

            // 统计箱子数量
            if (game->map[i][j] == BOX) {
                game->boxCount++;
            }
        }
    }

    fclose(file);
    memcpy(game->original_map, game->map, sizeof(game->map));
    game->steps = 0;
    return 1;
}


void saveScore(const char *playerName, int steps, int level) {
    FILE *file = fopen("scores.txt", "a"); // 追加模式
    if (!file) return;

    time_t now = time(NULL);
    struct tm *t = localtime(&now);

    fprintf(file, "%s,%d,%d,%04d-%02d-%02d %02d:%02d:%02d\n",
            playerName, steps, level,
            t->tm_year + 1900, t->tm_mon + 1, t->tm_mday,
            t->tm_hour, t->tm_min, t->tm_sec);

    fclose(file);
}


// 初始化迷宫
void loadLevel(GameState *game, int level)
{
    // Load map
    char level_filename[64];
    sprintf(level_filename, "maze_%d.txt", level);
    loadMap(game, level_filename);
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
void displayMaze(GameState *game) {
    system("cls");
    for(int i = 0; i < HEIGHT; i++) {
        for(int j = 0; j < WIDTH; j++) {
            printf("%c", game->map[i][j]);
        }
        printf("\n");
    }
}

void displayScore(GameState *game)
{
    printf("Score: %d\n", game->steps);
    printf("Goal: %d\n", game->targetsFilled);
}

void displayInterface(GameState *game)
{
    displayMaze(game);
    displayScore(game);
}

// 处理玩家移动
int movePlayer(GameState *game, int dx, int dy) {
    int newX = game->playerX + dx;
    int newY = game->playerY + dy;

    // 检查是否可以移动（不是墙壁）
    if(game->map[newY][newX] != WALL) {
        // 是否推动箱子
        if (game->map[newY][newX] == BOX)
        {
            // 是否有不可推动块
            if (game->map[newY+dy][newX+dx] == WALL || game->map[newY+dy][newX+dx] == BOX) return 0;
            // 设置箱子新位置
            game->map[newY+dy][newX+dx] = BOX;
            // 是否加减分
            if (game->original_map[newY][newX] == GOAL)
            {
                game->targetsFilled--;
            }
            else if (game->original_map[newY+dy][newX+dx] == GOAL) {game->targetsFilled++;}
        }

        // 更新玩家位置
        game->map[game->playerY][game->playerX] = PATH;
        // 复位类空气像素
        if (game->original_map[game->playerY][game->playerX] == GOAL)
        {
            printf("True");
            game->map[game->playerY][game->playerX] = GOAL;
        }
        // 设置新坐标
        game->playerX = newX;
        game->playerY = newY;
        // 设置新玩家显示位置
        game->map[game->playerY][game->playerX] = PLAYER;

        game->steps++;

        if (game->boxCount == game->targetsFilled) {return 1;}

        // 检查是否到达出口
        // if(playerX == exitX && playerY == exitY) {
        //     return 1; // 游戏胜利
        // }
    }
    return 0;
}

// Main loop
void gameLoop(GameState *game) {
    // define gameOver flag
    int gameOver = 0;

    char input;

    while(!gameOver) {
        displayInterface(game);
        input = getDirectionInput();

        switch(input) {
        case 'w': case 'W':
            gameOver = movePlayer(game, 0, -1); break;
        case 's': case 'S':
            gameOver = movePlayer(game, 0, 1); break;
        case 'a': case 'A':
            gameOver = movePlayer(game, -1, 0); break;
        case 'd': case 'D':
            gameOver = movePlayer(game, 1, 0); break;
        case 'q': case 'Q':
            return; // 退出游戏
        }
    }

    displayMaze(game); // update to show that player went to exit
    saveScore("player", game->steps, 0);
    printf("Level Clear!\n");
    system("pause");
}

int main() {
    SetConsoleOutputCP(65001);
    GameState game;

    int level;
    scanf("%d", &level);
    loadLevel(&game, level);
    gameLoop(&game);

    return 0;
}