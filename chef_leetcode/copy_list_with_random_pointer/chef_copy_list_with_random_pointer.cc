/**
 * A linked list is given such that each node contains an additional random
 * pointer which could point to any node in the list or null.
 *
 * Return a deep copy of the list.
 */

/**
 * Definition for singly-linked list with a random pointer.
 * struct RandomListNode {
 *     int label;
 *     RandomListNode *next, *random;
 *     RandomListNode(int x) : label(x), next(NULL), random(NULL) {}
 * };
 */
class Solution {
    public:
        RandomListNode *copyRandomList(RandomListNode *head) {
            if (head == NULL) {
                return NULL;
            }
            map<RandomListNode *, int> node2index;
            RandomListNode *p = head;
            vector<RandomListNode *> new_nodes;
            for (int i = 0; p; ++i, p = p->next) {
                node2index.insert(make_pair(p, i));
                new_nodes.push_back(new RandomListNode(p->label));
            }
            p = head;
            for (int i = 0; p; p = p->next, ++i) {
                new_nodes[i]->random = p->random ? new_nodes[node2index[p->random]] : NULL;
            }
            int i = 0;
            for (; i < new_nodes.size() - 1; ++i) {
                new_nodes[i]->next = new_nodes[i + 1];
            }
            new_nodes[i]->next = NULL;
            return new_nodes[0];
        }
};

