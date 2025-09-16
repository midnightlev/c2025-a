#include <stdio.h>
#include <stdbool.h>

bool is_prime(int integer)
{
    if (integer == 1) return false;
    // if (integer == 2) return true;
    for (int i=2; i <= integer/2; i++)
    {
        if (integer % i == 0) return false;
    }
    return true;
}

int main() {
    // 验证哥德巴赫猜想
    for (int i = 4; i <= 100; i+=2)
    {
        // 获取所有小于当前偶数的质数
        for (int j = 2; j < i; j++)
        {
            if (is_prime(j)) // 找到一个质数
            {
                if (is_prime(i - j)) // 当前偶数减去这个质数是否还是质数
                {
                    printf("%d = %d + %d\n", i, j, i - j);
                    goto next; // 跳过错误信息打印
                }
            }
        }
        printf("Failed: %d ", i);
        next: continue;
    }
    return 0;
}