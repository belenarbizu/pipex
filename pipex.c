#include <stdio.h>
#include <unistd.h>

void	ft_error(char *str)
{
	perror(str);
	exit(EXIT_SUCCESS);
}

void	ft_child_process(int *fd, int *file, char **argv, char **paths_sep)
{
	int	i;

	file[0] = open(argv[1], O_RDONLY); //argv[1] actúa como stdin que solo lee
	if (file[0] == -1)
		ft_error("Error en Child File");
	dup2(file[0], 0);
	dup2(fd[1], 1); //el hijo escribe, fd[1] escribe
	close(fd[0]);
	i = 0;
	while (paths_sep[i])
	{

		i++;
	}
}

void	ft_parent_process(int *fd, int *file, char **argv, char **paths_sep)
{
	file[1] = open(argv[4], O_RDWR | O_CREAT | O_TRUNC, 0744) //O_CREAT crea el archivo, le doy permisos 744??
	if (file[1] == -1)
		ft_error("Error en Parent File");
	dup2(file[1], 1);
	dup2(fd[0], 0);
	close(fd[1]);
}

char	*find_path(char **envp)
{
	int	i;
	char	*pathEnv;

	i = 0;
	while (!ft_strnstr(envp[i], "PATH", 4))
		i++;
	pathEnv = ft_strnstr(envp[i], "PATH", 4);
	return (pathEnv + 4);
}

int	main(int argc, char **argv, char **envp)
{
	int	fd[2];
	int	file[2];
	int	childPid;
	char	*pathEnv;
	char	**paths_sep;

	if (argc != 5)
		ft_error("Error en Argc: ./pipex arch1 cmd1 cmd2 arch2");
	if (pipe(fd) < 0)
		ft_error("Error en Pipe");
	pathEnv = find_path(envp);
	paths_sep = ft_split(pathEnv, ":");
	childPid = fork();
	if (childPid == -1)
		ft_error("Error en Fork");
	else if (childPid == 0)
		ft_child_process(fd, file, argv, paths_sep);
	else
		ft_parent_process(fd, file, argv, paths_sep);
}
