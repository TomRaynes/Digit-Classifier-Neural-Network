#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#define TRAINING_IMAGES_PATH "training_data/train-images.idx3-ubyte"
#define TRAINING_LABELS_PATH "training_data/train-labels.idx1-ubyte"
#define READ_ITEM_BYTES 4

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

typedef struct {
    unsigned int size, rows, cols, magicNumber;
    unsigned char** data;
} Images;

typedef struct {
    int size, magicNumber;
    unsigned char* data;
} Labels;

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
unsigned int swap_endian(unsigned int val);
unsigned int readReverseEndian(FILE* fp);
Images* load_images(char* filename);
Labels* load_labels(const char* filename);
void free_images(Images* images);
void free_labels(Labels* labels);