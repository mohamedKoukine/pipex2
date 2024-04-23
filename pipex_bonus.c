/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkaoukin <mkaoukin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 14:10:39 by mkaoukin          #+#    #+#             */
/*   Updated: 2024/04/23 14:20:05 by mkaoukin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_exit(int l, char *err)
{
	int	i;

	i = 0;
	if (l == 0)
		exit (0);
	else
	{
		while (err[i])
		{
			write(2, &err[i], 1);
			i++;
		}
		exit (1);
	}
}

void	command3(t_fd	*fd, char **av, char **env, int i)
{
	char	**cmd2;
	int		id;
	
	id = fork();
	if (id == -1)
		ft_exit(1 ,"Error Fork");
	if (id == 0)
	{
		parsing_b(av,env, fd, i);
		fd->file = open(av[i + 1], O_RDWR | O_CREAT | O_TRUNC, 0777);
		if (fd->file < 0)
			ft_exit(1, "ERROR IN OUTFILE\n");
		cmd2 = ft_split(av[i], ' ');
		dup2(fd->file, STDOUT_FILENO);
		if (execve(fd->path1, cmd2, env) == -1)
			ft_exit(1, "ERROR IN CMD2\n");
		close(fd->file);
	}
	else
		wait(NULL);
}

void	command1(t_fd	*fd, char **av, char **env, int i)
{
	char	**cmd1;
	int 	p[2];

	parsing_b(av,env, fd, i);
	if (pipe(p) == -1)
			ft_exit(1, "ERROR PIPE\n");
	fd->id1 = fork();
	if (fd->id1 == -1)
			ft_exit(1, "ERROR FORK()\n");
	if (fd->id1 == 0)
	{
		close(p[0]);
		cmd1 = ft_split(av[i], ' ');
		dup2(p[1], STDOUT_FILENO);
		if (execve(fd->path1, cmd1, env) == -1)
			ft_exit(1, "ERROR IN CMD1\n");
	}
	else
	{
		close(p[1]);
		dup2(p[0], STDIN_FILENO);
		wait(NULL);
	}
}

void	here_d(char *av,t_fd *fd)
{
	char	*line;

	fd->id2 = open ("/tmp/here_doc", O_CREAT | O_RDWR | O_APPEND ,0777);
	while (1)
	{
		line = get_next_line(0);
		if (!line)
		ft_exit(1, "ERROR\n");
		if (ft_strncmp(line, av, ft_strlen(av, 0)) == 0)
		{
			free(line);
			break;
		}
		write (fd->id2, line, ft_strlen(line,0));
		free (line);
		line = NULL;
	}
	close (fd->id2);
	fd->id2 = open ("/tmp/here_doc", O_RDWR | O_APPEND ,0777);
	if (fd->id2== -1)
				ft_exit(1, "Error\n");
	dup2(fd->id2, STDIN_FILENO);
	close (fd->id2);
}
void d()
{
	system("leaks pipex_bonus");
}

int	main(int ac, char **av, char **env)
{
	// atexit(d);
	t_fd	fd;
	int		i;
	int		l;

	if (ac >= 5)
	{
		if (ft_strcmp(av[1], "here_doc") == 0)
		{
			if (ac != 6)
				ft_exit(1, "Error_Argc\n");
			here_d(av[2],&fd);
			i = 2;
			l = 0;
		}
		else
		{
			fd.file = open(av[1], O_RDWR);
			if (fd.file == -1)
				ft_exit(1, "Error File\n");
			dup2(fd.file, STDIN_FILENO);
			close (fd.file);
			i = 1;
		}
		while (++i < ac - 2)
		{
			command1(&fd, av, env, i);
			if (fd.path1)
			{
				free(fd.path1);
				fd.path1 = NULL;
			}
		}
		free (fd.path1);
		if (l == 0)
			unlink("/tmp/here_doc");
		command3(&fd, av, env, i);
	}
	else
		write (2, "Error_Argc\n", 11);
}
