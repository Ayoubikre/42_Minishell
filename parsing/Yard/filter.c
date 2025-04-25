/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filter.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aakritah <aakritah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 18:47:36 by aakritah          #+#    #+#             */
/*   Updated: 2025/04/25 21:47:27 by aakritah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/main.h"
#include "../../include/parse.h"

void ft_remove_end_token(t_token **data)
{
	t_token *tmp;
	t_token *ptr;
	
	ptr=*data;
	while(ptr->next && ptr->next->type != end_t)
		ptr=ptr->next;
	tmp=ptr->next;
	ptr->next=NULL;
	tmp->prev=NULL;
	tmp->next=NULL;
	ft_free_list(&tmp);
}

void	ft_filter_list(t_token **data)
{
	t_token	*ptr;
	t_token	*tmp;
	t_token	*tmp2;

	ptr = *data;
	ft_remove_end_token(data);
	while (ptr->next)
	{
		if (ptr->type == cmd_t || ptr->type == b_cmd_t)
		{
			if (ptr->prev == NULL || (ptr->prev && ptr->prev->type == pipe_t)) // cmd first
			{
				if (ptr->next && ptr->next->type != pipe_t)
				{
					tmp = ptr;
					while(tmp->next && tmp->next->type != pipe_t)
						tmp = tmp->next;
					ptr->c_arg = ptr->next;
					ptr->next = tmp->next;
					ptr->c_arg->prev = NULL;
					tmp->next = NULL;
				}
			}
			else if (ptr->next == NULL || (ptr->next && ptr->next->type == pipe_t)) // cmd last
			{
				if (ptr->prev && ptr->prev->type != pipe_t)
				{
					
					tmp = ptr;
					while(tmp->prev && tmp->prev->type != pipe_t)
						tmp = tmp->prev;
					ptr->c_arg = tmp;
					ptr->prev->next=NULL;
					ptr->prev=tmp->prev;
					tmp->prev=NULL;
					if(ptr->prev==NULL)
						*data=ptr;
				}
			}
			// else // cmd middle
			// {
			// 	continue;
			// }
		}
		ptr = ptr->next;
	}
	return ;
}
