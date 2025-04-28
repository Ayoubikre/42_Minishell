/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filter_list2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noctis <noctis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 08:39:32 by noctis            #+#    #+#             */
/*   Updated: 2025/04/28 08:56:09 by noctis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/main.h"
#include "../../include/parse.h"

int	ft_filter_list2(t_token **data)
{
	t_token	*ptr;
    int f=0;
    
	ptr = *data;
    while(ptr)
    {
        if (ptr->type == cmd_t || ptr->type == b_cmd_t)
            f=1;
        ptr=ptr->next;   
    }
	ptr = *data;
	while (ptr)
	{
        if(f==0)
            ft_cas_0();
        else
        {   
            if (ptr->type == cmd_t || ptr->type == b_cmd_t)
            {
                ptr->c_arg = malloc(sizeof(char *) * (ft_count_arg_node2(ptr) + 1));
                if (!ptr->c_arg)
				return (-1);
                if (ft_copy_arg_node2(ptr) == -1)
				return (-1);
            }
        }
		ptr = ptr->next;
	}
	ft_free_arg_node2(data);
	return (0);
}


long	ft_count_arg_node2(t_token *ptr)
{
	long	count;

	count = 1;
	while (ptr && ptr->type != pipe_t)
	{
		if (0< ptr->type  && ptr->type < 5)
			count++;
		ptr = ptr->next;
	}
	return (count);
}

int	ft_copy_arg_node2(t_token *ptr)
{
	long	i;
	t_token	*tmp;

	i = 0;
	tmp = ptr;
	while (tmp && tmp->type != pipe_t)
	{
		if (0 < tmp->type && tmp->type < 5)
		{
			ptr->c_arg[i] = ft_strdup(tmp->value);
			if (!ptr->c_arg[i])
				return (-1);
			i++;
		}
		tmp = tmp->next;
	}
	ptr->c_arg[i] = NULL;
	return (0);
}

void	ft_free_arg_node2(t_token **data)
{
	t_token	*ptr;
	t_token	*tmp;

	ptr = *data;
	while (ptr)
	{
		tmp = ptr->next;
		if (0< ptr->type  && ptr->type < 5)
		{
			if (ptr->prev)
				ptr->prev->next = tmp;
			else
				*data = tmp;
			if (tmp)
				tmp->prev = ptr->prev;
			if (ptr->value)
				free(ptr->value);
			free(ptr);
		}
		ptr = ptr->next;
	}
}
