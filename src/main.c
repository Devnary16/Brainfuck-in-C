#include <stdlib.h>
#include <stdio.h>

void brainfuck(char* program, int length) {
    
    unsigned char  memory[32768];
    unsigned short memndx = 0;
    
    unsigned char  loopndx[32768];
    unsigned short loopcnt = 0;
    
    for (int i = 0; i < 32768; memory[i]=0,loopndx[i]=0,i++);
    
    int i;
    for (; i < length; i++) {
        
        if (program[i] == 43) { // +
            
            memory[memndx]++;
        }
        else if (program[i] == 45) { // -
            
            memory[memndx]--;
        }
        else if (program[i] == 62)  { // >
            
            if (memndx == 32767) {
                
                printf("Maximum cell index number exceeded. Aborting.\n");
                return;
            }
            
            memndx++;
        }
        else if (program[i] == 60) { // <
            
            if (memndx == 0) {
                
                printf("Cell index can't be negative. Aborting.\n");
                return;
            }
            
            memndx--;
        }
        else if (program[i] == 91) { // [
            
            if (loopcnt == 32767) {
                
                printf("Maximum loop count exceeded. Aborting.\n");
                return;
            }
            
            if (memory[memndx] > 0) {
                loopndx[loopcnt] = i;
                loopcnt++;
            }
            else
                for (; i < length && program[i] != 93; i++);
        }
        else if (program[i] == 93) { // ]
            
            if (loopcnt == 0) {
                
                printf("Unexpected char at position %d. Skiped.\n", i);
                continue;
            }
            
            if (memory[memndx] > 0)
                i = loopndx[loopcnt - 1];
            else
                loopcnt--;
        }
        else if (program[i] == 46) { // .
            
            printf("%c", memory[memndx]);
        }
        else if (program[i] == 44) { // ,
            
            printf("input:\n");
            scanf("%s", &memory[memndx]);
        }
    }
}

int main(int argc, char** argv) {
    
    if (argc < 2) {
        
        printf("./Brainfuck [program.bf]");
        return 0;
    }
    
    FILE* input_file = fopen(argv[1], "r"); // Open file in read mode 
    
    fseek(input_file, 0, SEEK_END);
    size_t size = ftell(input_file); // get file size
    fseek(input_file, 0, SEEK_SET);
    
    char program[size];
    fread(program, 1, size, input_file); // Put brainfuck program in memory
    
    brainfuck(program, size); // Run brainfuck program
    
    fclose(input_file);
    return 0;
}