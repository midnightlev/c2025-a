#include <stdio.h>
#include <time.h>

int main() {
    time_t start, end;
    start = time(NULL);
    for (int i = 2; i <= 1000; i++)
    {
        for (int j = 2; j <= i / 2; j++)
        {
            if (i % j == 0) {goto next;}
        }
        printf("%d ", i);
        next:continue;
    }
    printf("\n");
    end = time(NULL);
    printf("Total: %lld s\n", (end - start));
    return 0;
}