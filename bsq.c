/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bsq.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxgarci <maxgarci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/24 13:28:41 by maxgarci          #+#    #+#             */
/*   Updated: 2023/07/24 18:49:59 by maxgarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define BUFFER_SIZE 2048

struct	s_pos
{
	int	row_pos;
	int	column_pos;
};

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

void	write_x_matrix(char **matrix, int weigth, s_pos pos)
{
	
}

// char	**put_weight_in_matrix(char **matrix, struct s_pos *obstacles_dictionary, int row_count, int column_count)
// {
// 	int	row_pos;
// 	int	column_pos;
	
// 	row_pos = -1;
// 	column_pos = -1;
// 	return (matrix);
// }

struct s_pos *put_obstacles(char **matrix, struct s_pos *obstacles_dictionary, int row_count, int column_count)
{
	int	row_pos;
	int	column_pos;
	int	it;
	
	column_pos = -1;
	it = 0;
	while (++column_pos < column_count)
	{
		row_pos = -1;
		while (++row_pos < row_count)
		{
			if (matrix[row_pos][column_pos] == 'o')
			{
				obstacles_dictionary[it].column_pos = column_pos;
				obstacles_dictionary[it].row_pos = row_pos;
				it++;
			}
		}
	}
	obstacles_dictionary[it].column_pos = -1;
	obstacles_dictionary[it].row_pos = -1;
	return (obstacles_dictionary);
}

int	algorithm(int row_count, int column_count, char *buffer)
{
	char			**matrix;
	int				i;
	struct s_pos	*obstacles_dictionary;

	i = -1;
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
	obstacles_dictionary = (struct s_pos *)malloc(sizeof(struct s_pos) * row_count * column_count);
	if (!obstacles_dictionary)
		return (1);
	obstacles_dictionary = put_obstacles(matrix, obstacles_dictionary, row_count, column_count);
	int j = 0;
	while (obstacles_dictionary[j].column_pos != -1)
	{
		printf("\n%d %d\n", obstacles_dictionary[j].row_pos, obstacles_dictionary[j].column_pos);
		j++;
	}
	i = 0;
	while (i < row_count)
	{
		j = 0;
		while (j < column_count)
		{
			printf ("%c", matrix[i][j]);
			j++;
		}
		printf ("\n");
		i++;
	}
	//matrix = put_weight_in_matrix(matrix, obstacles_dictionary, row_count, column_count);
	return (0);
}

int	main(int argc, char *argv[])
{
	int		row_count;
	int		column_count;
	char	*buffer;

	row_count = -1;
	column_count = 0;
	buffer = (char *)malloc(sizeof(char) * BUFFER_SIZE);
	if (!argc)
		return (1);
	if (read_file(argv[1], &row_count, &column_count, &buffer) == (-1))
		return (1);
	if (algorithm(row_count, column_count, buffer))
		return (1);
	return (0);
}
