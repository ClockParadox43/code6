#include <iostream>

using namespace std;

// 枚举第i个公司分配到多少台机器, 求出最大盈利
int n,m;
int ai[20][20];
int maxn=0;
int maxx[20];
int main()
{
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++)
        for(int j=1;j<=m;j++)
            scanf("%d",&ai[i][j]);

    for(int a=0;a<=m;a++)
        for(int b=0;b<=m-a;b++)
            for(int c=0;c<=m-a-b;c++)
                for(int d=0;d<=m-a-b-c;d++)
                    for(int e=0;e<=m-a-b-c-d;e++)
                        for(int f=0;f<=m-a-b-c-d-e;f++)
                            for(int g=0;g<=m-a-b-c-d-e-f;g++)
                                for(int h=0;h<=m-a-b-c-d-e-f-g;h++)
                                    for(int i=0;i<=m-a-b-c-d-e-f-g-h;i++)
                                    {
                                        int j=m-a-b-c-d-e-f-g-h-i;
                                                if(maxn<ai[1][a]+ai[2][b]+ai[3][c]+ai[4][d]+ai[5][e]+ai[6][f]+ai[7][g]+ai[8][h]+ai[9][i]+ai[10][j])
                                                {    maxn=ai[1][a]+ai[2][b]+ai[3][c]+ai[4][d]+ai[5][e]+ai[6][f]+ai[7][g]+ai[8][h]+ai[9][i]+ai[10][j];
                                            //  cout<<maxn<<endl;
                                                maxx[1]=a;
                                            maxx[2]=b;
                                        maxx[3]=c;
                                    maxx[4]=d;
                                maxx[5]=e;
                            maxx[6]=f;
                        maxx[7]=g;
                    maxx[8]=h;
                maxx[9]=i;
            maxx[10]=j;
        }}
    printf("%d\n",maxn);
    for(int i=1;i<=n;i++)
//  if(maxx[i]!=0)
    printf("%d %d\n",i,maxx[i]);
    return 0;
}
