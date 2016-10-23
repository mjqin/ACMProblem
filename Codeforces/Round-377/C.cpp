// http://codeforces.com/contest/732/problem/C
#include <cstdio>
#include <cstring>
#include <iostream>
#include <queue>
#include <vector>
#include <map>
#include <set>
#include <cmath>
#include <stack>
#include <algorithm>
#include <functional>
#include <cmath>
#include <bitset>
using namespace std;
#define MP make_pair
#define FI first
#define SE second

long long a, b, c;

int main(){
    cin >> a >> b>> c;
    if(a == b && a == c) cout << 0 << endl;
    else if(a == b) {
        if(c < a) cout << a - 1 - c << endl;
        else cout << (c - 1 - a) * 2 << endl;
    }
    else if(b == c){
        if(a < b) cout << b - 1 - a << endl;
        else cout << (a - 1 - b) * 2 << endl;
    }
    else if(a == c){
        if(b < a) cout << a - 1 - b << endl;
        else cout << (b - 1 - a) * 2 << endl;
    }
    else{
        long long  t = max(a, max(b, c));
        cout << (t - a) + (t - b) + (t - c) - 2 << endl;
    }

    return 0;
}
