#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

int main() {
    FILE *file, *newFile;
    uint8_t *buffer;
    size_t BUFFER_SIZE = 1024; // Initial buffer size
    size_t file_size;

    // Open the binary file in read and binary mode
    file = fopen("binary_file.bin", "rb");
    if (file == NULL) {
        perror("Error opening file");
        return -1;
    }

    // Determine the file size
    fseek(file, 0, SEEK_END);
    file_size = ftell(file);
    rewind(file);

    // Allocate memory for the buffer based on file size
    buffer = (uint8_t *)malloc(file_size);
    if (buffer == NULL) {
        perror("Memory allocation failed");
        fclose(file);
        return -1;
    }

    // Read the contents of the file into the buffer
    size_t bytesRead = fread(buffer, sizeof(uint8_t), file_size, file);
    if (bytesRead != file_size) {
        perror("Error reading file");
        fclose(file);
        free(buffer);
        return -1;
    }

    fclose(file);

    // Define the range to remove (from offset 0x10 to 0x20)
    size_t removeStart = 0x0;
    size_t removeEnd = 0x256;

    // Calculate the size of the data to keep after removal
    size_t dataSize = file_size - (removeEnd - removeStart);

    // Shift the data in the buffer to remove the specified range
    for (size_t i = removeEnd; i < file_size; i++) {
        buffer[i - (removeEnd - removeStart)] = buffer[i];
    }

    // Create a new binary file to write the modified buffer
    newFile = fopen("output.bin", "wb");
    if (newFile == NULL) {
        perror("Error creating new file");
        free(buffer);
        return -1;
    }

    // Write the modified buffer to the new binary file
    size_t bytesWritten = fwrite(buffer, sizeof(uint8_t), dataSize, newFile);
    if (bytesWritten != dataSize) {
        perror("Error writing to file");
        fclose(newFile);
        free(buffer);
        return -1;
    }

    fclose(newFile);
    free(buffer);
    printf("New file created with modified data.\n");

    return 0;
}
