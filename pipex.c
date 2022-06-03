#include "pipex.h"

void	ft_error(char *str)
{
	perror(str);
	exit(0);
}

void	ft_child_process(int *fd, int *file, char **argv, char **envp)
{
	int		i;
	char	*cmd;
	char	*path_env;
	char	**paths_sep;
	char	**arg;

	path_env = ft_find_path(envp);
	paths_sep = ft_split(path_env, ':');
	arg = ft_split(argv[2], ' ');
	dup2(file[0], 0);
	dup2(fd[1], 1);
	close(fd[0]);
	close(file[0]);
	i = 0;
	while (paths_sep[i])
	{
		cmd = ft_strjoin(paths_sep[i], arg[0]);
		if (!access(cmd, X_OK))
			ft_error("Error en Comando");
		execve(cmd, arg, envp);
		//ft_error("Error en Execve");
		//free(cmd);
		i++;
	}
}

void	ft_parent_process(int *fd, int *file, char **argv, char **envp)
{
	int		status;
	int		i;
	char	*temp;
	char	*cmd;
	char	*path_env;
	char	**paths_sep;
	char	**arg;

	if (waitpid(-1, &status, 0) == -1)
		ft_error("Error en Waitpid");
	path_env = ft_find_path(envp);
	paths_sep = ft_split(path_env, ':');
	arg = ft_split(argv[3], ' ');
	dup2(file[1], 1);
	dup2(fd[0], 0);
	close(fd[1]);
	close(file[1]);
	i = 0;
	while (paths_sep[i])
	{
		temp = ft_strjoin(paths_sep[i], '/');
		cmd = ft_strjoin(temp, arg[0]);
		free(temp);
		if (!access(cmd, F_OK))
			ft_error("Error en Comando");
		execve(cmd, arg, envp);
		//ft_error("Error en Execve");
		//free(cmd);
		i++;
	}
}

char	*ft_find_path(char **envp)
{
	int		i;
	char	*path_env;

	i = 0;
	while (!ft_strnstr(envp[i], "PATH=", 5))
		i++;
	path_env = ft_strnstr(envp[i], "PATH=", 5);
	return (path_env + 5);
}

int	main(int argc, char **argv, char **envp)
{
	int			fd[2];
	int			file[2];
	pid_t		child_pid;

	if (argc != 5)
		ft_error("Error en Argc");
	if (pipe(fd) < 0)
		ft_error("Error en Pipe");
	file[0] = open(argv[1], O_RDONLY);
	if (file[0] == -1)
		ft_error("Error en Child File");
	file[1] = open(argv[4], O_RDWR | O_CREAT | O_TRUNC, 0644);
	if (file[1] == -1)
		ft_error("Error en Parent File");
	child_pid = fork();
	if (child_pid == -1)
		ft_error("Error en Fork");
	else if (child_pid == 0)
		ft_child_process(fd, file, argv, envp);
	else
		ft_parent_process(fd, file, argv, envp);
}
