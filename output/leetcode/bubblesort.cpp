#include <iostream>
#include <cstdio>
using namespace std;

int main() {
    int T;
    scanf("%d", &T);
    getchar(); 

    while (T--) 
    {
        int a[2000], n = 0;
        int x;
        char c;

        while (true) 
        { scanf("%d", &x);
            a[n++] = x;

            c = getchar();        
            if (c == '\n' || c == EOF)
             break;  
        }

        int iterations = 0;
        int count=0;
        while (true) 
        {
            bool swapped = false;
            // 冒泡从右往左
            for (int i = n - 1; i > count; i--) 
            {
                if (a[i] < a[i - 1]) 
                {
                    int t = a[i];
                    a[i] = a[i - 1];
                    a[i - 1] = t;
                    swapped = true;
                }
            }
            iterations++;

            count++;
            if (!swapped) 
            break;

        }
        if(iterations<n)
        printf("%d\n", iterations);
        else
        printf("%d\n",n-1);
    }

    return 0;
}
void bubbleSort(vector<int>& a) {
    int n = a.size();
    int count = 0; // 左边界，表示 count 左边全是排好序的

    while (true) {
        bool swapped = false;
        int lastSwapIndex = n; // 记录这一轮最后一次发生交换的下标 优化的最重点！

        // 冒泡从右往左
        for (int i = n - 1; i > count; i--) {
            if (a[i] < a[i - 1]) {
                swap(a[i], a[i - 1]);
                swapped = true;
                
                // 更新最后交换的位置:
                // 因为是从右往左扫，越晚发生的交换，下标越小（越靠左）
                // 这个位置就是新的有序边界
                lastSwapIndex = i; 
            }
        }

        if (!swapped) break;

        // 核心优化：直接把 count 更新为最后一次交换的位置
        // 如果 0~3 都没有发生交换，lastSwapIndex 就会停在 4，count 直接变 4
        count = lastSwapIndex; 
    }
}