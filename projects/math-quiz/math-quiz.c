#include <stdio.h>

int main()
{
    unsigned count[10] = {0};
    unsigned temp = 0;
    for (unsigned i = 1; i <= 168; ++i) {
        temp = i;
        while (temp > 0) {
            ++count[temp % 10];
            temp /= 10;
        }
    }
    for (unsigned i = 0; i < 10; ++i)
        printf("%d occurs %d times\n", i, count[i]);
    return 0;
}