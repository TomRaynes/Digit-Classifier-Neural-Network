#include "nn.h"

int main(void) {
    Images* images = load_images(TRAINING_IMAGES_PATH);
    Labels* labels = load_labels(TRAINING_LABELS_PATH);

    for (int i=0; i < images->rows * images->cols; i++) {
        if (i % images->cols == 0) {
            printf("\n");
        }
        printf("%3d  ", images->data[0][i]);
    }
    printf("\n\nLabel: %d", labels->data[0]);

    free_images(images);
    free_labels(labels);
    return 0;
}