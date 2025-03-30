#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "bytearray/bytearray.h"

void printUsageInfo(char* progName){
    fprintf(stderr, "\e[;94mUSAGE\e[0m: %s {input file} {output file}\n", progName);
}

void stripAndReplaceInvalidChars(char* str){
    const char* invalidChars = ".,;:@+-*/[](){} ";
    size_t invalidLen = strlen(invalidChars);
    size_t inStrLen = strlen(str);
    if (isdigit(str[0])){
        str[0] = '_';
    }
    for (size_t i = 0; i < inStrLen; ++i){
        for (size_t j = 0; j < invalidLen; ++j){
            if (str[i] == invalidChars[j]){
                str[i] = '_';
            }
        }  
    }
}

void fileToArray(char* in_filename, char* out_filename){
    ByteArray* file = file_to_byte_array(in_filename);
    FILE* out = fopen(out_filename, "w"); 
    stripAndReplaceInvalidChars(in_filename);
    fprintf(out, "const char %s[%d] = {", in_filename, file->bufsize);
    for (size_t i = 0; i < file->bufsize; ++i){
        fprintf(out, "0x%X", file->buf[i]);
        if (i != file->bufsize - 1){
            fprintf(out, ", ");
        }
    }
    fprintf(out, "};\n");
    fclose(out);
    cleanup_bytearray(&file);
}

int main(int argc, char** argv){
    if (argc < 2){
        printUsageInfo(argv[0]);
        fprintf(stderr, "\e[0;91mERROR\e[0m: NOT ENOUGH ARGS, GOT %d\n", argc);
        return -1;
    }
    else if (argc > 3){
        printUsageInfo(argv[0]);
        fprintf(stderr, "\e[0;91mERROR\e[0m: TOO MANY ARGS, GOT %d\n", argc);
        return -1;
    }
    fileToArray(argv[1], argv[2]);
    return 0;
}
