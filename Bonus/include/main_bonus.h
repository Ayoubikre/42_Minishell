/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aakritah <aakritah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 13:18:26 by aakritah          #+#    #+#             */
/*   Updated: 2025/06/16 21:33:36 by aakritah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAIN_BONUS_H
# define MAIN_BONUS_H

// delet later
# include "../libs/42_Libft/libft.h"
# include "./parse_bonus.h"
# include "./builtins_bonus.h"
# include <dirent.h>
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

# ifdef __linux__
#  include <linux/limits.h>
#  include <readline/history.h>
#  include <readline/readline.h>
# else
#  include "../../readline/history.h"
#  include "../../readline/readline.h"
#  include <limits.h>
# endif

# define RED "\033[1;31m"
# define CYAN "\033[1;36m"
# define YELLOW "\033[33m"
# define MAGENTA "\033[1;35m"
# define GREEN "\033[1;32m"
# define BLUE "\033[1;34m"
# define WHITE "\033[1;37m"
# define GRAY "\033[0;90m"

# define RESET "\033[0m"

extern volatile sig_atomic_t g_signal_received;

// Function declarations
void signal_init_interactive(void);
void signal_init_child(void);
void handle_signal_in_main(void);

//------------------------------ Main :
int		main(int ac, char **av, char **env);

//------------------------------ Delet Later :
void	leaks(void);
void	ft_print_list(t_token *data);
void	ft_print_list1(t_token *data);
void	ft_print_tab(char **t);
void	ft_print_list3(t_wc *data);

#endif

/*
	to conufigur readline in mac  :

		cd readline
		./configure --prefix=$(pwd)
		make && make install

*/