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
    int res = 0;
    char* line = (char*)calloc(256,1);
    if(!line){
        printf("Calloc died");
        exit(0);
    }
    int pos = 0;
    while(fread(line + pos, 1, 1, file)) {
        if(line[pos] == '\n'){
            int ind = 0;
            for(int i = 0; i < pos - 1; i++){
               if(line[i] > line[ind]){
                    ind = i;
                }
            }
            res += (line[ind] - '0') * 10; 
            ind = ind + 1;
            for(int i = ind + 1; i < pos; i++){ 
                if(line[i] > line[ind]){
                    ind = i;
                }
            }
            res += (line[ind] - '0');
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
    printf("%d\n", res);
    return 0; 
}
