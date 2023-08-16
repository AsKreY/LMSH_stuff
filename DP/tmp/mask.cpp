#include <iostream>
#include <vector>
#include <cmath>


bool isin(int mask, int val)
{
    mask >>= val;
    return mask & 1;
}


int main()
{
    int n;
    std::cin >> n;
    std::vector<std::vector<int>> graph(n, std::vector<int>(n));
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            std::cin >> graph[i][j];
        }
    }
    std::vector<std::vector<int>> dp(n, std::vector<int>(pow(2, n), 1e9));
    for (int i = 0; i < n; i++)
    {
        dp[i][pow(2, i)] = 0;
    }
    //for (int i = 0; i < n; i++)
    {
        //for (int j = 0; j < 1 << n; j++)
        //{
            //std::cout << dp[i][j] << " ";
        //}
        //std::cout << "\n";
    //}
    for (int i = 1; i < 1 << n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            for (int g = 0; g < n; g++)
            {
                if (!isin(i, j) && isin(i, g) && dp[g][i] + graph[j][g] < dp[j][i | 1 << j])
                {
                    dp[j][i | 1 << j] = dp[g][i] + graph[j][g];
                }
            }
        }
    }
    int mn = 1e9;
    for (int i = 0; i < n; i++)
    {
        if (dp[i].back() < mn)
        {
            mn = dp[i].back();
        }
    }
    std::cout << mn;
}