#include <iostream>
#include <vector>


int fastpow(int n, int p)
{
    if (p <= 0)
    {
        return 1;
    }
    if (p % 2 == 0)
    {
        int q;
        q = fastpow(n, p / 2);
        return q * q;
    }
    else
    {
        int q;
        q = fastpow(n, p / 2);
        return n * q * q;
    }
}


void dpcount(const std::vector<std::vector<int>>& graph, std::vector<bool>& dp, const std::vector<int>& neighbors, int n)
{
    int siz = fastpow(2, n), old = -1;
    dp[0] = 1;
    for (int i = 1; i < siz; i++)
    {
        if (!(i & (i - 1)))
        {
            ++old;
        }
        int tmp = i ^ (1 << old);
        if (dp[tmp] && ((tmp | neighbors[old]) ^ neighbors[old]))
        {
            dp[i] = 1;
        }
    }
}


void neighborscount(const std::vector<std::vector<int>>& graph, std::vector<int>& neighbors, const int n)
{
    for (int i = 0; i < n; i++)
    {
        int mask = 0;
        for (int j = 0; j < n; j++)
        {
            if (graph[i][j] == 1)
            {
                mask |= 1 << j;
            }
        }
        neighbors[i] = mask;
    }
}


int main(){
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
    std::vector<int> neighbors(n);
    neighborscount(graph, neighbors, n);
    for (int i = 0; i < n; i++)
    {
        std::cout << neighbors[i] << " ";
    }
    std::vector<bool> dp(fastpow(2, n));
    dpcount(graph, dp, neighbors, n);
    for (int i = 0; i < fastpow(2, n); i++)
    {
        std::cout << i << " " << dp[i] << "\n";
    }
}