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
    char* line = (char*)calloc(65536,1);
    if(!line){
        printf("Calloc died");
        exit(0);
    }
    int pos = 0;
    int num = 0;
    int numRows = 0;
    int numCols = 0;
    int curr = 0;
    int* nums[4] = {0};
    for(int i = 0; i < 4; i++) {
        nums[i] = calloc(1001, sizeof(int));
        if(!nums[i]){
            printf("Calloc died\n");
            exit(0);
        }
    }
    int yes = 0;
    while(fread(line + pos, 1, 1, file)) {
        if(line[pos] == '+') {
            for(int i = 0 ; i < numRows; i++) {
                res += nums[i][yes];
            }
            pos = -1;
            yes++;
        }
        else if(line[pos] == '*') {
            long product = 1;
            for(int i = 0; i < numRows; i++) {
                product *= nums[i][yes];
            }
            res += product;
            pos = -1;
            yes++;
        }
        else{
            if(line[pos] == ' ' && pos != 0){
                pos--;
                num = sad(line, pos);
                nums[numRows][curr] = num;
                curr++;
                pos = -1;
            }
            else if(line[pos] == '\n') {
                pos --;
                if(line[0] != ' ' && line[0] != '\n'){
                    num = sad(line, pos);
                    nums[numRows][curr] = num;
                }
                pos = -1;
                if(numCols == 0) {
                    numCols = curr;
                }
                curr = 0;
                numRows++;
            } 
            if(line[pos] == ' '){
                pos -= 1;
            }
        }
        pos++;
        
    }
    printf("%ld\n", res);
    fclose(file);
    memset(line, 0, 65536);
    free(line);
    line = NULL;
    return 0; 
}
