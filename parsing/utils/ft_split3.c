/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aakritah <aakritah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 12:45:20 by aakritah          #+#    #+#             */
/*   Updated: 2025/04/04 13:47:14 by aakritah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/main.h"
#include "../../include/parse.h"

// static int ft_count(char *t)
// {
//     int i=0;
//     int f=0;
//     int count=0;
    
//     while(t[i])
//     {
//         if(str[i], )
        
//         i++;
//     }
//     return count;
// }

// static ft_filter(char *str, int *i)
// {
    
// }

// static ft_copy(char *str, int *i)
// {
    
// }

// char	**ft_split3(char *str)
// {
// 	int		i;
// 	int		k;
// 	char	**t;

// 	i = 0;
// 	k = 0;
// 	if (!str)
// 		return (NULL);
// 	t = malloc(sizeof(char *) * (ft_count(str) + 1));
// 	if (!t)
// 		return (NULL);
// 	while (k < ft_count(str))
// 	{
//         ft_filter(str, &i);
// 		t[k] = ft_copy(str, &i);
//         if(!t[k])
//             return (ft_free(t), NULL);
//         k++;
// 	}
// 	return (t);
// }

static long ft_count3(char const *s)
{
    long i = 0, count = 0, in_word = 0, i_c = 0;
    char q;

    while (s[i])
    {
        if ((s[i] == '\'' || s[i] == '"') && i_c == 0)
            (q = s[i], i_c = 1);
        else if (i_c == 1 && s[i] == q)
            i_c = 0;
        else if (i_c == 0 && (s[i] == '|' || s[i] == '<' || s[i] == '>'))
        {
            if (in_word)
                count++;
            count++; // Count operator
            in_word = 0;
            if ((s[i] == '<' && s[i + 1] == '<') || (s[i] == '>' && s[i + 1] == '>'))
                i++; // Skip second char
        }
        else if (i_c == 0 && in_word == 0)
            in_word = 1;
        i++;
    }
    if (in_word)
        count++;
    if (i_c == 1)
        return -1;
    return count;
}

static char *ft_copy3(char const *s, long *i)
{
    long j = *i, k = 0, i_c = 0;
    char q, *t;

    while (s[j] && (i_c || (s[j] != '|' && s[j] != '<' && s[j] != '>' &&
                            !(s[j] == '<' && s[j + 1] == '<') &&
                            !(s[j] == '>' && s[j + 1] == '>'))))
    {
        if ((s[j] == '\'' || s[j] == '"') && i_c == 0)
            (q = s[j], i_c = 1);
        else if (i_c == 1 && s[j] == q)
            i_c = 0;
        j++;
    }
    if (i_c == 0 && s[j] && (s[j] == '|' || s[j] == '<' || s[j] == '>' ||
                             (s[j] == '<' && s[j + 1] == '<') ||
                             (s[j] == '>' && s[j + 1] == '>')))
        j = *i + (s[*i] == '<' || s[*i] == '>' ? (s[*i + 1] == s[*i] ? 2 : 1) : 1);
    t = malloc((j - *i + 1));
    if (!t)
        return NULL;
    while (*i < j)
        t[k++] = s[(*i)++];
    t[k] = '\0';
    return t;
}

char **ft_split3(char const *s)
{
    long i = 0, k = 0;
    char **t;

    if (!s || ft_count3(s) < 0)
        return NULL;
    t = malloc((ft_count3(s) + 1) * sizeof(char *));
    if (!t)
        return NULL;
    while (s[i])
    {
        if (s[i] != '|' && s[i] != '<' && s[i] != '>' &&
            !(s[i] == '<' && s[i + 1] == '<') && !(s[i] == '>' && s[i + 1] == '>'))
            t[k++] = ft_copy3(s, &i);
        else
        {
            t[k++] = ft_copy3(s, &i);
            if (i > 0 && (s[i - 1] == '<' || s[i - 1] == '>') &&
                s[i - 1] == s[i - 2])
                i--; // Adjust for << or >>
        }
        if (!t[k - 1])
        {
            ft_free(t);
            return NULL;
        }
    }
    t[k] = NULL;
    return t;
}