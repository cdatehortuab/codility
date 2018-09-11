// you can write to stdout for debugging purposes, e.g.
// printf("this is a debug message\n");

// Test sets:
// [5, 6, 3, 4, 9] -> 2
// [-10000, -10000] -> 0
// [10000, -10000] -> 0

#include <float.h>

int solution(int A[], int N) {
    int i, minAvgIndex = N, startIndex = 0, acumPosSum = 0;
    double minAvg = DBL_MAX, minAvgAux = DBL_MAX, aux;
    int * acumSum = (int *) malloc((N + 1) * sizeof(double));
    double * acumPreAvg = (double *) malloc((N + 1) * sizeof(double));
    double * acumPosAvg = (double *) malloc((N + 1) * sizeof(double));

    acumSum[0] = 0;
    acumPreAvg[0] = 0.0;
    acumPosAvg[N] = 0.0;

    for (i = 0; i < N; i++) {
        acumSum[i + 1] = acumSum[i] + A[i];
        acumPreAvg[i + 1] = ((double) acumSum[i + 1]) / (i + 1);
        acumPosSum += A[N - i - 1];
        acumPosAvg[N - i - 1] += ((double) acumPosSum) / (i + 1);
    }

    // printf("\n acumSum: ");
    // for (i = 0; i < N + 1; i++) {
    //     printf("    %d", acumSum[i]);
    // }
    //
    // printf("\n acumPreAvg: ");
    // for (i = 0; i < N + 1; i++) {
    //     printf("    %f", acumPreAvg[i]);
    // }
    //
    // printf("\n acumPosAvg: ");
    // for (i = 0; i < N + 1; i++) {
    //     printf("    %f", acumPosAvg[i]);
    // }

    for (i = 1; i < N + 1; i++) {
        aux = acumPreAvg[i];
        if (aux < minAvgAux) {
            minAvgAux = aux;
            minAvgIndex = i;
        }
    }

    minAvg = minAvgAux + 1;

    for (i = 0; i < minAvgIndex - 1; i++) {
        aux = ((double) (acumSum[minAvgIndex] - acumSum[i])) / (minAvgIndex - i);
        // printf("\ni is %d, minAvgIndex is %d, aux is %f, and minAvg is %f", i, minAvgIndex, aux, minAvg);
        if (aux < minAvg) {
            // printf("\t changing minAvg");
            minAvg = aux;
            startIndex = i;
        }
    }

    minAvgAux = DBL_MAX;
    for (i = 0; i < N; i++) {
        aux = acumPosAvg[i];
        if (aux < minAvgAux) {
            minAvgAux = aux;
            minAvgIndex = i;
        }
    }

    if (minAvgIndex != startIndex) {
        for (i = minAvgIndex + 1; i < N; i++) {
            aux = ((double) (acumSum[i + 1] - acumSum[minAvgIndex])) / (i + 1 - minAvgIndex);
            // printf("\ni is %d, minAvgIndex is %d, aux is %f, and minAvg is %f", i, minAvgIndex, aux, minAvg);
            if (aux < minAvg) {
                // printf("\t changing minAvg");
                minAvg = aux;
                startIndex = minAvgIndex;
                break;
            }
        }
    }

    return startIndex;
}
