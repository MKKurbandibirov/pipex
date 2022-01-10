/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: magomed <magomed@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/09 13:25:52 by magomed           #+#    #+#             */
/*   Updated: 2022/01/10 14:16:06 by magomed          ###   ########.fr       */
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

static void	parser(t_pipex *pipex, char **envr)
{
	char	**path;

	path = find_path(envr);
	pipex->file_fd[0] = open(pipex->argv[1], O_RDONLY);
	if (pipex->file_fd[0] < 0)
		perror("Error");
	pipex->file_fd[1] = open(pipex->argv[4], O_WRONLY | O_TRUNC | O_CREAT, S_IRWXU);
	if (pipex->file_fd[1] < 0)
		perror("Error");
	pipex->cmd1 = ft_split(pipex->argv[2], ' ');
	(pipex->cmd1)[0] = identify_cmd(pipex->cmd1[0], path);
	pipex->cmd2 = ft_split(pipex->argv[3], ' ');
	(pipex->cmd2)[0] = identify_cmd(pipex->cmd2[0], path);
	free_split(path);
}

static void	child1_process(t_pipex *pipex, char **envr)
{
	dup2(pipex->file_fd[0], STDIN_FILENO);
	dup2(pipex->pipe_fd[1], STDOUT_FILENO);
	close(pipex->file_fd[0]);
	close(pipex->file_fd[1]);
	close(pipex->pipe_fd[0]);
	close(pipex->pipe_fd[1]);
	execve(pipex->cmd1[0], pipex->cmd1, envr);
	print_error("Error: execve error!");
	exit(EXIT_FAILURE);
}

static void	child2_process(t_pipex *pipex, char **envr)
{
	dup2(pipex->pipe_fd[0], STDIN_FILENO);
	dup2(pipex->file_fd[1], STDOUT_FILENO);
	close(pipex->file_fd[0]);
	close(pipex->file_fd[1]);
	close(pipex->pipe_fd[0]);
	close(pipex->pipe_fd[1]);
	execve(pipex->cmd2[0], pipex->cmd2, envr);
	print_error("Error: execve error!");
	exit(EXIT_FAILURE);
}

static void	f_pipex(t_pipex *pipex, char **envr)
{
	pid_t	pid[2];
	int		status[2];

	pid[0] = fork();
	if (pid[0] == -1)
		print_error("Error: fork error!");
	if (pid[0] == 0)
		child1_process(pipex, envr);
	pid[1] = fork();
	if (pid[1] == -1)
		print_error("Error: fork error!");
	if (pid[1] == 0)
		child2_process(pipex, envr);
	close(pipex->file_fd[0]);
	close(pipex->file_fd[1]);
	close(pipex->pipe_fd[0]);
	close(pipex->pipe_fd[1]);
	waitpid(pid[0], &status[0], WNOHANG);
	waitpid(pid[1], &status[1], WNOHANG);
}

int	main(int argc, char **argv, char **envr)
{
	t_pipex pipex;

	if (argc != 5)
		print_error("Error: Wrong executable pattern!");
	pipex.argv = argv;
	parser(&pipex, envr);
	if (pipe(pipex.pipe_fd) == -1)
		print_error("Error: pipe error!");
	f_pipex(&pipex, envr);
	free_split(pipex.cmd1);
	free_split(pipex.cmd2);
	return (0);
}