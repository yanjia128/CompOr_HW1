#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node *next;
} Node;

// Split the linked list into two parts
void splitList(Node *head, Node **firstHalf, Node **secondHalf)
{
    

        /*
        if (!head || !head->next) {
            *firstHalf = head;
            *secondHalf = NULL;
            return;
        }*/

    /*
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
    */    
        asm volatile(
            // 初始化 slow = head
            "mv t2, %2      \n\t"         // t2 = slow = head
            
            // 初始化 fast = head->next
            "ld t3, 8(t2)    \n\t"      // t3 = fast = head->next
            
            // 如果 fast 為 NULL，跳到結束
            "beqz t3, 1f    \n\t"
            
            "0:             \n\t"                // 迴圈開始標籤
            
            
            "ld t4, 8(t3)   \n\t"      // t4 = fast->next
            "beqz t4, 1f    \n\t"      // 檢查 fast->next 是否為 NULL
            
           
            "ld t2, 8(t2)   \n\t"      // t2(slow) = slow->next
            
            
            "ld t3, 8(t4)   \n\t"      // t3(fast) = fast->next->next
            
            
            "bnez t3, 0b    \n\t"       // 如果 fast 不為 NULL，繼續迴圈
            
            "1:             \n\t"       // 迴圈結束
            
            
            "sd %2, 0(%0)   \n\t"      // *firstHalf = head
            
            
            "ld t4, 8(t2)   \n\t"      // *secondHalf = slow->next
            "sd t4, 0(%1)   \n\t"      // 存儲 slow->next 到 secondHalf 指向的位址
            
            
            "sd zero, 8(t2) \n\t"    // slow->next = NULL
            
            : 
            : "r" (firstHalf), "r" (secondHalf), "r" (head)
            : "t2", "t3", "t4", "memory"
        );

    

    }

// Merge two sorted linked lists
Node *mergeSortedLists(Node *a, Node *b)
{
    Node *result = NULL;
    Node *tail = NULL;
    
    asm volatile(
        // 假設寄存器分配如下:
        // a0: a 指針
        // a1: b 指針
        // a2: result 指針
        // a3: tail 指針
        // t0, t1: 臨時寄存器用於比較
        // t3: 代替 temp 變數
        
        // 主迴圈
        "1:\n\t"                       // while 迴圈開始
        "beqz %0, 5f        \n\t"             // 如果 a == NULL，跳出迴圈
        "beqz %1, 5f        \n\t"             // 如果 b == NULL，跳出迴圈
        
        // 比較 a->data 和 b->data
        "lw t0, 0(%0)       \n\t"            // t0 = a->data (載入 int)
        "lw t1, 0(%1)       \n\t"            // t1 = b->data (載入 int)
        "bgt t0, t1, 2f     \n\t"          // 如果 a->data > b->data，跳到 else 區塊
        
        // if (a->data <= b->data)
        "mv t3, %0          \n\t"               // t3(temp) = a
        "ld %0, 8(%0)       \n\t"            // a = a->next
        "j 3f               \n\t"                    // 跳到 if-else 結束
        
        // else
        "2:                 \n\t"
        "mv t3, %1          \n\t"               // t3(temp) = b
        "ld %1, 8(%1)       \n\t"            // b = b->next
        
        // temp->next = NULL
        "3:                 \n\t"
        "sd zero, 8(t3)     \n\t"          // t3(temp)->next = NULL
        
        // if (!result)
        "bnez %2, 4f        \n\t"             // 如果 result != NULL，跳到 else 區塊
        "mv %2, t3          \n\t"               // result = t3(temp)
        "mv %3, %2          \n\t"               // tail = result
        "j 1b               \n\t"                    // 跳回迴圈開始

        // else
        "4:                 \n\t"
        "sd t3, 8(%3)       \n\t"            // tail->next = t3(temp)
        "mv %3, t3          \n\t"               // tail = t3(temp)
        "j 1b               \n\t"                    // 跳回迴圈開始
        
        // 迴圈結束後處理剩餘節點
        "5:                 \n\t"
        "beqz %0, 7f        \n\t"             // 如果 a == NULL，跳到檢查 b
        
        // if (a)
        "bnez %2, 6f        \n\t"             // 如果 result != NULL，跳過 return a
        "mv %2, %0          \n\t"               // 準備返回 a (result = a)
        "j 9f               \n\t"                    // 跳到函數結束
        
        "6:                 \n\t"
        "sd %0, 8(%3)       \n\t"            // tail->next = a
        "j 9f               \n\t"                    // 跳到函數結束
        
        // else if (b)
        "7:                 \n\t"
        "beqz %1, 9f        \n\t"             // 如果 b == NULL，跳到函數結束
        "bnez %2, 8f        \n\t"             // 如果 result != NULL，跳過 return b
        "mv %2, %1          \n\t"               // 準備返回 b (result = b)
        "j 9f               \n\t"                    // 跳到函數結束
        
        "8:                 \n\t"
        "sd %1, 8(%3)       \n\t"            // tail->next = b
        
        
        "9:\n\t"
        
        : "+r" (a), "+r" (b), "+r" (result), "+r" (tail)
        : 
        : "t0", "t1", "t3", "memory"
    );
    


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
    if (cur) cur->next = NULL;  //// cur 現在是最後一個 node

    fclose(input);

    // Linked list sort
    head = mergeSort(head);

    cur = head;
    while (cur) {
        printf("%d ", cur->data);
        asm volatile(
            "ld %[cur], 8(%[cur])   \n\t"
            

            :[cur]"+r"(cur)
            :
            :"memory"
        );
        //cur = cur -> next;

    }
    printf("\n");
    return 0;
}
