/* Mid Point Circle Drawing Algorithm */
#include <stdio.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

// Function Defination
void myInit();
void midpoint(void);
void reshape(int, int);
double pow(double, double);
double sqrt(double);

// Global Variable for start point
double r;

/* ------------------------------------------------------- */
/* Driver Code for the program. Asks for start and end     */
/* points and calls Mid Point Circle Drawing Algorithm.    */
/* Returns 0                                               */
/* ------------------------------------------------------- */
int main(int argc, char *argv[])
{
    int X1, X2, Y1, Y2;
    printf("Enter X1:\t");
    scanf("%d", &X1);
    printf("Enter Y1:\t");
    scanf("%d", &Y1);
    printf("Enter X2:\t");
    scanf("%d", &X2);
    printf("Enter Y2:\t");
    scanf("%d", &Y2);
    printf("\nYou have entered:\nStarting Point: (%d, %d)\nEnding Point: (%d, %d)\n", X1, Y1, X2, Y2);

    // Calculating radius
    r = sqrt(pow((X2 - X1), 2) + pow((Y2 - Y1), 2)) / 2;
    printf("\nRadius: %lf\n", r);

    // Initialize GLUT Library
    glutInit(&argc, argv);
    // Set the initial display mode
    glutInitDisplayMode(GLUT_RGB);
    // Set the initial window position and size
    glutInitWindowPosition(0, 0);
    glutInitWindowSize(600, 600);
    // Create the window with title "Mid Point Circle Drawing Algorithm"
    glutCreateWindow("Mid Point Circle Drawing Algorithm (-300-300)");

    // Initialize drawing colors
    myInit();

    // Call the displaying call back function
    glutDisplayFunc(midpoint);
    // Call the reshape call back function
    glutReshapeFunc(reshape);
    glutMainLoop();
    return 0;
}

/* ------------------------------------------------------- */
/* Function to initialize. Sets clear color, fill color    */
/* and other OpenGL properties                             */
/* ------------------------------------------------------- */
void myInit()
{
    // Making background color to black as first
    glClearColor(0.0, 0.0, 0.0, 1.0);

    // Making Fill Color green (in RGB mode), as middle argument is 1.0
    glColor3f(0.0, 1.0, 0.0);
}

/* ------------------------------------------------------- */
/* Function implementing Mid Point Circle Drawing  algori- */
/* -thm, for Circle generation. Takes start point and puts */
/* circle in the screen.                                   */
/* ------------------------------------------------------- */
void midpoint()
{
    // Initialization
    int X, Y, p;
    p = (5 / 4) - r;
    X = 0;
    Y = r;

    // Clears buffers to preset values
    glClear(GL_COLOR_BUFFER_BIT);
    // Resets Modelview Matrix
    glLoadIdentity();
    while (X < Y)
    {
        // Plot the points
        glBegin(GL_POINTS);
        glVertex2i(X, Y);
        glVertex2i(-X, Y);
        glVertex2i(-X, -Y);
        glVertex2i(X, -Y);
        glVertex2i(Y, X);
        glVertex2i(-Y, X);
        glVertex2i(-Y, -X);
        glVertex2i(Y, -X);
        printf("(x, y) : (%d, %d)\n", X, Y);
        printf("(x, y) : (%d, %d)\n", -X, Y);
        printf("(x, y) : (%d, %d)\n", -X, -Y);
        printf("(x, y) : (%d, %d)\n", X, -Y);
        printf("(x, y) : (%d, %d)\n", Y, X);
        printf("(x, y) : (%d, %d)\n", -Y, X);
        printf("(x, y) : (%d, %d)\n", -Y, -X);
        printf("(x, y) : (%d, %d)\n", Y, -X);
        X = X + 1;
        if (p < 0)
        {
            p = p + (2 * X) + 1;
        }
        else
        {
            Y = Y - 1;
            p = p + (2 * (X - Y)) + 1;
        }
        // The points are specified
        glEnd();
        glFlush();
    }
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

/* ------------------------------------------------------- */
/* Helping Functions to find out power and square root of  */
/* double value.                                           */
/* ------------------------------------------------------- */
double pow(double a, double b)
{
    double result = 1;
    for (int i = 0; i < b; i++)
    {
        result = result * a;
    }
    return result;
}

double sqrt(double number)
{
    double error = 0.00001; //define the precision of your result
    double s = number;

    while ((s - number / s) > error) //loop until precision satisfied 
    {
        s = (s + number / s) / 2;
    }
    return s;
}