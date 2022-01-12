/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: magomed <magomed@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/12 18:54:55 by magomed           #+#    #+#             */
/*   Updated: 2022/01/12 18:55:21 by magomed          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	fd_close(t_pipex *pipex)
{
	int	i;

	i = -1;
	while (++i < (pipex->cmd_count - 1) * 2)
	{
		close(pipex->pipe_fd[i]);
	}
	if (!pipex->del)
		close(pipex->file_fd[0]);
	close(pipex->file_fd[1]);
}

void	child_proc(int fd_in, int fd_out, char **cmd, t_pipex *pipex)
{
	dup2(fd_in, STDIN_FILENO);
	dup2(fd_out, STDOUT_FILENO);
	fd_close(pipex);
	execve(cmd[0], cmd, NULL);
	print_error("Error: execve error!");
	exit(EXIT_FAILURE);
}

void	f_multiple_pipex(t_pipex *pipex)
{
		int i;

	i = -1;
	while (++i < pipex->cmd_count - 1)
		if (pipe(pipex->pipe_fd + i * 2) == -1)
			print_error("Error: pipe error!");
	i = -1;
	while (++i < pipex->cmd_count)
	{
		pipex->pid[i] = fork();
		if (pipex->pid[i] == -1)
			print_error("Error: fork error!");
		if (pipex->pid[i] == 0)
		{
			if (i == 0)
				child_proc(pipex->file_fd[0], pipex->pipe_fd[i * 2 + 1], pipex->cmd[i], pipex);
			else if (i == pipex->cmd_count - 1)
				child_proc(pipex->pipe_fd[2 * i - 2], pipex->file_fd[1], pipex->cmd[i], pipex);
			else
				child_proc(pipex->pipe_fd[2 * i - 2], pipex->pipe_fd[i * 2 + 1], pipex->cmd[i], pipex);
		}
	}
	i = -1;
	fd_close(pipex);
	while (++i < pipex->cmd_count)
		waitpid(pipex->pid[i], &pipex->status[i], WNOHANG);
}

void	heredoc_out(t_pipex *pipex)
{
	char	*line;
	char	*str;
	int		i;

	str = NULL;
	i = -1;
	while(++i < pipex->cmd_count - 1)
	{
		str = ft_strjoinfree(str, "pipe ");
	}
	str = ft_strjoinfree(str, "heredoc> ");
	while(1)
	{
		write(1, str, ft_strlen(str));
		line = get_next_line(0);
		if (!line)
			print_error("Error: gnl error for here_doc!");
		if (ft_strnstr(line, pipex->del, ft_strlen(pipex->del)))
			break ;
		free(line);
	}
}