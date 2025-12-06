#include <iostream>
#include <string>
#include <vector>
#include <algorithm> // 必须包含这个头文件才能使用 sort

using namespace std;

class student 
{
     public: 
    string name;
    int ID;
    int chinese;
    int math;
    int english;
    int total;

    student() {}

    student(int a1, string n, int a2, int a3, int a4) 
    {
        ID = a1;
        name = n;
        chinese = a2;
        math = a3;
        english = a4;
        total = a2 + a3 + a4;
    }

    static bool cmp(const student &a1, const student &b2) 
    {
        if (a1.total != b2.total) 
        {
            return a1.total > b2.total; 
        }
        if (a1.chinese != b2.chinese) 
        {
            return a1.chinese > b2.chinese; 
  
        
        }
        return a1.math>b2.math;
    }

    void print() 
    {
        cout << ID << " " << name << " " << total << endl;
    }
};

int main() 
{
    int N;
    if (cin >> N) 
    {
        vector<student> students;
        
        for (int i = 0; i < N; i++) 
        {
            int id, chi, math, eng;
            string name;
            cin >> id >> name >> chi >> math >> eng;
            students.push_back(student(id, name, chi, math, eng));
        }

        sort(students.begin(), students.end(), student::cmp);

        for (int i = 0; i < N; i++) 
        {
            students[i].print();
        }
    }
    return 0;
}