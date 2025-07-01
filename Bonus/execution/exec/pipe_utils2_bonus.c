/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_utils2_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aakritah <aakritah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 16:46:34 by anktiri           #+#    #+#             */
/*   Updated: 2025/07/01 14:45:44 by aakritah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/builtins_bonus.h"

void	close_pipe_in_parent(t_extra *x)
{
	if (x->cmd_index > 0 && x->pipefd[x->cmd_index - 1][0] != -1)
	{
		close(x->pipefd[x->cmd_index - 1][0]);
		x->pipefd[x->cmd_index - 1][0] = -1;
	}
	if (x->cmd_index < x->cmd_count - 1 && x->pipefd[x->cmd_index][1] != -1)
	{
		close(x->pipefd[x->cmd_index][1]);
		x->pipefd[x->cmd_index][1] = -1;
	}
	x->cmd_index++;
	close(x->stdin_backup);
	x->stdin_backup = -1;
	close(x->stdout_backup);
	x->stdout_backup = -1;
}
