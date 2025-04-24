/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shunting_yard.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noctis <noctis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 23:43:02 by noctis            #+#    #+#             */
/*   Updated: 2025/04/24 00:20:55 by noctis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/main.h"
#include "../../include/parse.h"
 
void	set_precedence(t_token **data)
{
	t_token	*ptr;

    while(ptr->next)
    {
        if(ptr->type==0)
            ptr->prec = pipe_p;
        else if(ptr->type<5)
            ptr->prec = redirect_p;
        else if(ptr->type=9)
            ptr->prec = end_p;
        else 
            ptr->prec = string_p;
    }
}

int	ft_shunting_yard(t_token **data)
{
	t_token	*a;
	t_token	*b;
	t_token	*ptr;
	t_token	*ptr2;
	t_token	*tmp;

	a = NULL;
	b = NULL;
	ptr = *data;
    
    set_precedence(data);
    while(ptr->type != end_t)
    {
        if(ptr->prec==string_p)
            ft_push(data, &a);
        else
        {
            if(!b)
                ft_push(data, &b);
            else
            {
                ptr2=ft_last_list(&b);
                if(ptr->prec >= ptr2->prec)
                    ft_push(data , &b);
                else
                {
                    // while(b && b->prc>= )
                    // {
                    // }
                }
                
            }
        }
            
    }
    
}
