#include <stdio.h>
#include <math.h>

float trapez_p(float, float, float);

int main()
{
    float a, b, h;
    printf("Input A: ");
    scanf("%f", &a);
    printf("Input B: ");
    scanf("%f", &b);
    printf("Input Height: ");
    scanf("%f", &h);

    float result = trapez_p(a, b, h);
    
    printf("Perimeter of the trapezoid: %f\n", result);
    return 0;
}

float trapez_p(float a, float b, float h)
{
    float delta = fabsf(a - b) / 2;
    
    return a + b + 2 * (sqrtf(h * h + delta * delta));
}
