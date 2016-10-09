/*
找一点使得到三个人的总距离最短。
*/
#include <cstdio>
#include <iostream>
using namespace std;

int main()
{
    int a, b, c;
    cin >> a >> b >> c;
    cout << max(a, max(b, c)) - min(a, min(b, c)) << endl;
    return 0;
}
