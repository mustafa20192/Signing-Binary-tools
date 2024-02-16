#include <stdio.h>
#include <stdlib.h>

void splitFile(const char *inputFileName, const char *outputFileName1, const char *outputFileName2, unsigned int offset) {
    FILE *inputFile = fopen(inputFileName, "rb");
    if (inputFile == NULL) {
        printf("Error opening input file.\n");
        return;
    }

    FILE *outputFile1 = fopen(outputFileName1, "wb");
    if (outputFile1 == NULL) {
        printf("Error creating output file 1.\n");
        fclose(inputFile);
        return;
    }

    FILE *outputFile2 = fopen(outputFileName2, "wb");
    if (outputFile2 == NULL) {
        printf("Error creating output file 2.\n");
        fclose(inputFile);
        fclose(outputFile1);
        return;
    }

    fseek(inputFile, 0, SEEK_END);
    long fileSize = ftell(inputFile);

    if (offset > fileSize) {
        printf("Offset is beyond file size.\n");
        fclose(inputFile);
        fclose(outputFile1);
        fclose(outputFile2);
        return;
    }

    rewind(inputFile);

    int ch;
    long bytesRead = 0;

    while (bytesRead < offset && (ch = fgetc(inputFile)) != EOF) {
        fputc(ch, outputFile1);
        bytesRead++;
    }

    while ((ch = fgetc(inputFile)) != EOF) {
        fputc(ch, outputFile2);
    }

    fclose(inputFile);
    fclose(outputFile1);
    fclose(outputFile2);

    printf("File split successfully.\n");
}

int main() {
    const char *inputFileName = "organal_binary_.bin"; // Replace with your input file name
    const char *outputFileName1 = "output1.bin"; // Replace with desired output file name 1
    const char *outputFileName2 = "output2.bin"; // Replace with desired output file name 2
    unsigned int offset = 0x512; // Replace with your desired offset

    splitFile(inputFileName, outputFileName1, outputFileName2, offset);

    return 0;
}
