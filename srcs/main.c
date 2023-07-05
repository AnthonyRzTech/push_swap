#include "../includes/push_swap.h"
#include <stdlib.h>

void print_stack(Stack *stack) {
    if (stack == NULL) {
        ft_printf("La pile est NULL.\n");
        return;
    }

    Node *current = stack->head;
    ft_printf("Contenu de la pile : ");
    while (current != NULL) {
        ft_printf("%d ", current->data);
        current = current->next;
    }
    ft_printf("\n");
}

Stack *stack_init() {
    Stack *stack;

    stack = (Stack *)malloc(sizeof(Stack));
    if (stack == NULL)
        return (NULL);

    stack->head = NULL;

    return stack;
}

void    stack_a_init(int *data, Stack *stack_a, int argc)
{
    int     i;
    i = argc -2;
    while (i >= 0)
    {
        push(stack_a, data[i]);
        i--;
    }
}
void performPushes(Stack *stack_a, Stack *stack_b, int smallest1, int smallest2)
{
    int count = 0;
    Node *current = stack_a->head;

    while (current != NULL && count < 2)
    {
        Node *nextNode = current->next;
        if (current->data == smallest1 || current->data == smallest2)
        {
            pb(stack_a, stack_b);
            count++;
        }
        else
        {
            ra(stack_a);
        }
        current = nextNode;
    }
}
void findTwoSmallest(Stack *stack_a, int *smallest1, int *smallest2)
{
    *smallest1 = INT_MAX;
    *smallest2 = INT_MAX;
    Node *current = stack_a->head;

    while (current != NULL)
    {
        int data = current->data;
        if (data < *smallest1)
        {
            *smallest2 = *smallest1;
            *smallest1 = data;
        }
        else if (data < *smallest2 && data != *smallest1)
        {
            *smallest2 = data;
        }
        current = current->next;
    }
}
void pushTwoSmallest(Stack *stack_a, Stack *stack_b)
{
    int smallest1;
    int smallest2;

    findTwoSmallest(stack_a, &smallest1, &smallest2);
    performPushes(stack_a, stack_b, smallest1, smallest2);
}

bool issorted(Stack *stack_a) {

    Node *current;
    current = stack_a->head;
    while (current->next != NULL) {
        if (current->data > current->next->data) {
            return false;
        }
        current = current->next;
    }

    return (true);
}

void calculateNewDataArray(int *data, int *data2, int size)
{
    int idx2 = 0;

    while (idx2 < size)
    {
        int idx = 0;
        int newdata = 0;

        while (idx < size)
        {
            if (data[idx2] > data[idx])
                newdata++;
            idx++;
        }

        data2[idx2] = newdata;
        idx2++;
    }
}

void fillDataArray(int argc, char **argv, int *data)
{
    int idx = 1;

    while (idx < argc)
    {
        data[idx - 1] = ft_atoi(argv[idx]);
        idx++;
    }
}

int *transform(int argc, char **argv)
{
    int *data;
    int *data2;

    data = (int *)malloc(sizeof(int) * (argc - 1));
    if (!data)
        return NULL;

    data2 = (int *)malloc(sizeof(int) * (argc - 1));
    if (!data2)
    {
        free(data);
        return NULL;
    }

    fillDataArray(argc, argv, data);
    calculateNewDataArray(data, data2, argc - 1);

    free(data);

    return data2;
}



void sort_3_elements(Stack *stack_a) {

    int first;
    int second;
    int third;

    first = stack_a->head->data;
    second = stack_a->head->next->data;
    third = stack_a->head->next->next->data;
    if (first > second && second < third && first < third) {
        sa(stack_a);
    }
    else if (first > second && third < second && first > third) {
        sa(stack_a);
        rra(stack_a);
    }
    else if (second < first && first > third && second < third) {
        ra(stack_a);
    }
    else if (second > third && third > first && second > first) {
        sa(stack_a);
        ra(stack_a);
    }
    else if (third < first && first < second && second > third) {
        rra(stack_a);
    }
}

void sort_5_elements(Stack *stack_a, Stack *stack_b) {

    pushTwoSmallest(stack_a, stack_b);
    sort_3_elements(stack_a);
    if (stack_b->head->data < stack_b->head->next->data)
        sb(stack_b);
    pa(stack_a, stack_b);
    pa(stack_a, stack_b);
}

int         ft_lstsize2(Stack *stack)
{
    int         count;
    Node *current;

    current = stack->head;
    count = 0;
    while (current != NULL) 
    {
        count++;
        current = current->next;
    }
    
    return count;
}

Node *get_next_min(Stack *stack)
{
	Node *current = stack->head;
	Node *min = NULL;

	while (current != NULL)
	{
		if (current->index == -1 && (min == NULL || current->data < min->data))
			min = current;
		current = current->next;
	}
	if (min != NULL)
		min->index = 0;
	return min;
}
void index_stack(Stack *stack)
{
	Node *current;
	int index = 0;

	current = stack->head;
	while (current != NULL)
	{
		current->index = -1;
		current = current->next;
	}
	current = stack->head;
	while (current != NULL)
	{
		Node *min = get_next_min(stack);
		if (min != NULL)
			min->index = index++;
		current = current->next;
	}
}

static int get_max_bits(Stack *stack)
{
    Node *head = stack->head;
    int max = 0;
    int max_bits = 0;

    while (head)
    {
        if (head->data > max)
            max = head->data;
        head = head->next;
    }

    while ((max >> max_bits) != 0)
        max_bits++;

    return max_bits;
}
void radix_sort(Stack *stack_a, Stack *stack_b)
{
	Node	*head_a;
	int		i;
	int		j;
	int		size;
	int		max_bits;

	i = 0;
	head_a = stack_a->head;
	size = ft_lstsize2(stack_a);
	max_bits = get_max_bits(stack_a);
	while (i < max_bits)
	{
		j = 0;
		while (j++ < size)
		{
			head_a = stack_a->head;
			if (((head_a->data >> i) & 1) == 1)
				ra(stack_a);
			else
				pb(stack_a, stack_b);
		}
		while (ft_lstsize2(stack_b) != 0)
			pa(stack_a, stack_b);
		i++;
	}
}
int main(int argc, char **argv) {
    Stack *stack_a;
    Stack *stack_b;

    stack_a = stack_init();
    stack_b = stack_init();

    if (test(argc, argv) == 0)
    {
        ft_printf("ERROR\n");
        exit(EXIT_FAILURE);
    }
    stack_a_init(transform(argc, argv), stack_a, argc);
    if (issorted(stack_a) == true) {
        exit(EXIT_SUCCESS);
    }
    if (argc == 4)
        sort_3_elements(stack_a);
    if (argc == 6)
        sort_5_elements(stack_a, stack_b);
    else if (argc > 6) {
        index_stack(stack_a);
        radix_sort(stack_a, stack_b);
    }
     return (0);
}
