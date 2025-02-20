/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pchapuis <pchapuis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/23 11:18:43 by pchapuis          #+#    #+#             */
/*   Updated: 2022/11/24 14:08:07 by pchapuis         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	ft_free(char **ptr)
{
	if (*ptr != NULL)
	{
		free(*ptr);
		ptr = NULL;
	}
}

char	*put_result(char *temp, int p, char **buffer)
{
	if (p <= 0)
	{
		if (!*buffer[0])
		{
			free(*buffer);
			*buffer = NULL;
			return (NULL);
		}
		temp = *buffer;
		*buffer = NULL;
		return (temp);
	}
	*buffer = ft_substr(temp, p, BUFFER_SIZE);
	temp[p] = '\0';
	return (temp);
}

char	*put_line(int fd, char **buffer, char *temp)
{
	char	*p;
	int		nb;
	char	*temp1;

	temp1 = *buffer;
	nb = 0;
	p = ft_strchr(*buffer, '\n');
	while (!p)
	{
		nb = read(fd, temp, BUFFER_SIZE);
		if (nb <= 0)
			return (put_result(temp1, nb, buffer));
		temp[nb] = '\0';
		temp1 = ft_strjoin(*buffer, temp);
		ft_free(buffer);
		*buffer = temp1;
		p = ft_strchr(temp1, '\n');
	}
	return (put_result(temp1, p - temp1 + 1, buffer));
}

char	*get_next_line(int fd)
{
	static char	*buffer;
	char		*result;
	char		*temp;

	if (read(fd, 0, 0) == -1 || BUFFER_SIZE <= 0)
	{
		free(buffer);
		buffer = NULL;
		return (NULL);
	}
	temp = malloc(sizeof(char) * BUFFER_SIZE + 1);
	if (!temp)
		return (NULL);
	if (!buffer)
		buffer = ft_strdup("");
	result = put_line(fd, &buffer, temp);
	ft_free(&temp);
	return (result);
}
