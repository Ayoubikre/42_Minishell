/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   a.c                                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aakritah <aakritah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 13:29:56 by aakritah          #+#    #+#             */
/*   Updated: 2025/06/13 18:36:18 by aakritah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <dirent.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>
#define GREEN "\033[1;32m"
#define RED "\033[1;31m"
#define RESET "\033[0m"
// int	ft_compare(t_cr cr, int i, int j);
// int	ft_valid(char *str, char *filename);
// // -----------------------------------------
// typedef struct s_cr
// {
// 	char	*t;
// 	char	*filename;
// 	int		i_c;
// 	char	q_c;
// }			t_cr;

// typedef struct s_wc
// {
// 	char *str;
// 	char *file;
// 	int i_c;
// 	char q_c;
// }	t_wc;

// // typedef struct s_match
// // {
// // 	const char	*t;
// // 	const char	*filename;
// // 	int			cr.i_c;
// // 	char		q_c;
// // }				t_match;

// // -----------------------------------------
// typedef struct s_cr
// {
// 	char	*t;
// 	char	*filename;
// 	int		i_c;
// 	char	q_c;
// }			t_cr;

// int	ft_compare(t_cr cr, int i, int j)
// {
// 	if (cr.t[i] == '\0')
// 	{
// 		return (cr.filename[j] == '\0' && !cr.i_c);
// 	}
// 	if (cr.filename[j] == '\0' && cr.t[i] != '*' && !cr.i_c)
// 	{
// 		return (0);
// 	}
// 	if ((cr.t[i] == '\"' || cr.t[i] == '\'') && !cr.i_c)
// 	{
// 		i++;
// 		cr.i_c = 1;
// 		cr.q_c = cr.t[i - 1];
// 		return (ft_compare(cr, i, j));
// 	}
// 	if (cr.t[i] == cr.q_c && cr.i_c)
// 	{
// 		i++;
// 		cr.i_c = 0;
// 		cr.q_c = 0;
// 		return (ft_compare(cr, i, j));
// 	}
// 	if (cr.t[i] == '*' && !cr.i_c)
// 	{
// 		while (1)
// 		{
// 			if (ft_compare(cr, i + 1, j))
// 			{
// 				return (1);
// 			}
// 			if (!cr.filename[j])
// 			{
// 				break ;
// 			}
// 			j++;
// 		}
// 		return (0);
// 	}
// 	if (cr.t[i] == cr.filename[j])
// 	{
// 		i++;
// 		j++;
// 		return (ft_compare(cr, i, j));
// 	}
// 	return (0);
// }

// int	ft_valid(char *str, char *filename)
// {
// 	t_cr	cr;

// 	if (!str || !filename)
// 		return (0);
// 	cr.t = str;
// 	cr.filename = filename;
// 	cr.i_c = 0;
// 	return (ft_compare(cr, 0, 0));
// }

// // -----------------------------------------

// // int	ft_valid(str, filenam)
// // {
// // 	t_cr	cr;

// // 	if (!str || !filename)
// // 		return (0);
// // 	cr.str = str;
// // 	cr.filename = filename;
// // 	i = 0;
// // 	j = 0;
// // 	cr.i_c = 0;
// // 	return (ft_compare(cr));
// // }

// // int	ft_compare(t_cr cr)
// // {
// // }

// // -----------------------------------------

// int	ft_count_cr_match(char *str, char **t)
// {
// 	int	i;
// 	int	count;
// 	int	f;

// 	i = 0;
// 	count = 0;
// 	while (t[i])
// 	{
// 		f = ft_valid(str, t[i]);
// 		if (f == -1)
// 			return (-1);
// 		else if (f == 1)
// 			count++;
// 		i++;
// 	}
// 	return (count);
// }

// char	**ft_filter_cr_list(char *str, char **t)
// {
// 	int		i;
// 	int		j;
// 	int		s;
// 	int		f;
// 	char	**t2;

// 	i = 0;
// 	j = 0;
// 	s = 0;
// 	s = ft_count_cr_match(str, t);
// 	if (s == -1)
// 		return (NULL);
// 	t2 = malloc((s + 1) * sizeof(char *));
// 	if (!t2)
// 		return (NULL);
// 	i = 0;
// 	j = 0;
// 	while (t[i])
// 	{
// 		f = ft_valid(str, t[i]);
// 		if (f == -1)
// 			return (NULL);
// 		else if (f == 1)
// 		{
// 			t2[j] = strdup(t[i]);
// 			i++;
// 		}
// 		j++;
// 	}
// 	t2[j] = NULL;
// 	return (t2);
// }
char	*ft_strjoin3(char **s1)
{
	char	*t;
	int		s;
	int		i;
	int		j;

	if (!s1)
		return (NULL);
	i = 0;
	s = 0;
	while (s1[i])
		s += strlen(s1[i++]);
	t = malloc(s + 1);
	if (!t)
		return (NULL);
	i = 0;
	s = 0;
	while (s1[i] != '\0')
	{
		j = 0;
		while (s1[i][j])
			t[s++] = s1[i][j++];
		i++;
	}
	t[s] = '\0';
	return (t);
}
int	main(void)
{
	int		i;
	char	**rs;
	char	**rs1;
	char	*str;
	char	**t;

	str = "*a*";
	t = malloc((10 + 1) * sizeof(char *));
	t[0] = strdup("     usdfasdfiifsdfaiiiaaaiu.......");
	t[1] = strdup("..a..b");
	t[2] = strdup("u*u");
	t[3] = strdup("ab.");
	t[4] = strdup("[[[[[kldjsfa");
	t[5] = strdup("..");
	t[6] = strdup(".a b.");
	t[7] = strdup("a.b");
	t[8] = strdup("faklsab");
	t[9] = strdup("asdsklfjbdsf      1");
	t[10] = NULL;
	i = 0;
		printf("%s",ft_strjoin3(t));
	// while (i < 10)
	// {
	// 	if (ft_valid(str, t[i]) == 1)
	// 		printf(GREEN "%s  :  valid\n" RESET, t[i]);
	// 	else
	// 		printf(RED "%s  :  not valid\n" RESET, t[i]);
	// 	i++;
	// }
	return (0);
}



// -----------------------------------------
