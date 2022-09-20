#include <stdio.h>
#include <math.h>
#define ERR_IO 1
#define ERR_NOT_TRIANGLE 2
#define OK_INSIDE 3
#define OK_OUTSIDE 4
#define OK_ON_SIDE 5
#define EPS 0.0000001

int solve(float, float, float, float, float, float, float, float);
float triangle_sq(float, float, float, float, float, float);
int f_equal(float, float);

int main()
{
    int return_code;
    float ax, ay, bx, by, cx, cy, px, py;
    printf("Please enter points A, B, C, P: ");
    if (scanf("%f%f%f%f%f%f%f%f", &ax, &ay, &bx, &by, &cx, &cy, &px, &py) != 8)
    {
        printf("Invalid input!\n");
        return_code = ERR_IO;
    }
    else
    {
        int pos = solve(ax, ay, bx, by, cx, cy, px, py);
        switch (pos)
        {
            case ERR_NOT_TRIANGLE:
                printf("Point A, B, C doesn't represent a triangle!\n");
                return_code = 1;
                break;
            case OK_OUTSIDE:
                printf("Point is outside of triangle: 2\n");
                return_code = 0;
                break;
            case OK_INSIDE:
                printf("Point is inside of triangle: 0\n");
                return_code = 0;
                break;
            case OK_ON_SIDE:
                printf("Point is on the side of triangle: 1\n");
                return_code = 0;
                break;
        }
    }
    return return_code;
}

int solve(float ax, float ay, float bx, float by, float cx, float cy, float px, float py)
{
    int result;

    float abp, bcp, acp, abc;
    abp = triangle_sq(ax, ay, bx, by, px, py);
    bcp = triangle_sq(bx, by, cx, cy, px, py);
    acp = triangle_sq(ax, ay, cx, cy, px, py);
    abc = triangle_sq(ax, ay, bx, by, cx, cy);

    if (f_equal(abc, 0))
    {
        result = ERR_NOT_TRIANGLE;
    }
    else if (f_equal(abp, 0) || f_equal(bcp, 0) || f_equal(acp, 0))
    {
        result = OK_ON_SIDE;
    }
    else if (f_equal(abp + bcp + acp, abc))
    {
        result = OK_INSIDE;
    }
    else
    {
        result = OK_OUTSIDE;
    }

    return result;
}

float triangle_sq(float ax, float ay, float bx, float by, float cx, float cy)
{
    return fabsf((bx - ax) * (cy - ay) - (cx - ax) * (by - ay)) / 2;
}

int f_equal(float f0, float f1)
{
    return (fabsf(f0 - f1) < EPS);
}
