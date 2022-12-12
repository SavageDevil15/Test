#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

// Data Size Macros
#define WORDS 100
#define BYTE 4
#define BUFFER_SIZE 41
#define INSTRUCTION_SIZE 10
#define DATA_SIZE 40

// Status Macros
#define TRUE 1
#define FALSE 0

// Global Declarations
char memory[WORDS][BYTE];
char general_purpose_register[BYTE];
char instruction_register[BYTE];
char buffer[BUFFER_SIZE];
char file_data[INSTRUCTION_SIZE];
int instruction_counter;
int flag;

FILE *input_fp = NULL;
FILE *output_fp = NULL;

int service_interrupt = 0;

// Function Declarations
void allocate(void);
void cleanup(void);
void init(void);
int read_input_line(FILE*, char*);
void check_service_interrupt(int);
void read(int);
void write(int);
void terminate(void);
void load_register(int);
void store_register(int);
void compare_register(int);
void bt(int);
void execute_user_program(void);
void start_execution(void);
void load(void);

// Function Definitions
void allocate(void)
{
    // Code
    input_fp = fopen("input.txt", "r");
    if (input_fp == NULL)
    {
        printf("Input File Not Found ... Exiting Now !!!\n");
        exit(EXIT_FAILURE);
    }

    output_fp = fopen("output.txt", "w");
    if (output_fp == NULL)
    {
        printf("Output File Not Found ... Exiting Now !!!\n");
        exit(EXIT_FAILURE);
    }
}

void cleanup(void)
{
    // Code
    if (output_fp)
    {
        fclose(output_fp);
        output_fp = NULL;
    }

    if (input_fp)
    {
        fclose(input_fp);
        input_fp = NULL;
    }
}

void init(void)
{
    // Code
    memset(memory, 0, WORDS * BYTE);
    memset(general_purpose_register, 0, BYTE);
    memset(instruction_register, 0, BYTE);
}

int read_input_line(FILE* fp, char* buffer)
{
    // Code
    int result = fscanf(fp, "%[^\n]", buffer);
    getc(fp);
    return result;
}

void check_service_interrupt(int address)
{
    // Code
    switch(service_interrupt)
    {
        case 1:
            read(address);
        break;

        case 2:
            write(address);
        break;

        case 3:
            terminate();
        break;

        default:
            return;
    }

    service_interrupt = 0;
}

void read(int address)
{
    // Code
    memset(instruction_register, 0, BYTE);

    int result = read_input_line(input_fp, buffer);
    if (result == -1)
    {
        cleanup();
        exit(EXIT_FAILURE);
    }

    if ((buffer[0] == '$') && (buffer[1] == 'E') && (buffer[2] == 'N') && (buffer[3] == 'D'))
    {
        service_interrupt = 3;
        terminate();
    }

    memcpy(memory[address], buffer, DATA_SIZE);

    execute_user_program();
}

void write(int address)
{
    // Code
    memset(instruction_register, 0, BYTE);

    fprintf(output_fp, "%s\n", memory[address]);

    execute_user_program();
}

void terminate(void)
{
    // Code
    fprintf(output_fp, "\n\n");

    load();
}

void load_register(int address)
{
    // Code
    memcpy(general_purpose_register, memory[address], BYTE);
    execute_user_program();
}

void store_register(int address)
{
    // Code
    memcpy(memory[address], general_purpose_register, BYTE);
    execute_user_program();
}

void compare_register(int address)
{
    // Code
    int result = memcmp(memory[address], general_purpose_register, BYTE);
    if (result == 0)
        flag = TRUE;
    else 
        flag = FALSE;

    execute_user_program();
}

void bt(int address)
{
    // Code
    if (flag == TRUE)
        instruction_counter = address;
        
    execute_user_program();
}

void execute_user_program(void)
{
    // Local Variables
    char ir1, ir2, ir3, ir4;
    char temp[2] = "";
    int address = 0;

    // Code
    memcpy(instruction_register, memory[instruction_counter], BYTE);
    
    instruction_counter = instruction_counter + 1;

    ir1 = instruction_register[0];

    if (ir1 != 'H')
    {
        ir2 = instruction_register[1];
        ir3 = instruction_register[2];
        ir4 = instruction_register[3];

        temp[0] = ir3;
        temp[1] = ir4;

        address = atoi(temp);
    }

    if (ir1 == 'G' && ir2 == 'D')
    {
        service_interrupt = 1;
        check_service_interrupt(address);
    }   
    else if (ir1 == 'P' && ir2 == 'D')
    {
        service_interrupt = 2;
        check_service_interrupt(address);
    }
    else if (ir1 == 'H')
    {
        service_interrupt = 3;
        check_service_interrupt(address);
    }   
    else if (ir1 == 'L' && ir2 == 'R')
        load_register(address);
    else if (ir1 == 'S' && ir2 == 'R')
        store_register(address);
    else if (ir1 == 'C' && ir2 == 'R')
        compare_register(address);
    else if (ir1 == 'B' && ir2 == 'T')
        bt(address);      
}

void start_execution(void)
{
    // Local Variables
    instruction_counter = 0;

    // Code
    execute_user_program();
}

void load(void)
{
    // Local Variables
    int i = 0;
    int offset = 0;

    // Code
    instruction_counter = 0;

    while (!feof(input_fp))
    {
        int result = read_input_line(input_fp, buffer);
        if (result == -1)
        {
            printf("\nEnd-Of-File (EOF) Error ... Exiting Now !!!\n");
            cleanup();
            exit(EXIT_FAILURE);
        }

        if ((buffer[0] == '$') && (buffer[1] == 'A') && (buffer[2] == 'M') && (buffer[3] == 'J'))
        {
            init();
            
            result = read_input_line(input_fp, buffer);
            if (result == -1)
            {
                printf("Error Occurred While Reading Program Card ... Exiting Now !!!\n");
                cleanup();
                exit(EXIT_FAILURE);
            }

            while (TRUE)
            {
                if (i > 100)
                {
                    printf("Memory Overflow Occurred ... Exiting Now !!!\n");
                    cleanup();
                    exit(EXIT_FAILURE);
                }

                char data = buffer[offset];

                if (data == '\0')
                {
                    result = read_input_line(input_fp, buffer);
                    offset = 0;
                    data = buffer[offset];
                    if (result == -1)
                    {
                        printf("\nEnd-Of-File (EOF) Error ... Exiting Now !!!\n");
                        cleanup();
                        exit(EXIT_FAILURE);
                    }
                }

                if (data == 'H')
                {
                    memory[i++][0] = buffer[offset];
                    break;
                }
                else
                {
                    memcpy(memory[i++], buffer + offset, BYTE);
                    offset = offset + BYTE;
                }
            }
        }

        else if ((buffer[0] == '$') && (buffer[1] == 'D') && (buffer[2] == 'T') && (buffer[3] == 'A'))
        {
            start_execution();
        }

        else if ((buffer[0] == '$') && (buffer[1] == 'E') && (buffer[2] == 'N') && (buffer[3] == 'D'))
        {
            continue;
        }
    }
   
}


int main(void)
{
    allocate();
    load();
    cleanup();

    return 0;
}
