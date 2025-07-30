
#include <stdio.h>
#include <stdlib.h>
int main() {
   int sum = 1;
    int a[256];
    for(int i=0;i<256;i++)
    {
        a[i]=i;
    }
    for (int i = 0; i < 256; i++) {
        sum = (a[255-i]*sum)/8;
    }
    printf(sum);
    return 0;
}