#include <iostream>
using namespace std;

// Forward declaration of isBadVersion API.
/*
Last executed input:
versions, 1702766719 is the first bad version.

The problem for the above solution is the way of calculating mid, which could cause overflow problem.
int mid = (front + end) / 2;
We should use following safety way.
int mid = left + (right - left) / 2;

What's more.
What if there is no bad version? we should directly return -1.
if (!isBadVersion(n)){
    return -1;
}
*/

bool isBadVersion(int version);

class Solution {
public:
    int binarySearch(int low, int high)
    {
        if(low < high){
            int mid = low + (high - low)/2;
            if(isBadVersion(mid))
                return binarySearch(low, mid);
            else
                return binarySearch(mid + 1, high);
        }
        else
            return low;
    }
    int firstBadVersion(int n) {
        if(!isBadVersion(n))
            return -1;
        return binarySearch(1,n);
    }
};
