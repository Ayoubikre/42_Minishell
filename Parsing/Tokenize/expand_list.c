/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_list.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aakritah <aakritah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 09:31:09 by aakritah          #+#    #+#             */
/*   Updated: 2025/05/08 10:46:34 by aakritah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/main.h"
#include "../../include/parse.h"





int	ft_strcmp(const char *s1, const char *s2)
{
	while (*s1 && *s2 && *s1 == *s2)
	{
		s1++;
		s2++;
	}
	return (*(unsigned char *)s1 - *(unsigned char *)s2);
}

//--------------------------- new func :

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

void	ft_print_expanded_variable(t_env *env_list, char *var_name , char *t, int *i)
{
	t_env	*env;

	env = env_list;
	while (env)
	{
		if (ft_strcmp(var_name, env->name) == 0)
		{
			int j=0;
            while(env->value[j])
            {
                t[*i]=env->value[j];
                j++;
                (*i)++;
            }
			break ;
		}
		env = env->next;
	}
}

int	ft_toggle_quote(char **ptr, int *in_single_quote, int *in_double_quote)
{
	if (**ptr == '\'' && !(*in_double_quote))
	{
		*in_single_quote = !(*in_single_quote);
		(*ptr)++;
		return (1);
	}
	if (**ptr == '"' && !(*in_single_quote))
	{
		*in_double_quote = !(*in_double_quote);
		(*ptr)++;
		return (1);
	}
	return (0);
}

char	*ft_copy_expand_var(char **ptr, int *f)
{
	char	*var_name;
	int		j;

	j = 0;
	var_name = malloc(ft_calcul_var_len(*ptr) + 1);
	if (!var_name)
		return (NULL); // return NULL to signal allocation failure
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

//--------------------------- end .

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

char *ft_expand(char *ptr, t_env *env_list)
{
	char *var_name; // fix static , a.k.a segfault ....
	char t[1000000];
    int i=0;
    int j=0;
	int(in_single_quote), (in_double_quote), f = 0;
	in_single_quote = 0;
	in_double_quote = 0;
	if (!ptr)
		return NULL;
	while (*ptr)
	{
		if (ft_toggle_quote(&ptr, &in_single_quote, &in_double_quote))
			continue ;
		if (*ptr == '$' && ft_check_ptr_value(*(ptr + 1), 0)
			&& !in_single_quote)
		{
			var_name = (ptr++, ft_copy_expand_var(&ptr, &f));
			if (!var_name)
				return NULL; // we may need to return -1 or not ...
			// if (f == 1)
			// 	ft_handle_special_char(var_name);
            ft_print_expanded_variable(env_list, var_name, t, &i);
			// free(var_name);
		}
		else
		{
          t[i]=*ptr;
          i++;
          ptr++;   
        }
	}
    t[i]='\0';
            // printf("\n>%s<\n",t);
    if(i==0)
        return NULL;
    return (ft_strdup(t));
}

int ft_check(char *t)
{
    int i=0;
    while(t[i])
    {
        if(t[i]=='$')
            return 1;
        i++;
    }
    return 0;
}

int ft_expand_list(t_token **data, t_env *env_list)
{
	t_token	*ptr;
    char *t;
    
    ptr=*data;
    while(ptr->type!=end_t)
    {
        if(ft_check(ptr->value))
        {
            t=ft_strdup(ptr->value);
            free(ptr->value);
            ptr->value=ft_expand(t,env_list);
            free(t);
        }
        ptr=ptr->next;
    }
    return 0;
}