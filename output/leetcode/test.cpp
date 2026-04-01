#include <iostream>
struct ListNode 
{ int val;
    ListNode * next;
    ListNode (int x):val(x),next(NULL){}

};
ListNode * merge(ListNode*A1,ListNode*A2)
{
    ListNode dummy(0);
    ListNode* tail=&dummy;
    while(A1!=NULL&&A2!=NULL)
    {
        if(A1->val>=A2->val)
        {
            tail->next=A1;
            A1=A1->next;
        }
        if(A1->val<A2->val)
        {
            tail->next=A2;
            A2=A2->next;
        }
        tail=tail->next;
    }
    if(A1!=NULL)
    {
        tail->next=A1;
    }
    if(A2!=NULL)
    {
        tail->next=A2;
    }
    return dummy.next;
}
ListNode * createlist(int n)
{
    if(n==0)
    return NULL;
    ListNode*head=NULL;
    ListNode *tail=NULL;
    for(int i=0;i<n;i++)
    {
        int val;
        cin>>val;
        ListNode*newNode =new ListNode(val);
        if(head==NULL)
        {
            head=newNode;
            tail=newNode;
        }
        else
        {
            tail->next =newNode;
            tail=tail->next;
        }
    }
    return head;
}
int main()
{
    int 
  
}