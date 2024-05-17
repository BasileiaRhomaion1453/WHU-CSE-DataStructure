#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void build_tree(int N, int *tree_count)
{
    int *arr = (int *)malloc(N * sizeof(int)), idx = 1;
    for (int j = 0; j < N; j++)
        arr[j] = 0;
    while (idx > 0)
    {
        if (idx == N + 1)
        {
            (*tree_count)++;
            printf("%d:", *tree_count);
            for (int i = 1; i < N; i++)
                printf("%d,", arr[i]);
            
            printf("%d\n", arr[N]);
            idx--;
        }
        if ((!arr[idx]) || ((arr[idx] >= arr[idx - 1] + 1) && (arr[idx] <= (arr[idx - 1] * 2))))
        {
            if (!arr[idx])
                arr[idx] = arr[idx - 1] + 1;
            else
                arr[idx]++;
            while (arr[idx] <= (arr[idx - 1] * 2))
            {
                int l = 1,temp = idx;
                while (l <temp)
                {
                    int mid = (l +temp) / 2;
                    if ((arr[idx] / 2) > arr[mid])
                        l = mid + 1;
                    else
                       temp = mid;
                }
                if (arr[l] == (arr[idx] / 2))
                    break;
                arr[idx]++;
            }
            idx++;
        }
        else
        {
            arr[idx] = 0;
            idx--;
        }
    }
}

int main()
{
    int N, tree_count = 0;
    printf("请输入结点数：\n");
    scanf("%d", &N);
    printf("\n");
    build_tree(N, &tree_count);
    printf("tree_count is %d when N is %d\n", tree_count, N);
    system("pause");
    return 0;
}