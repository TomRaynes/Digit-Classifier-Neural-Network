#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct Matrix {
    int size, depth;
    double** weights;
    double* biases;
    void (*free)(struct Matrix*);
    void (*print)(struct Matrix*);
} Matrix;

typedef struct Vector {
    int size;
    double* data;
    void (*free)(struct Vector*);
    void (*print)(struct Vector*);
    struct Vector* (*multiply)(struct Vector*, Matrix*);
    void (*rectify)(struct Vector*);
    void (*softmax)(struct Vector*);
} Vector;

double dot_product(Vector* input, double* matrix_layer);
Vector* newVector(int size);
Vector* matrix_multiply(Vector* input, Matrix* matrix);
void freeVector(Vector* vector);
Matrix* newMatrix(int size, int depth, char* weightsPath);
void printVector(Vector* vector);
void printMatrix(Matrix* weight);
void freeMatrix(Matrix* matrix);
void rectify(Vector* vector);
void softmax(Vector* vector);
void saveWeights(Matrix* matrix, char* filename);
void loadWeights(Matrix* matrix, char* filename);