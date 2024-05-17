#include<stdio.h>
#include<stdlib.h>
#include<math.h>
double log2(int n)
{
    return log10(n) / log10(2);
}
long long int jie(int n)
{
    int i ;long long int s = n;
    for (i=n-1; i > 0; i--)
        s = s * i;
    return s;
}
int main()
{
    int n;
    scanf_s("%d", &n);
    printf("log2n   sqrtn   n   nlog2n  n^2     n^3     n!\n");
    for (; n > 0; n--)
        printf("%5.2f   %5.2f  %2d   %5.2f  %5.2f  %5.2f  %5lld\n", log2(n), sqrt(n), n, n * log2(n), pow(n, 2), pow(n, 3), jie(n));
    return 0;
}