// #include <iostream>
// #include <vector>
// using namespace std;

//   struct ListNode {
//       int val;
//      ListNode *next;
//       ListNode() : val(0), next(nullptr) {}
//      ListNode(int x) : val(x), next(nullptr) {}
//       ListNode(int x, ListNode *next) : val(x), next(next) {}
//   };
 
// class Solution {
// public:
//     ListNode* removeElements(ListNode* head, int val) 
//     {
//         while(head!=nullptr&&head->val==val)
//         {ListNode*temp =head;
//             head=head->next;
//             delete temp;

//         }
//         ListNode* cur=head;
//         while(cur!=NULL&&cur->next!=NULL)
//         {
//             if(cur->next->val==val)
//             {
//                 ListNode*p =cur->next;
//                 cur->next=cur->next->next;
//                 delete p;
//             }
//             else
//             cur=cur->next;
//         }
//         return head;

//     }
// };
//上述是对头节点特殊处理的方法，下面是使用虚拟头结点的做法。
// class Solution {
// public:
//     ListNode* removeElements(ListNode* head, int val) 
//     {ListNode *dummyhead=new ListNode(0);
//         dummyhead->next=head;
//         ListNode *cur =dummyhead;
//         while(cur->next!=nullptr)
//         {if(cur->next->val==val)
//             {
//                 ListNode*tmp =cur->next;
//                 cur->next=cur->next->next;
//                 delete tmp;
//             }
//             else
//             cur=cur->next;
//         }
//         return dummyhead->next;
//         delete dummyhead;

       
//     }
// };
//再来写一个递归。
// class Solution {
// public:
//     ListNode* removeElements(ListNode* head, int val) 
//     {  if(head==nullptr)
//         return head;
//         if(head->val==val)
//         {
//             ListNode *tmp=head;
//             return removeElements(head->next,val);
//             delete tmp;
//         }      
//         else
//         {
//             head->next=removeElements(head->next,val);
//                 return head;
//         }
             
       
//     }
// };