/* C Program to apply transformation on points, line, triangle, or any polygon */
#include <stdio.h>
#include <stdlib.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <math.h>

// Function Declarations
void display(void);
void reshape(int, int);

// Global Variables
int vertexCount;
int pointMatrix[3][15];

/* ------------------------------------------------------- */
/* Driver Code for the program. Asks for object and its    */
/* corresponding transformation. Calls required Functions  */
/* Returns 0.                                              */
/* ------------------------------------------------------- */
int main(char argc, char *argv[])
{
    char ch, op;
    int check = 1;
    int Xcoord[15], Ycoord[15];
    do
    {
        int cond = 1;
        printf("\n/* PROGRAM TO TRANSFORM OBJECTS */\n");
        printf("Please enter the type of object:\n");
        printf("1.Point\n2.Line\n 3.Triangle\n4.Polygon\nPRESS 0 TO EXIT\n");
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
            // Input Checking
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
        
        // To Exit The Program
        if (check == 0)
            break;

        // Take co-ordinates with respect to the objects
        for (int i = 0; i < vertexCount; i++)
        {
            printf("\nPlease enter the co-ordinate of the point %d:\n", (i + 1));
            printf("x:\t");
            scanf("%d", Xcoord[i]);
            printf("y:\t");
            scanf("%d", Ycoord[i]);
        }

        // Form the Point Matrix of the object
        for (int i = 0; i < vertexCount; i++)
        {
            pointMatrix[0][i] = Xcoord[i];
            pointMatrix[1][i] = Ycoord[i];
            pointMatrix[2][i] = 1;
        }

        do
        {
            printf("Please enter the type of operation to perform:\n");
            printf("1.Translation\n2.Rotation\n 3.Scaling\n4.Reflextion\nPRESS 0 TO GO BACK\n");
            op = getchar();
            switch (op)
            {
            case 0:
                cond = 0; 
                break;
            case 1:
                int x, y;
                printf("\nEnter the translation amount in X-axis:\t");
                scanf("%d", &x);
                printf("\nEnter the translation amount in Y-axis:\t");
                scanf("%d", &y);
                /* code */
                break;
            case 2:
                int choice, degree;
                printf("\nEnter the rotation amount in degrees:\t");
                scanf("%d", &degree);
                printf("\nEnter your rotation choice\n1.About Origin\n2.About 1st Point\n");
                scanf("%d", &choice);
                if (choice == 1)
                {
                    /* code */
                }
                else if (choice == 2)
                {
                    /* code */
                }
                else
                {
                    printf("\nWrong Input. Try Again.\n");
                    continue;
                }
                break;
            case 3:
                int x, y;
                printf("\nEnter the scale amount in X-axis:\t");
                scanf("%d", &x);
                printf("\nEnter the scale amount in Y-axis:\t");
                scanf("%d", &y);
                /* code */
                break;
            case 4:
                int choice, x1, y1, x2, y2;
                printf("\nEnter your reflection choice:\n");
                printf("1.About X-axis\n2.About Y-axis\nAbout a line\n");
                scanf("%d", &choice);
                if (choice == 1)
                {
                    /* code */
                }
                else if (choice == 2)
                {
                    /* code */
                }
                else if (choice == 3)
                {
                    /* code */
                }
                else
                {
                    printf("\nWrong Input. Try Again.\n");
                    continue;
                }
                break;
            default:
                printf("\nPLEASE ENTER CORRECT OPTION\n");
                break;
            }

            // To go back
            if (cond == 0)
                break;
            
            // Diplay Point and Resultant Matrix
            /* code */

            // Initialize GLUT Library
            glutInit(&argc, argv);
            // Set the initial display mode
            glutInitDisplayMode(GLUT_RGB);
            // Set the initial window position and size
            glutInitWindowPosition(0, 0);
            glutInitWindowSize(600, 600);
            // Create the window with title "Window name"
            glutCreateWindow("Window name");

            // Initialize drawing colors
            myInit();

            // Call the displaying call back function
            glutDisplayFunc(display);
            // Call the reshape call back function
            glutReshapeFunc(reshape);
            glutMainLoop();
        } while (1); 
    } while (1);
    return 0;
}