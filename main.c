#include "nn.h"

int main(void) {
    Matrix* layer1 = newMatrix(784, 128, NULL);
    Matrix* layer2 = newMatrix(128, 64, NULL);
    Matrix* layer3 = newMatrix(64, 10, NULL);
    Vector* input = newVector(784);

    Vector* pass1 = input->multiply(input, layer1);
    //input->free(input);
    pass1->rectify(pass1);
    Vector* pass2 = pass1->multiply(pass1, layer2);
    pass1->free(pass1);
    pass2->rectify(pass2);
    Vector* pass3 = pass2->multiply(pass2, layer3);
    pass2->free(pass2);
    pass3->softmax(pass3);




    // srand(time(NULL));
    // Vector* input = newVector(3);
    // Matrix* matrix = newMatrix(3, 2, NULL);
    // saveWeights(matrix, "weights.txt");
    //
    //
    // printf("Input layer:\n");
    // input->print(input);
    // printf("\n\nMatrix\n");
    // matrix->print(matrix);
    //
    // Vector* output = input->multiply(input, matrix); //matrix_multiply(input, matrix);
    //
    //
    // printf("\n\nOutput layer:\n");
    // output->print(output);
    //
    //
    // output->free(output);
    // matrix->free(matrix);

    return 0;
}







