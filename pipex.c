/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: barbizu- <barbizu-@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 11:15:13 by barbizu-          #+#    #+#             */
/*   Updated: 2022/06/07 17:09:54 by barbizu-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "pipex.h"
#include <stdio.h>

void	ft_paths_arg(char **paths_sep, char **arg, char **envp)
{
	char	*temp;
	char	*cmd;
	int		i;

	i = 0;
	while (paths_sep[i])
	{
		temp = ft_strjoin(paths_sep[i], "/");
		cmd = ft_strjoin(temp, arg[0]);
		free(temp);
		execve(cmd, arg, envp);
		if (!access(cmd, F_OK))
			ft_error("Error en Comando");
		free(cmd);
		i++;
	}
}

void	ft_child_process(int *fd, int *file, char **argv, char **envp)
{
	char	**arg;
	char	*path_env;
	char	**paths_sep;

	path_env = ft_find_path(envp);
	paths_sep = ft_split(path_env, ':');
	arg = ft_split(argv[2], ' ');
	close(fd[0]);
	dup2(file[0], STDIN_FILENO);
	dup2(fd[1], STDOUT_FILENO);
	close(fd[1]);
	ft_paths_arg(paths_sep, arg, envp);
}

void	ft_parent_process(int *fd, int *file, char **argv, char **envp)
{
	char	**arg;
	char	*path_env;
	char	**paths_sep;

	path_env = ft_find_path(envp);
	paths_sep = ft_split(path_env, ':');
	arg = ft_split(argv[3], ' ');
	close(fd[1]);
	dup2(file[1], STDOUT_FILENO);
	dup2(fd[0], STDIN_FILENO);
	close(fd[0]);
	ft_paths_arg(paths_sep, arg, envp);
}

void	ft_pipex(int *fd, char **argv, char **envp)
{
	int		file[2];
	pid_t	child_pid;

	file[0] = open(argv[1], O_RDONLY);
	file[1] = open(argv[4], O_RDWR | O_CREAT | O_TRUNC, 0644);
	if (file[0] == -1 || file[1] == -1)
		ft_error("Error en File");
	child_pid = fork();
	if (child_pid == -1)
		ft_error("Error en Fork");
	else if (child_pid == 0)
		ft_child_process(fd, file, argv, envp);
	else
		ft_parent_process(fd, file, argv, envp);
}

int	main(int argc, char **argv, char **envp)
{
	int			fd[2];
	int			status;

	if (argc != 5)
		ft_error("Error en Argc");
	if (pipe(fd) < 0)
		ft_error("Error en Pipe");
	ft_pipex(fd, argv, envp);
	waitpid(-1, &status, 0);
}
