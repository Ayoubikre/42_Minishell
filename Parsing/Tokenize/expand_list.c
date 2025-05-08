/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_list.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noctis <noctis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 09:31:09 by aakritah          #+#    #+#             */
/*   Updated: 2025/05/08 13:36:56 by noctis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/main.h"
#include "../../include/parse.h"

int	ft_check(char *t)
{
	int	i;

	i = 0;
	while (t[i])
	{
		if (t[i] == '$')
			return (1);
		i++;
	}
	return (0);
}

int	ft_strcmp(const char *s1, const char *s2)
{
	while (*s1 && *s2 && *s1 == *s2)
	{
		s1++;
		s2++;
	}
	return (*(unsigned char *)s1 - *(unsigned char *)s2);
}

int	ft_check_ptr_value(char c, int f)
{
	if (f == 0)
	{
		if (c && (c == '?' || c == '@' || c == '_' || ft_isalnum(c)))
			return (1);
	}
	if (f == 1)
	{
		if (c && (c == '?' || c == '@' || ft_isdigit(c)))
			return (1);
	}
	else if (f == 2)
	{
		if (c && (ft_isalnum(c) || c == '_'))
			return (1);
	}
	return (0);
}

int	ft_calcul_var_len(char *ptr)
{
	int	s;

	s = 0;
	if (ft_check_ptr_value(*ptr, 1))
	{
		return (1);
	}
	else
	{
		while (ft_check_ptr_value(*ptr, 2))
		{
			s++;
			ptr++;
		}
	}
	return (s);
}

int	ft_calculs_exp_len(t_env *env_list, char *var_name)
{
	t_env	*env;

	env = env_list;
	while (env)
	{
		if (ft_strcmp(var_name, env->name) == 0)
		{
			return (ft_strlen(env->value));
		}
		env = env->next;
	}
	return (0);
}

void	ft_get_expand_value(t_env *env_list, char *var_name, char *t, int *i)
{
	t_env	*env;
	int		j;

	env = env_list;
	while (env)
	{
		if (ft_strcmp(var_name, env->name) == 0)
		{
			j = 0;
			while (env->value[j])
			{
				t[*i] = env->value[j];
				j++;
				(*i)++;
			}
			break ;
		}
		env = env->next;
	}
}

int	ft_toggle_quote(char **ptr, int *s_q, int *d_q)
{
	if (**ptr == '\'' && !(*d_q))
	{
		*s_q = !(*s_q);
		(*ptr)++;
		return (1);
	}
	if (**ptr == '"' && !(*s_q))
	{
		*d_q = !(*d_q);
		(*ptr)++;
		return (1);
	}
	return (0);
}

char	*ft_get_expand_name(char **ptr, int *f)
{
	char	*var_name;
	int		j;

	j = 0;
	var_name = malloc(ft_calcul_var_len(*ptr) + 1);
	if (!var_name)
		return (NULL);
	if (ft_check_ptr_value(**ptr, 1))
	{
		var_name[j++] = *(*ptr)++;
		*f = 1;
	}
	else
	{
		while (ft_check_ptr_value(**ptr, 2))
			var_name[j++] = *(*ptr)++;
	}
	var_name[j] = '\0';
	return (var_name);
}

void	ft_handle_special_char(char *var_name)
{
	// if (ft_strcmp(var_name, "?") == 0)
	// {
	// 	// extern int g_exit_status;
	// 	// ft_putnbr(g_exit_status);
	// }
	return ;
}


int	ft_is_n_flag(char *str)
{
	if (!str || str[0] != '-')
		return (0);
	str++;
	if (!*str)
		return (0);
	while (*str)
	{
		if (*str != 'n')
			return (0);
		str++;
	}
	return (1);
}

int	ft_calcul_total_len(int s, char *ptr, t_env *env_list)
{
	char	*var_name;

	int(s_q), (d_q), f = 0;
	s_q = 0;
	d_q = 0;
	while (*ptr)
	{
		if (ft_toggle_quote(&ptr, &s_q, &d_q))
			continue ;
		if (*ptr == '$' && ft_check_ptr_value(*(ptr + 1), 0) && !s_q)
		{
			var_name = (ptr++, ft_get_expand_name(&ptr, &f));
			if (!var_name)
				return (0);
			// if(f==1)
			// ft_handle_special_char();
			// else
				s += ft_calculs_exp_len(env_list, var_name);
			free(var_name);
		}
		else
			(s++, ptr++);
	}
	return (s);
}

char	*ft_expand(int i, char *ptr, t_env *env_list)
{
	char	*var_name;
	char	*t;

	int (s_q), (d_q), f = 0;
	s_q = 0;
	d_q = 0;
	t = malloc(ft_calcul_total_len(0, ptr, env_list) + 1);
	if (!t)
		return (NULL);
	while (*ptr)
	{
		if (ft_toggle_quote(&ptr, &s_q, &d_q))
			continue ;
		if (*ptr == '$' && ft_check_ptr_value(*(ptr + 1), 0) && !s_q)
		{
			var_name = (ptr++, ft_get_expand_name(&ptr, &f));
			if (!var_name)
				return (NULL);
			// if (f == 1)
			// 	ft_handle_special_char(var_name);
			// else
			ft_get_expand_value(env_list, var_name, t, &i);
			free(var_name);
		}
		else
			t[i++] = *(ptr++);
	}
	t[i] = '\0';
	if (i == 0)
		return (free(t), NULL);
	return (t);
}

int	ft_expand_list(t_token **data, t_env *env_list)
{
	t_token	*ptr;
	char	*t;

	ptr = *data;
	while (ptr->type != end_t)
	{
		if (ft_check(ptr->value))
		{
			t = ft_strdup(ptr->value);
			if (!t)
				return (-1);
			free(ptr->value);
			ptr->value = ft_expand(0, t, env_list);
			free(t);
		}
		ptr = ptr->next;
	}
	return (0);
}
