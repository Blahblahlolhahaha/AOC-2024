#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

int main(int argc, char** argv){
    FILE* file = fopen(argv[1], "r");
    if(!file){
        printf("Cannot open file\n");
        exit(0);
    }
    long res = 0;
    char* line = (char*)calloc(256,1);
    if(!line){
        printf("Calloc died");
        exit(0);
    }
    int pos = 0;
    while(fread(line + pos, 1, 1, file)) {
        if(line[pos] == '\n'){
            int len = pos;
            int ind= 0;
            for(int x = 11; x >= 0; x--){
                for(int y = ind; y < pos - (x); y++){
                    if(line[y] > line[ind]){
                        ind = y;
                    }
                }
                res += (line[ind] - '0') * powl(10,x);
                ind ++;
            } 
            memset(line, 0, 256);
            pos = 0;

        }
        else{
            pos += 1;
        }
    }
    fclose(file);
    free(line);
    line = NULL;
    printf("%ld\n", res);
    return 0; 
}
