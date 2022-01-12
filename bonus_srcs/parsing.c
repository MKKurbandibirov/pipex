/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: magomed <magomed@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/12 18:51:25 by magomed           #+#    #+#             */
/*   Updated: 2022/01/12 18:52:05 by magomed          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

char	**find_path(char **envr)
{
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
	if (!envr[i])
		print_error("Error: no path in envr!");
	path = ft_split(tmp + 5, ':');
	i = -1;
	while (path[++i])
		path[i] = ft_strjoin(path[i], "/");
	return (path);
}

char	*identify_cmd(char *cmd, char **path)
{
	int		i;
	char	*tmp;

	i = -1;
	while (path[++i])
	{
		tmp = ft_strjoin(path[i], cmd);
		if (access(tmp, F_OK) == 0)
		{
			free(cmd);
			return (tmp);
		}
		else
			free(tmp);
	}
	if (!path[i])
		print_error("Error: command not found!");
	return (NULL);
}

void    check_del(t_pipex *pipex)
{
	if (ft_strnstr(pipex->argv[1], "here_doc", 8))
	{
		pipex->del = pipex->argv[2];
		pipex->file_fd[0] = 0;
		pipex->file_fd[1] = open(pipex->argv[pipex->argc - 1], O_WRONLY | O_TRUNC | O_CREAT, S_IRWXU);
		if (pipex->file_fd[1] < 0)
			print_error("Error: here_doc outfile error!");
		pipex->cmd_count = pipex->argc - 4;
	}
	else
	{
		pipex->del = NULL;
		pipex->file_fd[0] = open(pipex->argv[1], O_RDONLY);
		if (pipex->file_fd[0] < 0)
			print_error("Error: infile error!");
		pipex->file_fd[1] = open(pipex->argv[pipex->argc - 1], O_WRONLY | O_TRUNC | O_CREAT, S_IRWXU);
		if (pipex->file_fd[1] < 0)
			print_error("Error: outfile error!");
		pipex->cmd_count = pipex->argc - 3;
	}
}

void	init_pipex(t_pipex *pipex)
{
	pipex->pipe_fd = malloc(sizeof(int) * (pipex->cmd_count * 2));
	pipex->pid = malloc(sizeof(pid_t) * pipex->cmd_count);
	pipex->status = malloc(sizeof(int) * pipex->cmd_count);
	if (!(pipex->pid && pipex->pipe_fd && pipex->status))
		print_error("Error: malloc error!");
}

void	parser(char **envr, t_pipex *pipex)
{
	int	i;
	char	**path;
	char	*tmp;

	path = find_path(envr);
	if (pipex->argc < 5 || (pipex->argc < 6 && ft_strnstr(pipex->argv[1], "here_doc", 8)))
		print_error("Error: wrong executable pattern");
	check_del(pipex);
	pipex->cmd = (char ***)malloc(sizeof(char **) * (pipex->cmd_count + 1));
	if (!pipex->cmd)
		print_error("Error: malloc error!");
	i = -1;
	while (++i < pipex->cmd_count)
	{
		pipex->cmd[i] = ft_split(pipex->argv[pipex->argc - pipex->cmd_count - 1 + i], ' ');
		tmp = identify_cmd(pipex->cmd[i][0], path);
		pipex->cmd[i][0] = tmp;
	}
	pipex->cmd[i] = NULL;
	init_pipex(pipex);
}