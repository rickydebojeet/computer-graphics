/* Digital Differential Analyzer Algorithm for Line Drawing */
#include <stdio.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <math.h>
#include <time.h>

// Function Declarations
void myInit();
void delay(int);
int abs(int);
void dda(int, int, int, int);

/* ------------------------------------------------------- */
/* Driver Code for the program. Asks for start and end     */
/* points and calls dda function by passing those values.  */
/* Return 0                                                */
/* ------------------------------------------------------- */
int main(int argc, char *argv[])
{
    int x1, x2, y1, y2;
    printf("\n Enter x1:\t");
    scanf("%d", &x1);
    printf("\n Enter y1:\t");
    scanf("%d", &y1);
    printf("\n Enter x2:\t");
    scanf("%d", &x2);
    printf("\n Enter y2:\t");
    scanf("%d", &y2);
    printf("\nYou have entered:\nStarting Point: (%d, %d)\nEnding Point: (%d, %d)\n", x1, y1, x2, y2);
    
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

    // Call the displaying function
    glutDisplayFunc(dda(x1, y1, x2, y2));
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
     
    // Breadth of picture boundary is 1 pixel
    // glPointSize(1.0);
    // glMatrixMode(GL_PROJECTION);
    // glLoadIdentity();
     
    // Setting Window Dimension in X- and Y- direction
    gluOrtho2D(0, 600, 0, 600);
}

/* ------------------------------------------------------- */
/* Function to insert delay in seconds.                    */
/* ------------------------------------------------------- */
void delay(int number_of_seconds)
{
    // Converting time into milli_seconds
    int milli_seconds = 1000 * number_of_seconds;
  
    // Storing start time
    clock_t start_time = clock();
  
    // Looping till required time is not achieved
    while (clock() < start_time + milli_seconds);
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
void dda(int x1, int y1, int x2, int y2)
{
    // Calculates dx & dy values
    int dx = x2 - x1;
    int dy = y2 - y1;

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

    float x = x1;
    float y = y1;
    
    // Clears buffers to preset values
    glClear(GL_COLOR_BUFFER_BIT);
    // Plot the points
    glBegin(GL_POINTS);
    
    while (x < x2)
    {
        glVertex2d(round(x), round(y));
        printf("(x, y) : (%d, %d)\n", round(x), round(y));
        x = x1 + Xinc;
        y = y1 + Yinc;
        // Delay of 1 second
        delay(1);
    }
    glEnd();
    glFlush();
}
