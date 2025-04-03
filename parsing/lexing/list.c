/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aakritah <aakritah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 07:10:20 by aakritah          #+#    #+#             */
/*   Updated: 2025/04/03 07:33:51 by aakritah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/main.h"
#include "../../include/parse.h"

t_token ft_creat_new_list(char *t, t_token_type type)
{
    t_token *n;
    
    n=malloc(sizeof(t_token));
    n->value=t;
    n->type=type;
    n->next=NULL;
    n->prev=NULL;
}

t_token ft_add_list_front(t_token **data, t_token *n)
{
    if(!data || !n)
        (perror("Error list.c : 30"), ft_free_list(data));
    (*data)->prev=n;
    n->next=(*data);
    (*data)=n;
    
}

t_token ft_add_list_end(t_token **data, t_token *n)
{
    if(!data | !n)
        (perror("Error list.c : 40"), ft_free_list(data));
    t_token *tmp;
    
    tmp=(*data);
    while(tmp->next)
        tmp=tmp->next;
    tmp->next=n;
    n->prev=tmp;
}

void ft_free_list(t_token **data)
{
    if(!data)
        return;
    t_token *tmp;
    
    while(*data)
    {
        tmp=(*data);
        (*data)=(*data)->next;
        free(tmp);
    }
}