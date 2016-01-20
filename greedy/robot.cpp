// Problem#: 1321
// Submission#: 1177427
// The source code is licensed under Creative Commons Attribution-NonCommercial-ShareAlike 3.0 Unported License
// URI: http://creativecommons.org/licenses/by-nc-sa/3.0/
// All Copyright reserved by Informatic Lab of Sun Yat-sen University
#include <cstdio>
#include <cstring>
#include <queue>
using namespace std;

struct Path {
    int i, j;
    int dist;
    Path( int a, int b, int c ) { i = a; j = b; dist = c; }
    friend bool operator < ( const Path &p1, const Path &p2 ) { return p1.dist > p2.dist; }
};

int dirt[ 4 ][ 2 ] = { { -1, 0 }, { 0, 1 }, { 1, 0 }, { 0, -1 } };

int main()
{
    int T;
    int row, column;
    int si, sj, ti, tj;
    int i, j, k;
    int grid[ 101 ][ 101 ];
    bool included[ 101 ][ 101 ];

    scanf( "%d", &T );
    while ( T-- ) {
        priority_queue<Path> q;
        scanf( "%d%d", &row, &column );
        for ( i = 1; i <= row; i++ ) {
            for ( j = 1; j <= column; j++ )
                scanf( "%d", &grid[ i ][ j ] );
        }
        scanf( "%d%d%d%d", &si, &sj, &ti, &tj );

        memset( included, false, sizeof( included ) );
        included[ si ][ sj ] = true;
        Path add = Path( si, sj, grid[ si ][ sj ] );
        while ( !included[ ti ][ tj ] ) {
            for ( k = 0; k < 4; k++ ) {
                i = add.i + dirt[ k ][ 0 ];
                j = add.j + dirt[ k ][ 1 ];
                if ( i >= 1 && i <= row && j >= 1 && j <= column && !included[ i ][ j ] ) {
                    q.push( Path( i, j, add.dist + grid[ i ][ j ] ) );
                }
            }

            add = q.top();
            while ( included[ add.i ][ add.j ] ) {
                q.pop();
                add = q.top();
            }
            included[ add.i ][ add.j ] = true;
        }
        printf( "%d\n",add.dist );
    }

    return 0;

}
