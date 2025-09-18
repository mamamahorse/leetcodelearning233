
//   struct ListNode
//    {
//      int val;
//       ListNode *next;
//       ListNode() : val(0), next(nullptr) {}
//      ListNode(int x) : val(x), next(nullptr) {}
//       ListNode(int x, ListNode *next) : val(x), next(next) {}
//   };

// class Solution {
// public:
//     ListNode* removeNthFromEnd(ListNode* head, int n) 
//     {ListNode* dummy = new ListNode (0);
//       dummy->next =head;
//       ListNode* cur =dummy;
//       int count =0;
//         while(cur->next!=nullptr)
//         { count++;
//             cur =cur->next;
//         }
//         cur=dummy;
//         int index=count -n;
//         while(index--)
//         {
//             cur=cur->next;
//         }
//         ListNode*tmp =cur->next;
//         cur->next= tmp->next;
//         delete tmp;
//         return dummy->next;
        
//     }
// };