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
    int start = 50;
    int res = 0;
    char* line = (char*)calloc(10,1);
    if(!line){
        printf("Calloc died");
        exit(0);
    }
    int pos = 0;
    while(fread(line + pos, 1, 1, file)) {
        if(line[pos] == '\n'){
            int neg = 0;
            if(line[0] == 'L'){
               neg = 1;
            }
            int index = 0;
            int sad = 0;
            while((pos - index - 1) != 0){
                sad += (line[pos - index - 1] - '0') * pow(10, index);
                index += 1;
            }
            if(neg){
                sad *= -1;
            }
            for(int i = 0; i < abs(sad); i++){
                if(neg){
                    start--;
                }
                else{
                    start++;
                }
                if(start == 100 || start == 0){
                    res++;
                }
                if(start >= 100){
                    start -= 100;
                }
                else if(start < 0){
                    start += 100;
                }
            }
            memset(line, 0, 10);
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
