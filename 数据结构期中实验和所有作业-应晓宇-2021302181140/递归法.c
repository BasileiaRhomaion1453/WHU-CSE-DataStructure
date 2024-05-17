#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void arrange(int arr[], int idx, int N, int *tree_count, int *height)
{
    if (idx == N)
    {
        (*tree_count)++;
        printf("%d:", *tree_count);
        for (int i = 0; i < N; i++)
            printf("%d,", arr[i]);
        printf("\n");
        *height += (int)(ceil(log(arr[N - 1] + 1) / log(2)));
        return;
    }
    for (int i = 0; i < idx; ++i)
    {
        arr[idx] = 2 * arr[i];
        if (arr[idx] > arr[idx - 1])
            arrange(arr, idx + 1, N, tree_count, height);

        arr[idx] = 2 * arr[i] + 1;
        if (arr[idx] > arr[idx - 1])
            arrange(arr, idx + 1, N, tree_count, height);
    }
}
int catalan(int n)
{
    if (n <= 1)
        return 1;
    int *h = (int *)malloc(sizeof(int));
    h[0] = h[1] = 1;
    for (int i = 2; i <= n; ++i)
    {
        h[i] = 0;
        for (int j = 0; j < i; j++)
            h[i] += (h[j] * h[i - 1 - j]);
    }
    int result = h[n];
    free(h);
    return result;
}

int main()
{
    int N;
    printf("请输入二叉树结点数\n");
    scanf("%d", &N);
    printf("\n");
    int *arr = (int *)malloc(sizeof(int) * N);
    for (int i = 0; i < N; i++)
        arr[i] = 1;
    int count = 0, height = 0;
    arr[0] = 1;
    double aver;
    int c;
    c = catalan(N);
    arrange(arr, 1, N, &count, &height);
    aver = (float)height / count;
    printf("*tree_count is %d when N is %d\n", count, N);
    if (count == c)
        printf("N为%d时卡塔兰数为%d,符合\n", N, c);
    else
        printf("N为%d时卡塔兰数为%d,不符合\n", N, c);
    printf("平均高度 %lf\n", aver);
    printf("log2N is %lf\n", log(N) / log(2));
    system("pause");
    return 0;
}