#include <stdio.h>

#define N 1010
#define M 1050
#define base 100000
#define basebit 5

int n;
int A[N],B[N];
// res:答案(最大中的最小的钱数), mx:大数乘
// dvd:累加和/B[i]
int res[M],mx[M],dvd[M],tmp[M]; 
int sres,smx,sdv,stmp;

inline int read()
{
    int x=0;
    char ch;
    do ch=getchar();while(ch==' '||ch=='\n');
    while(ch!=' '&&ch!='\n'&&~ch)
        x=x*10+ch-'0',ch=getchar();
    return x;
}

inline void data_swap(int a,int b)
{
    if(a^b)
    {
        A[a]^=A[b];
        A[b]^=A[a];
        A[a]^=A[b];
        B[a]^=B[b];
        B[b]^=B[a];
        B[a]^=B[b];
    }
}

void quick_sort(int l,int r)
{
    if(l>=r)return;
    int mid=A[l+r>>1]*B[l+r>>1];
    int i=l-1,j=r+1;
    while(i<j)
    {
        while(A[++i]*B[i]<mid);
        while(A[--j]*B[j]>mid);
        if(i<j)data_swap(i,j);
    }
    quick_sort(l,j);
    quick_sort(j+1,r);
}

inline void divd(int a[],int b,int c[])
{
    int flag=0;
    int t=0;
    stmp=1;tmp[0]=1;
    for(int i=smx-1;i>=0;i--)
    {
        t=t*base+mx[i];
        if(t>b||flag)
        {
            tmp[i]=t/b,t%=b;
            if(!flag)
            {
                stmp=i+1;
                flag=1;
            }
        }
    }
    for(int i=0;i<stmp;i++)
        c[i]=tmp[i];
    sdv=stmp;
}

inline void mul(int x,int a[])
{
    stmp=0;
    int t=0;
    for(int i=0;i<smx;i++)
    {
        t+=a[i]*x;
        tmp[stmp++]=t%base;
        t/=base;
    }
    while(t)
    {
        tmp[stmp++]=t%base;
        t/=base;
    }
    for(int i=0;i<stmp;i++)
        a[i]=tmp[i];
    smx=stmp;
}

inline void maxv(int a[],int b[])
{
    if(sres>sdv)return;
    else if(sres<sdv)
    {
        for(int i=0;i<sdv;i++)
            res[i]=dvd[i];
        sres=sdv;
    }
    else
        for(int i=sdv-1;i>=0;i--)
            if(dvd[i]>res[i])
            {
                for(int i=0;i<sdv;i++)
                    res[i]=dvd[i];
                sres=sdv;
                return;
            }
}

inline void print(int x)
{
    int mod=base/10;
    for(int i=1;i<=basebit;i++)
    {
        putchar(48+x/mod);
        x%=mod;
        mod/=10;
    }
}

int main()
{
    n=read();
    A[0]=read(),B[0]=read();
    for(int i=1;i<=n;i++)
        A[i]=read(),B[i]=read();
    quick_sort(1,n);
    mx[0]=1,smx=1;
    for(int i=0;i<=n;i++)
    {
        if(i)
        {
            divd(mx,B[i],dvd);
            maxv(res,dvd);
        }
        mul(A[i],mx);
    }
    printf("%d",res[sres-1]);
    for(int i=sres-2;i>=0;i--)
        print(res[i]);
    return 0;
}
