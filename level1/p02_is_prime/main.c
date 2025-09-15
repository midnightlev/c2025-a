#include <stdio.h>

int main() {
    int num;
    printf("Enter an integer: ");
    scanf("%d", &num);
    // 排除特殊值 0, 1
    if (num == 1 || num == 0)
    {
        printf("Not prime\n");
        return 0;
    }
    for (int i = 2; i < num; i++)
    {
        if (num % i == 0)
        {
            printf("Not Prime\n");
            return 0;
        }
    }
    printf("Prime\n");
    return 0;
}