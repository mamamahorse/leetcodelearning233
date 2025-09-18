// #include <iostream>
// using namespace std;
// int main()
// {
//     int n; 
//     int arr[40][40]={0};
//     cin>>n;
//     int x,y;
//     arr[0][n/2]=1;
//     x=0;
//     y=n/2;
//     for(int i=2;i<=n*n;i++)
//     {
//         if(x==0&&y!=n-1)
//        { arr[n-1][y+1]=i;
//         x=n-1;
//         y+=1;}
//         else if(x!=0&&y==n-1)
//        {arr[x-1][0]=i;
//         x-=1;
//         y=0;
//        }
//         else if(x==0&&y==n-1)
//        {arr[x+1][y]=i;
//         x+=1;
 
//        }
//        else if(x!=0&&y!=n-1)
//        {
//         if(arr[x-1][y+1]==0)
//         {
//             arr[x-1][y+1]=i;
//             x--;
//             y++;
//         }
//         else
//         {
//             arr[x+1][y]=i;
//             x++;
//         }
//        }
//     }
//     for(int i=0;i<n;i++)
//     {
//     for(int j=0;j<n;j++)
//     {cout<<arr[i][j]<<" ";
//     }
//     cout<<endl;}
// }