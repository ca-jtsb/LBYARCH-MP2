#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <Windows.h>

extern void acc(int rows, float* matrix, int* result);

void calc_acceleration(int rows, float* matrix, int* result) {
    const float cf = 1000.0f / 3600.0f;

    for (int i = 0; i < rows; i++) {
        float Vi = matrix[i * 3];
        float Vf = matrix[i * 3 + 1];
        float T = matrix[i * 3 + 2];

        float converted_Vi = Vi * cf;
        float converted_Vf = Vf * cf;
        float acceleration = (converted_Vf - converted_Vi) / T;
        result[i] = (int)(acceleration + 0.5);
    }

}

int main(int argc, char* argv[]) {
    int rows;
    printf("Enter number of rows: ");
    scanf_s("%d", &rows);

    // allocate memory for matrix and result
    float* matrix = (float*)malloc(rows * 3 * sizeof(float));
    int* result = (int*)malloc(rows * sizeof(int));
    int* result_C = (int*)malloc(rows * sizeof(int));

    // get inputs
    printf("Enter matrix values (Vi, Vf, T):\n");
    for (int i = 0; i < rows; i++) {
        printf("Row %d (Vi Vf T): ", i + 1);
        scanf_s("%f %f %f", &matrix[i * 3], &matrix[i * 3 + 1], &matrix[i * 3 + 2]);
    }

    // generate random values for matrix (testing runtime) for input Y size = {10, 100, 1000, 10000}
    // ----- UNCOMMENT THIS AND COMMENT OUT "get inputs" code to generate random values ------
    //for (int i = 0; i < rows; i++) {
    //    matrix[i * 3] = (float)(rand() % 161); // Vi
    //    matrix[i * 3 + 1] = (float)(rand() % (200 - (int)matrix[i * 3])) + (int)matrix[i * 3]; // Vf
    //    matrix[i * 3 + 2] = (float)(rand() % 30) + 1; // T
    //}

    // print the input matrix 
    printf("\nInput Matrix:\n");
    for (int i = 0; i < rows; i++) {
        printf("Row %d: Vi = %.2f, Vf = %.2f, T = %.2f\n",
            i + 1, matrix[i * 3], matrix[i * 3 + 1], matrix[i * 3 + 2]);
    }
    // timer variable
    LARGE_INTEGER frequency, start, end;
    double time_taken;
    QueryPerformanceFrequency(&frequency);

    // ---------- call C function for correctness check ---------------
    calc_acceleration(rows, matrix, result_C);
    printf("\nOutput (C):\n");
    for (int i = 0; i < rows; i++) {
        printf("Row %d: acceleration = %d m/s^2\n", i + 1, result_C[i]);
    }

    // --------------- call asm function (x86-64) ---------------------
    // get avg runtime
    double sum = 0;
    for (int i = 0; i < 30; i++) {
        QueryPerformanceCounter(&start);
        acc(rows, matrix, result);
        QueryPerformanceCounter(&end);
        time_taken = ((double)(end.QuadPart - start.QuadPart) / frequency.QuadPart) * 1000000.0;
        sum += time_taken;
    }

    printf("\nOutput (x86-64):\n");
    for (int i = 0; i < rows; i++) {
        printf("Row %d: acceleration = %d m/s^2\n", i + 1, result[i]);
    }

    printf("\nTotal runtime = %lf microseconds", sum);
    printf("\nAverage runtime = %lf microseconds\n", (sum / 30));

    return 0;
}