#include <iostream>

using namespace std;

/*

1. 先排除不相交的四种情况
2. 在有相交的情况下，分别求x轴和y轴的两个上下限x1,x2
    x1取两个矩形的左下角x值的较大者，
    x2取两个矩形的右上角x值的较小者，

*/

class Solution {
public:
    int computeArea(int A, int B, int C, int D, int E, int F, int G, int H) {
        int square1 = (C - A) * (D - B);
        int square2 = (G - E) * (H - F);
        int square = square1 + square2;
        if(C <= E || G <= A)
            return square;
        if(D <= F || H <= B)
            return square;

        int x1,x2,y1,y2;
        x1 = E > A ? E : A;
        x2 = G > C ? C : G;
        y1 = B > F ? B : F;
        y2 = H > D ? D : H;

        int repeat = (x2 - x1) * (y2 - y1);

        return square - repeat;

    }
};
