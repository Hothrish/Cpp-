class Solution {
public:
    ListNode *detectCycle(ListNode *head) {
        if (!head || !head->next) return NULL;
        ListNode *slow = head, *fast = head;
        while (fast && fast->next) {
            slow = slow->next;
            fast = fast->next->next;
            if (slow == fast) {
                ListNode *start = head;
                while (start != slow) {
                    start = start->next;
                    slow = slow->next;
                }
                return start;
            }
        }
        return NULL;
    }
};
