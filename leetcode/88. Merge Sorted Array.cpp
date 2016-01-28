#include <iostream>
#include <vector>
using namespace std;

class Solution {
public:
    void merge(vector<int>& nums1, int m, vector<int>& nums2, int n) {
        int i=0;
        int j=0;
        int k=0;
        while(k < m && j < n)
        {
            if(nums1[i] < nums2[j]){
                i++;
                k++;
            }
            else if(nums1[i] > nums2[j]){
                nums1.insert(nums1.begin()+i, nums2[j]);
                i++;
                j++;
            }
            else{
                nums1.insert(nums1.begin()+i, nums2[j]);
                j++;
                i+=2;
                k++;
            }
        }
        while(j < n)
            nums1[i++] = nums2[j++];

        for(int i = nums1.size()-1; i >= m+n; i--)
            nums1.erase(nums1.begin()+i);
    }
};

class Solution {
public:
	void merge(vector<int>& nums1, int m, vector<int>& nums2, int n)
	{
		nums1.resize(m + n);

		while (m > 0 && n > 0)
		{
			if (nums1[m - 1] < nums2[n - 1]){
				nums1[m + n - 1] = nums2[n - 1];
				--n;
			}
			else{
				nums1[m + n - 1] = nums1[m - 1];
				--m;
			}
		}
		while (n > 0)
		{
			nums1[n - 1] = nums2[n - 1];
			--n;
		}
	}
};

int main()
{
    vector<int> nums1{1,2,3,0,0,0};
    vector<int> nums2{2,5,6};

    Solution s;
    s.merge(nums1,3,nums2,3);
    for(int i=0; i < nums1.size(); i++)
        cout<<nums1[i]<<" ";
    cout<<endl;
}




