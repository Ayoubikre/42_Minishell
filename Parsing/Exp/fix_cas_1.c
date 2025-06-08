/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fix_cas_1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aakritah <aakritah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/11 23:54:04 by noctis            #+#    #+#             */
/*   Updated: 2025/06/08 18:13:04 by aakritah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/main.h"
#include "../../include/parse.h"

int	ft_initialize_list2(char *str, t_token **data);

void	ft_set_mini_tokens(t_token **new)
{
	t_token	*ptr;

	ptr = *new;
	while (ptr)
	{
		ptr->type = cmd_arg_t;
		ptr->f = 1;
		ptr = ptr->next;
	}
	return ;
}

void	ft_connect_list(t_token *prev, t_token *next, t_token *new,
		t_token **data)
{
	t_token	*last;

	if (prev)
	{
		prev->next = new;
		new->prev = prev;
	}
	else
		*data = new;
	last = ft_last_list(new);
	if (next)
	{
		last->next = next;
		next->prev = last;
	}
}

int	ft_add_nodes(char *t, t_token *ptr, t_token **data)
{
	t_token	*new;
	t_token	*tmp;
	t_token	*next;
	t_token	*prev;

	new = NULL;
	next = ptr->next;
	prev = ptr->prev;
	if (ft_initialize_list(t, &new) < 0)
		return (-1);
	if (ft_remove_end_token(&new) == -1)
		return (ft_free_list(&new), -1);
	ft_set_mini_tokens(&new);
	ft_connect_list(prev, next, new, data);
	tmp = ptr;
	ptr = next;
	free(tmp->value);
	free(tmp);
	return (0);
}

// int	ft_handle_cas_1(t_token **data, t_token *ptr)
// {
// 	int		s;
// 	char	**t;

// 	t = ft_split4(ptr->value);
// 	if (!t)
// 		return (-1);
// 	s = ft_strlen_2(t);
// 	if (ptr->prev && (0 < ptr->prev->type && ptr->prev->type < 5))
// 	{
// 		if (s > 1)
// 			ptr->type = ambiguous_t;
// 	}
// 	else if (!ptr->prev || (ptr->prev && !(0 < ptr->prev->type
// 				&& ptr->prev->type < 5)))
// 	{
// 		if (ft_add_nodes(ptr->value, ptr, data) < 0)
// 			return (-1);
// 	}
// 	ft_free(t);
// 	return (1);
// }





int ft_check_if_it_ambiguous(char *str)
{
	int i;
	int s;
	int f;
	char **t;

	t=ft_split4(str);
	if(!t)
		return -1;
	i=0;
	while(t[i])
	{
		f=ft_check_dollar_2(t[i]);
		s=ft_count_split2(t[i], ' ');
		if(f==0 && s >1)
			return (ft_free(t), -2);
		i++;
	}
	return (ft_free(t), 0);

}





int	ft_handle_cas_1(t_token **data, t_token *ptr)
{
	int 	i;
	int 	f;

	if (ptr->prev && (1 < ptr->prev->type && ptr->prev->type < 5))
	{
		f=ft_check_if_it_ambiguous(ptr->value);
		if (f == -1)
			return -1;
		else if (f == -2)
			ptr->type = ambiguous_t;
	}
	else if (!ptr->prev || (ptr->prev && !(0 < ptr->prev->type
				&& ptr->prev->type < 5)))
	{
		if (ft_add_nodes(ptr->value, ptr, data) < 0)
			return (-1);
	}	
	return (1);
}


char	*strip_outer_quotes(const char *s)
{
	int		i;
	int		j;
	int		len;
	char	*res;

	i = 0;
	j = 0;
	len = 0;
	while (s[len])
		len++;
	if (len >= 2 && ((s[0] == '\'' && s[len - 1] == '\'') || (s[0] == '"' && s[len - 1] == '"')))
	{
		res = malloc(len - 1);
		if (!res)
			return (NULL);
		i = 1;
		while (i < len - 1)
			res[j++] = s[i++];
	}
	else
	{
		res = malloc(len + 1);
		if (!res)
			return (NULL);
		while (s[i])
			res[j++] = s[i++];
	}
	res[j] = '\0';
	return (res);
}


int	ft_remove_qouat(char **t)
{
	int	i = 0;
	char *tmp;

	while (t[i])
	{
		tmp = strip_outer_quotes(t[i]);
		if(!tmp)
			return -1;
		free(t[i]);
		t[i] = tmp;
		i++;
	}
	return 0;
}



int	ft_initialize_list2(char *str, t_token **data)
{
	int		i;
	int		f;
	int		j;
	char	**t1;
	char	**t2;

	i = 0;
	t1 = ft_split4(str);
	if (!t1)
		return (-1);
	while (t1[i])
	{
		t2 = ft_split2(t1[i], ' ');
		if (!t2)
			return (ft_free(t1), -1);
		// if(ft_remove_qouat(t2) == -1)
		// 	return (ft_free(t2),ft_free(t1), -1);
		j = 0;
		while (t2[j])
		{
			// if(j==0)
			// {
			// 	if()
			// }
			ft_add_list_end(data, ft_creat_new_list(t2[j], string_t));
			j++;
		}
	(ft_free(t2), i++);
	}
	ft_free(t1);
	ft_add_list_end(data, ft_creat_new_list(NULL, end_t));
	return (0);
}
