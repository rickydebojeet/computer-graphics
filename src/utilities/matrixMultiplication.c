/* C Program for Matrix Multiplication */
#include <stdio.h>
#include <stdlib.h>

//Function Declaration
void matrixMultiplication(int *, int *, int *, int, int, int);

/* ------------------------------------------------------- */
/* Driver Code for the program. Asks for the matrix values */
/* Calls Required functions and prints the result.         */
/* Returns 0.                                              */
/* ------------------------------------------------------- */
int main()
{
    // Initialising the matrices
    int a[20][20], b[20][20], c[20][20];

    // Initialising the dimensions such that the dimensions are (m x n) (n x o) = (m x o)
    int m, n, o, tmp;
    // Initialising the dimension of the first matrix
    printf("\nEnter the dimensions of the first matrix:\n");
    printf("m:\t");
    scanf("%d", &m);
    printf("n:\t");
    scanf("%d", &n);
    // Initialising the dimension of the second matrix
    printf("\nEnter the dimensions of the second matrix:\n");
    printf("n:\t");
    scanf("%d", &tmp);
    // Checking for error prevention
    if (tmp != n)
    {
        printf("\nCan't Perform Multiplication\n");
        exit(EXIT_SUCCESS);
    }
    printf("o:\t");
    scanf("%d", &o);

    // Initialising the first matrix
    printf("\nEnter the values of matrix A:\n");
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            printf("Enter a[%d][%d]:\t", i, j);
            scanf("%d", &a[i][j]);
        }
    }
    printf("\nEnter the values of matrix B:\n");
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < o; j++)
        {
            printf("Enter b[%d][%d]:\t", i, j);
            scanf("%d", &b[i][j]);
        }
    }

    // Calling the function for Matrix Multiplication
    matrixMultiplication((int *)a, (int *)b, (int *)c, m, n, o);

    // Printing the output
    printf("\nThe values of C are:\n");
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < o; j++)
        {
            printf("%d\t", c[i][j]);
        }
        printf("\n");
    }
    printf("\n\n");
    return 0;
}

/* ------------------------------------------------------- */
/* Function  for matrix multiplication. Asks for 3 matric- */
/* -es and corresponding dimensions. Multiplies first 2    */
/* matrices and puts the result in the third matrix        */
/* ------------------------------------------------------- */
void matrixMultiplication(int *a, int *b, int *c, int m, int n, int o)
{
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < o; j++)
        {
            // c[i][j] = 0
            *((c + i * 20) + j) = 0;
            for (int k = 0; k < n; k++)
            {
                // c[i][j] += a[i][k] * b[k][j]
                *((c + i * 20) + j) += *((a + i * 20) + k) * (*((b + k * 20) + j));
            }
        }
    }
}

