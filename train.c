#include "nn.h"

int main(void) {
    Images* images = load_images(TRAINING_IMAGES_PATH);
    Labels* labels = load_labels(TRAINING_LABELS_PATH);
    Layers* layers = model_layers();

    for (int i=0; i < images->rows * images->cols; i++) {
        if (i % images->cols == 0) {
            printf("\n");
        }
        printf("%3d  ", images->data[7][i]);
    }
    printf("\n\nLabel: %d\n", labels->data[7]);

    free_images(images);
    free_labels(labels);
    return 0;
}

double loss(Vector** outputs, int* targets, int batchSize) {
    double sumLoss = 0;

    for (int i=0; i < batchSize; i++) {
        sumLoss += -log(outputs[i]->data[targets[i]]);
    }
    return sumLoss / batchSize;
}

void back_propagate() {

}