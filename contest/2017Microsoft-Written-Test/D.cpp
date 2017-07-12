/*
题目链接：http://hihocoder.com/problemset/problem/1402
给一个矩阵，其中包含一些特殊点组成M和S两个字母，不同字母之间是分开的，求其中两个字母的个数。

分析：
观察可以发现M和S字母的最小外包矩形的中心和字母两个端点的中间点区别较大，所以可以利用这个特征来进行区分。
区分的阈值还是要经过不断的调整。

----- 来自讨论区的大牛(http://hihocoder.com/discuss/question/3970)
*/


#include <queue>
#include <cmath>
#include <cstring>
#include <cstdio>
using namespace std;
#define min(a,b) ((a)<(b)?(a):(b))
#define max(a,b) ((a)>(b)?(a):(b))
#define MAXN 501
#define DOT '#'
#define CLR 'X'
#define BEG '@'
#define END '@'
#define MID '@'

int H, W;
char pic[MAXN][MAXN];
const int dx[] = { 1, 1, 1, -1, -1, -1, 0, 0 };
const int dy[] = { 1,-1, 0,  1, -1,  0, 1,-1 };

struct Point {
    int x, y;
    Point( int x = 0, int y = 0 ) : x(x), y(y) { }
    bool valid() const {
        return 0 <= x && x < H && 0 <= y && y < W;
    }
    bool operator==( const Point &rhs ) const {
        return x == rhs.x && y == rhs.y;
    }
};

void coloring( Point sp, Point &hp, int &u, int &d, int &l, int &r ) {
    if ( !sp.valid() || pic[sp.x][sp.y] != DOT ) { return; }
    pic[sp.x][sp.y] = CLR;
    if( sp.x < u ) { hp = sp; }
    u = min(u, sp.x); d = max(d, sp.x);
    l = min(l, sp.y); r = max(r, sp.y);
    for( int i = 0; i < sizeof(dx)/sizeof(dx[0]); ++i ) {
        coloring( Point(sp.x+dx[i],sp.y+dy[i]), hp, u, d, l, r );
    }
}

// 找端点
void bfs( Point sp, Point &ep ) {
    bool vis[MAXN][MAXN];
    memset(vis, false, sizeof(vis));
    queue<Point> q;
    q.push( sp );
    while( !q.empty() ) {
        Point p = q.front(); q.pop();
        for( int i = 0; i < sizeof(dx)/sizeof(dx[0]); ++i ) {
            Point np(p.x+dx[i], p.y+dy[i]);
            if( np.valid() && pic[np.x][np.y] == CLR && !vis[np.x][np.y] ) {
                vis[np.x][np.y] = true;
                q.push( np );
            }
        }
        ep = p;
    }
}

void output(){
    puts("######### DEBUG! ########");
    for(int i=0;i<H;i++){
        puts(pic[i]);
    }
}

int main()
{
    while( 2 == scanf("%d %d", &H, &W) ) {
        for( int i = 0; i < H; ++i ) {
            scanf( "%s", pic[i] );
        }
        int countM = 0;
        int countS = 0;
        for( int x = 0; x < H; ++x ) {
            for( int y = 0; y < W; ++y ) {
                if( pic[x][y] != DOT ) { continue; }
                int u = H, d = 0, l = W, r = 0;
                Point sp( x, y ), hp( x, y );
                coloring( sp, hp, u, d, l, r );  // 找上下左右边界
                Point center( (u+d)/2, (l+r)/2 );

                //printf("x:%d y:%d l:%d r:%d u:%d d:%d\n", x, y, l, r, u, d);
                //output();

                Point ep1, ep2, mid;
                bfs( hp,  ep1 );  // 随便从一点出发找其中一个端点
                bfs( ep1, ep2 );  // 从找到的一个端点出发，找另外一个端点

                mid = Point( (ep1.x+ep2.x)/2, (ep1.y+ep2.y)/2 );
                pic[mid.x][mid.y] = MID;
                pic[ep1.x][ep1.y] = BEG;
                pic[ep2.x][ep2.y] = END;

                Point &m = mid;
                Point &c = center;
                
                //利用字母端点的中点和矩形的中心的曼哈顿距离进行区分
                if( abs(m.x-c.x)+abs(m.y-c.y) < ((r-l)+(d-u)) / 5 ) {  // 5这个参数的自己慢慢调
                    ++countS;
                } else {
                    ++countM;
                }
            }
        }
        printf("%d %d\n", countM, countS);
    }
}
