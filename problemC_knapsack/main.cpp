/* Problem C - Budgeted Study Plan (0/1 Knapsack)
 Technique: Dynamic Programming

 dp[j] = maximum value achievable using a time budget of exactly-or-up-to j
 hours, considering the modules processed so far.

 Recurrence (1D rolling array, standard 0/1 knapsack trick):
   for each module i (time t_i, value v_i):
       for j = T down to t_i:
           dp[j] = max(dp[j], dp[j - t_i] + v_i)

 Iterating j in DECREASING order guarantees each module is used at most
 once per row update (it prevents reusing the same module twice within the
 same iteration, which is what would happen in an unbounded knapsack).

 Time complexity:  O(n * T)   (n modules, T budget levels)
 Space complexity: O(T) using the rolling 1D array (a 2D dp[n][T] table
                    would be O(n*T); we only need the previous row at any
                    time, so we compress it to O(T)).
*/

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
using ll = long long;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, T;
    if (!(cin >> n >> T)) return 0;

    vector<int> t(n);
    vector<ll> v(n);
    for (int i = 0; i < n; i++) cin >> t[i] >> v[i];

    vector<ll> dp(T + 1, 0);

    for (int i = 0; i < n; i++) {
        if (t[i] > T) continue; // module can never fit, skip early
        for (int j = T; j >= t[i]; j--) {
            dp[j] = max(dp[j], dp[j - t[i]] + v[i]);
        }
    }

    ll best = dp[T];
    cout << best << "\n";
    return 0;
}
