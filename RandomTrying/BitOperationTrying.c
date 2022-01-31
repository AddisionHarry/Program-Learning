#include<stdio.h>

int main(void){
    int a = 0x004A02;
    printf("a \t\t= 0x%X\n",a);
    printf("a & 0xFF00 \t= 0x%X\n",a & 0xFF00);
    printf("a >> 2 \t\t= 0x%X\t\ta / 4 \t= 0x%X\n",a >> 2,a / 4);
    printf("a << 2 \t\t= 0x%X\t\ta * 4 \t= 0x%X\n",a << 2,a * 4);
    printf("(a >> 2) << 2 \t= 0x%X\n\n",(a >> 2) << 2);

    short b = -1;
    printf("b \t\t\t= 0x%X\n",b);
    printf("b >> 8 \t\t\t= 0x%X\n",b >> 8);
    printf("(unsigned char)(b >> 8)   = 0x%X\n", (unsigned char)(b >> 8));
    printf("(unsigned char)(b & 0xFF) = 0x%X\n", (unsigned char)(b & 0xFF));
    unsigned char c=(unsigned char)(b >> 8),d=(unsigned char)(b & 0xFF);
    printf("(unsigned char)(b >> 8) << 8 | (unsigned char)(b & 0xFF) = 0x%X\n",(c << 8) | d);
    printf("(short)((unsigned char)(b >> 8) << 8 | (unsigned char)(b & 0xFF)) = %d\n\n",(short)((c << 8) | d));

    return 0;
}
