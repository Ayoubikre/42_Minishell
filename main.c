/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aakritah <aakritah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 13:18:28 by aakritah          #+#    #+#             */
/*   Updated: 2025/04/03 00:46:54 by aakritah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void ll()
{
    system("leaks -q a");
}
int main(int ac, char **av, char **env)
{
    atexit(ll);
    char *t;
    t=readline("enter here > ");
    printf("\n----------------\n");
    printf("> %s <", t);
    printf("\n----------------\n");

}
