/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aakritah <aakritah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 02:45:32 by aakritah          #+#    #+#             */
/*   Updated: 2025/04/03 07:36:16 by aakritah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_H
#define PARSE_H

typedef enum e_token_type
{
    pipe,
    in,
    out,
    heredoc,
    append,
    left_bracket,
    right_bracket,
    string,
    cmd,
    end
}   t_token_type;

typedef struct s_token 
{
   char *value;
   t_token_type type;
//    int index;
   struct s_token *next;
   struct s_token *prev; 
}   t_token;


// parsing :
void ft_parse(char *t);

// tokenizing
void ft_lexing(char *t, t_token *data);

t_token ft_creat_new_list(char *t, t_token_type type);
t_token ft_add_list_front(t_token **data, t_token *n);
t_token ft_add_list_end(t_token **data, t_token *n);
void ft_free_list(t_token **data);

#endif