/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: magomed <magomed@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/11 09:04:33 by magomed           #+#    #+#             */
/*   Updated: 2022/01/12 18:55:13 by magomed          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	print_error(char *str)
{
	write(2, str, ft_strlen(str));
	write(2, "\n", 1);
	exit(EXIT_FAILURE);
}

int	main(int argc, char **argv, char **envr)
{
	t_pipex pipex;

	pipex.argv = argv;
	pipex.argc = argc;
	parser(envr, &pipex);
	if (!pipex.del)
		f_multiple_pipex(&pipex);
	else
	{
		f_multiple_pipex(&pipex);
		heredoc_out(&pipex);
	}
	return (0);
}