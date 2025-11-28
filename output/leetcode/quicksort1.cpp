#include <iostream>
#include <sstream>
#include <vector>
using namespace std;

int Partition(vector<int>& a)
{
    int n = a.size();
    int pivot = a[n - 1];  
    int left = 0, right = n - 2;

    while (true)
    {
        while (a[left] < pivot) 
        left++;
        while (right >= 0 && a[right] > pivot) 
        right--;

        if (left >= right) break;

        swap(a[left], a[right]);
        left++;
        right--;
    }
    swap(a[left], a[n - 1]);

    return left;     
}

int main() 
{
    string line;
    int T;
    cin >> T;
    cin.ignore();

    while (T--) {
        getline(cin, line);
        stringstream ss(line);
        vector<int> a;
        int x;
        while (ss >> x) a.push_back(x);

        int pos = Partition(a);
        cout << pos << "\n";
    }

    return 0;
}
