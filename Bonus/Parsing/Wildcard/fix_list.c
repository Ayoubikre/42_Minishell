/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fix_list.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noctis <noctis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 01:07:20 by noctis            #+#    #+#             */
/*   Updated: 2025/06/11 02:08:44 by noctis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/main.h"
#include "../../include/parse.h"


int ft_add_nodes2(t_token **data, t_token **ptr, char **t)
{
    int i;
	t_token	*new;
    t_token *prev;
    t_token *tmp;
    t_token *next;
    
	new = NULL;
    prev=(*ptr)->prev;
    next=(*ptr)->next;
	i = 0;
	while (t[i])
	{
        ft_add_list_end(&new, ft_creat_new_list(t[i], cmd_arg_t));
        i++;
	}
    // ft_print_list(new);
	ft_connect_list(prev, next, new, data);
	tmp = (*ptr);
	// (*ptr) = next;
	free(tmp->value);
	free(tmp);
	return (1);
}

int ft_fix_wc_list(t_token **data, t_token **ptr, char **t)
{
    int s;
    t_token *prev;
    t_token *next;


    prev=(*ptr)->prev;
    next=(*ptr)->next;
    s=ft_strlen_2(t);
        printf("here 1\n");
    if(s==1)
    {

        free((*ptr)->value);
        (*ptr)->value=ft_strdup(t[0]);
        if(!(*ptr)->value)
            return -1;
    }
    else if(s>1)
    {
                printf("here 2\n");

        if(prev && 1 < prev->type && prev->type < 5)
        {
                printf("here 3\n");

            (*ptr)->type=ambiguous_t;
        }
        else
        {
                printf("here 4\n");

            // if (ft_add_nodes2( ptr, data, t))
            //     return (0);
            // else 
            //     return -1;
            
            if (ft_add_nodes2( ptr, data, t)== -1)
                return -1;
        }   
    }
    (*ptr)=next;
    return 0;
}

          