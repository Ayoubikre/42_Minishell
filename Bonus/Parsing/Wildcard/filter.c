/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filter.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noctis <noctis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 22:59:03 by noctis            #+#    #+#             */
/*   Updated: 2025/06/13 03:02:35 by noctis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/main.h"
#include "../../include/parse.h"



// int	ft_valid(char *str, char *t)
// {
// 	int		i;
// 	int		j;
// 	int		k;
// 	int		f;
// 	char	**rs;

// 	i = 0;
// 	j = 0;
// 	k = 0;
// 	f = 0;
// 	rs = ft_split4(str);
// 	if (!rs)
// 		return (-1);
// 	while (rs[k])
// 	{
// 		f = ft_check_q_status(rs[i]);
// 		if (f == 0)
// 		{
// 			i = ft_consume_1(rs[k], t, &j);
// 			if (i == -1)
// 				return (-1);
// 			else if (i == 0)
// 				return (0);
// 		}
// 		else
// 		{
// 			i = ft_consume_2(rs[k], t, &j);
// 			if (i == -1)
// 				return (-1);
// 			else if (i == 0)
// 				return (0);
// 		}
// 		k++;
// 	}
// 	return (1);
// }

static int match_wildcard(const char *pattern, const char **filename_ptr)
{
    const char *p = pattern;
    const char *f = *filename_ptr;
    const char *star_p = NULL;
    const char *star_f = NULL;

    while (*f)
    {
        if (*p == '*')
        {
            star_p = ++p;
            star_f = f;
        }
        else if (*p == *f)
        {
            p++;
            f++;
        }
        else if (star_p)
        {
            p = star_p;
            f = ++star_f;
        }
        else
        {
            return 0;
        }
    }

    while (*p == '*')
        p++;

    if (*p == '\0')
    {
        *filename_ptr = f;
        return 1;
    }

    return 0;
}

int ft_valid(const char *pattern, const char *filename)
{
    char **split = ft_split4(pattern);
    if (!split)
        return 0;

    int i = 0;
    const char *f = filename;

    while (split[i])
    {
        int is_quoted = ft_check_q_status(split[i]);
        const char *segment = split[i];

        // Debug output
        printf("[DEBUG] Segment: \"%s\" | Quoted: %d | Filename head: \"%s\"\n",
               segment, is_quoted, f);

        if (is_quoted)
        {
            size_t len = strlen(segment);
            if (strncmp(f, segment, len) != 0)
            {
                printf("[DEBUG] Literal mismatch: \"%s\" vs \"%s\"\n", segment, f);
                return 0;
            }
            f += len;
        }
        else
        {
            if (!match_wildcard(segment, &f))
            {
                printf("[DEBUG] Wildcard mismatch: \"%s\" vs \"%s\"\n", segment, f);
                return 0;
            }
        }
        i++;
    }

    if (*f != '\0')
    {
        printf("[DEBUG] Leftover filename content: \"%s\"\n", f);
        return 0;
    }

    return 1;
}

int	ft_count_wc_match(char *str, char **t)
{
	int	i;
	int	count;
	int	f;

	i = 0;
	count = 0;
	while (t[i])
	{
		f = ft_valid(str, t[i]);
		if (f == -1)
			return (-1);
		else if (f == 1)
			count++;
		i++;
	}
	return (count);
}

char	**ft_filter_wc_list(char *str, char **t)
{
	int		i;
	int		j;
	int		s;
	int		f;
	char	**t2;

	s = ft_count_wc_match(str, t);
	if (s == -1)
		return (ft_free(t), NULL);
	t2 = malloc((s + 1) * sizeof(char *));
	if (!t2)
		return (ft_free(t), NULL);
	i = 0;
	j = 0;
	while (t[i])
	{
		f = ft_valid(str, t[i]);
		if (f == -1)
			return (ft_free(t2), ft_free(t), NULL);
		else if (f == 1)
		{
			t2[j] = ft_strdup(t[i]);
			j++;
		}
		i++;
	}
	t2[j] = NULL;
	return (ft_free(t), t2);
}

