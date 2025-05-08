/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aakritah <aakritah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/27 07:32:22 by anktiri           #+#    #+#             */
/*   Updated: 2025/05/08 01:47:45 by aakritah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/builtins.h"

int is_n_flag(char *str)
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

// add later to libft 
int ft_strcmp(const char *s1, const char *s2)
{
    while (*s1 && *s2 && *s1 == *s2)
    {
        s1++;
        s2++;
    }
    return (*(unsigned char *)s1 - *(unsigned char *)s2);
}

int ft_calcul_var_len(char *ptr)
{
    int s=0;
    
    if (*ptr == '?')
    {
        return 1;
    }
    else
    {
        while (*ptr && (ft_isalnum(*ptr) || *ptr == '_'))
        {
            s++;
            ptr++;
        }
    }
    return s;
}

void print_expanded_arg(char *arg, t_env *env_list)
{
    char *ptr = arg;
    char *var_name;
    int j;
    int in_single_quote = 0;
    int in_double_quote = 0;

    if (!arg)
        return;

    while (*ptr)
    {
        // Toggle quote states
        if (*ptr == '\'' && !in_double_quote)
        {
            in_single_quote = !in_single_quote;
            ptr++;
            continue;
        }
        if (*ptr == '"' && !in_single_quote)
        {
            in_double_quote = !in_double_quote;
            ptr++;
            continue;
        }

        // Handle variable expansion outside single quotes
        if (*ptr == '$' && *(ptr + 1) && (ft_isalnum(*(ptr + 1)) || *(ptr + 1) == '?') && !in_single_quote)
        {
            ptr++;
            j = 0;


            var_name=malloc(ft_calcul_var_len(ptr)+1);
            if(!var_name)
                return ; // change the return type to int so we can return -1; , or keep it  void, no idea


            if (*ptr == '?')
            {
                var_name[j++] = *ptr++;
            }
            else
            {
                while (*ptr && (ft_isalnum(*ptr) || *ptr == '_'))
                    var_name[j++] = *ptr++;
            }
            var_name[j] = '\0';

            if (ft_strcmp(var_name, "?") == 0)
            {
                // extern int g_exit_status;
                // ft_putnbr(g_exit_status);
            }
            else
            {
                t_env *env = env_list;
                while (env)
                {
                    if (ft_strcmp(var_name, env->name) == 0)
                    {
                        ft_putstr(env->value);
                        break;
                    }
                    env = env->next;
                }
            }
            free(var_name);
        }
        else
        {
            ft_putchar(*ptr);
            ptr++;
        }
    }
}

int ft_echo(t_token *data)
{
    int newline = 1;
    int i = 1;
    int first_arg = 1;

    if (!data || !data->c_arg || !data->c_arg[0])
    {
        ft_putstr("\n");
        return (0);
    }

    // Check for -n flags
    while (data->c_arg[i] && is_n_flag(data->c_arg[i]))
    {
        newline = 0;
        i++;
    }

    // Process each argument
    while (data->c_arg[i])
    {
        if (!first_arg)
            ft_putstr(" ");
        print_expanded_arg(data->c_arg[i], data->env_list);
        first_arg = 0;
        i++;
    }

    // Print newline if -n is not specified
    if (newline)
        ft_putstr("\n");

    return (0);
}
