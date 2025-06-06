/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aakritah <aakritah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 09:31:09 by aakritah          #+#    #+#             */
/*   Updated: 2025/06/06 13:23:49 by aakritah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/main.h"
#include "../../include/parse.h"

int	ft_expanding_list(t_token **data, t_extra *x)
{
	char *t;
	t_token	*ptr;

	ptr = *data;
	while (ptr->type != end_t)
	{
		if (ft_check(ptr->value))
		// {
			ptr->f = 1;
			t = ft_strdup(ptr->value);
			if (!t)
				return (-1);
			free(ptr->value);
			ptr->value = ft_swap_value(0, t, x);
			if (!ptr->value)
				return (-1);
			free(t);
		// }
		ptr = ptr->next;
	}
	return (0);
}

// int	ft_expanding_list(t_token **data, t_extra *x)
// {
// 	int i;
// 	int f;
// 	char **t;
// 	t_token	*ptr;

// 	ptr = *data;
// 	while (ptr->type != end_t)
// 	{
// 		f=0;
// 		if(ptr->prev && (ptr->prev->type == 1 || ptr->prev->type == 3 || ptr->prev->type == 4))
// 			f=1;
// 		if (ft_check(ptr->value))
// 			ptr->f = 1;
		
// 		t=ft_split4(ptr->value);
// 		if (!t)
// 			return (-1);
// 		i=0;
// 		ft_print_tab(t);
// 		while(t[i])
// 		{
// 			char *tmp=ft_strdup(t[i]);
// 			if(!tmp)
// 				return (-1);
// 			t[i] = ft_swap_value(0, t[i], x);
// 			if (!ptr->value)
// 				return (-1);
// 			free(tmp);
// 			i++;
// 		}
// 		ft_print_tab(t);
// 		// free(ptr->value);
// 		// ptr->value = ft_swap_value(0, t, x);
// 		// if (!ptr->value)
// 		// 	return (-1);
// 		free(t);
// 		ptr = ptr->next;
// 	}
// 	return (0);
// }

int	ft_expand(t_token **data, t_extra *x)
{
	t_token	*ptr;

	if (ft_expanding_list(data, x) < 0)
		return (-1);

		
	// if (ft_fix_list(data) < 0)
	// 	return (-1);

		
	// ptr = *data;
	// while (ptr && ptr->next && ptr->type != end_t)
	// {
	// 	if (ptr->type != ambiguous_t && ptr->type != skip_t)
	// 		ptr->type = undefiend;
	// 	ptr = ptr->next;
	// }

	
	// ft_set_tokens_after_expanding(data);

	
	// ptr = *data;
	// while (ptr && ptr->next && ptr->type != end_t)
	// {
	// 	if (ptr->type == ambiguous_t)
	// 	{
	// 		free(ptr->value);
	// 		ptr->value = NULL;
	// 	}
	// 	ptr = ptr->next;
	// }
	
	return (0);
}
