/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_single.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aakritah <aakritah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/25 17:13:15 by anktiri           #+#    #+#             */
/*   Updated: 2025/07/01 20:46:32 by aakritah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/builtins.h"

int	exec_builtin(t_token *data, t_extra *x)
{
	if (!data->value || !data->value[0])
		return (ERROR);
	if (ft_strcmp(data->value, "echo") == 0)
		return (ft_echo(data));
	else if (ft_strcmp(data->value, "cd") == 0)
		return (ft_cd(data->c_arg, x));
	if (ft_strcmp(data->value, "pwd") == 0)
		return (ft_pwd(x->env_list));
	else if (ft_strcmp(data->value, "export") == 0)
		return (ft_export(data, x));
	else if (ft_strcmp(data->value, "unset") == 0)
		return (ft_unset(data, &x));
	else if (ft_strcmp(data->value, "env") == 0)
		return (ft_env(data, x));
	else if (ft_strcmp(data->value, "exit") == 0)
		return (ft_exit(data, x));
	return (ERROR);
}

int	exec_single(t_token *data, t_extra *x)
{
	if (setup_heredoc(data, x) != 0)
	{
		close(data->pi_doc[0]);
		close (x->stdin_backup);
		close (x->stdout_backup);
		return (ERROR);
	}
	if (setup_redirections(data, x) != 0)
	{
		restore_std_fds(x);
		return ((x->exit_status = 1));
	}
	x->exit_status = exec_builtin(data, x);
	if (restore_std_fds(x) != 0)
		return ((x->exit_status = ERROR));
	return (x->exit_status);
}
