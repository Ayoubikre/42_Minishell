/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aakritah <aakritah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/25 18:18:51 by anktiri           #+#    #+#             */
/*   Updated: 2025/06/21 13:07:31 by aakritah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/builtins.h"

char	*ft_strjoin3(char *s1, char *s2, char *s3)
{
	char	*t;
	int		s, i, j, k;  // Fixed syntax error

	if (!s1 || !s2 || !s3)
		return (NULL);
	s = ft_strlen(s1) + ft_strlen(s2) + ft_strlen(s3);
	t = malloc(s + 1);
	if (!t)
		return (NULL);
	i = 0;
	while (s1[i] != '\0')
	{
		t[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2[j] != '\0')
		t[i++] = s2[j++];
	k = 0;
	while (s3[k] != '\0')
		t[i++] = s3[k++];
	t[i] = '\0';
	return (t);
}

int	ft_dup2(int f1, int f2)
{
	if (dup2(f1, f2) == -1)
		return (ERROR);
	return (SUCCESS);
}

int	cleanup_execution_vars(t_extra *x)
{
	if (x->stdin_backup != -1)
	{
		close(x->stdin_backup);
		x->stdin_backup = -1;
	}
	if (x->stdout_backup != -1)
	{
		close(x->stdout_backup);
		x->stdout_backup = -1;
	}
	if (x->pipe_count > 0)
		free_pipe(x);
	return (x->exit_status);
}

void	print_error(char *file, char *error_msg)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd(file, STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	ft_putstr_fd(error_msg, STDERR_FILENO);
	ft_putstr_fd("\n", STDERR_FILENO);
}
