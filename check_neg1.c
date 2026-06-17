#include <stdio.h>

int main()
{
    int x = -1;
    unsigned char *p = (unsigned char *)&x;
    for (int i = 0; i < sizeof(int); i++) {
        printf("%02x ", p[i]);
    }
    printf("\n");
    return 0;
}
