/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moves.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noctis <noctis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 23:52:48 by noctis            #+#    #+#             */
/*   Updated: 2025/04/28 07:57:27 by noctis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/main.h"
#include "../../include/parse.h"


int is_right_associative(t_token_type type)
{
	return (type >= append_t && type <= infile_t);
}

void ft_move_list_shunting_yard(t_token **data, t_token **a, t_token **b)
{
    t_token *tmp;
    if (!data || !*data)
        return;
    tmp = *data;
    if (tmp->type >= string_t && tmp->type <= cmd_arg_t)
        ft_push(data, a);
    else
    {
        while (*b && (ft_last_list(*b)->prec > tmp->prec ||
                      (ft_last_list(*b)->prec == tmp->prec &&
                       !is_right_associative(ft_last_list(*b)->type))))
            ft_pop(b, a);
        ft_push(data, b);
    }
}


// void	ft_move_list_shunting_yard(t_token **data, t_token **a, t_token **b)
// {
// 	if ((*data)->prec == string_p)
// 	{
// 		ft_push(data, a);
// 	}
// 	else
// 	{
// 		if (!*b)
// 			ft_push(data, b);
// 		else
// 		{
// 			if ((*data)->prec > ft_last_list(*b)->prec)
// 				ft_push(data, b);
// 			else
// 			{
// 				while (*b && (*data)->prec <= ft_last_list(*b)->prec)
// 					ft_pop(b, a);
// 				ft_push(data, b);
// 			}
// 		}
// 	}
// 	return ;
// }

void	ft_push(t_token **data, t_token **a)
{
	t_token	*ptr;
	t_token	*last;

	if (!data || !*data)
		return ;
	ptr = *data;
	(*data) = (*data)->next;
	if (*data)
		(*data)->prev = NULL;
	ptr->next = NULL;
	ptr->prev = NULL;
	if (!*a)
		*a = ptr;
	else
	{
		last = ft_last_list(*a);
		last->next = ptr;
		ptr->prev = last;
	}
}

void	ft_pop(t_token **b, t_token **a)
{
	t_token	*ptr;
	t_token	*last;

	if (!b || !*b || !a)
		return ;
	last = ft_last_list(*b);
	ptr = NULL;
	if (last->prev)
		last->prev->next = NULL;
	else
		*b = NULL;
	last->next = NULL;
	last->prev = NULL;
	if (!*a)
		*a = last;
	else
	{
		ptr = ft_last_list(*a);
		ptr->next = last;
		last->prev = ptr;
	}
}
