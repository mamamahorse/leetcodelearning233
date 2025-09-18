# class ListNode:
#     def __init__(self,x):
#         self.val=x
#         self.next =None

# class Solution:
#     def getIntersectionNode(self, headA: ListNode, headB: ListNode) -> ListNode:
#         curA=headA
#         curB=headB
#         lenA,lenB=0,0
#         while curA:
#             curA=curA.next
#             lenA+=1
#         while curB:
#             curB=curB.next
#             lenB+=1
#         curA=headA
#         curB=headB
#         if lenA>lenB:
#             curA,curB=curB,curA
#             lenA,lenB=lenB,lenA
#         for _ in range(lenB-lenA):
#             curB=curB.next
#         while curA:
#             if curA==curB:
#                 return curA
#             else:
#                 curA=curA.next
#                 curB=curB.next
#         return None

        


