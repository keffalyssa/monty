#define _POSIX_C_SOURCE 200809L
#include "monty.h"

char *push_arg = NULL;

int main(int argc, char *argv[])
{
FILE *file;
char *line = NULL;
size_t len = 0;
long read;
unsigned int line_number = 0;
stack_t *stack = NULL;
char *opcode;
instruction_t instructions[] = {
{"push", op_push},
{"pall", op_pall},
{NULL, NULL}
};
int i, found;

if (argc != 2)
{
fprintf(stderr, "USAGE: monty file\n");
exit(EXIT_FAILURE);
}
file = fopen(argv[1], "r");
if (!file)
{
fprintf(stderr, "Error: Can't open file %s\n", argv[1]);
exit(EXIT_FAILURE);
}
while ((read = getline(&line, &len, file)) != -1)
{
line_number++;
if (line[read - 1] == '\n')
line[read - 1] = '\0';
opcode = strtok(line, " \t\r");
if (!opcode || opcode[0] == '#')
continue;
push_arg = strtok(NULL, " \t\r");
found = 0;
for (i = 0; instructions[i].opcode; i++)
{
if (strcmp(opcode, instructions[i].opcode) == 0)
{
instructions[i].f(&stack, line_number);
found = 1;
break;
}
}
if (!found)
{
fprintf(stderr, "L%u: unknown instruction %s\n", line_number, opcode);
free(line);
fclose(file);
while (stack)
{
stack_t *tmp = stack->next;
free(stack);
stack = tmp;
}
exit(EXIT_FAILURE);
}
}
free(line);
fclose(file);
while (stack)
{
stack_t *tmp = stack->next;
free(stack);
stack = tmp;
}
return (EXIT_SUCCESS);
}
