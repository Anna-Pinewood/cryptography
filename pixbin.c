
#include <stdio.h>

void bin(int arg){
    int v = 128;
    for (int i=0; i<8; i++){
        if ((arg >= v)&& (arg !=0)) {
            printf("1");
            arg = arg-v;
        }
        else printf("0");
        v = v / 2;
        if (i==7) printf("\t");
    }
}
void pixbin(int arg1, int arg2, int arg3) {
    bin(arg1);
    bin(arg2);
    bin(arg3);
}
int main()
{
    int dig1;
    int dig2;
    int dig3;
    scanf("%d%d%d", &dig1, &dig2, &dig3);
   pixbin(dig1, dig2, dig3);
    return 0;
}
