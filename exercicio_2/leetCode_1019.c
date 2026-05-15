#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct ListNode {
      int val;
      struct ListNode *next;
 } Node;



int* nextLargerNodes(struct ListNode* head, int* returnSize);


int main(){
  
    
  
    return 0;
}

int* nextLargerNodes(struct ListNode* head, int* returnSize) {
    if (!head) {
        *returnSize = 0;
        return NULL;
    }

    int size = 0;
    struct ListNode* curr = head;
    while (curr) {
        size++;
        curr = curr->next;
    }

    int* values = (int*)malloc(size * sizeof(int));
    curr = head;
    for (int i = 0; i < size; i++) {
        values[i] = curr->val;
        curr = curr->next;
    }

    int* result = (int*)calloc(size, sizeof(int));
    int* stack = (int*)malloc(size * sizeof(int));
    int top = -1;

    for (int i = 0; i < size; i++) {
        while (top >= 0 && values[i] > values[stack[top]]) {
            result[stack[top--]] = values[i];
        }
        stack[++top] = i;
    }

    free(values);
    free(stack);

    *returnSize = size;
    return result;
}