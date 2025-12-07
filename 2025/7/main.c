#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int numSplit(char** field, int x, int y, int numRows, int numCols) {
    int res = 0;
    for(int i = y + 1; i < numRows; i++) {
        if(field[i][x] == '|') {
            return res;
        }
        if(field[i][x] != '^') {
            field[i][x] = '|';
        }
        else{
            field[i][x] = '|';
            res++;
            if(x - 1 >= 0 && field[i][x - 1] != '|' && field[i][x - 1] != '^') {
                field[i][x - 1] = '|';
                res += numSplit(field, x - 1, i, numRows, numCols);
            }
           if(x + 1 < numCols && field[i][x + 1] != '^' && field[i][x + 1] != '|') {
              field[i][x + 1] = '|';
              res += numSplit(field, x + 1, i, numRows, numCols);
           }
           return res; 
        }
    }
    return res;
}

long numSplit2(char** field, long** cache,int x, int y, int numRows, int numCols) {
    if(cache[y][x]) {
        return cache[y][x];
    }
    if(y + 1 == numRows) {
        cache[y][x] = 1;
        return 1;
    }
    if(field[y + 1][x] == '.') {
        cache[y][x] = numSplit2(field, cache, x, y + 1, numRows, numCols);
    }
    else if(field[y + 1][x] == '^') {
        long res = 0;
        if(x - 1 >= 0) {
            res += numSplit2(field, cache, x - 1, y, numRows, numCols);
        }
        if(x + 1 < numCols) {
            res += numSplit2(field, cache, x + 1, y, numRows, numCols);
        }
        cache[y][x] = res;
    }
    return cache[y][x];
}


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
    char** lines = calloc(256, sizeof(char*));
    if(!lines) {
        printf("Calloc died\n");
        exit(0);
    }
    for(int i = 0; i < 256; i++) {
        lines[i] = calloc(256, sizeof(char));
        if(!lines[i]) {
            printf("Calloc died");
            exit(0);
        }
    }
    int numRows = 0;
    int numCols = 0;
    int startCol = 0;
    while(fread(line + pos, 1, 1, file)) {
        if(line[pos] == '\n') {
            pos--;
            if(numCols == 0) {
                numCols = pos + 1;
            }
            strncpy(lines[numRows], line, numCols);
            numRows++;
            pos = -1;
        }
        if(line[pos] == 'S') {
            startCol = pos;
        } 
        pos++;
    }
    long** cache = calloc(numRows, sizeof(long*));
    if(!cache) {
        printf("Calloc died");
        exit(0);
    }
    for(int i = 0; i < numRows; i++) {
        cache[i] = calloc(numCols, sizeof(long));
        if(!cache[i]) {
            printf("Calloc died");
            exit(0);
        }
    }
    res = numSplit2(lines, cache, startCol, 0, numRows, numCols);
    fclose(file);
    for(int i = 0; i < 256; i++) {
        memset(lines[i], 0, 256);
        free(lines[i]);
        lines[i] = NULL;
    } 
    memset(lines, 0, sizeof(char*) * 256);
    free(lines);
    lines = NULL;
    memset(line, 0, 256);
    free(line);
    line = NULL;
    printf("%ld\n", res);
    return 0; 
}
