/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aimkrtch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 22:07:36 by aimkrtch          #+#    #+#             */
/*   Updated: 2023/02/17 13:04:17 by aimkrtch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*ft_return_value(char *tmp)
{
	char	*dub;
	int		i;

	i = 0;
	if (!tmp)
		return (NULL);
	while (tmp && tmp[i] && tmp[i] != '\n')
		i++;
	if (i == 0)
		dub = (char *)malloc(sizeof(char) * (i + 1));
	else
		dub = (char *)malloc(sizeof(char) * (i + 2));
	i = 0;
	while (tmp[i] && tmp[i] != '\n')
	{
		dub[i] = tmp[i];
		i++;
	}
	if (tmp[i] && tmp[i] == '\n')
	{
		dub[i] = '\n';
		i++;
	}
	dub[i] = '\0';
	return (dub);
}

char	*ft_read(int fd, char *s)
{
	char			*buff;
	int				read_size;

	buff = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buff)
		return (0);
	while (1)
	{
		read_size = read(fd, buff, BUFFER_SIZE);
		if (read_size == -1)
		{
			free(buff);
			return (0);
		}
		buff[read_size] = '\0';
		s = ft_strjoin(s, buff);
		if (ft_strchr(buff, '\n') || read_size == 0)
			break ;
	}
	free(buff);
	return (s);
}

char	*ft_remaind(char *s)
{
	int		i;
	int		j;
	char	*str;

	i = 0;
	if (!s)
		return (0);
	while (s[i] && s[i] != '\n')
		i++;
	if (s[i] == '\0')
	{
		free(s);
		return (0);
	}
	str = (char *)malloc(sizeof(char) * (ft_strlen(s) - i));
	if (!str)
		return (0);
	j = 0;
	while (s[i] && s[++i])
		str[j++] = s[i];
	str[j] = '\0';
	free(s);
	return (str);
}

char	*get_next_line(int fd)
{
	static char		*tmp[OPEN_MAX];
	char			*ptr;

	ptr = 0;
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (0);
	tmp[fd] = ft_read(fd, tmp[fd]);
	if (!tmp[fd])
		return (0);
	ptr = ft_return_value(tmp[fd]);
	tmp[fd] = ft_remaind(tmp[fd]);
	if (ptr && !ptr[0])
	{
		free(ptr);
		return (0);
	}
	return (ptr);
}

// int	main(void)
// {
// 	int		fd;
// 	char	*s;
// 	int		i;

// 	fd = open("text.txt", O_RDONLY);
// 	i = 0;

// 	// while (i++ < 5)
// 	// {
// 	// 	s = get_next_line(fd);
// 	// 	printf("%s", s);
// 	// 	free(s);
// 	// 	s = 0;
// 	// }
// }
