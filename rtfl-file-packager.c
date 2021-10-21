#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define MAX_FILESIZE 32767

#define MAGIC_NUMBER (char[]) {1, 3, 3, 7}
#define COMPILER_VERSION 0
#define RTFL_VERSION 4

int main(int argc, char const *argv[]) {
    if(argc < 4) {
        printf("Usage: %s <input file> <output .rtfc file> <container variable name>", argv[0]);
    } else {
        const char* inputFile = argv[1];
        const char* outputFile = argv[2];
        const char* varName = argv[3];

        FILE* fptr;
        char* buffer;
        long flen;

        // Open file
        fptr = fopen(inputFile, "rb");
        fseek(fptr, 0, SEEK_END);
        flen = ftell(fptr);

        // Check if file is too large
        if(flen > MAX_FILESIZE) {
            fprintf(stderr, "File is %d bytes long, which exceeds max size of %d", flen, MAX_FILESIZE);
            fclose(fptr);
            return 1;
        } else {
            // Read file to buffer
            rewind(fptr);
            buffer = (char*) malloc(flen*sizeof(char));
            fread(buffer, flen, 1, fptr);

            // Close input file
            fclose(fptr);

            // Open output file
            FILE* outptr;
            outptr = fopen(outputFile, "w");

            /* Write metadata */
            // Write magic number
            fputs(MAGIC_NUMBER, outptr);
            // Write versions
            fputc(COMPILER_VERSION, outptr);
            fputc(RTFL_VERSION, outptr);
            // Write variable name as filename
            fputc(strlen(varName), outptr);
            fputs(varName, outptr);
            // Don't record line numbers
            fputc(0, outptr);

            /* Write content */
            // Write variable definition
            fputc(0, outptr);
            fputc(strlen(varName), outptr);
            fputs(varName, outptr);
            // Write value type
            fputc(5, outptr);
            // Write length as short
            signed short len = flen*sizeof(char);
            char numBuf[2];
	        memcpy(numBuf, &len, 2);
            fputc(numBuf[1], outptr);
            fputc(numBuf[0], outptr);
            // Write value
            fputs(buffer, outptr);

            // Close write file
            fclose(outptr);
        }
    }

    return 0;
}
