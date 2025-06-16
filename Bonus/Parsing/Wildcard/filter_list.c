/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filter_list.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noctis <noctis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 22:59:03 by noctis            #+#    #+#             */
/*   Updated: 2025/06/16 04:44:18 by noctis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/main.h"
#include "../../include/parse.h"


int ft_valide(char *t, t_wc *data)
{
	int i=0;
	int j=0;
	int k=0;
	t_wc *ptr;

	ptr=data;
	
	while(ptr)
	{
		if(ptr->f==0)
		{
			if(!ptr->next)
			{

				if(strncmp(t+i, ptr->value,strlen(ptr->value))!=0)
				{
					printf("faile %c\n",t[i]);
					return 0;
				}
				else
				{
					while(strncmp(t+i, ptr->value, strlen(ptr->value))==0)
					{
						printf("good %c\n",t[i]);

						i++;
					}
				}
			}
			else
			{
				if(strncmp(t+i, ptr->value, strlen(ptr->value))!=0)
				{
					return 0;
				}
				i+=strlen(ptr->value);
			}	
		}
		else
		{
			if(!ptr->next)
			{
				return 1;
			}
			else
			{
				while (t[i])
				{
					if (strncmp(t + i, ptr->next->value, strlen(ptr->next->value)) == 0)
						break;
					i++;
				}
				if (!t[i])
					return 0; 
			}
		}

		ptr=ptr->next;
	}

	// while (ptr)
	// {
	// 	if (ptr->f == 0)
	// 	{
	// 		size_t len = strlen(ptr->value);
	// 		if (strncmp(t + i, ptr->value, len) != 0)
	// 			return 0;
	// 		i += len;
	// 	}
	// 	else
	// 	{
	// 		if (!ptr->next)
	// 			return 1; // trailing wildcard, matches everything
	// 		while (t[i])
	// 		{
	// 			if (strncmp(t + i, ptr->next->value, strlen(ptr->next->value)) == 0)
	// 				break;
	// 			i++;
	// 		}
	// 		if (!t[i])
	// 			return 0; // couldn't find match for post-wildcard
	// 	}
	// 	ptr = ptr->next;
	// }

	
	if(t[i])
		return 0;
    return 1;
}


int	ft_count_wc_match(char **t1, t_wc *data)
{
	int	i;
	int	count;
	int	f;

	i = 0;
	count = 0;
	while (t1[i])
	{
		f = ft_valide(t1[i], data);
		if (f == -1)
			return (-1);
		else if (f == 1)
			count++;
		i++;
	}
	return (count);
}

char	**ft_filter_wc_list(char **t1, t_wc *data)
{
	int		i;
	int		j;
	int		s;
	int		f;
	char	**t2;

    
	s = ft_count_wc_match(t1, data);
	if (s == -1)
		return (ft_free(t1), NULL);

    printf("\n\t >> size : %d << \n\n",s);
	t2 = malloc((s + 1) * sizeof(char *));
	if (!t2)
		return (ft_free(t1), NULL);

        
	i = 0;
	j = 0;
	// while (t1[i])
	// {
	// 	f = ft_valide(t1[i], data);
	// 	if (f == -1)
	// 		return (ft_free(t1), NULL);
	// 	else if (f == 1)
	// 	{
	// 		t2[j] = ft_strdup(t1[i]);
	// 		if(!t2[j])
	// 			return (ft_free(t1), ft_free(t2), NULL);
	// 		j++;
	// 	}
	// 	i++;
	// }
	// t2[j] = NULL;

	while (t1[i])
	{
		f = ft_valide(t1[i], data);
		if (f == 1)
			printf(GREEN" > %s < is valid \n"RESET, t1[i]);
		else if (f == 1)
		{
			printf(RED" > %s < is NOT_ valid \n"RESET, t1[i]);
		}
		i++;
	}

	return (t2);
	// return (ft_free(t1), t2);
}
