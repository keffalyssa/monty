#include "monty.h"

void op_push(stack_t **stack, unsigned int line_number)
{
stack_t *node;
int n;
char *endptr;

if (!push_arg)
{
fprintf(stderr, "L%u: usage: push integer\n", line_number);
exit(EXIT_FAILURE);
}
n = (int)strtol(push_arg, &endptr, 10);
if (*endptr != '\0')
{
fprintf(stderr, "L%u: usage: push integer\n", line_number);
exit(EXIT_FAILURE);
}
node = malloc(sizeof(stack_t));
if (!node)
{
fprintf(stderr, "Error: malloc failed\n");
exit(EXIT_FAILURE);
}
node->n = n;
node->prev = NULL;
node->next = *stack;
if (*stack)
(*stack)->prev = node;
*stack = node;
}

void op_pall(stack_t **stack, unsigned int line_number)
{
stack_t *current;

(void)line_number;
current = *stack;
while (current)
{
printf("%d\n", current->n);
current = current->next;
}
}
