// #include <iostream>
// #include <vector>
// using namespace std;
// class MyLinkedList {

// public:
// struct linkedlist
// {int val;
//  linkedlist* next;
//  linkedlist(int val):val(val),next(nullptr){} 
// };

//     MyLinkedList() 
//     { dummyhead=new linkedlist(0); 
//         size=0;
//     }
    
//     int get(int index) 
//     { if(index<0||index>size-1)
//         return -1;
//         linkedlist* cur=dummyhead->next;
//         while(index--)
//         {
//             cur=cur->next;
//         }
//         return cur->val;
//     }
    
//     void addAtHead(int val) 
//     {  linkedlist*tmp= new linkedlist(val);
//         tmp->next=dummyhead->next;
//         dummyhead->next=tmp;
//         size++;
        
//     }
    
//     void addAtTail(int val) 
//     { linkedlist*p =new linkedlist(val);
//         linkedlist* cur=dummyhead;
//         while(cur->next!=NULL)
//         cur=cur->next;
//         cur->next=p;
//         size++;
        
//     }
    
//     void addAtIndex(int index, int val)
//      {  if(index>size)
//         return ;
//         if(index<0)
//         index=0;
//         linkedlist *p =new linkedlist(val);
//         linkedlist *cur =dummyhead;
//         while(index--)
//         {
//             cur =cur->next;
//         }
//         p->next=cur->next;
//         cur->next=p;
//         size++;
//     }
    
//     void deleteAtIndex(int index) 
//     {if(index>=0&&index<size)
//         {  linkedlist* cur=dummyhead;
//             while(index--)
//             {
//                 cur=cur->next;
//             }
//             linkedlist*tmp=cur->next;
//             cur->next=tmp->next;
//             delete tmp;
//             tmp=NULL;
//             size--;
//         }
        
        
//     }
//     private:
// int size;
// linkedlist* dummyhead;
// };
