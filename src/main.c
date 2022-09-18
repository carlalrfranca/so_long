/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cleticia <cleticia@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/17 21:24:37 by cleticia          #+#    #+#             */
/*   Updated: 2021/10/19 20:57:22 by cleticia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/so_long.h"

int	main(int argc, char *argv[])
{
	if (argc == 2)
		so_long(argv[1]);
	else
	{
		write(2, "Error\n", 6);
		write(2, "Invalid number of argument.\n", 28);
		exit (1);
	}
	return (0);
}
