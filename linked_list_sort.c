#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node *next;
} Node;

// Split the linked list into two parts
void splitList(Node *head, Node **firstHalf, Node **secondHalf)
{
    //asm volatile(
        /*
        Block A (splitList), which splits the linked list into two halves
        */
    //    "");
    if (!head || !head->next) {
        *firstHalf = head;
        *secondHalf = NULL;
        return;
    }

    Node *slow = head;
    Node *fast = head->next;

    // 使用快慢指標法找到中間點
    while (fast && fast->next) {
        slow = slow->next;
        fast = fast->next->next;
    }

    *firstHalf = head;
    *secondHalf = slow->next;
    slow->next = NULL; // 分割 list
}

// Merge two sorted linked lists
Node *mergeSortedLists(Node *a, Node *b)
{
    Node *result = NULL;
    Node *tail = NULL;

    //asm volatile(
        /*
        Block B (mergeSortedList), which merges two sorted lists into one
        */
    //    "");
    while (a && b) {
        Node *temp;
        if (a->data <= b->data) {
            temp = a;
            a = a->next;
        } else {
            temp = b;
            b = b->next;
        }

        temp->next = NULL;
        if (!result) {
            result = temp;
            tail = result;
        } else {
            tail->next = temp;
            tail = tail->next;
        }
    }

    // 如果還有剩下的節點，接上去
    if (a) {
        if (!result) return a;
        tail->next = a;
    } else if (b) {
        if (!result) return b;
        tail->next = b;
    }


    return result;
}

// Merge Sort function for linked list
Node *mergeSort(Node *head)
{
    if (!head || !head->next)
        return head; // Return directly if there is only one node

    Node *firstHalf, *secondHalf;
    splitList(head, &firstHalf,
              &secondHalf); // Split the list into two sublists

    firstHalf = mergeSort(firstHalf);   // Recursively sort the left half
    secondHalf = mergeSort(secondHalf); // Recursively sort the right half

    return mergeSortedLists(firstHalf, secondHalf); // Merge the sorted sublists
}

int main(int argc, char *argv[])
{
    if (argc < 2) {
        printf("Usage: %s <input_file>\n", argv[0]);
        return 1;
    }

    FILE *input = fopen(argv[1], "r");
    if (!input) {
        fprintf(stderr, "Error opening file: %s\n", argv[1]);
        return 1;
    }
    int list_size;
    fscanf(input, "%d", &list_size);
    Node *head = (list_size > 0) ? (Node *)malloc(sizeof(Node)) : NULL;
    Node *cur = head;
    for (int i = 0; i < list_size; i++) {
        fscanf(input, "%d", &(cur->data));
        if (i + 1 < list_size)
            cur->next = (Node *)malloc(sizeof(Node));
        cur = cur->next;
    }
    fclose(input);

    // Linked list sort
    head = mergeSort(head);

    cur = head;
    while (cur) {
        printf("%d ", cur->data);
        //asm volatile(
            /*
            Block C (Move to the next node), which updates the pointer to
            traverse the linked list
            */
        //    "");
        cur = cur->next;
    }
    printf("\n");
    return 0;
}
