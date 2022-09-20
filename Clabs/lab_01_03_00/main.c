#include <stdio.h>

float normal_mass(float, float);

float body_index(float, float);

int main()
{
    float h, t, m;
    printf("Input height: ");
    scanf("%f", &h);
    printf("Input chest girth: ");
    scanf("%f", &t);
    printf("Input body mass: ");
    scanf("%f", &m);

    float m_normal = normal_mass(h, t);
    float bmi = body_index(m, h / 100);
    printf("Normal mass: %f\nBMI: %f\n", m_normal, bmi);
    return 0;
}

float normal_mass(float h, float t)
{
    return h * t / 240;
}

float body_index(float m, float h)
{
    return m / (h * h);
}
