/* Digital Differential Analyzer Algorithm for X2Line Drawing */
#include <stdio.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

// Function Declarations
void myInit();
int abs(int);
void dda();
void reshape(int, int);

// Global Variables
int X1, X2, Y1, Y2;

/* ------------------------------------------------------- */
/* Driver Code for the program. Asks for start and end     */
/* points and calls dda function by passing those values.  */
/* Return 0                                                */
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
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    // Set the initial window position and size
    glutInitWindowPosition(0, 0);
    glutInitWindowSize(600, 600);
    // Create the window with title "DDA Line Drawing"
    glutCreateWindow("DDA Line Drawing");

    // Initialize drawing colors
    myInit();

    // Call the displaying call back function
    glutDisplayFunc(dda);
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
/* Function implementing DDA algorith for line generation  */
/* Takes start and end points and puts it in the screen    */
/* ------------------------------------------------------- */
void dda()
{
    // Calculates dx & dy values
    int dx = X2 - X1;
    int dy = Y2 - Y1;

    // If m < 1 then step = dx else step = dy
    int step = dx;
    if (step < dy)
    {
        step = dy;
    }

    // Calculating inital increment values we can see that
    // If m < 1; Xinc = 1 & Yinc = dy / dx [m]
    // If m > 1; Xinc = dx / dy [1 / m] & Yinc = 1
    float Xinc = dx / (float) step;
    float Yinc = dy / (float) step;

    float x = X1;
    float y = Y1;
    
    // Clears buffers to preset values
    glClear(GL_COLOR_BUFFER_BIT);
    // Resets Modelview Matrix
    glLoadIdentity();
    // Plot the points
    glBegin(GL_POINTS);
    
    for(int k = 0; k < step; k++)
    {
        // Specify Points
        glVertex2f(x, y);
        printf("(x, y) : (%d, %d)\n", (int)(x + 0.5), (int)(y + 0.5));
        x = x + Xinc;
        y = y + Yinc;
    }
    // The points are specified
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
    gluOrtho2D(0, 600, 0, 600);
    glMatrixMode(GL_MODELVIEW);
}
