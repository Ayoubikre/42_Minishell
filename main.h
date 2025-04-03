/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aakritah <aakritah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 13:18:26 by aakritah          #+#    #+#             */
/*   Updated: 2025/04/03 00:45:17 by aakritah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAIN_H
#define MAIN_H

#include "./42_Libft/libft.h"
#include <stdio.h>
#include <unistd.h>

# ifdef __linux__
    #include <readline/readline.h>
    #include <readline/history.h>
# else
    #include "readline/readline.h"
    #include "readline/history.h"
# endif




int main(int ac, char **av, char **env);






#endif


/*
    to conufigur readline in mac  :
    
        cd readline
        ./configure --prefix=$(pwd)
        make && make install

*/