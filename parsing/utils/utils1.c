/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aakritah <aakritah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 02:59:30 by aakritah          #+#    #+#             */
/*   Updated: 2025/04/12 18:27:16 by aakritah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/main.h"
#include "../../include/parse.h"

void	ft_free(char **t)
{
	int	i;

	i = 0;
	while (t[i])
	{
		free(t[i]);
		i++;
	}
	free(t);
}

void	ft_put_error(char *t, int fd)
{
	int	s;

	if (t && fd >= 0)
	{
		s = ft_strlen(t);
		write(fd, t, s);
	}
}

char	**ft_set_charset(void)
{
	char	**charset;

	charset = malloc(sizeof(char *) * 8);
	if (!charset)
		return (NULL);
	charset[0] = ">>";
	charset[1] = "<<";
	charset[2] = ">";
	charset[3] = "<";
	charset[4] = "|";
	charset[5] = "\"";
	charset[6] = "\'";
	charset[7] = NULL;
	return (charset);
}
