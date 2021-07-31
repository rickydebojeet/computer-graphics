/* C Program to apply Boundary Filliing algorithm on triangle, or any polygon */
#include <stdio.h>
#include <stdlib.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

// Structure to Store the Color Values
typedef struct floatColor
{
    GLfloat red;
    GLfloat green;
    GLfloat blue;
} color;
// Structure to Store Points
typedef struct intPoint
{
    GLint x;
    GLint y;
} point;

// Global Variables
int vertexCount, option;
int pointMatrix[3][15];
color bColor, fillColor;
point startPoint;
int con4 = 0, set = 0;

// Function Declarations
color getColor(GLint, GLint);
void setColor(GLint, GLint, color);
void fourConnectedFill(GLint, GLint, color, color);
void eightConnectedFill(GLint, GLint, color, color);
// Display Functions
void display(void);
void reshape(int, int);
void myInit();

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
        bColor.red = 1.0;
        bColor.green = 0.0;
        bColor.blue = 0.0;
        printf("\nPlease enter fill color type:\n");
        printf("1.Green\n2.Blue\n3.White\n");
        scanf("%d", &choice1);
        switch (choice1)
        {
        case 1:;
            fillColor.red = 0.0;
            fillColor.green = 1.0;
            fillColor.blue = 0.0;
            break;

        case 2:;
            fillColor.red = 0.0;
            fillColor.green = 0.0;
            fillColor.blue = 1.0;
            break;

        case 3:;
            fillColor.red = 1.0;
            fillColor.green = 1.0;
            fillColor.blue = 1.0;
            break;

        default:
            printf("\nPLEASE ENTER CORRECT OPTION\n");
            break;
        }
        break;
    case 2:;
        int choice2;
        bColor.red = 0.0;
        bColor.green = 1.0;
        bColor.blue = 0.0;
        printf("\nPlease enter fill color type:\n");
        printf("1.Red\n2.Blue\n3.White\n");
        scanf("%d", &choice2);
        switch (choice2)
        {
        case 1:;
            fillColor.red = 1.0;
            fillColor.green = 0.0;
            fillColor.blue = 0.0;
            break;

        case 2:;
            fillColor.red = 0.0;
            fillColor.green = 0.0;
            fillColor.blue = 1.0;
            break;

        case 3:;
            fillColor.red = 1.0;
            fillColor.green = 1.0;
            fillColor.blue = 1.0;
            break;

        default:
            printf("\nPLEASE ENTER CORRECT OPTION\n");
            break;
        }
        break;
    case 3:;
        int choice3;
        bColor.red = 0.0;
        bColor.green = 0.0;
        bColor.blue = 1.0;
        printf("\nPlease enter fill color type:\n");
        printf("1.Red\n2.Green\n3.White\n");
        scanf("%d", &choice3);
        switch (choice3)
        {
        case 1:;
            fillColor.red = 1.0;
            fillColor.green = 0.0;
            fillColor.blue = 0.0;
            break;

        case 2:;
            fillColor.red = 0.0;
            fillColor.green = 1.0;
            fillColor.blue = 0.0;
            break;

        case 3:;
            fillColor.red = 1.0;
            fillColor.green = 1.0;
            fillColor.blue = 1.0;
            break;

        default:
            printf("\nPLEASE ENTER CORRECT OPTION\n");
            break;
        }
        break;
    case 4:;
        int choice4;
        bColor.red = 1.0;
        bColor.green = 1.0;
        bColor.blue = 1.0;
        printf("\nPlease enter fill color type:\n");
        printf("1.Red\n2.Green\n3.Blue\n");
        scanf("%d", &choice4);
        switch (choice4)
        {
        case 1:;
            fillColor.red = 1.0;
            fillColor.green = 0.0;
            fillColor.blue = 0.0;
            break;

        case 2:;
            fillColor.red = 0.0;
            fillColor.green = 1.0;
            fillColor.blue = 0.0;
            break;

        case 3:;
            fillColor.red = 0.0;
            fillColor.green = 0.0;
            fillColor.blue = 1.0;
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
    printf("1.4-Connected\n2.8-Connected\n");
    scanf("%d", &choice);
    if (choice == 1)
    {
        option = 1;
        printf("Enter Starting Point:\nX:\t");
        scanf("%d", &(startPoint.x));
        printf("Y:\t");
        scanf("%d", &(startPoint.y));
    }
    else if (choice == 2)
    {
        option = 2;
        printf("Enter Starting Point:\nX:\t");
        scanf("%d", &(startPoint.x));
        printf("Y:\t");
        scanf("%d", &(startPoint.y));
    }
    else
    {
        printf("\nWrong Input. Try Again.\n");
    }

    // Initialize GLUT Library
    glutInit(&argc, argv);
    // Set the initial display mode
    glutInitDisplayMode(GLUT_RGB);
    // Set the initial window position and size
    glutInitWindowPosition(0, 0);
    glutInitWindowSize(600, 600);
    // Create the window with title "Window name"
    glutCreateWindow("Boundary Filling Operation");

    // Initialize drawing colors
    myInit();

    // Call the displaying call back function
    glutDisplayFunc(display);
    // Call the reshape call back function
    glutReshapeFunc(reshape);
    glutMainLoop();
    return 0;
}

/* ------------------------------------------------------- */
/* Function to get color of a pixel . Uses graphics and    */
/* and other OpenGL properties                             */
/* ------------------------------------------------------- */
color getColor(GLint x, GLint y)
{
    color tmpColor;
    glReadPixels(x, y, 1, 1, GL_RGB, GL_FLOAT, &tmpColor);
    return tmpColor;
}

/* ------------------------------------------------------- */
/* Function to set color of a pixel . Uses graphics and    */
/* and other OpenGL properties                             */
/* ------------------------------------------------------- */
void setColor(GLint x, GLint y, color tmpColor)
{
    printf("\nI'm in set color. Entry no. %d\n", set);
    glColor3f(tmpColor.red, tmpColor.green, tmpColor.blue);
    glBegin(GL_POINTS);
    glVertex2i(x, y);
    glEnd();
    glFlush();
    printf("\n Exiting set color\n");
}

/* ------------------------------------------------------- */
/* Function for 4-Connected fill algorithms. Asks for point*/
/* fill color and background color and does the operation  */
/* ------------------------------------------------------- */
void fourConnectedFill(GLint x, GLint y, color bgcolor, color fcolor)
{
    con4++;
    printf("\nI'm in 4 connected fill. Entry no. %d\n", con4);
    color intColor = getColor(x, y);
    if ((intColor.red != bgcolor.red || intColor.green != bgcolor.green ||
         intColor.blue != bgcolor.blue) &&
        (intColor.red != fillColor.red ||
         intColor.green != fillColor.green || intColor.blue != fillColor.blue))
    {
        printf("\nI am inside if\n");
        setColor(x, y, fcolor);
        fourConnectedFill((x + 1), y, bgcolor, fcolor);
        fourConnectedFill((x - 1), y, bgcolor, fcolor);
        fourConnectedFill(x, (y + 1), bgcolor, fcolor);
        fourConnectedFill(x, (y - 1), bgcolor, fcolor);
    }
    printf("\n Exiting four Connected Fill\n");
}

/* ------------------------------------------------------- */
/* Function for 8-Connected fill algorithms. Asks for point*/
/* fill color and background color and does the operation  */
/* ------------------------------------------------------- */
void eightConnectedFill(GLint x, GLint y, color bgcolor, color fcolor)
{
    color intColor = getColor(x, y);
    if (intColor.red != bgcolor.red && intColor.green != bgcolor.green &&
        intColor.blue != bgcolor.blue && intColor.red != fillColor.red &&
        intColor.green != fillColor.green && intColor.blue != fillColor.blue)
    {
        setColor(x, y, fcolor);
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

void floodFill(GLint x, GLint y, color oldColor, color newColor)
{
    
    color intColor = getColor(x, y);

    if (intColor.red == oldColor.red && intColor.green == oldColor.green && intColor.blue == oldColor.blue)
    {
        setColor(x, y, newColor);
        floodFill(x + 1, y, oldColor, newColor);
        floodFill(x - 1, y, oldColor, newColor);
        floodFill(x, y + 1, oldColor, newColor);
        floodFill(x, y - 1, oldColor, newColor);
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
    glColor3f(bColor.red, bColor.green, bColor.blue);
    for (int i = 0; i < vertexCount; i++)
    {
        glVertex2i(objectx[i], objecty[i]);
    }
    glEnd();

    switch (option)
    {
    case 1:
        // fourConnectedFill(startPoint.x, startPoint.y, bColor, fillColor);
        floodFill(startPoint.x, startPoint.y, bColor, fillColor);
        break;

    case 2:
        eightConnectedFill(startPoint.x, startPoint.y, bColor, fillColor);
        break;

    default:
        printf("\nWrong Input. Try Again.\n");
        break;
    }

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
    gluOrtho2D(-300, 300, -300, 300);
    glMatrixMode(GL_MODELVIEW);
}
