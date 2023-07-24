/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bsq.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxgarci <maxgarci@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/24 13:28:41 by maxgarci          #+#    #+#             */
/*   Updated: 2023/07/24 14:22:23 by maxgarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include<stdlib.h>
#include<fcntl.h>
#include<unistd.h>
#include<stdio.h>

# define BUFFER_SIZE 2048 

int	read_file(char *file_name, int *row_count, int *column_count)
{
	int		file;
	char	buffer[BUFFER_SIZE];
	int		i;
	int		len;

	file = open(file_name, O_RDONLY);
	if (file == -1)
		return (-1);
	len = read(file, buffer, BUFFER_SIZE);
	if (len == -1)
	{
		close(file);
		return (-1);
	}
	i = -1;
	while (++i < len)
	{
		if (buffer[i] == '\n')
			++(*row_count);
		else if (!(*row_count))
			++(*column_count);
	}
	if (close(file) == -1)
		return (-1);
	return (0);
}

int	main(int argc, char *argv[])
{
	int	row_count;
	int	column_count;

	row_count = -1;
	column_count = 0;
	if (argc < 2)
	{
		perror("Error en la lectura del mapa");
		return (1);
	}	
	
	if (read_file(argv[1], &row_count, &column_count) == (-1))
	{
		perror("Fallo en la lectura del archivo: calculo filas y columnas");
		return (1);
	}
	printf("%d %d", row_count, column_count);
	return (0);
}