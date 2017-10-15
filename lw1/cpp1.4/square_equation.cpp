#include <cmath>
#include <cstdio>

int main()
{
    // 1. prompt user to enter coefficients
    std::puts("Please enter a, b and c for 'ax^2 + bx + c = 0':");

    // 2. read coefficients for equation `ax + b = 0`
    float a = 0;
    float b = 0;
    float c = 0;
    std::scanf("%f %f %f", &a, &b, &c);

    // 3. solve equation `ax^2 + bx + c = 0`
    // solution: `d = b * b  - 4 * a * c` and solution: 'x'

    float d = b * b - 4 * a * c;
    if (d > 0)
    {
        float x1 = (-b + sqrt(d)) / 2 * a;
        float x2 = (-b - sqrt(d)) / 2 * a;
        std::printf("solution: %f %f\n", x1, x2);
    }
    else
    {
        if (d = 0)
        {
            float x = -b / 2 * a;
            std::printf("solution: %f\n", x);
        }
        else
        {
            std::puts("no roots");
        }
    }
}