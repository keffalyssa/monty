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

/**
 * op_pint - prints the value at the top of the stack
 * @stack: pointer to the top of the stack
 * @line_number: current line number
 */
void op_pint(stack_t **stack, unsigned int line_number)
{
if (!*stack)
{
fprintf(stderr, "L%u: can't pint, stack empty\n", line_number);
free_stack(stack);
exit(EXIT_FAILURE);
}
printf("%d\n", (*stack)->n);
}

/**
 * op_pop - removes the top element of the stack
 * @stack: pointer to the top of the stack
 * @line_number: current line number
 */
void op_pop(stack_t **stack, unsigned int line_number)
{
stack_t *tmp;

if (!*stack)
{
fprintf(stderr, "L%u: can't pop an empty stack\n", line_number);
free_stack(stack);
exit(EXIT_FAILURE);
}
tmp = *stack;
*stack = (*stack)->next;
if (*stack)
(*stack)->prev = NULL;
free(tmp);
}

/**
 * op_swap - swaps the top two elements of the stack
 * @stack: pointer to the top of the stack
 * @line_number: current line number
 */
void op_swap(stack_t **stack, unsigned int line_number)
{
int tmp;

if (!*stack || !(*stack)->next)
{
fprintf(stderr, "L%u: can't swap, stack too short\n", line_number);
free_stack(stack);
exit(EXIT_FAILURE);
}
tmp = (*stack)->n;
(*stack)->n = (*stack)->next->n;
(*stack)->next->n = tmp;
}

/**
 * op_add - adds the top two elements of the stack
 * @stack: pointer to the top of the stack
 * @line_number: current line number
 */
void op_add(stack_t **stack, unsigned int line_number)
{
stack_t *tmp;

if (!*stack || !(*stack)->next)
{
fprintf(stderr, "L%u: can't add, stack too short\n", line_number);
free_stack(stack);
exit(EXIT_FAILURE);
}
(*stack)->next->n += (*stack)->n;
tmp = *stack;
*stack = (*stack)->next;
(*stack)->prev = NULL;
free(tmp);
}

/**
 * op_nop - doesn't do anything
 * @stack: pointer to the top of the stack
 * @line_number: current line number
 */
void op_nop(stack_t **stack, unsigned int line_number)
{
(void)stack;
(void)line_number;
}

/**
 * op_div - divides the second top element by the top element
 * @stack: pointer to the top of the stack
 * @line_number: current line number
 */
void op_div(stack_t **stack, unsigned int line_number)
{
stack_t *tmp;

if (!*stack || !(*stack)->next)
{
fprintf(stderr, "L%u: can't div, stack too short\n", line_number);
free_stack(stack);
exit(EXIT_FAILURE);
}
if ((*stack)->n == 0)
{
fprintf(stderr, "L%u: division by zero\n", line_number);
free_stack(stack);
exit(EXIT_FAILURE);
}
(*stack)->next->n /= (*stack)->n;
tmp = *stack;
*stack = (*stack)->next;
(*stack)->prev = NULL;
free(tmp);
}

/**
 * op_sub - subtracts the top element from the second top element
 * @stack: pointer to the top of the stack
 * @line_number: current line number
 */
void op_sub(stack_t **stack, unsigned int line_number)
{
stack_t *tmp;

if (!*stack || !(*stack)->next)
{
fprintf(stderr, "L%u: can't sub, stack too short\n", line_number);
free_stack(stack);
exit(EXIT_FAILURE);
}
(*stack)->next->n -= (*stack)->n;
tmp = *stack;
*stack = (*stack)->next;
(*stack)->prev = NULL;
free(tmp);
}

/**
 * op_mul - multiplies the second top element with the top element
 * @stack: pointer to the top of the stack
 * @line_number: current line number
 */
void op_mul(stack_t **stack, unsigned int line_number)
{
stack_t *tmp;

if (!*stack || !(*stack)->next)
{
fprintf(stderr, "L%u: can't mul, stack too short\n", line_number);
free_stack(stack);
exit(EXIT_FAILURE);
}
(*stack)->next->n *= (*stack)->n;
tmp = *stack;
*stack = (*stack)->next;
(*stack)->prev = NULL;
free(tmp);
}
