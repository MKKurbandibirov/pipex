/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: magomed <magomed@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/11 09:04:51 by magomed           #+#    #+#             */
/*   Updated: 2022/01/12 18:55:46 by magomed          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

# include <unistd.h>
# include <fcntl.h>
# include <stdlib.h>
# include <sys/wait.h>
# include "../get_next_line/get_next_line.h"

typedef struct s_pipex
{
	char	***cmd;
	int		*pipe_fd;
	pid_t	*pid;
	int		*status;
	int		file_fd[2];
	char	*del;
	int		cmd_count;
	char	**argv;
	int		argc;
}	t_pipex;

void	print_error(char *str);

void	parser(char **envr, t_pipex *pipex);

void	f_multiple_pipex(t_pipex *pipex);
void	heredoc_out(t_pipex *pipex);

int		ft_strlen(const char *c);
char	*ft_strnstr(const char *h, const char *n, int len);
char	*ft_strjoin(char *s1, char *s2);
char	**ft_split(char const *s, char c);

#endif