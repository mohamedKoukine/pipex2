/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkaoukin <mkaoukin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 14:27:17 by mkaoukin          #+#    #+#             */
/*   Updated: 2024/03/15 14:27:17 by mkaoukin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "pipex.h"

void	free_all(char **p)
{
	int	i;

	i = 0;
	while (p[i])
	{
		free (p[i]);
		i++;
	}
	free(p);
}

static int	ft_position(const char *s1, const char *s2)
{
	size_t	i;

	i = 0;
	while (s1[i] && s1[i] == s2[i])
		i++;
	return (i);
}

static void	cont_access_cmd(char **path, char **path2, t_fd *fd)
{
	while (*path)
	{
		*path2 = ft_strjoin(*path2, fd->av3);
		if (access(*path2, F_OK | X_OK) != -1)
			fd->path2 = ft_substr(*path2, 0, ft_strlen(*path2));;
		*path = ft_strjoin(*path, fd->av2);
		if (access(*path, F_OK | X_OK) != -1)
			fd->path1 = ft_substr(*path, 0, ft_strlen(*path));
		path--;
		path2--;
	}
	if (!fd->path2 || !fd->path1)
		ft_exit(1, "ERROR\n");
	path++;
	path2++;
	free_all(path);
	free_all(path2);
	free (fd->av2);
	free (fd->av3);
	free (fd->line);
}

static void	access_cmd(char **path, char **path2, t_fd *fd, char **av)
{
	int	i;

	while (*path)
	{
		if (ft_strncmp(*path, av[2], ft_strlen(*path)) == 0)
		{
			i = ft_position(*path, av[2]);
			fd->av2 = ft_substr(av[2], i, ft_strlen(av[2]) - i);
		}
		if (ft_strncmp(*path2, av[3], ft_strlen(*path2)) == 0)
		{
			i = ft_position(*path2, av[3]);
			fd->av3 = ft_substr(av[3], i, ft_strlen(av[3]) - i);
		}
		path++;
		path2++;
	}
	if (!fd->av2)
		fd->av2 = ft_substr(av[2], 0, ft_strlen(av[2]));
	if (!fd->av3)
		fd->av3 = ft_substr(av[3], 0, ft_strlen(av[3]));
	path--;
	path2--;
	cont_access_cmd(path, path2, fd);
}

void	parsing(char **av, char **env, t_fd *fd)
{
	char	**path;
	char	**path2;

	fd->line = NULL;
	fd->path1 = NULL;
	fd->path2 = NULL;
	while (*env)
	{
		if (ft_strncmp(*env, "PATH=", 5) == 0)
		{
			fd->line = ft_strdup((*env + 5));
			break ;
		}
		env++;
	}
	path = ft_split(fd->line, ':');
	path2 = ft_split(fd->line, ':');
	if (!path || !path2)
		ft_exit(1, "ERROR_IN_SPLIT\n");
	access_cmd(path, path2, fd, av);
}