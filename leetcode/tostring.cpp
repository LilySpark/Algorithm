#include <iostream>
#include <string>
#include <stdio.h>
using namespace std;

int main()
{
    int n = -65535;
    char t[256];
    string s;

    sprintf(t, "%d", n);
    s = t;
    cout << s << endl;

    return 0;
}
