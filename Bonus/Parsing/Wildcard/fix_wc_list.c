/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fix_wc_list.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noctis <noctis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 01:07:20 by noctis            #+#    #+#             */
/*   Updated: 2025/06/15 03:39:03 by noctis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/main.h"
#include "../../include/parse.h"

int	ft_add_nodes2(t_token **data, t_token **ptr, char **t)
{
	int		i;
	t_token	*new;
	t_token	*prev;
	t_token	*tmp;
	t_token	*next;

	new = NULL;
	prev = (*ptr)->prev;
	next = (*ptr)->next;
	i = 0;
	while (t[i])
	{
		ft_add_list_end(&new, ft_creat_new_list(t[i], cmd_arg_t));
		i++;
	}
	ft_set_mini_tokens(&new);
	ft_connect_list(prev, next, new, data);
	tmp = (*ptr);
	(*ptr) = next;
	free(tmp->value);
	free(tmp);
	return (1);
}

int	ft_fix_wc_list(t_token **data, t_token **ptr, char **t)
{
	t_token	*next;
	
	//return quots sould not be removed for file name from DIR .
	next = (*ptr)->next;
	if (ft_strlen_2(t) == 1)
	{
		free((*ptr)->value);
		(*ptr)->value = ft_strdup(t[0]);
		if (!(*ptr)->value)
			return (-1);
	}
	else if (ft_strlen_2(t) > 1)
	{
		if ((*ptr)->prev && 1 < (*ptr)->prev->type && (*ptr)->prev->type < 5)
		{
			(*ptr)->type = ambiguous_t;
		}
		else
		{
			if (ft_add_nodes2(data, ptr, t))
				return (0);
			else
				return (-1);
		}
	}
	return ((*ptr) = next, 0);
}
