#include <iostream>
#include <vector>
#include <string>
#include <unordered_set>
#include <unordered_map>
#include <queue>
using namespace std;

int main()
{
    int n;
    string begingStr, endStr, str;
    cin >> n;
    cin >> begingStr >> endStr;

    unordered_set<string> strSet;
    for (int i = 0; i < n; i++)
    {
        cin >> str;
        strSet.insert(str);
    }

    // 如果起点等于终点，最短变换长度为 1（只包含起点）
    if (begingStr == endStr)
    {
        cout << 1 << endl;
        return 0;
    }

    // 确保终点在集合中，否则无法到达（有些题目要求这样）
    strSet.insert(endStr);

    unordered_map<string, int> visited; // 存储单词到步数（从 1 开始计）
    queue<string> que;
    que.push(begingStr);
    visited[begingStr] = 1;

    while (!que.empty())
    {
        string word = que.front();
        que.pop();
        int path = visited[word];

        for (int i = 0; i < (int)word.size(); i++)
        {
            string newword = word;
            for (char c = 'a'; c <= 'z'; c++)
            {
                if (c == word[i]) continue; // 跳过与当前字符相同的替换
                newword[i] = c;
                if (strSet.count(newword))
                {
                    if (newword == endStr)
                    {
                        cout << path + 1 << endl;
                        return 0;
                    }
                    if (!visited.count(newword))
                    {
                        visited[newword] = path + 1;
                        que.push(newword);
                    }
                }
            }
        }
    }

    // 无法到达终点
    cout << 0 << endl;
    return 0;
}