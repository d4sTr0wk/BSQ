/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bsq3.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouhaik <ybouhaik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 20:31:39 by ybouhaik          #+#    #+#             */
/*   Updated: 2023/07/25 20:42:54 by ybouhaik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

struct	s_pos
{
	int	row_pos;
	int	column_pos;
};

struct s_param
{
	int num_lines;
	char empty;
	char obs;
	char fill;
};

// int	check_matrix(char **matrix, struct s_param params, char *buffer)
// {

// }

void	print_matrix(char **matrix, int row_count, int column_count)
{
	int	i;
	int	j;

	i = 0;
	while (i < row_count)
	{
		j = 0;
		while (j < column_count)
		{
			write(1, &(matrix[i][j]), 1);
			j++;
		}
		write(1, "\n", 1);
		i++;
	}
}

char	**write_x_in_matrix(char **matrix, int weigth, struct s_pos pos)
{
	int	row_pos;
	int	column_pos;

	column_pos = pos.column_pos;
	while (column_pos < pos.column_pos + weigth)
	{
		row_pos = pos.row_pos;
		while (row_pos < pos.row_pos + weigth)
		{
			matrix[row_pos][column_pos] = 'x';
			row_pos++;
		}
		column_pos++;
	}
	return (matrix);
}

char	**fill_matrix(char **matrix, char *buffer, int rcnt)
{
	int	row_pos;
	int	column_pos;
	int	pos_buffer;

	pos_buffer = 0;
	row_pos = 0;
	column_pos = 0;
	while (*(buffer + (pos_buffer++)) != '\n')
		;
	while (*(buffer + pos_buffer) != '\0' && row_pos != rcnt)
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
