#include <bits/stdc++.h>
// #include <bits/extc++.h>
#define px first
#define py second
#define endl '\n'
#define LF cout << '\n'
#define rep(x, y, z) for (x = (y); (x) <= (z); (x)++)
#define per(x, y, z) for (x = (y); (x) >= (z); (x)--)
#define all(x) (x).begin(), (x).end()
#define SZ(x) ((int)(x).size())
#define pb push_back
#define mp make_pair
using namespace std;
// using namespace __gnu_pbds;
mt19937 rnd(time(0));
typedef long long LL;
typedef long double LD;
typedef pair<int, int> PII;
typedef vector<int> VI;
typedef vector<LL> VLL;
typedef vector<PII> VPII;
// tree<int,null_type,less<int>,rb_tree_tag,tree_order_statistics_node_update> tr;
const double eps = 1e-8;
const int INF = 0x3f3f3f3f;
const LL LINF = 9e18 + 7;
const LL mod = 1e9 + 7;
inline LL powmod(LL a, LL b) // 快速幂
{LL res = 1; a %= mod; assert(b >= 0); for (; b; b >>= 1){if (b & 1)res = res * a % mod; a = a * a % mod;} return res;}
LL gcd(LL a, LL b) { return b ? gcd(b, a % b) : a; } // gcd
template <typename T> inline void read(T &x) // 快读,无需处理前面空白
{x = 0; int f = 1; char ch = getchar(); while (!isdigit(ch)){if (ch == '-') f = -1; ch = getchar();}
while (isdigit(ch)){x = x * 10 + (ch ^ 48); ch = getchar();} x *= f;}
template <typename T> inline void write(T x) //快写
{if (x < 0) putchar('-'), x = -x; if (x > 9) write(x / 10); putchar(x % 10 + '0');}
inline void close_iostream_sync(){ios::sync_with_stdio(0); cin.tie(0),cout.tie(0);}
inline void local_debug(){
#ifndef ONLINE_JUDGE
    freopen("D:\\ACM programs\\in.txt", "r+", stdin);
    freopen("D:\\ACM programs\\out.txt", "w+", stdout);
#endif
}


// #define double LD

struct point // 点
{
    double x,y;
    point(){}
    point(double x,double y):x(x),y(y){}
};
typedef point vec;  // 向量
typedef vector<point> poly; // 多边形
struct line // 直线（点向式）
{
    point p;vec v;
    line(){}
    line(point x,vec y):p(x),v(y){}
};   
struct seg // 线段（存两个端点）
{
    point a,b;
    seg(){}
    seg(point a,point b):a(a),b(b){}
};       
struct circle // 圆（存圆心和半径）
{
    point o;double r;
    circle(){}
    circle(point a,double b):o(a),r(b){}
};

// 输入输出流
istream &operator>>(istream &in, point &p) // 点
{
    in >> p.x >> p.y;
    return in;
}

ostream &operator<<(ostream &out, point &p) // 点
{
    out << p.x << ' ' << p.y;
    return out;
}

// 常量
// const double eps = 1e-8;
const double PI=acos(-1);
const point O={0,0};                   // 原点
const line OX={O,{1,0}},OY={O,{0,1}}; // 坐标轴

int sign(double x) // 符号函数
{
    if (abs(x)<eps) return 0;
    if (x<0) return -1;
    return 1;
}

int cmp(double x, double y) // 比较函数
{
    if (abs(x-y)<eps) return 0;
    if (x<y) return -1;
    return 1;
}

// 函数依赖
bool eq(double a, double b){return abs(a-b)<eps;} // ==
bool gt(double a, double b){return a-b>eps;}      // >
bool lt(double a, double b){return a-b<-eps;}     // <
bool ge(double a, double b){return a-b>-eps;}     // >=
bool le(double a, double b){return a-b<eps;}      // <=

// 基础操作
double rtod(double rad){return 180/PI*rad;}             //弧度转角度
double dtor(double degree){return PI/180*degree;}       //角度转弧度
vec operator+(vec u,vec v){return {u.x+v.x,u.y+v.y};}   // 向量加向量
vec operator-(vec u,vec v){return {u.x-v.x,u.y-v.y};}   // 向量减向量
vec operator*(vec v,double k){return {k*v.x,k*v.y};}    // 数乘
vec operator*(double k,vec v){return {k*v.x,k*v.y};}    // 数乘
vec operator/(vec v,double k){return {1/k*v.x,1/k*v.y};}// 数除
vec operator/(double k,vec v){return {1/k*v.x,1/k*v.y};}// 数除
double operator*(vec u,vec v){return u.x*v.x+u.y*v.y;}  // 点乘
double operator^(vec u,vec v){return u.x*v.y-u.y*v.x;}  // 叉乘

// 点
point mid(point a,point b){return (a+b)/2;} // 两点中点

// 向量
double area(vec v,vec u){return v^u;}                  // 有向面积
double len(vec v){return sqrt(v.x*v.x+v.y*v.y);}       // 向量长度
double polar_angle(vec v){return atan2(v.y,v.x);}      // 极角
double angle(vec u,vec v){return acos(u*v/len(u)/len(v));} // 两向量的夹角
double angle_cos(vec u,vec v){return u*v/len(u)/len(v);}   // 两向量的夹角余弦
double slope(vec v){return v.y/v.x;}                   // 斜率,不要用isinf判断斜率不存在，用后面的paral_y
vec norm(vec v){return {v.x/len(v),v.y/len(v)};}       // 归一化向量（与原向量方向相同的单位向量）
vec pnorm(vec v){return (v.x<0?-1:1)/len(v)*v;}        // 与原向量平行且横坐标大于等于0的单位向量
vec ra90(vec v){return {-v.y,v.x};}                    // 逆时针旋转90度的向量
vec rc90(vec v){return {v.y,-v.x};}                    // 顺时针旋转90度的向量
vec ra180(vec v){return {-v.x,-v.y};}                  // 逆时针旋转180度的向量
vec rc180(vec v){return {-v.x,-v.y};}                  // 顺时针旋转180度的向量

// 直线
line get_line(point a,point b){return {a,b-a};}         // 两点式直线
line get_line(double k,double b){return {{0,b},{1,k}};} // 斜截式直线
line get_line(point p,double k){return {p,{1,k}};}      // 点斜式直线
line get_line(seg l){return {l.a,l.b-l.a};}             // 线段所在直线
// 给定直线的横坐标求纵坐标,请确保直线不与y轴平行
double get_y(line l,double x){return l.p.y+(x-l.p.x)*l.v.y/l.v.x;}
// 给定直线的纵坐标求横坐标,请确保直线不与x轴平行
double get_x(line l,double y){return l.p.x-(y+l.p.y)*l.v.x/l.v.y;}
point pedal(point p,line l){return l.p-(l.p-p)*l.v/(l.v*l.v)*l.v;} // 点到直线的垂足
line perp(point p,line l){return {p,rc90(l.v)};}                   // 过某点作直线的垂线
line bisec(point p,vec u,vec v){return {p,norm(u)+norm(v)};}       // 角平分线

// 线段
vec dvec(seg l){return l.b-l.a;} // 线段的方向向量,直线的方向向量直接访问属性v
point midp(seg l){return {(l.a.x+l.b.x)/2,(l.a.y+l.b.y)/2};} // 线段中点
line mid_perp(seg l){return {midp(l),rc90(l.b-l.a)};}        // 线段中垂线

// 多边形
double area(poly &p) // 求多边形有向面积
{
    double res=0;
    int i;
    rep(i,1,SZ(p)-2)res+=(p[i]-p[0])^(p[i+1]-p[0]);
    return res/2;
}

// 几何对象之间的关系
bool verti(vec u,vec v){return eq(u*v,0);} // 向量是否互相垂直
bool paral(vec u,vec v){return eq(u^v,0);} // 向量是否互相平行
bool paral_x(vec v){return eq(v.y,0);}     // 向量是否与x轴平行
bool paral_y(vec v){return eq(v.x,0);}     // 向量是否与y轴平行
bool on(point p,line l){return eq((p.x-l.p.x)*l.v.y,(p.y-l.p.y)*l.v.x);} // 点是否在直线上
bool on(point p,seg l){return eq(len(p-l.a)+len(p-l.b),len(l.a-l.b));}   // 点是否在线段上
bool on(point p,circle c){return eq(len(p-c.o),c.r);}                    // 点是否在圆上
bool onleft(point a,point b,point c){return gt((b-a)^(c-a),0);}     // c点是否在向量 ab 左边
bool onright(point a,point b,point c){return lt((b-a)^(c-a),0);}    // c点是否在向量 ab 右边
bool onleft(line a,point b){return gt(a.v^(b-a.p),0);}              // b点是否在直线 a 左边
bool onright(line a,point b){return lt(a.v^(b-a.p),0);}             // b点是否在直线 a 右边
double cross(point a,point b,point c){return (b-a)^(c-b);}          // 返回onleft函数中的叉积
bool operator==(point a,point b){return eq(a.x,b.x)&&eq(a.y,b.y);}  // 两个点是否重合
bool operator!=(point a,point b){return !(a==b);}                   // 两个点是否不重合
bool operator==(line a,line b){return on(a.p,b)&&on(a.p+a.v,b);}    // 两条直线是否重合
bool operator!=(line a,line b){return !(a==b);}                     // 两条直线是否不重合
bool operator==(seg a,seg b){return (a.a==b.a&&a.b==b.b)||(a.a==b.b&&a.b==b.a);} // 两条线段是否重合
bool operator!=(seg a,seg b){return !(a==b);}                       // 两条线段是否不重合
bool operator==(circle a,circle b){return (a.o==b.o)&&eq(a.r,b.r);} // 两个圆是否重合
bool operator!=(circle a,circle b){return !(a==b);}                 // 两个圆是否不重合
// 第一关键词为 横坐标、第二关键字为 纵坐标
bool operator<(point a,point b){return lt(a.x,b.x)||(eq(a.x,b.x)&&lt(a.y,b.y));}
// 第一关键字为 极角，第二关键字为 左右位置，在平行线中靠左的在前
bool operator<(line x,line y)
{
    double a1,a2;
    a1=polar_angle(x.v);
    a2=polar_angle(y.v);
    if(!eq(a1,a2))return a1<a2;
    return onright(x,y.p);
}
bool istan(line l,circle c){return eq(abs((c.o^l.v)-(l.p^l.v)),c.r*len(l.v));} // 直线与圆是否相切
bool istan(circle c1,circle c2){return eq(len(c1.o-c2.o),c1.r+c2.r);} // 圆与圆是否相切
bool in(point a,circle c){return lt(len(a-c.o),c.r);} // 点 a 是否严格在圆内
bool in(point a,poly &p) // 点 a 是否在多边形内
{
    int i,n=p.size(),cnt=0;
    rep(i,0,n-1)
    {
        if(on(a,seg(p[i],p[(i+1)%n])))return -1;
        int k=sign(((p[(i+1)%n]-p[i])^(a-p[i])));
        int d1=sign(p[i].y-a.y);
        int d2=sign(p[(i+1)%n].y-a.y);
        if(k>0&d1<=0&d2>0)cnt++;
        if(k<0&d2<=0&d1>0)cnt--;
    }
    if(cnt)return 1;
    else return 0;
}

// 距离
double dis(point a,point b){return len(a-b);} // 两点间的距离
double dis(point p,line l){return abs((p^l.v)-(l.p^l.v))/len(l.v);} // 点到直线的距离
double dis(point p,seg l) // 点到线段的距离
{
    point a=l.a,b=l.b;
    if(a==b)return dis(p,a);
    vec v1=b-a,v2=p-a,v3=p-a;
    if(sign(v1*v2)<0)return len(v2);
    if(sign(v1*v3)>0)return len(v3);
    return dis(p,get_line(l));
}
double dis(line a,line b){return abs((a.p^pnorm(a.v))-(b.p^pnorm(b.v)));} // 平行直线间的距离,请确保两直线是平行的

// 平移
line operator+(line l,vec v){return {l.p+v,l.v};}
seg operator+(seg l,vec v){return {l.a+v,l.b+v};}

// 旋转
// 将 向量/点 顺时针/逆时针 旋转 rad 度，以向量起点为中心
vec rttc(vec v,double rad){return {v.x*cos(rad)+v.y*sin(rad),-v.x*sin(rad)+v.y*cos(rad)};}
vec rtta(vec v,double rad){return {v.x*cos(rad)-v.y*sin(rad),v.x*sin(rad)+v.y*cos(rad)};}
// 将 p 点围绕 c 点 顺时针/逆时针 旋转 rad 度
point rttc(point p,point c,double rad){return c+rttc(p-c,rad);}
point rtta(point p,point c,double rad){return c+rtta(p-c,rad);}
// 将直线围绕 c 点 顺时针/逆时针 旋转 rad 度
line rttc(line l,point c,double rad){return {rttc(l.p,c,rad),rttc(l.v,rad)};}
line rtta(line l,point c,double rad){return {rtta(l.p,c,rad),rtta(l.v,rad)};}
// 将线段围绕 c 点 顺时针/逆时针 旋转 rad 度
seg rttc(seg l,point c,double rad){return {rttc(l.a,c,rad),rttc(l.b,c,rad)};}
seg rtta(seg l,point c,double rad){return {rtta(l.a,c,rad),rtta(l.b,c,rad)};}

// 对称
// 关于点 p 对称
point sym(point a,point p){return {p.x*2-a.x,p.y*2-a.y};}
line sym(line l,point p){return {sym(l.p,p),l.v};} //等效平移      
seg sym(seg l,point p){return {sym(l.a,p),sym(l.b,p)};}

// 关于直线（对称轴）对称
// NOTE 向量和点在这里的表现不同，求向量关于某直线的对称向量需要用 sym_vec
point sym(point a,line ax){return sym(a,pedal(a,ax));}            
vec sym_vec(vec v,line ax){return sym(v,ax)-sym(O,ax);}       
line sym(line l,line ax){return {sym(l.p,ax),sym_vec(l.v,ax)};} //轴对称
seg sym(seg l,line ax){return {sym(l.a,ax),sym(l.b,ax)};}

// 投影
double proj(vec a,vec b){return a*b/len(b);} // 向量 a 在 向量 b 上的投影

// 交点 重合时返回空集
// 直线与直线交点
typedef vector<point> VP;
vector<point> inter(line a,line b)
{
    double c=a.v^b.v;
    if(eq(c,0))return {};
    double t=(b.v^(a.p-b.p))/(a.v^b.v);
    return {{a.p.x+a.v.x*t,a.p.y+a.v.y*t}};
}

// 直线与圆交点
vector<point> inter(line l,circle c)
{
    point p=pedal(c.o,l);
    double h=len(p-c.o);
    if(gt(h,c.r))return {};
    if(eq(h,c.r))return {p};
    double d=sqrt(c.r*c.r-h*h);
    vec v=d/len(l.v)*l.v;
    return {p+v,p-v};
}

// 圆与圆的交点
vector<point> inter(circle c1,circle c2)
{
    vec v1=c2.o-c1.o,v2=rc90(v1);
    double d=len(v1);
    if(gt(d,c1.r+c2.r)||gt(abs(c1.r-c2.r),d))return {};
    if(eq(d,c1.r+c2.r)||eq(d,abs(c1.r-c2.r)))return {c1.o+c1.r/d*v1};
    double a=((c1.r*c1.r-c2.r*c2.r)/d+d)/2;
    double h=sqrt(c1.r*c1.r-a*a);
    vec av=a/len(v1)*v1,hv=h/len(v2)*v2;
    if((c1.o+av+hv)!=(c1.o+av+hv))return {};
    return {c1.o+av+hv,c1.o+av-hv};
}

// 圆
// 以两点连线为直径的圆
circle get_circle(point a,point b){return {mid(a,b),dis(a,b)/2};} 
circle get_circle(point a,point b,point c) // 三点确定一个圆
{
    seg l1={a,b},l2={a,c};
    point o=inter(mid_perp(l1),mid_perp(l2))[0];
    return {o,dis(o,a)};
}

double outcr(double x){if(!sign(x))return 0;return x;} // 输出 0 修正



const int N = 1e5 + 11;

VP v;
int used[N],stk[N],idx=-1;
int n;
VP ans(4);
double ans_area;

void get_convex()
{
    sort(v.begin()+1,v.end());
    int i;
    rep(i,1,n)
    {
        if(i>1&&v[i]==v[i-1])continue;
        while(idx>=1&&ge(cross(v[stk[idx-1]],v[stk[idx]],v[i]),0))
        {
            if(eq(cross(v[stk[idx-1]],v[stk[idx]],v[i]),0))idx--;
            else used[stk[idx--]]=0;
        }
        used[i]=1;
        stk[++idx]=i;
    }
    used[1]=0;
    int top=idx;
    per(i,n,1)
    {
        if(used[i]||i<=n-1&&v[i]==v[i+1])continue;
        while(idx>=top+1&&ge(cross(v[stk[idx-1]],v[stk[idx]],v[i]),0))
        {
            if(eq(cross(v[stk[idx-1]],v[stk[idx]],v[i]),0))idx--;
            else used[stk[idx--]]=0;
        }
        used[i]=1;
        stk[++idx]=i;
    }
    reverse(stk,stk+idx+1);

}


void rotating_calipers()
{
    int i,a,b,c;
    a=c=2;b=1;
    rep(i,0,idx-1)
    {
        point d=v[stk[i]],e=v[stk[i+1]];
        line l=get_line(d,e);
        while(lt(dis(v[stk[a]],l),dis(v[stk[(a+1)%idx]],l)))a=(a+1)%idx;
        if(gt(cross(d,v[stk[c]],v[stk[a]]),0))c=a;
        while(gt(proj(v[stk[c]]-d,l.v),proj(v[stk[(c+1)%idx]]-d,l.v)))c=(c+1)%idx;
        while(lt(proj(v[stk[b]]-d,l.v),proj(v[stk[(b+1)%idx]]-d,l.v)))b=(b+1)%idx;
        double h=dis(v[stk[a]],l);
        double w=abs(proj(v[stk[c]]-d,l.v))+abs(proj(v[stk[b]]-d,l.v));
        if(h*w<ans_area)
        {
            ans_area=h*w;
            ans[0]=d+rc180(norm(l.v))*abs(proj(v[stk[c]]-d,l.v));
            ans[1]=d+norm(l.v)*abs(proj(v[stk[b]]-d,l.v));
            vec up=ra90(norm(l.v))*h;
            ans[3]=ans[0]+up;
            ans[2]=ans[1]+up;
        }

    }

}



signed main()
{
    local_debug();
    int i,j;
    cin>>n;
    v.resize(n+1);
    rep(i,1,n)cin>>v[i];
    ans_area=9e18;
    get_convex();
    rotating_calipers();
    printf("%.5f\n",ans_area);
    point minn={9e18,9e18};
    int pos;
    rep(i,0,3)
        if(ans[i].y<minn.y||ans[i].y==minn.y&&ans[i].x<minn.x)
        {
            minn=ans[i];
            pos=i;
        }
    rep(i,pos,pos+3)
        printf("%.5f %.5f\n",ans[i%4].x,ans[i%4].y);
    return 0;
}

