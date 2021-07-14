/* C Program to apply transformation on points, line, triangle, or any polygon */
#include <stdio.h>
#include <stdlib.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <math.h>

// Function Declarations


// Global Variables
int vertexCount;

/* ------------------------------------------------------- */
/* Driver Code for the program. Asks for object and its    */
/* corresponding transformation. Calls requires Functions  */
/* Returns 0.                                              */
/* ------------------------------------------------------- */
int main(char argc, char *argv[])
{
    char ch;
    int check = 1;
    int Xcoord[15], Ycoord[15];
    do
    {
        printf("\n/* PROGRAM TO TRANSFORM OBJECTS */\n");
        printf("Please enter the type of object:\n");
        printf("1. Point\n2. Line\n 3. Triangle\n4. Polygon\nPRESS 0 TO EXIT\n");
        ch = getchar();
        switch (ch)
        {
        case 0:
            check = 0;
            break;
        case 1:
            vertexCount = 1;
            break;
        case 2:
            vertexCount = 2;
            break;
        case 3:
            vertexCount = 3;
            break;
        case 4:
            printf("Enter the number of vertices(1 - 15):\t");
            scanf("%d", &vertexCount);
            if (vertexCount < 1 || vertexCount > 15)
            {
                printf("\nInvalid input. Try Again\n");
                continue;
            }
            
            break;
        default:
            printf("\nPLEASE ENTER CORRECT OPTION\n");
            break;
        }
        for (int i = 0; i < vertexCount; i++)
        {
            printf("\nPlease enter the co-ordinate of the point %d:\n", (i + 1));
            printf("x:\t");
            scanf("%d", Xcoord[i]);
            printf("y:\t");
            scanf("%d", Ycoord[i]);
        }
        
    } while (check);
    
    
}