// you can write to stdout for debugging purposes, e.g.
// printf("this is a debug message\n");
#define NUM_COUNT_NUCLEOTIDES 3

int getImpact(char nucleotide) {
    switch (nucleotide) {
        case 'A':
        return 1;
        case 'C':
        return 2;
        case 'G':
        return 3;
        case 'T':
        return 4;
    }
    return 0;
}

struct Results solution(char *S, int P[], int Q[], int M) {
    struct Results result;
    int i, N = strlen(S), impact, k, from, to;
    int * results = calloc(M, sizeof(int));
    int ** countNucleotides = (int **) malloc(NUM_COUNT_NUCLEOTIDES * sizeof(int *));

    for (i = 0; i < NUM_COUNT_NUCLEOTIDES; i++)  {
        countNucleotides[i] = calloc(N + 1, sizeof(int));
    }

    for (k = 0; k < N; k++) {
        impact = getImpact(S[k]);
        for (i = 1; i <= NUM_COUNT_NUCLEOTIDES; i++) {
            if (i == impact) {
                countNucleotides[i - 1][k + 1] = countNucleotides[i - 1][k] + 1;
            } else {
                countNucleotides[i - 1][k + 1] = countNucleotides[i - 1][k];
            }
        }
    }

    // for (i = 0; i < NUM_COUNT_NUCLEOTIDES; i++) {
    //     printf("\nCount nucleotides for impact %d: ", i + 1);
    //     for (k = 0; k < N + 1; k++) {
    //         printf("\t%d", countNucleotides[i][k]);
    //     }
    // }

    // printf("\n\nResults: ");
    for (k = 0; k < M; k++) {
        from = P[k];
        to = Q[k] + 1;
        for (i = 0; i < NUM_COUNT_NUCLEOTIDES; i++) {
            if (countNucleotides[i][to] - countNucleotides[i][from] > 0) {
                results[k] = i + 1;
                break;
            }
        }
        if (results[k] == 0) {
            results[k] = NUM_COUNT_NUCLEOTIDES + 1;
        }
        // printf("\t%d", results[k]);
    }

    for (i = 0; i < NUM_COUNT_NUCLEOTIDES; i++) {
        free(countNucleotides[i]);
    }
    free(countNucleotides);

    result.A = results;
    result.M = M;
    return result;
}