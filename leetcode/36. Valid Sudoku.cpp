#include <iostream>
#include <vector>
#include <map>

using namespace std;

class Solution {
public:
    bool isValidSudoku(vector<vector<char>>& board) {

        map<char,int> count[27];

        for(int i = 0; i < 9; i++)
        {
            for(int j = 0; j < 9; j++)
            {
                if(board[i][j]!='.')
                {
                    count[i][board[i][j]]++;
                    if(count[i][board[i][j]] > 1)
                        return false;

                    count[j+9][board[i][j]]++;
                    if(count[j+9][board[i][j]] > 1)
                        return false;

                    int idx = (i/3)*3 + j/3 + 9*2;
                    count[idx][board[i][j]]++;
                    if(count[idx][board[i][j]] > 1)
                        return false;
                }

            }
        }

        return true;

    }
};
