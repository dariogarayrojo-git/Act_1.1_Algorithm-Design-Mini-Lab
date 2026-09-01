/* Problem B - Minimum Meeting Rooms (Scheduling)
 Technique: Greedy (event sweep / two-pointer over sorted starts & ends)

 Idea: sort all start times and all end times separately. Sweep through
 meetings in order of start time. Keep a pointer to the earliest end time
 not yet "freed". Whenever the current meeting starts at or after that
 earliest end, a room is freed and can be reused (no new room needed);
 otherwise we need a brand new room.

 This is equivalent to: at every moment, the number of rooms needed equals
 the maximum number of meetings simultaneously "in progress". The greedy
 choice (reuse a room as soon as it's free) is optimal because we never
 hold a room idle when a waiting meeting could use it, and we never need
 more rooms than the true maximum overlap.

 Time complexity:  O(m log m) for sorting starts and ends.
 Space complexity: O(m) for the two arrays of starts/ends.
*/

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int m;
    if (!(cin >> m)) return 0;

    vector<long long> starts(m), ends(m);
    for (int i = 0; i < m; i++) {
        cin >> starts[i] >> ends[i];
    }

    sort(starts.begin(), starts.end());
    sort(ends.begin(), ends.end());

    int rooms = 0, maxRooms = 0;
    int i = 0, j = 0;

    while (i < m) {
        if (starts[i] < ends[j]) {
            // A meeting starts before the earliest currently-running one ends
            // -> need a new room.
            rooms++;
            i++;
            maxRooms = max(maxRooms, rooms);
        } else {
            // starts[i] >= ends[j]: a room has freed up (a meeting ending at
            // the same time a new one starts does NOT count as overlap, so
            // the freed room can be reused).
            rooms--;
            j++;
        }
    }

    cout << maxRooms << "\n";
    return 0;
}
