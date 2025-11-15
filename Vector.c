#include <math.h>

#include "nn.h"

Vector* newVector(int size) {
    Vector* vector = malloc(sizeof(Vector));

    if (vector == NULL) {
        fprintf(stderr, "Failed to allocate memory for vector\n");
        exit(EXIT_FAILURE);
    }
    vector->size = size;
    vector->data = malloc(size * sizeof(double));

    if (vector->data == NULL) {
        printf("Failed to allocate memory for tensor\n");
        exit(EXIT_FAILURE);
    }
    for (int i = 0; i < size; i++) {
        vector->data[i] = (double) rand() / RAND_MAX;
    }
    vector->free = freeVector;
    vector->print = printVector;
    vector->multiply = matrix_multiply;
    vector->rectify = rectify;
    vector->softmax = softmax;
    return vector;
}

void freeVector(Vector* vector) {
    free(vector->data);
    free(vector);
}

Vector* matrix_multiply(Vector* input, Matrix* matrix) {
    Vector* output = newVector(matrix->depth);

    for (int i = 0; i < output->size; i++) {
        output->data[i] = dot_product(input, matrix->weights[i]);
        output->data[i] += matrix->biases[i];
    }
    return output;
}

double dot_product(Vector* input, double* matrix_layer) {
    double sum = 0;

    for (int i = 0; i < input->size; i++) {
        sum += input->data[i] * matrix_layer[i];
    }
    return sum;
}

void rectify(Vector* vector) {
    for (int i = 0; i < vector->size; i++) {
        if (vector->data[i] < 0) {
            vector->data[i] = 0;
        }
    }
}

void softmax(Vector* vector) {
    double sum = 0.0;
    double maxValue = vector->data[0];

    for (int i = 0; i < vector->size; i++) {
        if (vector->data[i] > maxValue) {
            maxValue = vector->data[i];
        }
    }
    for (int i = 0; i < vector->size; i++) {
        sum += vector->data[i] = exp(vector->data[i] - maxValue);
    }
    for (int i = 0; i < vector->size; i++) {
        vector->data[i] /= sum;
    }
}

void printVector(Vector* vector) {
    for (int i = 0; i < vector->size; i++) {
        printf("%.2f\n", vector->data[i]);
    }
}