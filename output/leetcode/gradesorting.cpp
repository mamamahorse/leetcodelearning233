#include <iostream>
#include <string>
#include <vector>

using namespace std;

class student {
public: 
    string name;
    int ID;
    int chinese;
    int math;
    int english;
    int total;

    student() {}

    void calculateTotal() 
    {
        total = chinese + math + english;
    }

    void print() 
    {
        cout << ID << " " << name << " " << total << endl;
    }
};

int main() {
    int N;
    cin >> N; 

    vector<student> students(N);
    for (int i = 0; i < N; i++) 
    {
        cin >> students[i].ID 
            >> students[i].name 
            >> students[i].chinese 
            >> students[i].math 
            >> students[i].english;
        
        students[i].calculateTotal();
    }

    for (int i = 0; i < N - 1; i++) 
    {
        for (int j = 0; j < N - 1 - i; j++) 
        {
            bool Swap = false;
            
            student s1 = students[j];   
            student s2 = students[j + 1]; 
            if (s2.total > s1.total) 
            {
                Swap = true;
            } 
            else if (s2.total == s1.total) 
            {
                if (s2.chinese > s1.chinese) 
                {
                    Swap = true;
                }
                else if (s2.chinese == s1.chinese) 
                {
                    if (s2.math > s1.math) 
                    {
                        Swap = true;
                    }
                }
            }

            if (Swap) 
            {
                student temp = students[j];
                students[j] = students[j + 1];
                students[j + 1] = temp;
            }
        }
    }

    for (int i = 0; i < N; i++) {
        students[i].print();
    }

    return 0;
}