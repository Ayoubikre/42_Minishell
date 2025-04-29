/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noctis <noctis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 05:09:22 by noctis            #+#    #+#             */
/*   Updated: 2025/04/29 01:26:43 by noctis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/main.h"
#include "../../include/parse.h"


t_token	*ft_pop2(t_token **data)
{
	t_token	*last;

	if (!data || !*data)
		return NULL ;
	last = ft_last_list(*data);
	if (last->prev)
		last->prev->next = NULL;
	else
		*data = NULL;
	last->next = NULL;
	last->prev = NULL;
    
    return last;
}

void ft_tree(t_token **data)
{
    // t_token *head;
    // t_token *left;
    // t_token *right;
    // t_token *ptr;
    // t_token *tmp;
    
    // tmp=ft_last_list(*data);
    // head=ft_pop2(data);
    // while(*data)
    // {
    //     if(!head)
    //         return ;
   
        
    // }
    
    
    return;
}