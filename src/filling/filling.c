/* C Program to apply Boundary Filliing algorithm on triangle, or any polygon */
#include <stdio.h>
#include <stdlib.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

// Global Variables
int vertexCount, option;
int pointMatrix[3][15];
float bColor[3], fillColor[3];

// Function Declarations
void fourConnectedFill(GLint, GLint, float *, float *);  // Function for Four Connected Filling
void eightConnectedFill(GLint, GLint, float *, float *); // Function for Eight Connected Filling
void floodFill(GLint, GLint, float *, float *);          //Function for Flood Filling
// Display Functions
void display(void);
void reshape(int, int);
void myInit();
void mouse(int, int, int, int);

/* ------------------------------------------------------- */
/* Driver Code for the program. Asks for object and fills  */
/* it with a color. Calls required Functions  and returns  */
/* Returns 0.                                              */
/* ------------------------------------------------------- */
int main(char argc, char *argv[])
{
    int ch, op;
    int Xcoord[15], Ycoord[15];
    printf("\n/* PROGRAM TO FILL OBJECTS WITH COLOR */\n");
    printf("Please enter the type of object:\n");
    printf("\n1.Triangle\n2.Polygon\n");
    scanf("%d", &ch);
    switch (ch)
    {
    case 1:
        vertexCount = 3;
        break;
    case 2:
        printf("Enter the number of vertices(4 - 15):\t");
        scanf("%d", &vertexCount);
        // Input Checking
        if (vertexCount < 4 || vertexCount > 15)
        {
            printf("\nInvalid input. Try Again\n");
        }
        break;
    default:
        printf("\nPLEASE ENTER CORRECT OPTION\n");
        break;
    }

    // Take co-ordinates with respect to the objects
    for (int i = 0; i < vertexCount; i++)
    {
        printf("\nPlease enter the co-ordinate of the point %d:\n", (i + 1));
        printf("x:\t");
        scanf("%d", &Xcoord[i]);
        printf("y:\t");
        scanf("%d", &Ycoord[i]);
    }

    // Form the Point Matrix of the object
    for (int i = 0; i < vertexCount; i++)
    {
        pointMatrix[0][i] = Xcoord[i];
        pointMatrix[1][i] = Ycoord[i];
        pointMatrix[2][i] = 1;
    }

    printf("\nPlease enter boundary color type:\n");
    printf("1.Red\n2.Green\n3.Blue\n4.White\n");
    scanf("%d", &op);
    switch (op)
    {
    case 1:;
        int choice1;
        bColor[0] = 1.0;
        bColor[1] = 0.0;
        bColor[2] = 0.0;
        printf("\nPlease enter fill color type:\n");
        printf("1.Green\n2.Blue\n3.White\n");
        scanf("%d", &choice1);
        switch (choice1)
        {
        case 1:;
            fillColor[0] = 0.0;
            fillColor[1] = 1.0;
            fillColor[2] = 0.0;
            break;

        case 2:;
            fillColor[0] = 0.0;
            fillColor[1] = 0.0;
            fillColor[2] = 1.0;
            break;

        case 3:;
            fillColor[0] = 1.0;
            fillColor[1] = 1.0;
            fillColor[2] = 1.0;
            break;

        default:
            printf("\nPLEASE ENTER CORRECT OPTION\n");
            break;
        }
        break;
    case 2:;
        int choice2;
        bColor[0] = 0.0;
        bColor[1] = 1.0;
        bColor[2] = 0.0;
        printf("\nPlease enter fill color type:\n");
        printf("1.Red\n2.Blue\n3.White\n");
        scanf("%d", &choice2);
        switch (choice2)
        {
        case 1:;
            fillColor[0] = 1.0;
            fillColor[1] = 0.0;
            fillColor[2] = 0.0;
            break;

        case 2:;
            fillColor[0] = 0.0;
            fillColor[1] = 0.0;
            fillColor[2] = 1.0;
            break;

        case 3:;
            fillColor[0] = 1.0;
            fillColor[1] = 1.0;
            fillColor[2] = 1.0;
            break;

        default:
            printf("\nPLEASE ENTER CORRECT OPTION\n");
            break;
        }
        break;
    case 3:;
        int choice3;
        bColor[0] = 0.0;
        bColor[1] = 0.0;
        bColor[2] = 1.0;
        printf("\nPlease enter fill color type:\n");
        printf("1.Red\n2.Green\n3.White\n");
        scanf("%d", &choice3);
        switch (choice3)
        {
        case 1:;
            fillColor[0] = 1.0;
            fillColor[1] = 0.0;
            fillColor[2] = 0.0;
            break;

        case 2:;
            fillColor[0] = 0.0;
            fillColor[1] = 1.0;
            fillColor[2] = 0.0;
            break;

        case 3:;
            fillColor[0] = 1.0;
            fillColor[1] = 1.0;
            fillColor[2] = 1.0;
            break;

        default:
            printf("\nPLEASE ENTER CORRECT OPTION\n");
            break;
        }
        break;
    case 4:;
        int choice4;
        bColor[0] = 1.0;
        bColor[1] = 1.0;
        bColor[2] = 1.0;
        printf("\nPlease enter fill color type:\n");
        printf("1.Red\n2.Green\n3.Blue\n");
        scanf("%d", &choice4);
        switch (choice4)
        {
        case 1:;
            fillColor[0] = 1.0;
            fillColor[1] = 0.0;
            fillColor[2] = 0.0;
            break;

        case 2:;
            fillColor[0] = 0.0;
            fillColor[1] = 1.0;
            fillColor[2] = 0.0;
            break;

        case 3:;
            fillColor[0] = 0.0;
            fillColor[1] = 0.0;
            fillColor[2] = 1.0;
            break;

        default:
            printf("\nPLEASE ENTER CORRECT OPTION\n");
            break;
        }
        break;
    default:
        printf("\nPLEASE ENTER CORRECT OPTION\n");
        break;
    }

    int choice;
    printf("\nEnter your filling operation\n");
    printf("1.4-Connected\n2.8-Connected\n3.Flood Filling\n");
    scanf("%d", &choice);
    if (choice == 1)
    {
        option = 1;
    }
    else if (choice == 2)
    {
        option = 2;
    }
    else if (choice == 3)
    {
        option = 3;
    }
    else
    {
        printf("\nWrong Input. Try Again.\n");
    }

    // Initialize GLUT Library
    glutInit(&argc, argv);
    // Set the initial display mode
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    // Set the initial window position and size
    glutInitWindowPosition(200, 200);
    glutInitWindowSize(640, 480);
    // Create the window with title "Window name"
    glutCreateWindow("Boundary Filling Operation (Click Mouse)");

    // Initialize drawing colors
    myInit();

    // Call the displaying call back function
    glutDisplayFunc(display);
    // Call the reshape call back function
    glutReshapeFunc(reshape);
    glutMouseFunc(mouse);
    glutMainLoop();
    return 0;
}

/* ------------------------------------------------------- */
/* Function for 4-Connected fill algorithms. Asks for point*/
/* fill color and background color and does the operation  */
/* ------------------------------------------------------- */
void fourConnectedFill(GLint x, GLint y, float *bgcolor, float *fcolor)
{
    float intColor[3];
    glReadPixels(x, y, 1.0, 1.0, GL_RGB, GL_FLOAT, intColor);
    if ((intColor[0] != bgcolor[0] || intColor[1] != bgcolor[1] ||
         intColor[2] != bgcolor[2]) &&
        (intColor[0] != fcolor[0] ||
         intColor[1] != fcolor[1] || intColor[2] != fcolor[2]))
    {
        glColor3f(fcolor[0], fcolor[1], fcolor[2]);
        glBegin(GL_POINTS);
        glVertex2i(x, y);
        glEnd();
        glFlush();
        fourConnectedFill(x + 1, y, bgcolor, fcolor);
        fourConnectedFill(x - 1, y, bgcolor, fcolor);
        fourConnectedFill(x, y + 1, bgcolor, fcolor);
        fourConnectedFill(x, y - 1, bgcolor, fcolor);
    }
}

/* ------------------------------------------------------- */
/* Function for 8-Connected fill algorithms. Asks for point*/
/* fill color and background color and does the operation  */
/* ------------------------------------------------------- */
void eightConnectedFill(GLint x, GLint y, float *bgcolor, float *fcolor)
{
    float intColor[3];
    glReadPixels(x, y, 1.0, 1.0, GL_RGB, GL_FLOAT, intColor);
    if ((intColor[0] != bgcolor[0] || intColor[1] != bgcolor[1] ||
         intColor[2] != bgcolor[2]) &&
        (intColor[0] != fcolor[0] ||
         intColor[1] != fcolor[1] || intColor[2] != fcolor[2]))
    {
        glColor3f(fcolor[0], fcolor[1], fcolor[2]);
        glBegin(GL_POINTS);
        glVertex2i(x, y);
        glEnd();
        glFlush();
        eightConnectedFill((x + 1), y, bgcolor, fcolor);
        eightConnectedFill((x - 1), y, bgcolor, fcolor);
        eightConnectedFill(x, (y + 1), bgcolor, fcolor);
        eightConnectedFill(x, (y - 1), bgcolor, fcolor);
        eightConnectedFill((x + 1), (y + 1), bgcolor, fcolor);
        eightConnectedFill((x - 1), (y + 1), bgcolor, fcolor);
        eightConnectedFill((x - 1), (y - 1), bgcolor, fcolor);
        eightConnectedFill((x + 1), (y - 1), bgcolor, fcolor);
    }
}

/* ------------------------------------------------------- */
/* Function for Flood filling algorithms. Asks for point,  */
/* fill color and background color and does the operation  */
/* ------------------------------------------------------- */
void floodFill(GLint x, GLint y, float *oldColor, float *fcolor)
{
    float intColor[3];
    glReadPixels(x, y, 1.0, 1.0, GL_RGB, GL_FLOAT, intColor);

    if (intColor[0] == oldColor[0] && intColor[1] == oldColor[1] && intColor[2] == oldColor[2])
    {
        glColor3f(fcolor[0], fcolor[1], fcolor[2]);
        glBegin(GL_POINTS);
        glVertex2i(x, y);
        glEnd();
        glFlush();
        floodFill(x + 1, y, oldColor, fcolor);
        floodFill(x - 1, y, oldColor, fcolor);
        floodFill(x, y + 1, oldColor, fcolor);
        floodFill(x, y - 1, oldColor, fcolor);
    }
    return;
}

/* ------------------------------------------------------- */
/* Function to initialize. Sets clear color, fill color    */
/* and other OpenGL properties                             */
/* ------------------------------------------------------- */
void myInit()
{
    // Making background color to black as first
    glClearColor(0.0, 0.0, 0.0, 1.0);
}

/* ------------------------------------------------------- */
/* Function for drawing the figures by using openGL        */
/* ------------------------------------------------------- */
void display()
{
    glLineWidth(2);
    glPointSize(1);
    // Clears buffers to preset values
    glClear(GL_COLOR_BUFFER_BIT);
    // Resets Modelview Matrix
    glLoadIdentity();

    // Storing the values of object for plotting
    int objectx[vertexCount], objecty[vertexCount];
    for (int i = 0; i < vertexCount; i++)
    {
        objectx[i] = pointMatrix[0][i];
        objecty[i] = pointMatrix[1][i];
    }

    // Plot the original 2d Object
    glBegin(GL_LINE_LOOP);
    // Making Fill Color of Original object Red (in RGB mode)
    glColor3f(bColor[0], bColor[1], bColor[2]);
    for (int i = 0; i < vertexCount; i++)
    {
        glVertex2i(objectx[i], objecty[i]);
    }
    glEnd();

    // switch (option)
    // {
    // case 1:
    //     // fourConnectedFill(startPoint.x, startPoint.y, bColor, fillColor);
    //     fourConnectedFill(startPoint.x, startPoint.y, bColor, fillColor);
    //     break;

    // case 2:
    //     eightConnectedFill(startPoint.x, startPoint.y, bColor, fillColor);
    //     break;

    // default:
    //     printf("\nWrong Input. Try Again.\n");
    //     break;
    // }

    glFlush();
}

/* ------------------------------------------------------- */
/* Function to reshape screen properties. Sets orthographic*/
/* co-ordinates of  Porjection View Matrix                 */
/* ------------------------------------------------------- */
void reshape(int w, int h)
{
    // Sets the view port same as window
    glViewport(0, 0, w, h);

    // Switch to Projection View Matrix and reset it
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    // Setting Window Dimension in X- and Y- direction and switching back to Model View Matrix
    gluOrtho2D(0, 640, 0, 480);
    glMatrixMode(GL_MODELVIEW);
}

/* ------------------------------------------------------- */
/* Function for mouse properties.Sets the starting point or*/
/* co-ordinates of filling algorithm                       */
/* ------------------------------------------------------- */
void mouse(int btn, int state, int x, int y)
{
    y = 480 - y;
    if (btn == GLUT_LEFT_BUTTON)
    {
        if (state == GLUT_DOWN)
        {
            if (option == 1)
            {
                fourConnectedFill(x, y, bColor, fillColor);
            }
            else if (option == 2)
            {
                eightConnectedFill(x, y, bColor, fillColor);
            }
            else if (option == 3)
            {
                float oldColor[] = {0.0, 0.0, 0.0};
                floodFill(x, y, oldColor, fillColor);
            }
            else
            {

            }
        }
    }
}
