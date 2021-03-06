#include <cstdio>

#define max(a, b) (a > b ? a : b)
#define max_3(a, b, c) max(a, max(b, c))

int main()
{
    int no_of_trees;
    scanf("%d", &no_of_trees);

    long long height[no_of_trees + 1];
    long long x[no_of_trees + 1];
    for(int i = 1; i <= no_of_trees; i++)
        scanf("%I64d %I64d", &x[i], &height[i]);

    const int RIGHT = 1, STRAIGHT = 0, LEFT = 2;
    int max_cut[no_of_trees + 1][3];
    max_cut[0][RIGHT] = max_cut[0][STRAIGHT] = max_cut[0][LEFT] = 0;

    for(int i = 1; i <= no_of_trees; i++)
    {
        max_cut[i][STRAIGHT] = max_3(max_cut[i - 1][LEFT], max_cut[i - 1][STRAIGHT], max_cut[i - 1][RIGHT]);

        max_cut[i][LEFT] = max_cut[i][RIGHT] = max_cut[i][STRAIGHT];

        if(i == 1 || x[i] - height[i] > x[i - 1])
            max_cut[i][LEFT] = 1 + max(max_cut[i - 1][LEFT], max_cut[i - 1][STRAIGHT]);

        if(height[i - 1] + height[i] + x[i - 1] < x[i])
            max_cut[i][LEFT] = max(max_cut[i][LEFT], 1 + max_cut[i - 1][RIGHT]);

        if(i == no_of_trees || height[i] + x[i] < x[i + 1])
            max_cut[i][RIGHT] = 1 + max_cut[i][STRAIGHT];

    }

    int answer = max_3(max_cut[no_of_trees][RIGHT], max_cut[no_of_trees][STRAIGHT], max_cut[no_of_trees][LEFT]);

    printf("%d\n", answer);
    return 0;
}
