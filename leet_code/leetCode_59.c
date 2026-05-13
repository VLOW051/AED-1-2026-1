#include <stdio.h>
#include <stdlib.h>

int** generateMatrix(int n, int* returnSize, int** returnColumnSizes);


int main() {
    
    int n = 0 ; 
    int returnSize;
    int* returnColumnSizes;

    printf("informe o numero\n ");
    scanf("%d", &n);  


    int** result = generateMatrix(n, &returnSize, &returnColumnSizes);

    for (int i = 0; i < returnSize; i++) {
        for (int j = 0; j < returnColumnSizes[i]; j++) {
            printf("%d\t", result[i][j]);
        }
        printf("\n");
    }

    for (int i = 0; i < n; i++) {
        free(result[i]);
    }
    free(result);
    free(returnColumnSizes);

    return 0;
}

int** generateMatrix(int n, int* returnSize, int** returnColumnSizes) {
    
    *returnSize = n;
    
    *returnColumnSizes = (int*)malloc(n * sizeof(int));
    
    int** matrix = (int**)malloc(n * sizeof(int*));
    
    for (int i = 0; i < n; i++) {
        
      matrix[i] = (int*)malloc(n * sizeof(int));
        (*returnColumnSizes)[i] = n;
    }

    int top = 0, bottom = n - 1;
    int left = 0, right = n - 1;
    int num = 1;

    while (num <= n * n) {
        for (int i = left; i <= right; i++) {
            matrix[top][i] = num++;
        }
        top++;

        for (int i = top; i <= bottom; i++) {
            matrix[i][right] = num++;
        }
        right--;

        if (top <= bottom) {
            for (int i = right; i >= left; i--) {
                matrix[bottom][i] = num++;
            }
            bottom--;
        }

        if (left <= right) {
            for (int i = bottom; i >= top; i--) {
                matrix[i][left] = num++;
            }
            left++;
        }
    }

    return matrix;
}
