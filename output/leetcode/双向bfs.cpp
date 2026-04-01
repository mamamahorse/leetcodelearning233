#include <iostream>
#include <vector>
#include <string>
#include <unordered_set>
#include <unordered_map>
#include <queue>
using namespace std;

int main() {
    string beginStr, endStr, str;
    int n;
    cin >> n;
    
    unordered_set<string> strSet;
    cin >> beginStr >> endStr;
    for (int i = 0; i < n; i++) {
        cin >> str;
        strSet.insert(str);
    }

    // 【重要】双向BFS的前提：终点必须在字典里，否则无法从终点出发
    if (strSet.find(endStr) == strSet.end()) {
        cout << 0 << endl;
        return 0;
    }

    // 定义两个队列，分别从起点和终点出发
    queue<string> q1, q2;
    q1.push(beginStr);
    q2.push(endStr);

    // 定义两个Map，分别记录从 起点->当前 和 终点->当前 的路径长度
    // key: 单词, value: 路径长度(包含自身)
    unordered_map<string, int> visit1, visit2;
    visit1[beginStr] = 1;
    visit2[endStr] = 1;

    // 只要两个队列都不为空，就继续搜
    // 如果其中一个空了还没相遇，说明断路了
    while (!q1.empty() && !q2.empty()) {
        
        // 【优化】每次只扩展 较小 的那个队列
        // 这样可以保证两边的搜索范围尽可能平衡，避免一边过大
        if (q1.size() > q2.size()) {
            swap(q1, q2);
            swap(visit1, visit2);
        }

        // 取出当前较小队列的头元素进行扩展
        string word = q1.front();
        q1.pop();
        int curPath = visit1[word];

        // 开始变换字符
        for (int i = 0; i < word.size(); i++) {
            string newWord = word;
            for (int j = 0; j < 26; j++) {
                newWord[i] = j + 'a';

                if (newWord == word) continue; // 跳过自己

                // 【核心相遇判断】
                // 如果 newWord 在另一个方向的 visitMap 中出现过，说明两军会师了！
                if (visit2.find(newWord) != visit2.end()) {
                    // 总路径 = (起点到当前word的长度) + (终点到newWord的长度)
                    // 此时 newWord 就是连接点
                    // 比如: begin -> ... -> word -> newWord <- ... <- end
                    // word是这一侧的最后一站，newWord是那一侧的边界
                    cout << curPath + visit2[newWord] << endl;
                    return 0;
                }

                // 普通的 BFS 扩展逻辑
                // 如果在字典中，且在 本方向 未访问过
                if (strSet.find(newWord) != strSet.end() && visit1.find(newWord) == visit1.end()) {
                    visit1[newWord] = curPath + 1;
                    q1.push(newWord);
                }
            }
        }
    }

    // 无法相遇
    cout << 0 << endl;
    return 0;
}