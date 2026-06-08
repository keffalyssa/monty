#include "monty.h"

/**
 * op_push - pushes an element onto the stack
 * @stack: pointer to the top of the stack
 * @line_number: current line number
 */
void op_push(stack_t **stack, unsigned int line_number)
{
stack_t *new_node;
int n, i;

if (!g_arg)
{
fprintf(stderr, "L%u: usage: push integer\n", line_number);
free_stack(stack);
exit(EXIT_FAILURE);
}
i = (g_arg[0] == '-') ? 1 : 0;
if (!g_arg[i])
{
fprintf(stderr, "L%u: usage: push integer\n", line_number);
free_stack(stack);
exit(EXIT_FAILURE);
}
for (; g_arg[i]; i++)
{
if (g_arg[i] < '0' || g_arg[i] > '9')
{
fprintf(stderr, "L%u: usage: push integer\n", line_number);
free_stack(stack);
exit(EXIT_FAILURE);
}
}
n = atoi(g_arg);
new_node = malloc(sizeof(stack_t));
if (!new_node)
{
fprintf(stderr, "Error: malloc failed\n");
free_stack(stack);
exit(EXIT_FAILURE);
}
new_node->n = n;
new_node->prev = NULL;
new_node->next = *stack;
if (*stack)
(*stack)->prev = new_node;
*stack = new_node;
}

/**
 * op_pall - prints all values on the stack
 * @stack: pointer to the top of the stack
 * @line_number: current line number
 */
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
