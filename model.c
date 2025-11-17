#include "nn.h"

Vector* model(Vector* input, Layers* layers) {
    Vector* layer1_result = matrix_multiply(input, layers->layer1);
    rectify(layer1_result);

    Vector* layer2_result = matrix_multiply(layer1_result, layers->layer2);
    rectify(layer2_result);

    Vector* output = matrix_multiply(layer2_result, layers->layer3);
    softmax(output);

    freeVector(layer1_result);
    freeVector(layer2_result);

    return output;
}

Layers* model_layers() {
    Layers* layers = malloc(sizeof(Layers));

    if (layers == NULL) {
        printf("Error allocating memory for layers\n");
        exit(EXIT_FAILURE);
    }
    layers->layer1 = newMatrix(784, 128, NULL);
    layers->layer2 = newMatrix(128, 64, NULL);
    layers->layer3 = newMatrix(64, 10, NULL);
    return layers;
}