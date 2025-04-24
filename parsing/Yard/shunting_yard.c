/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shunting_yard.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noctis <noctis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 23:43:02 by noctis            #+#    #+#             */
/*   Updated: 2025/04/24 09:51:57 by noctis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/main.h"
#include "../../include/parse.h"

void	set_precedence(t_token **data)
{
	t_token	*ptr;

    if(!data)
        return;
        
    ptr=(*data);
	while (ptr)
	{
		if (ptr->type == 0)
			ptr->prec = pipe_p;
		else if (ptr->type < 5)
			ptr->prec = redirect_p;
		else if (ptr->type == 9)
			ptr->prec = end_p;
		else
			ptr->prec = string_p;
        ptr=ptr->next;
	}
}

void	ft_push(t_token **data, t_token **a)
{
	t_token	*ptr;
	t_token	*tmp;

	if ((!data && !*data))
		return ;
	tmp = *data;
	(*data) = (*data)->next;
	ptr = ft_last_list(a);
    if(!ptr)
	    ptr->next = tmp;
    else
        ptr=tmp;
	return ;
}

t_token	*ft_pop(t_token **b)
{
	t_token	*ptr;
	t_token	*tmp;

	if (!b && !*b)
		return (NULL);
	tmp = ft_last_list(b);
	ptr = tmp->prev;
	if (!ptr)
		ptr->next = NULL;
	return (tmp);
}

void	ft_shunting_yard(t_token **data)
{
	t_token	*a;
	t_token	*b;
	t_token	*ptr_d;
	t_token	*tmp;

	a = NULL;
	b = NULL;
	set_precedence(data);
	// while (ptr_d->type != end_t)
	// {
    //     ptr_d = *data;
	// 	if (ptr_d->prec == string_p)
	// 		ft_push(data, &a);
    //     else
	// 		ft_push(data, &b);

	// 	else
	// 	{
	// 		if (!b)
	// 			ft_push(data, &b);
	// 		else
	// 		{
	// 			if (ptr_d->prec >= ft_last_list(&b)->prec)
	// 				ft_push(data, &b);
	// 			else
	// 			{
	// 				while (b && ptr_d->prec <= ft_last_list(&b)->prc)
	// 				{
	// 					tmp = ft_pop(&b);
	// 					ft_push(&tmp, &a);
	// 				}
	// 			}
	// 		}
	// 	}
	// }
    // ft_push(data, &a);
    data=&a;
    return;
}
