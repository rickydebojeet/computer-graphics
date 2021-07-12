/* Digital Differential Analyzer Algorithm for Line Drawing */
#include <stdio.h>
#include <graphics.h>
#include <math.h>

// Function Declarations
int abs(int);
void dda(int, int, int, int);

/* ------------------------------------------------------- */
/* Driver Code for the program. Asks for start and end     */
/* points and calls dda function by passing those values.  */
/* Return 0                                                */
/* ------------------------------------------------------- */
int main()
{
    int x1, x2, y1, y2;
    int gd = DETECT, gm;
    // Graphics funtion initialization
    initgraph(&gd, &gm, "");
    x1 = 1;
    y1 = 1;
    x2 = 8;
    y2 = 4;
    // printf("\n Enter x1:\t");
    // scanf("%d", &x1);
    // printf("\n Enter y1:\t");
    // scanf("%d", &y1);
    // printf("\n Enter x2:\t");
    // scanf("%d", &x2);
    // printf("\n Enter y2:\t");
    // scanf("%d", &y2);
    dda(x1, y1, x2, y2);
    closegraph();
    return 0;
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
    while (x < x2)
    {
        // Put pixel in the screen
        putpixel(round(x), round(y), RED);
        x = x1 + Xinc;
        y = y1 + Yinc;
        // For visualization step by step
        delay(100);
    }
}