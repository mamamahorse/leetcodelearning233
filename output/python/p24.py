
# class ListNode:
#     def __init__(self, val=0, next=None):
#         self.val = val
#         self.next = next

        

# class Solution:
#     def swapPairs(self,head):
#         dummyhead =ListNode(next=head)
#         current = dummyhead
#         while current.next and current.next.next:
#             temp=current.next
#             temp1=current.next.next.next
#             current.next = current.next.next
#             current.next.next = temp
#             temp.next = temp1
#             current = current.next.next
#         return dummyhead.next

    