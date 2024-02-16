#include <stdio.h>
#include <stdlib.h>

int main() {
    FILE *sourceFile, *destinationFile, *outputFile;
    char sourceFileName[] = "first_binary.bin";
    char destinationFileName[] = "second_binary.bin";
    char outputFileName[] = "output.bin";
    long offset = 0x00; // Offset where you want to insert the content

    // Open source file for reading in binary mode
    sourceFile = fopen(sourceFileName, "rb");
    if (sourceFile == NULL) {
        perror("Error opening source file");
        return EXIT_FAILURE;
    }

    // Open destination file for reading in binary mode
    destinationFile = fopen(destinationFileName, "rb");
    if (destinationFile == NULL) {
        perror("Error opening destination file");
        fclose(sourceFile);
        return EXIT_FAILURE;
    }

    // Create output file for writing in binary mode
    outputFile = fopen(outputFileName, "wb");
    if (outputFile == NULL) {
        perror("Error creating output file");
        fclose(sourceFile);
        fclose(destinationFile);
        return EXIT_FAILURE;
    }

    // Copy contents of destination file up to the offset into the output file
    int ch;
    fseek(destinationFile, 0, SEEK_SET);
    while (offset > 0 && (ch = fgetc(destinationFile)) != EOF) {
        fputc(ch, outputFile);
        offset--;
    }

    // Copy contents of source file into the output file
    fseek(sourceFile, 0, SEEK_SET);
    while ((ch = fgetc(sourceFile)) != EOF) {
        fputc(ch, outputFile);
    }

    // Copy the remaining content of the destination file into the output file
    fseek(destinationFile, 0, SEEK_CUR); // Move the destination file pointer to the current position
    while ((ch = fgetc(destinationFile)) != EOF) {
        fputc(ch, outputFile);
    }

    // Close all files
    fclose(sourceFile);
    fclose(destinationFile);
    fclose(outputFile);

    printf("Merged content created successfully in %s\n", outputFileName);

    return EXIT_SUCCESS;
}
