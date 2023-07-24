/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bsq.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouhaik <ybouhaik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/24 13:28:41 by maxgarci          #+#    #+#             */
/*   Updated: 2023/07/24 16:54:34 by ybouhaik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define BUFFER_SIZE 2048

int	read_file(char *file_name, int *row_count, int *column_count, char **buffer)
{
	int	file;
	int	i;
	int	len;

	file = open(file_name, O_RDONLY);
	if (file == -1)
		return (-1);
	len = read(file, *buffer, BUFFER_SIZE);
	if (len == -1)
	{
		close(file);
		return (-1);
	}
	i = -1;
	while (++i < len)
	{
		if (*(*buffer + i) == '\n')
			++(*row_count);
		else if (!(*row_count))
			++(*column_count);
	}
	if (close(file) == -1)
		return (-1);
	return (0);
}

char	**fill_matrix(char **matrix, char *buffer)
{
	int	row_pos;
	int	column_pos;
	int	pos_buffer;

	pos_buffer = 0;
	row_pos = 0;
	column_pos = 0;
	while (*(buffer + (pos_buffer++)) != '\n')
		;
	while (*(buffer + pos_buffer) != '\0')
	{
		if ((*(buffer + pos_buffer) == 'o') || (*(buffer + pos_buffer) == '.'))
			matrix[row_pos][column_pos] = *(buffer + pos_buffer);
		if (*(buffer + pos_buffer++) == '\n')
		{
			++row_pos;
			column_pos = 0;
		}
		else
			++column_pos;
	}
	return (matrix);
}

// char **put_weight_in_matrix(char **matrix, int row_count, int column_count)
// {
// 	int		row_pos;
// 	int		column_pos;

// 	row_count = -1;
// 	column_count = -1;

// 	while ()
// 	return (matrix);
// }

int	main(int argc, char *argv[])
{
	int		row_count;
	int		column_count;
	char	**matrix;
	int		i;
	char	*buffer;

	row_count = -1;
	column_count = 0;
	buffer = (char *)malloc(sizeof(char) * BUFFER_SIZE);
	i = -1;
	if (!argc)
		return (1);
	if (read_file(argv[1], &row_count, &column_count, &buffer) == (-1))
		return (1);
	matrix = (char **)malloc(sizeof(char *) * row_count);
	if (!matrix)
		return (1);
	while (++i < column_count)
	{
		matrix[i] = (char *)malloc(sizeof(char) * column_count);
		if (!(matrix[i]))
			return (1);
	}
	matrix = fill_matrix(matrix, buffer);
	// printf ("Matriz copiada:\n");
	// i = 0;
	// int j;
	// while (i < row_count)
	// {
	// 	j = 0;
	// 	while (j < column_count)
	// 	{
	// 		printf ("%c", matrix[i][j]);
	// 		j++;
	// 	}
	// 	printf ("\n");
	// 	i++;
	// }
	// while (i >= 0)
	// 	free(matrix[--i]);
	// free(matrix);
	return (0);
}
