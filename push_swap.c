/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebennix <ebennix@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 22:13:37 by ebennix           #+#    #+#             */
/*   Updated: 2023/03/22 04:39:08 by ebennix          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	push_to_b(t_list **stack_a, t_list **stack_b, int chunk, int last_pos)
{
	int	mid;

	mid = chunk / 2;
	while (*stack_a && chunk > 0)
	{
		if ((*stack_a)->position <= last_pos)
		{
			if ((*stack_a)->position <= last_pos - mid)
				push(stack_a, stack_b, 'b');
			else
			{
				push(stack_a, stack_b, 'b');
				rotate(stack_a, stack_b, 'b');
			}
			chunk--;
		}
		else
			rotate(stack_a, stack_b, 'a');
	}
}

void	sort_chunks(int size, t_list **stack_a, t_list **stack_b, int divide)
{
	int	chunk;
	int	reset;
	int	index;
	int	lstlen;

	chunk = size / divide;
	reset = chunk;
	while (ft_lstsize(*stack_a))
	{
		push_to_b(stack_a, stack_b, chunk, reset);
		reset += chunk;
	}
	lstlen = ft_lstsize(*stack_b) - 1;
	while (*stack_b)
	{
		init_index(*stack_b);
		index = get_index(*stack_b, lstlen);
		if ((*stack_b)->position == lstlen)
		{
			push(stack_a, stack_b, 'a');
			lstlen--;
		}
		else if (index <= lstlen / 2)
			rotate(stack_a, stack_b, 'b');
		else if (index >= lstlen / 2)
			reverse_rotate(stack_a, stack_b, 'b');
	}
}

int	push_swap(int ac, char **av)
{
	t_list	*stack_a;
	t_list	*stack_b;
	int		size;

	check_valid(av);
	stack_a = get_node(ac, av);
	stack_b = NULL;
	size = ft_lstsize(stack_a);
	init_index(stack_a);
	init_position(stack_a);
	if (size <= 5)
		sort_under_five(size, &stack_a, &stack_b);
	else if (size <= 200)
		sort_chunks(size, &stack_a, &stack_b, 5);
	else
		sort_chunks(size, &stack_a, &stack_b, 10);
	// printf("\n");
	// while(stack_a)
	// {
	//     printf("|| stack : a = %d      with the position %d            with the index %d\n",stack_a -> content,stack_a-> position,stack_a -> index);
	//     stack_a = stack_a -> next;
	// }
	// printf("\n");
	// while(stack_b)
	// {
	//     printf("|| stack : b = %d      with the position %d            with the index %d\n",stack_b -> content,stack_b -> position,stack_b -> index);
	//     stack_b = stack_b -> next;
	// }
	return (0);
}

int	main(int ac, char **av)
{
	int	err;

	if (ac == 1)
		exit(1);
	err = push_swap(ac, av);
	return (err);
}

// leaks still