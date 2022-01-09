/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: magomed <magomed@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/09 13:25:52 by magomed           #+#    #+#             */
/*   Updated: 2022/01/09 19:31:41 by magomed          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

#include <stdio.h>

void	print_error(char *str)
{
	write(2, str, ft_strlen(str));
	write(2, "\n", 1);
	exit(EXIT_FAILURE);
}

void	parser(t_pipex *pipex, char **envr)
{
	pipex->fd1 = open(pipex->argv[1], O_RDONLY);
	if (pipex->fd1 < 0)
		perror("Error");
	pipex->fd2 = open(pipex->argv[4], O_WRONLY | O_TRUNC | O_CREAT, S_IRWXU);
	if (pipex->fd2 < 0)
		perror("Error");
	
	int 	i;
	char	*tmp;
	char	**path;

	i = -1;
	tmp = malloc(sizeof(char));
	if (!tmp)
		print_error("Error: malloc error!");
	tmp[0] = '\0';
	while (envr[++i])
	{
		tmp = ft_strnstr(envr[i], "PATH=", 6);
		if (tmp)
			break ;
	}
	path = ft_split(tmp + 5, ':');
	
	// printf("%s\n", path[0]);
	// printf("%s\n", path[1]);
	// printf("%s\n", path[2]);
	// printf("%s\n", path[4]);
}

int	main(int argc, char **argv, char **envr)
{
	t_pipex pipex;

	if (argc != 5)
		print_error("Error: Wrong executable pattern!");
	pipex.argv = argv;
	parser(&pipex, envr);
	
	return (0);
}