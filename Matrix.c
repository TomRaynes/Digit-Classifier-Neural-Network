#include "nn.h"

Matrix* newMatrix(int size, int depth, char* weightsPath) {
    Matrix *matrix = malloc(sizeof(Matrix));
    matrix->size = size;
    matrix->depth = depth;
    matrix->weights = malloc(depth * sizeof(double*));

    if (matrix->weights == NULL) {
        printf("Failed to allocate memory for matrix data\n");
        exit(EXIT_FAILURE);
    }
    for (int i = 0; i < depth; i++) {
        matrix->weights[i] = malloc(size * sizeof(double));

        if (matrix->weights[i] == NULL) {
            printf("Failed to allocate memory for matrix data[%d]\n", i);
            exit(EXIT_FAILURE);
        }
        if (weightsPath == NULL) {
            for (int j = 0; j < size; j++) {
                matrix->weights[i][j] = (double) rand() / RAND_MAX * 2 - 1;
            }
        }
    }
    if (weightsPath != NULL) {
        loadWeights(matrix, weightsPath);
    }
    matrix->biases = malloc(depth * sizeof(double));
    // TODO: load biases

    if (matrix->biases == NULL) {
        printf("Failed to allocate memory for matrix bias data\n");
        exit(EXIT_FAILURE);
    }
    for (int i = 0; i < depth; i++) {
        matrix->biases[i] = (double) rand() / RAND_MAX * 2 - 1;
    }
    matrix->free = freeMatrix;
    matrix->print = printMatrix;
    return matrix;
}

void freeMatrix(Matrix* matrix) {
    for (int i = 0; i < matrix->depth; i++) {
        free(matrix->weights[i]);
    }
    free(matrix->weights);
    free(matrix->biases);
    free(matrix);
}

void printMatrix(Matrix* matrix) {
    for (int row = 0; row < matrix->size; row++) {
        for (int col = 0; col < matrix->depth; col++) {
            printf("%.2f   ", matrix->weights[col][row]);
        }
        printf("\n");
    }
}

void saveWeights(Matrix* matrix, char* filename) {
    FILE* fp = fopen(filename, "w");

    if (fp == NULL) {
        printf("Failed to open file for writing\n");
        exit(EXIT_FAILURE);
    }
    for (int layer = 0; layer < matrix->depth; layer++) {
        fwrite(matrix->weights[layer], sizeof(double), matrix->size, fp);
    }
    fclose(fp);
}

void loadWeights(Matrix* matrix, char* filename) {
    FILE* fp = fopen(filename, "r");

    if (fp == NULL) {
        printf("Failed to open %s\n", filename);
        exit(EXIT_FAILURE);
    }
    for (int layer = 0; layer < matrix->depth; layer++) {
        fread(matrix->weights[layer], sizeof(double), matrix->size, fp);
    }
    fclose(fp);
}