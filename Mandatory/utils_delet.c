/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_delet.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aakritah <aakritah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 02:49:05 by aakritah          #+#    #+#             */
/*   Updated: 2025/06/21 19:11:18 by aakritah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/main.h"
#include "./include/parse.h"

void	leaks(void)
{
	system("leaks -q minishell");
}

// ----------------------------------------------------

static void	ft_print_tab2(int s, char **arr, const char *label)
{
	int	i;

	printf("\t" CYAN "%-8s:" RESET " ", label);
	if (!arr || !arr[0])
	{
		printf(YELLOW "None\n" RESET);
		return ;
	}
	i = 0;
	while (i < s)
	{
		printf("%s", arr[i]);
		if (i + 1 < s)
			printf(YELLOW " | " RESET);
		i++;
	}
	printf("\n");
}

void	ft_print_list(t_token *data)
{
	int	index;

	index = 0;
	printf(RED "           Linked List Contents             \n" RESET);
	if (!data)
	{
		printf("\t[Empty List]\n");
		return ;
	}
	while (data)
	{
		printf(RED "Node %d:\n" RESET, index++);
		if (data->value)
			printf(" \t" CYAN "%-8s:" RESET " %s\n", "CMD", data->value);
		else
			printf(" \t" CYAN "%-8s:" RESET " " YELLOW "None" RESET "\n",
				"CMD");
		printf("\t" CYAN "%-8s:" RESET " %d\n", "Token", data->type);
		printf("\t" CYAN "%-8s:" RESET " %d\n", "expand", data->f);
		ft_print_tab2(data->arg_s, data->c_arg, "Args");
		ft_print_tab2(data->red_s, data->c_red, "Redirs");
		printf("\n");
		data = data->next;
	}
	printf(RED "               End of List                 \n" RESET);
}

// ----------------------------------------------------

void	ft_print_list1(t_token *data)
{
	if (!data)
	{
		ft_printf("nothing\n");
		return ;
	}
	ft_printf("\n----------------\n");
	while (data)
	{
		ft_printf(" %s ", data->value);
		data = data->next;
	}
	ft_printf("\n----------------\n");
}

// ----------------------------------------------------

void	ft_print_tab(char **t)
{
	int	i;

	i = 0;
	if (!t)
		return ;
	while (t[i])
	{
		ft_printf("\n\t\t > %s <\n", t[i]);
		i++;
	}
}

// ----------------------------------------------------





int	ft_check33(char *t, char *ar)
{
	if ((ft_strnstr(t, ar, ft_strlen(ar)) != NULL) && (ft_strlen(t)
			- 1 == ft_strlen(ar)))
		return (1);
	return (0);
}

int	ft_check_q_status2(char *t)
{
	int		i;
	int		f;
	char	**s1;

	s1 = ft_split4(t);
	if (!s1)
		return (-1);
	i = 0;
	while (s1[i])
	{
		f = ft_check_q_status(s1[i]);
		if (f != 0)
			return (ft_free(s1), f);
		i++;
	}
	return (ft_free(s1), 0);
}

int	filter_heredoc_line(char **line, char *del, t_extra *x)
{
	int		f1;
	int		f2;
	char	*t1;
	char	*t2;

	t1 = ft_strdup(del);
	if (!t1)
		return (-1);
	f1 = ft_check_q_status2(t1);
	t1 = ft_remove_q(t1);
	if (f1 != 0)
	{
		f2 = ft_check33(*line, t1);
		return (free(t1), f2);
	}
	else
	{
		t2 = ft_strdup(*line);
		if (!t2)
			return (-1);
		free(*line);
		*line = ft_swap_value(0, t2, x, 0);
		f2 = ft_check33(t2, t1);
		return (free(t1),free(t2), f2);
	}
}

// -----------------------------------------------------------------

int	handle_heredoc1(char *del, t_token *data, t_extra *x)
{
	char	*line;
	int		f;

	while (1)
	{
		write(STDOUT_FILENO, "> ", 2);
		line = get_next_line(STDIN_FILENO);
		if (!line)
			break ;
		f = filter_heredoc_line(&line, del, x);
		if (f == -1)
			return (-1);
		if (f == 1)
			break ;
		free(line);
	}
	return (SUCCESS);
}

int	handle_heredoc2(char *del, t_token *data, t_extra *x)
{
	char	*line;
	int		f;

	while (1)
	{
		write(STDOUT_FILENO, "> ", 2);
		line = get_next_line(STDIN_FILENO);
		if (!line)
			break ;
		f = filter_heredoc_line(&line, del, x);
		if (f == -1)
			return (-1);
		if (f == 1)
			break ;
		ft_putstr_fd(line, data->pi_doc[1]);
		free(line);
	}
	close(data->pi_doc[0]);
	close(data->pi_doc[1]);
	return (SUCCESS);
}