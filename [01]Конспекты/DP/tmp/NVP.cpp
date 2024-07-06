#include <iostream>
#include <vector>
#include <algorithm>

int main(){
    int n;
    std::cin >> n;
    std::vector<int> a(n);
    for (int i = 0; i < n; i++)
    {
        std::cin >> a[i];
    }
    std::vector<std::vector<int>> dp(n, std::vector<int>(n));
    dp[0][0] = a[0];
    for (int i = 1; i < n; i++)
    {
        dp[0][i] =  1e9;
    }
    for (int i = 1; i < n; i++)
    {
        dp[i] = dp[i - 1];
        int tmp = std::lower_bound(dp[i].begin(), dp[i].end(), a[i]) - dp[i].begin();
        dp[i][tmp] = a[i];
    }
    int ans = 0;
    for (int i = 0; i < n; i++)
    {
        if (dp[n - 1][i] < 1e9)
        {
            ans++;
        }
    }
    int j = n - 1;
    std::vector<int> answer(ans);
    for (int i = ans - 1; i >= 0; i--)
    {
        while (j > 0 && dp[j - 1][i] < 1e9)
        {
            j--;
        }
        answer[i] = dp[j][i];
    }
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            std::cout << dp[i][j] << " ";
        }
        std::cout << "\n";
    }
    for (int i = 0; i < ans; i++)
    {
        std::cout << answer[i];
    }

}