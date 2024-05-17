#include<stdio.h>
#include<stdlib.h>
#define maxsize 100
typedef struct
{
    char data[maxsize];
    int length;
}str;
void strassign(str &s, char cstr[])
{
    int i;
    for (i = 0; cstr[i] != '\0'; i++)
        s.data[i] = cstr[i];
    s.length = i;
}
void dispstr(str s)
{
    int i;
    if (s.length > 0)
    {
        for (i = 0; i < s.length; i++)
            printf("%c", s.data[i]);
        printf("\n");
    }
}
int easy(str s, str t)
{
    int i = 0, j = 0;
    while (i < s.length && j < t.length)
    {
        if (s.data[i] == t.data[j])
        {
            i++;
            j++;
        }
        else
        {
            i = i - j + 1;
            j = 0;
        }
    }
    if (j >= t.length)
        return (i - t.length);
    else
        return -1;
}
void getnext(str t, int next[])
{
    int j, k;
    j = 0; k = -1; next[0] = -1;
    while (j < t.length - 1)
    {
        if (k == -1 || t.data[j] == t.data[k])
        {
            j++;
            k++;
            next[j] = k;
        }
        else
            k = next[k];
    }
}
int kmp(str s, str t)
{
    int next[maxsize], i = 0, j = 0;
    getnext(t, next);
    while (i < s.length && j< t.length)
    {
        if (j == -1 || s.data[i] == t.data[j])
        {
            i++;
            j++;
        }
        else
            j = next[j];
    }
    if (j >= t.length)
        return (i - t.length);
    else
        return -1;
}
void getnextval(str t, int nextval[])
{
    int j = 0, k = -1;
    nextval[0] = -1;
    while (j < t.length)
    {
        if (k == -1 || t.data[j] == t.data[k])
        {
            j++;
            k++;
            if (t.data[j] != t.data[k])
                nextval[j] = k;
            else
                nextval[j] = nextval[k];
        }
        else
            k = nextval[k];
    }
}
int kmpup(str s, str t)
{
    int nextval[maxsize], i = 0, j = 0;
    getnextval(t, nextval);
    while (i < s.length && j < t.length)
    {
        if (j == -1 || s.data[i] == t.data[j])
        {
            i++;
            j++;
        }
        else
            j = nextval[j];
    }
    if (j >= t.length)
        return (i - t.length);
    else
        return -1;
}
int main()
{
    int j;
    int next[maxsize], nextval[maxsize];
    str s, t;
    char ss[] = "abcabcdabcdeabcdefabcdefg";
    char tt[] = "abcdeabcdefab";
    strassign(s, ss);
    strassign(t, tt);
    printf("串s："); dispstr(s);
    printf("串t："); dispstr(t);
    printf("简单匹配算法：\n");
    printf("t在s中的位置=%d\n", easy(s, t));
    getnext(t, next);
    getnextval(t, nextval);
    printf("j      ");
    for (j = 0; j < t.length; j++)
        printf("%4d", j);
    printf("\n");
    printf("t[j]   ");
    for (j = 0; j < t.length; j++)
        printf("%4c", t.data[j]);
    printf("\n");
    printf("next   ");
    for (j = 0; j < t.length; j++)
        printf("%4d", next[j]);
    printf("\n");
    printf("nextval");
    for (j = 0; j < t.length; j++)
        printf("%4d", nextval[j]);
    printf("\n");
    printf("kmp算法：\n");
    printf("t在s中的位置=%d\n", kmp(s, t));
    printf("改进的kmp算法：\n");
    printf("t在s中的位置=%d\n", kmpup(s, t));
    system("pause");
    return 0;
}