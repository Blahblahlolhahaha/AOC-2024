#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

long sad(char* buffer, int len){
    long res = 0;
    for(int i = len; i >= 0; i--){
        res += (buffer[i] - '0') * pow(10, len - i);
    }
    return res;
}

int das(char* buffer, long target){
    int i = 0;
    int len = log10(target) + 1;
    while(target > 0){
        buffer[len - i - 1] = '0' + (target % 10);
        target /= 10;
        i++;
    }
    return len;
}

int main(int argc, char** argv){
    FILE* file = fopen(argv[1], "r");
    if(!file){
        printf("Cannot open file\n");
        exit(0);
    }
    long res = 0;
    char* line = (char*)calloc(15,1);
    if(!line){
        printf("Calloc died");
        exit(0);
    }
    int pos = 0;
    long start = 0;
    long end = 0;
    int second = 0;
    while(fread(line + pos, 1, 1, file)) {
        if(line[pos] == '-'){
            pos--;
            start = sad(line, pos);
            pos = -1;
        }
        else if(line[pos] == ','){
            pos --;
            end = sad(line, pos);
            pos = 0;
            char* buffer = calloc(15, 1);
            if(!buffer){
                printf("Calloc died\n");
                exit(0);
            }
            
            for(long i = start; i <= end; i++){
               int len = das(buffer, i);
               if(len % 2 != 0){
                   continue;
               }
               if(!strncmp(buffer, buffer + (len/2), len / 2)){
                   res += i;
               }
            }
            memset(buffer, 0, 15);
            free(buffer);
            pos = -1;
        }
        pos++;
        
    }
    fclose(file);
    memset(line, 0, 15);
    free(line);
    line = NULL;
    printf("%ld\n", res);
    return 0; 
}
