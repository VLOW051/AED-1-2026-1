#include <stdio.h>
#include <stdlib.h>

struct ListNode {
    int val;
    struct ListNode *next;
};

int* nextLargerNodes(struct ListNode* head, int* returnSize);
struct ListNode* createNode(int val);
struct ListNode* buildList(int* arr, int size);
void freeList(struct ListNode* head);

int main() {
    int inputSize;

    printf("Digite o tamanho do vetor: ");
    if (scanf("%d", &inputSize) != 1 || inputSize <= 0) {
        printf("Tamanho invalido.\n");
        return 1;
    }

    int* inputData = (int*)malloc(inputSize * sizeof(int));
    if (inputData == NULL) {
        printf("Erro ao alocar memoria.\n");
        return 1;
    }

    printf("Digite os %d elementos do vetor:\n", inputSize);
    for (int i = 0; i < inputSize; i++) {
        printf("Elemento [%d]: ", i);
        if (scanf("%d", &inputData[i]) != 1) {
            printf("Entrada invalida.\n");
            free(inputData);
            return 1;
        }
    }

    struct ListNode* head = buildList(inputData, inputSize);

    int returnSize = 0;
    int* result = nextLargerNodes(head, &returnSize);

    printf("\nInput:  [");
    for (int i = 0; i < inputSize; i++) {
        printf("%d%s", inputData[i], (i == inputSize - 1) ? "" : ", ");
    }
    printf("]\n");

    printf("Output: [");
    for (int i = 0; i < returnSize; i++) {
        printf("%d%s", result[i], (i == returnSize - 1) ? "" : ", ");
    }
    printf("]\n");

    free(inputData);
    free(result);
    freeList(head);

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

struct ListNode* createNode(int val) {
    struct ListNode* newNode = (struct ListNode*)malloc(sizeof(struct ListNode));
    newNode->val = val;
    newNode->next = NULL;
    return newNode;
}

struct ListNode* buildList(int* arr, int size) {
    if (size == 0) return NULL;
    struct ListNode* head = createNode(arr[0]);
    struct ListNode* curr = head;
    for (int i = 1; i < size; i++) {
        curr->next = createNode(arr[i]);
        curr = curr->next;
    }
    return head;
}

void freeList(struct ListNode* head) {
    struct ListNode* tmp;
    while (head) {
        tmp = head;
        head = head->next;
        free(tmp);
    }
}