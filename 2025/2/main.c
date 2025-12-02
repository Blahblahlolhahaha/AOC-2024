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
        else if(line[pos] == ',') {
            pos --;
            end = sad(line, pos);
            pos = 0;
            char* buffer = calloc(15, 1);
            if(!buffer){
                printf("Calloc died\n");
                exit(0);
            }
            
            for(long i = start; i <= end; i++) {
               int len = das(buffer, i);
               int maxLen = len / 2;
               for(int j = 1; j <= maxLen; j++) {
                   int bad = 0;
                   if(len % j != 0){
                       continue;
                   }
                   for(int k = 0; k < j; k++) {
                       for(int l = k; l < len; l += j){
                           if(buffer[k] != buffer[l]){
                               bad = 1;
                               break;
                           }
                       }
                   }
                   if(!bad){

                       res += i;
                       break;
                   }
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
