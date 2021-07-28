/* C Program to apply transformation on points, line, triangle, or any polygon */
#include <stdio.h>
#include <stdlib.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <math.h>

#define PI 3.14159265359

// Function Declarations
// Utility Functions
void matrixMultiply(int a[3][3], int b[3][15], int c[3][15]); //For Matrix Multiplication
void doubleMatrixMultiply(double a[3][3], double b[3][15], double c[3][15]);
void displayMatrix(int a[3][15]); //For Displaying Matrix
//Translation Functions
void translate(int tx, int ty, int a[3][15], int b[3][15]);   //For Translation Operation
void rotationOrigin(int degree, int a[3][15], int b[3][15]);  //For Rotation about Origin
void rotationPoint(int degree, int a[3][15], int b[3][15]);   //For Rotation about First Point
void scale(double sx, double sy, int a[3][15], int b[3][15]); //For Scaling Operation
void reflectionx(int a[3][15], int b[3][15]);                 //For Reflection about x axis
void reflectiony(int a[3][15], int b[3][15]);                 //For Reflection about y axis
// Display Functions
void display(void);
void reshape(int, int);
void myInit();

// Global Variables
int vertexCount;
int pointMatrix[3][15];
int resultantMatrix[3][15];

/* ------------------------------------------------------- */
/* Driver Code for the program. Asks for object and its    */
/* corresponding transformation. Calls required Functions  */
/* Returns 0.                                              */
/* ------------------------------------------------------- */
int main(char argc, char *argv[])
{
    int ch, op;
    int Xcoord[15], Ycoord[15];
    printf("\n/* PROGRAM TO TRANSFORM OBJECTS */\n");
    printf("Please enter the type of object:\n");
    printf("1.Point\n2.Line\n3.Triangle\n4.Polygon\n");
    scanf("%d", &ch);
    switch (ch)
    {
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
    printf("\nPlease enter the type of operation to perform:\n");
    printf("1.Translation\n2.Rotation\n3.Scaling\n4.Reflextion\n");
    scanf("%d", &op);
    switch (op)
    {
    case 1:;
        int tx, ty;
        printf("\nEnter the translation amount in X-axis:\t");
        scanf("%d", &tx);
        printf("Enter the translation amount in Y-axis:\t");
        scanf("%d", &ty);
        translate(tx, ty, pointMatrix, resultantMatrix);
        break;
    case 2:;
        int selection, degree;
        printf("\nEnter the rotation amount in degrees:\t");
        scanf("%d", &degree);
        printf("\nEnter your rotation selection\n1.About Origin\n2.About 1st Point\n");
        scanf("%d", &selection);
        if (selection == 1)
        {
            rotationOrigin(degree, pointMatrix, resultantMatrix);
        }
        else if (selection == 2)
        {
            rotationPoint(degree, pointMatrix, resultantMatrix);
        }
        else
        {
            printf("\nWrong Input. Try Again.\n");
        }
        break;
    case 3:;
        double sx, sy;
        printf("\nEnter the scale amount in X-axis:\t");
        scanf("%lf", &sx);
        printf("Enter the scale amount in Y-axis:\t");
        scanf("%lf", &sy);
        scale(sx, sy, pointMatrix, resultantMatrix);
        break;
    case 4:;
        int choice, x1, y1, x2, y2;
        printf("\nEnter your reflection selection:\n");
        printf("1.About X-axis\n2.About Y-axis\nAbout a line\n");
        scanf("%d", &choice);
        if (choice == 1)
        {
            reflectionx(pointMatrix, resultantMatrix);
        }
        else if (choice == 2)
        {
            reflectiony(pointMatrix, resultantMatrix);
        }
        else if (choice == 3)
        {
            /* code */
        }
        else
        {
            printf("\nWrong Input. Try Again.\n");
        }
        break;
    default:
        printf("\nPLEASE ENTER CORRECT OPTION\n");
        break;
    }

    // Diplay Point and Resultant Matrix
    printf("\nOriginal Point Matrix:\n");
    displayMatrix(pointMatrix);
    printf("\nNew Point Matrix:\n");
    displayMatrix(resultantMatrix);

    // Initialize GLUT Library
    glutInit(&argc, argv);
    // Set the initial display mode
    glutInitDisplayMode(GLUT_RGB);
    // Set the initial window position and size
    glutInitWindowPosition(0, 0);
    glutInitWindowSize(600, 600);
    // Create the window with title "Window name"
    glutCreateWindow("Transformation Operation");

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
/* Function  for matrix multiplication. Asks for 3 matric- */
/* -es. Multiplies first 2 matrices and puts the result in */
/* third matrix.                                           */
/* ------------------------------------------------------- */
void matrixMultiply(int a[3][3], int b[3][15], int c[3][15])
{
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < vertexCount; j++)
        {
            c[i][j] = 0;
            for (int k = 0; k < 3; k++)
            {
                c[i][j] += (a[i][k] * b[k][j]);
            }
        }
    }
}

void doubleMatrixMultiply(double a[3][3], double b[3][15], double c[3][15])
{
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < vertexCount; j++)
        {
            c[i][j] = 0;
            for (int k = 0; k < 3; k++)
            {
                c[i][j] += (a[i][k] * b[k][j]);
            }
        }
    }
}

/* ------------------------------------------------------- */
/* Function for displaying matrix. Asks for a matrix and   */
/* Prints the result in the screen                         */
/* ------------------------------------------------------- */
void displayMatrix(int a[3][15])
{
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < vertexCount; j++)
        {
            printf("%d\t", a[i][j]);
        }
        printf("\n");
    }
    printf("\n\n");
}

/* ------------------------------------------------------- */
/* Function for Translation Operation. Asks for translation*/
/* Values, point matrix and resultant matrix and does the  */
/* Translation operation.                                  */
/* ------------------------------------------------------- */
void translate(int tx, int ty, int a[3][15], int b[3][15])
{
    int t[3][3]; //Translation Matrix
    //Initialising Translation Matrix
    t[0][0] = 1;
    t[0][1] = 0;
    t[0][2] = tx;
    t[1][0] = 0;
    t[1][1] = 1;
    t[1][2] = ty;
    t[2][0] = 0;
    t[2][1] = 0;
    t[2][2] = 1;
    matrixMultiply(t, a, b);
}

/* ------------------------------------------------------- */
/* Function for Rotation Operation about origin. Asks for  */
/* degree, point matrix and resultant matrix. Does the ro- */
/* -tation operation about origin and stores it in the re- */
/* -sultant matrix                                         */
/* ------------------------------------------------------- */
void rotationOrigin(int degree, int a[3][15], int b[3][15])
{
    // Converting degree into radians
    double radian = (((double)degree) * PI) / 180.0;

    double r[3][3]; //Rotation Matrix
    // Initialising Rotation Matrix
    r[0][0] = cos(radian);
    r[0][1] = sin(radian);
    r[0][2] = 0;
    r[1][0] = -sin(radian);
    r[1][1] = cos(radian);
    r[1][2] = 0;
    r[2][0] = 0;
    r[2][1] = 0;
    r[2][2] = 1;

    // Temporary double variables
    double init[3][15], final[3][15];

    // Initialising the temporary double variables
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 15; j++)
        {
            init[i][j] = a[i][j];
            final[i][j] = b[i][j];
        }
    }

    // Doing the rotation operation
    doubleMatrixMultiply(r, init, final);

    // Storing the final results
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 15; j++)
        {
            b[i][j] = final[i][j];
        }
    }
}

/* ------------------------------------------------------- */
/* Function for Rotation Operation about first point. Asks */
/* for degree, point matrix and resultant matrix and does  */
/* rotation operation about first point and stores it in   */
/* the resultant matrix                                    */
/* ------------------------------------------------------- */
void rotationPoint(int degree, int a[3][15], int b[3][15])
{
    // Temporary Matrix to store intermediate values
    int temp1[3][15], temp2[3][15];

    // Step 1: Shift/Translation where T(-firstxcoord, -firstycoord)
    translate(-a[0][0], -a[1][0], a, temp1);

    // Step 2: Rotation about origin with R(degree)
    rotationOrigin(degree, temp1, temp2);

    // Step 3: Shift/Translation where T(firstxcoord, firstycoord)
    translate(a[0][0], a[1][0], temp2, b);
}

/* ------------------------------------------------------- */
/* Function for Scale Operation. Asks for scale about x,   */
/* y, point matrix and resultant matrix and does scaling   */
/* operation and stores it in resultant matrix             */
/* ------------------------------------------------------- */
void scale(double sx, double sy, int a[3][15], int b[3][15])
{
    double s[3][3]; //Scaling Matrix
    // Initialising Scaling Matrix
    s[0][0] = sx;
    s[0][1] = 0;
    s[0][2] = 1;
    s[1][0] = 0;
    s[1][1] = sy;
    s[1][2] = 0;
    s[2][0] = 0;
    s[2][1] = 0;
    s[2][2] = 1;

    // Temporary double variables
    double init[3][15], final[3][15];

    // Initialising the temporary double variables
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 15; j++)
        {
            init[i][j] = a[i][j];
            final[i][j] = b[i][j];
        }
    }

    // Doing the scaling operation
    doubleMatrixMultiply(s, init, final);

    // Storing the final results
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 15; j++)
        {
            b[i][j] = final[i][j];
        }
    }
}

/* ------------------------------------------------------- */
/* Function for Reflection Operationa about x axis.Asks for*/
/* point matrix and resultant matrix and does scaling op   */
/* and stores it in resultant matrix                       */
/* ------------------------------------------------------- */
void reflectionx(int a[3][15], int b[3][15])
{
    int rfx[3][3]; // Rotation Matrix
    // Initialising Rotation Matrix
    rfx[0][0] = 1;
    rfx[0][1] = 0;
    rfx[0][2] = 0;
    rfx[1][0] = 0;
    rfx[1][1] = -1;
    rfx[1][2] = 0;
    rfx[2][0] = 0;
    rfx[2][1] = 0;
    rfx[2][2] = 1;

    // Refection Operation    
    matrixMultiply(rfx, a, b);
}

/* ------------------------------------------------------- */
/* Function for Reflection Operationa about yaxis.Asks for */
/* point matrix and resultant matrix and does scaling op   */
/* and stores it in resultant matrix                       */
/* ------------------------------------------------------- */
void reflectiony(int a[3][15], int b[3][15])
{
    int rfy[3][3]; // Rotation Matrix
    // Initialising Rotation Matrix
    rfy[0][0] = -1;
    rfy[0][1] = 0;
    rfy[0][2] = 0;
    rfy[1][0] = 0;
    rfy[1][1] = 1;
    rfy[1][2] = 0;
    rfy[2][0] = 0;
    rfy[2][1] = 0;
    rfy[2][2] = 1;

    // Refection Operation    
    matrixMultiply(rfy, a, b);
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

    // Plot the 2d Cartesian plane
    glBegin(GL_LINES);
    // Making Fill Color White (in RGB mode)
    glColor3f(1.0, 1.0, 1.0);
    // The points are specified
    glVertex2i(0, 300);
    glVertex2i(0, -300);
    glVertex2i(300, 0);
    glVertex2i(-300, 0);
    glEnd();

    // Storing the values of old and new onjects for plotting
    int originx[vertexCount], originy[vertexCount], newx[vertexCount], newy[vertexCount];
    for (int i = 0; i < vertexCount; i++)
    {
        originx[i] = pointMatrix[0][i];
        originy[i] = pointMatrix[1][i];
        newx[i] = resultantMatrix[0][i];
        newy[i] = resultantMatrix[1][i];
    }

    // Code for the glBegin
    int code;

    switch (vertexCount)
    {
    case 1:
        code = GL_POINTS;
        break;

    case 2:
        code = GL_LINES;
        break;

    default:
        code = GL_LINE_LOOP;
        break;
    }

    // Plot the original 2d Object
    glBegin(code);
    // Making Fill Color of Original object Red (in RGB mode)
    glColor3f(1.0, 0.0, 0.0);
    for (int i = 0; i < vertexCount; i++)
    {
        glVertex2i(originx[i], originy[i]);
    }
    glEnd();

    // Plot the new 2d Object
    glBegin(code);
    // Making Fill Color of new object blue (in RGB mode)
    glColor3f(0.0, 0.0, 1.0);
    for (int i = 0; i < vertexCount; i++)
    {
        glVertex2i(newx[i], newy[i]);
    }
    glEnd();

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