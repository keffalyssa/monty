#define _POSIX_C_SOURCE 200809L
#include "monty.h"

char *g_arg = NULL;

/**
 * free_stack - frees a stack
 * @stack: pointer to the stack
 */
void free_stack(stack_t **stack)
{
stack_t *tmp;

while (*stack)
{
tmp = (*stack)->next;
free(*stack);
*stack = tmp;
}
}

/**
 * run_opcode - finds and executes the matching opcode
 * @op: opcode string
 * @arg: argument for the opcode
 * @stack: pointer to stack
 * @ln: line number
 */
void run_opcode(char *op, char *arg, stack_t **stack, unsigned int ln)
{
int i;
instruction_t ops[] = {
{"push", op_push},
{"pall", op_pall},
		{"pint", op_pint},
		{"pop", op_pop},
{NULL, NULL}
};

g_arg = arg;
for (i = 0; ops[i].opcode; i++)
{
if (strcmp(op, ops[i].opcode) == 0)
{
ops[i].f(stack, ln);
return;
}
}
fprintf(stderr, "L%u: unknown instruction %s\n", ln, op);
free_stack(stack);
exit(EXIT_FAILURE);
}

/**
 * main - entry point
 * @argc: argument count
 * @argv: argument vector
 * Return: EXIT_SUCCESS
 */
int main(int argc, char *argv[])
{
FILE *fp;
char *line = NULL;
size_t len = 0;
unsigned int ln = 0;
char *op, *arg;
stack_t *stack = NULL;

if (argc != 2)
{
fprintf(stderr, "USAGE: monty file\n");
exit(EXIT_FAILURE);
}
fp = fopen(argv[1], "r");
if (!fp)
{
fprintf(stderr, "Error: Can't open file %s\n", argv[1]);
exit(EXIT_FAILURE);
}
while (getline(&line, &len, fp) != -1)
{
ln++;
op = strtok(line, " \t\n");
if (!op || op[0] == '#')
continue;
arg = strtok(NULL, " \t\n");
run_opcode(op, arg, &stack, ln);
}
free(line);
fclose(fp);
free_stack(&stack);
return (EXIT_SUCCESS);
}
