#include <iostream>
#include <cstdio>
using namespace std;
// lomuto
int main() 
{
    int T;
    scanf("%d", &T);
    getchar(); 

    while (T--) 
    {
        int a[2000], n = 0;
        int x;
        char c;
        while (true) 
        {
            if (scanf("%d", &x) != 1) 
            break;
            a[n++] = x;

            c = getchar();
            if (c == '\n' || c == EOF) 
            break;
        }
        int pivot = a[n - 1];
        int i = -1;

        for (int j = 0; j < n - 1; j++) 
        {
            if (a[j] < pivot) 
            {
                i++;
                int tmp = a[i];
                a[i] = a[j];
                a[j] = tmp;
            }
        }

        int tmp = a[i + 1];
        a[i + 1] = a[n - 1];
        a[n - 1] = tmp;

        printf("%d\n", i + 1); 
    }

    return 0;
}
