#include <stdio.h>
#include <stdlib.h>

typedef struct link{
    int element;
    struct link * next;
} Link;

void destroy(Link *node)
{
    if (node && (node->next))
    {
        destroy(node->next);
    }
    free(node);
}

void insert(Link *node, int element)
{
    Link *newNode = (Link *)malloc(sizeof(Link));
    newNode->element = element;
    newNode->next = node->next;
    node->next = newNode;
}

Link* reverse(Link *head)
{
    Link *prev = NULL;
    Link *current = head;
    Link *next = NULL;

    while (current != NULL) {
        next = current->next;
        current->next = prev;
        prev = current;
        current = next;
    }

    return prev;  // 返回新的头节点
}

int search(Link *head, int element_to_search, int start_from, int skip)
{
    if (!head) return -1;

    // 跳过start_from个节点
    if (start_from > 0) {
        int result = search(head->next, element_to_search, start_from - 1, skip);
        return (result == -1) ? -1 : result + 1;
    }

    // 检查当前节点
    if (head->element == element_to_search) {
        if (skip > 0) {
            return search(head->next, element_to_search, 0, skip - 1);
        } else {
            return 0;
        }
    }

    // 继续搜索
    int result = search(head->next, element_to_search, 0, skip);
    return (result == -1) ? -1 : result + 1;
}

int main(void)
{
    Link *header = nullptr;

    Link* first = (Link*)malloc(sizeof(Link));
    first->element = 1;
    first->next = nullptr;

    header = first;

    Link* current = first;
    for (int i = 2; i <= 9; i++)
    {
        Link* node = (Link*)malloc(sizeof(Link));
        node->element = i;
        node->next = nullptr;
        current->next = node;
        current = node;
    }

    // insert
    // insert(current, 111);

    // search
    printf("%d", search(header, 4, 3, 0));

    // reverse
    reverse(header);

    // destroy
    destroy(header);

    return 0;
}
