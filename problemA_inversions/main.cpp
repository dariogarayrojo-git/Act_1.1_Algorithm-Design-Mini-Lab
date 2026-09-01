/* Problem A - Inversion Counter for Quality Control
 Technique: Divide & Conquer (modified Merge Sort)

 A pair (i, j) with i < j is an inversion if A[i] > A[j].
 We count inversions while merge-sorting the array: every time we take an
 element from the RIGHT half before the LEFT half is exhausted, all the
 remaining elements in the left half form an inversion with it.

 Time complexity:  O(n log n)  -> same recurrence as merge sort:
      T(n) = 2*T(n/2) + O(n)  =>  O(n log n)
 Space complexity: O(n) auxiliary array + O(log n) recursion stack.
*/

#include <iostream>
#include <vector>
using namespace std;
using ll = long long;

// Merge two sorted halves a[l..mid] and a[mid+1..r], counting split inversions.
ll mergeCount(vector<ll>& a, vector<ll>& tmp, int l, int mid, int r) {
    int i = l, j = mid + 1, k = l;
    ll inv = 0;

    while (i <= mid && j <= r) {
        if (a[i] <= a[j]) {
            tmp[k++] = a[i++];
        } else {
            // a[i] > a[j]  =>  a[i..mid] are all > a[j] (left half is sorted)
            // so all of them form inversions with a[j].
            inv += (mid - i + 1);
            tmp[k++] = a[j++];
        }
    }
    while (i <= mid) tmp[k++] = a[i++];
    while (j <= r)   tmp[k++] = a[j++];

    for (int p = l; p <= r; p++) a[p] = tmp[p];
    return inv;
}

ll sortCount(vector<ll>& a, vector<ll>& tmp, int l, int r) {
    if (l >= r) return 0;
    int mid = l + (r - l) / 2;
    ll inv = 0;
    inv += sortCount(a, tmp, l, mid);
    inv += sortCount(a, tmp, mid + 1, r);
    inv += mergeCount(a, tmp, l, mid, r);
    return inv;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    if (!(cin >> n)) return 0;
    vector<ll> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];

    vector<ll> tmp(n);
    ll inv = (n > 1) ? sortCount(a, tmp, 0, n - 1) : 0;

    cout << inv << "\n";
    return 0;
}
