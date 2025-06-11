/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noctis <noctis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 21:26:33 by noctis            #+#    #+#             */
/*   Updated: 2025/06/11 02:01:19 by noctis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../../include/main.h"
#include "../../include/parse.h"

int ft_check_wc_string(char *t)
{
    int i=0;
    if(!t)
        return 0;
    while(t[i] && t[i]!='/')
    {
        if(t[i] == '*')
            return 1;
        i++;
    }
    return 0;
}

int ft_expanding_wc(t_token **data, t_extra *x)
{
    char **t;
    t_token *ptr;
    t_token *next;
    
    ptr=*data;
    while(ptr && ptr->type != end_t)
    {
        if( ft_check_wc_string(ptr->value) && (!ptr->prev || (ptr->prev && ptr->prev->type!=heredoc_t)))
        {
                t= ft_get_wc_list(ptr->value);
                if(!t)   
                    return -1;
                // ft_print_tab(t);
                printf("befor\n");
                if (ft_fix_wc_list(data, &ptr, t) < 0)
                	return (ft_free(t), -1); 
                printf("after\n");
                ft_free(t);
                // ptr=ptr->next;             
        }
        else
            ptr=ptr->next; 
    }
    // if (ft_re_tokenizing(data) < 0)
	// 	return (-1);
    return 0;
}

int ft_wildcard(t_token **data, t_extra *x)
{
	if (ft_expanding_wc(data, x) < 0)
		return (-1);


    // if (ft_re_tokenizing(data) < 0)
    // 	return (-1);    
    return 0;
}



