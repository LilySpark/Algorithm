#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>

char* strcpy(char *dst,const char *src)   //[1]
{
    assert(dst != NULL && src != NULL);    //[2]

    char *ret = dst;  //[3]

    while ((*dst++=*src++)!='\0'); //[4]

    return ret;
}

char *my_memcpy(char *dst, const char* src, int cnt)
{
    assert(dst != NULL && src != NULL);

    char *ret = dst;

    if (dst >= src && dst <= src+cnt-1) //内存重叠，从高地址开始复制
    {
        dst = dst+cnt-1;
        src = src+cnt-1;
        while (cnt--)
            *dst-- = *src--;
    }
    else    //正常情况，从低地址开始复制
    {
        while (cnt--)
            *dst++ = *src++;
    }

    return ret;
}

//有内存重叠的情况
char* strcpy2(char *dst,const char *src)
{
    assert(dst != NULL && src != NULL);

    char *ret = dst;

    my_memcpy(dst, src, strlen(src)+1);

    return ret;
}


int main()
{
    char a[10];
    char b[10] = "apple";
    char* c = strcpy2(b+2, b);
    printf("%s", b);
    return 0;
}
