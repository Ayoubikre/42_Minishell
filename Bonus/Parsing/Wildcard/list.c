/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aakritah <aakritah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 21:41:25 by aakritah          #+#    #+#             */
/*   Updated: 2025/06/13 21:54:28 by aakritah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/main.h"
#include "../../include/parse.h"

void	ft_free_list2(t_wc **data)
{
	t_wc	*ptr;

	if (!data)
		return ;
	while (*data)
	{
		ptr = (*data);
		(*data) = (*data)->next;
		if (ptr->value)
			free(ptr->value);
		free(ptr);
	}
}

t_wc	*ft_creat_new_list2(char *str, int i)
{
	t_wc	*n;

	n = malloc(sizeof(t_wc));
	if (!n)
		return (NULL);
	if (!str)
		n->value = NULL;
	else
		n->value = ft_strdup(str);
	n->f = i;
	n->next = NULL;
	n->prev = NULL;
	return (n);
}

char	*ft_prosses_wc_string(char *t1)
{
	int		i;
	char	*rs;
	char	**s1;

	if (!t1)
		return (NULL);
	s1 = ft_split4(t1);
	if (!s1)
		return (NULL);
	i = 0;
	while (s1[i])
	{
		s1[i] = ft_remove_q(s1[i]);
		if (!s1[i])
			return (ft_free(s1), NULL);
		i++;
	}
	rs = ft_strjoin4(s1);
	if (!rs)
		return (ft_free(s1), NULL);
	return (rs);
}

void	ft_add_list_end2(t_wc **data, t_wc *n)
{
	t_wc	*ptr;

	if (!data)
		return ;
	if (!*data)
	{
		*data = n;
		return ;
	}
	ptr = (*data);
	while (ptr->next)
		ptr = ptr->next;
	ptr->next = n;
	n->prev = ptr;
	return ;
}

int	ft_initialize_list2(char *str, t_wc **data)
{
	int		i;
	char	**t1;
	char	*rs;

	t1 = ft_split5(str);
	if (!t1)
		return (-1);
	i = 0;
	while (t1[i])
	{
		if (ft_strcmp(t1[i], "*") == 0)
		{
			ft_add_list_end2(data, ft_creat_new_list2(t1[i], 1));
		}
		else
		{
			rs = ft_prosses_wc_string(t1[i]);
			if (!rs)
				return (ft_free(t1), ft_free_list2(data), -1);
			ft_add_list_end2(data, ft_creat_new_list2(rs, 0));
			free(rs);
		}
		i++;
	}
	return (ft_free(t1), 0);
}
