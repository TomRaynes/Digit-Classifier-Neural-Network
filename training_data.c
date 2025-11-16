#include "nn.h"

unsigned int swap_endian(unsigned int val) {
    return val>>24 & 0xff |       // move byte 3 to byte 0
           val<<8 & 0xff0000 |    // move byte 1 to byte 2
           val>>8 & 0xff00 |      // move byte 2 to byte 1
           val<<24 & 0xff000000;  // move byte 0 to byte 3
}

unsigned int readReverseEndian(FILE* fp) {
    unsigned int val;
    fread(&val, READ_ITEM_BYTES, 1, fp);
    return swap_endian(val);
}

Images* load_images(char* filename) {
    Images* images = malloc(sizeof(Images));

    if (images == NULL) {
        printf("Error allocating memory for images\n");
        exit(EXIT_FAILURE);
    }
    FILE *fp = fopen(filename, "rb");

    if (fp == NULL) {
        printf("Failed to open file %s\n", filename);
        exit(EXIT_FAILURE);
    }
    images->magicNumber = readReverseEndian(fp);
    images->size = readReverseEndian(fp);
    images->rows = readReverseEndian(fp);
    images->cols = readReverseEndian(fp);
    images->data = malloc(images->size * sizeof(unsigned char*));

    for (int i = 0; i < images->size; i++) {
        images->data[i] = malloc(images->rows * images->cols);
        fread(images->data[i], 1, images->rows * images->cols, fp);
    }
    fclose(fp);
    return images;
}

void free_images(Images* images) {
    for (int i = 0; i < images->size; i++) {
        free(images->data[i]);
    }
    free(images->data);
    images->data = NULL;
    free(images);
    images = NULL;
}

Labels* load_labels(const char* filename) {
    Labels* labels = malloc(sizeof(Labels));

    if (labels == NULL) {
        printf("Error allocating memory for labels\n");
        exit(EXIT_FAILURE);
    }
    FILE *fp = fopen(filename, "rb");

    if (fp == NULL) {
        printf("Failed to open file %s\n", filename);
        exit(EXIT_FAILURE);
    }
    labels->magicNumber = readReverseEndian(fp);
    labels->size = readReverseEndian(fp);
    labels->data = malloc(labels->size);
    fread(labels->data, 1, labels->size, fp);

    fclose(fp);
    return labels;
}

void free_labels(Labels* labels) {
    free(labels->data);
    labels->data = NULL;
    free(labels);
    labels = NULL;
}