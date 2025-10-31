#include <iostream>
#include <vector>
using namespace std;

int main() {
    int n;
    cin >> n;
    vector<int> table(n, -1); 
    int key;
    while (cin >> key) 
    {
        int h = key % n;
        while (table[h] != -1) 
        {  
            h = (h + 1) % n;
        }
        table[h] = key;
    }
    for (int i = 0; i < n; i++) 
    {
        if (table[i] != -1)
            cout << i << " " << table[i] << "\n";
    }
}
