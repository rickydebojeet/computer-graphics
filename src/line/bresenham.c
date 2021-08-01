/* Bresenham's Line Generation Algorithm */
#include <stdio.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

// Function Defination
void myInit();
int abs(int);
void bresenham(void);
void reshape(int, int);

// Global Variable for start and end points
int X1, X2, Y1, Y2;

/* ------------------------------------------------------- */
/* Driver Code for the program. Asks for start and end     */
/* points and calls Bresenham's Algorithm. Returns 0       */
/* ------------------------------------------------------- */
int main(int argc, char *argv[])
{
    printf("Enter X1:\t");
    scanf("%d", &X1);
    printf("Enter Y1:\t");
    scanf("%d", &Y1);
    printf("Enter X2:\t");
    scanf("%d", &X2);
    printf("Enter Y2:\t");
    scanf("%d", &Y2);
    printf("\nYou have entered:\nStarting Point: (%d, %d)\nEnding Point: (%d, %d)\n", X1, Y1, X2, Y2);
    
    // Initialize GLUT Library
    glutInit(&argc, argv);
    // Set the initial display mode
    glutInitDisplayMode(GLUT_RGB);
    // Set the initial window position and size
    glutInitWindowPosition(0, 0);
    glutInitWindowSize(600, 600);
    // Create the window with title "Bresenham Line Generation Algorithm"
    glutCreateWindow("Bresenham Line Generation Algorithm (0-600)");

    // Initialize drawing colors
    myInit();

    // Call the displaying call back function
    glutDisplayFunc(bresenham);
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
/* Function to find the absolute value of a integer. Takes */
/* Integer and return the absolute value of the integer    */
/* ------------------------------------------------------- */
int abs(int init)
{
    if (init > 0)
    {
        return init;
    }
    else
    {
        return (-1 * init);
    }
}

/* ------------------------------------------------------- */
/* Function implementing Bresenham line generation algor-  */ 
/* -ithm, for line generation. Takes start and end points  */
/* and puts it in the screen                               */
/* ------------------------------------------------------- */
void bresenham()
{
    // Calculates dx & dy values
    int dx = X2 - X1;
    int dy = Y2 - Y1;
    int X = X1, Y = Y1;

    // Clears buffers to preset values
    glClear(GL_COLOR_BUFFER_BIT);
    // Resets Modelview Matrix
    glLoadIdentity();
    // Plot the points
    glBegin(GL_POINTS);
    glVertex2i(X, Y);
    printf("(x, y) : (%d, %d)\n", X, Y);
    // The points are specified
    glEnd();
    glFlush();

    // If m < 1
    if (dx > dy) {
        int d = (2 * dy) - dx;
        while (X < X2)
        {
            // Plot the points
            glBegin(GL_POINTS);
            X = X + 1;
            if (d < 0)
                d = d + (2 * dy);
            else {
                Y = Y + 1;
                d = d + (2 * (dy - dx));
            }
            glVertex2i(X, Y);
            printf("(x, y) : (%d, %d)\n", X, Y);
            // The points are specified
            glEnd();
            glFlush();
        }
    }
    else{
        int d = (2 * dx) - dy;
        while (Y < Y2)
        {
            // Plot the points
            glBegin(GL_POINTS);
            Y = Y + 1;
            if (d < 0)
                d = d + (2 * dx);
            else {
                X = X + 1;
                d = d + (2 * (dx - dy));
            }
            glVertex2i(X, Y);
            printf("(x, y) : (%d, %d)\n", X, Y);
            // The points are specified
            glEnd();
            glFlush();
        }
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
    gluOrtho2D(0, 600, 0, 600);
    glMatrixMode(GL_MODELVIEW);
}