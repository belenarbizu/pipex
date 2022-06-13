/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: barbizu- <barbizu-@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 11:15:13 by barbizu-          #+#    #+#             */
/*   Updated: 2022/06/09 11:30:28 by barbizu-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "pipex.h"

char	*ft_paths_arg(char **paths_sep, char **arg, char **envp)
{
	char	*temp;
	char	*cmd;
	int		i;

	i = 0;
	(void)envp;
	while (paths_sep[i])
	{
		temp = ft_strjoin(paths_sep[i], "/");
		cmd = ft_strjoin(temp, arg[0]);
		free(temp);
		if (!access(cmd, F_OK))
			return (cmd);
		free(cmd);
		i++;
	}
	return (NULL);
}

void	ft_child_process(int *fd, int *file, char **argv, char **envp)
{
	char	**arg;
	char	*path_env;
	char	**paths_sep;
	char	*cmd;

	path_env = ft_find_path(envp);
	paths_sep = ft_split(path_env, ':');
	arg = ft_split(argv[2], ' ');
	close(fd[0]);
	close(file[1]);
	if (dup2(file[0], STDIN_FILENO) == -1)
		ft_error("Error en Dup");
	if (dup2(fd[1], STDOUT_FILENO) == -1)
		ft_error("Error en Dup");
	close(fd[1]);
	close(file[0]);
	cmd = ft_paths_arg(paths_sep, arg, envp);
	if (!cmd)
	{
		free_matrix(paths_sep);
		ft_putstr_fd("command not found: ", 2);
		ft_putendl_fd(argv[2], 2);
		free(cmd);
	}
	execve(cmd, arg, envp);
}

void	ft_parent_process(int *fd, int *file, char **argv, char **envp)
{
	char	**arg;
	char	*path_env;
	char	**paths_sep;
	char	*cmd;

	path_env = ft_find_path(envp);
	paths_sep = ft_split(path_env, ':');
	arg = ft_split(argv[3], ' ');
	close(fd[1]);
	close(file[0]);
	if (dup2(file[1], STDOUT_FILENO) == -1)
		ft_error("Error en Dup");
	if (dup2(fd[0], STDIN_FILENO) == -1)
		ft_error("Error en Dup");
	close(fd[0]);
	close(file[1]);
	cmd = ft_paths_arg(paths_sep, arg, envp);
	if (!cmd)
	{
		free_matrix(paths_sep);
		ft_putstr_fd("command not found: ", 2);
		ft_putendl_fd(argv[3], 2);
		free(cmd);
	}
	execve(cmd, arg, envp);
}

void	ft_pipex(int *fd, char **argv, char **envp)
{
	int		file[2];
	pid_t	child_pid;

	file[0] = open(argv[1], O_RDONLY);
	file[1] = open(argv[4], O_RDWR | O_CREAT | O_TRUNC, 0644);
	if (file[0] == -1 || file[1] == -1)
	{
		perror("Error en File");
		exit(0);
	}
	child_pid = fork();
	if (child_pid == -1)
	{
		perror("Error en Fork");
		exit(127);
	}
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
	{
		ft_putendl_fd("Error en Argc: ./pipex archv1 cm1 cm2 archv2", 2);
		exit(127);
	}
	if (pipe(fd) < 0)
	{
		perror("Error en Pipe");
		exit(127);
	}
	ft_pipex(fd, argv, envp);
	waitpid(-1, &status, 0);
}
