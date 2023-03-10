#include <bits/stdc++.h>
using namespace std;
const int inf=1e9;
int a;
int main()
{
    srand(clock());
    freopen("out","w",stdout);
    printf("100\n");
    for(int i=1;i<=100;i++)
    {
        int a=rand();
        while(a<-1*inf||a>inf)
        {
            a=rand();
        }
        printf("%d ",a);
    }
    return 0;
}