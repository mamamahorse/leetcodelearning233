// #include <iostream>
// #include <cstdio>
// #include <cmath>
// using namespace std;

// bool primenumber(int n)
// {
//     if (n <= 1)
//         return false;
//     if (n == 2)
//         return true;
//     for (int i = 2; i * i <= n; i++)
//     {
//         if (n % i == 0)
//             return false;
//     }
//     return true;
// }

// int findmax(int a[])
// {
//     int max = 0;
//     for (int i = 0; i < 26; i++)
//     {
//         if (max < a[i])
//             max = a[i];
//     }
//     return max;
// }

// int findmin(int a[])
// {
//     int min;
//     for (int i = 0; i < 26; i++)
//     {
//         if (a[i] != 0)
//         {
//             min = a[i];
//             break;
//         }
//     }
//     for (int i = 0; i < 26; i++)
//     {
//         if (a[i] > 0 && a[i] < min)
//             min = a[i];
//     }
//     return min;
// }

// int main()
// {
//     char s[100];
//     scanf("%s", s);
//     int array[26] = {0};
//     for (int i = 0; s[i]; i++)
//     {
//         array[s[i] - 'a']++;
//     }
//     int maxn = findmax(array);
//     int minn = findmin(array);
//     if (primenumber(maxn - minn))
//         cout << "Lucky Word" << endl;
//     else
//         cout << "No Answer" << endl;
//     cout << maxn - minn;
// }
