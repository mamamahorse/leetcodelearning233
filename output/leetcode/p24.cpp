// #include <iostream>
// using namespace std;
// struct ListNode {
//       int val;
//       ListNode *next;
//       ListNode() : val(0), next(nullptr) {}
//       ListNode(int x) : val(x), next(nullptr) {}
//       ListNode(int x, ListNode *next) : val(x), next(next) {}
//   };
// class Solution {
// public:
//     ListNode* swapPairs(ListNode* head) 
//     {
//         ListNode* dummynode =new ListNode(0);
//         dummynode->next =head;
//         ListNode* cur = dummynode;
//         while(cur->next!=nullptr&&cur->next->next!=nullptr)
//         {
//             ListNode* tmp= cur->next;
//             ListNode* tmp1 = cur->next->next->next;
//             cur->next = cur->next->next;   
//             cur->next->next = tmp;          
//             cur->next->next->next = tmp1;
//             cur=cur->next->next;
//         }
//         ListNode* result =dummynode -> next;
//           delete dummynode;
//         return result;
 

//     }
// };