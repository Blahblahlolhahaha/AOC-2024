#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>

typedef struct Block Block;
struct Block{
    long id;
    long start;
    long end;
};

int main() {
    FILE* file = fopen("input", "r");
    if(file){
        fseek(file, 0L, SEEK_END);
        long size = ftell(file);
        fseek(file, 0L, SEEK_SET);
        char* input = (char*) malloc(size);
        long max_disk_size = size * 9 * sizeof(struct Block);
        struct Block* disk = (Block*) malloc(max_disk_size);
        if(input && disk){
            memset(input, 0, size);
            memset(disk, 0, max_disk_size);
            int read = fread(input,1, size,file);
            if(read){
                long disk_size = 0;
                for(long i = 0; i < size; i++){
                    if(input[i] < 48){
                        continue;
                    }
                    int file_size = input[i] - 48;
                    long id = (i+1) % 2 == 0? -1 : i/2;
                    struct Block block = {id, disk_size, disk_size + file_size};
                    disk[i] = block;
                    disk_size += file_size;
                }
                long checksum = 0;
                for(int i = 0; i< disk_size; i++){
                    struct Block block = disk[i];
                    if(block.id != -1){
                        for(long j = block.start; j< block.end; j++){
                            checksum += block.id * j;
                        }
                        continue;
                    }
                    for(int j = disk_size - 1; j > i;j--){
                        struct Block test = disk[j];
                        long file_size = block.end - block.start;
                        long test_size = test.end - test.start;
                        if(test.id != -1 && test_size <= file_size){
                            for(long y = 0; y< test_size; y++){
                                checksum += test.id * (block.start + y);
                            }
                            block.start = block.start + test_size;
                            disk[j].id = -1;
                            if(block.start == block.end){
                                break;
                            }
                            
                        }
                    }
                }
                printf("%lu\n",checksum);
            }
            memset(input,0,size);
            free(input);
            input = NULL;
        
            memset(disk,0,max_disk_size);
            free(disk);
            disk = NULL;

        }
        
    }
}
