#include <stdio.h>

void move_one(char from, char to)
{
    printf("%c -> %c.\n", from, to);
};

void hanoi(int n, char from, char by, char to)
{
    if (n==1)
    {
        move_one(from, to);
        return;
    }
    hanoi(n-1, from, to, by);
    move_one(from, to);
    hanoi(n-1, by, from, to);
}

int main() {
    hanoi(3, 'A', 'B', 'C');
    return 0;
}
