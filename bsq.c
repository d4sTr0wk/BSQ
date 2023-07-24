/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bsq.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouhaik <ybouhaik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/24 13:28:41 by maxgarci          #+#    #+#             */
/*   Updated: 2023/07/24 19:52:30 by ybouhaik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define BUFFER_SIZE 2048

struct			s_pos
{
	int			row_pos;
	int			column_pos;
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

// char	**put_weight_in_matrix(char **matrix, struct s_pos *obs_dic,
//		int row_count, int column_count)
// {
// 	int	row_pos;
// 	int	column_pos;

// 	row_pos = -1;
// 	column_pos = -1;
// 	return (matrix);
// }

struct s_pos	*put_obstacles(char **matrix, struct s_pos *obs_dic, int rcnt,
		int ccnt)
{
	int	row_pos;
	int	column_pos;
	int	it;

	column_pos = -1;
	it = 0;
	while (++column_pos < ccnt)
	{
		row_pos = -1;
		while (++row_pos < rcnt)
		{
			if (matrix[row_pos][column_pos] == 'o')
			{
				obs_dic[it].column_pos = column_pos;
				obs_dic[it].row_pos = row_pos;
				it++;
			}
		}
	}
	obs_dic[it].column_pos = -1;
	obs_dic[it].row_pos = -1;
	return (obs_dic);
}

int	algorithm(int rcnt, int ccnt, char *buffer)
{
	char			**matrix;
	int				i;
	struct s_pos	*obs_dic;

	i = -1;
	matrix = (char **)malloc(sizeof(char *) * rcnt);
	if (!matrix)
		return (1);
	while (++i < ccnt)
	{
		matrix[i] = (char *)malloc(sizeof(char) * ccnt);
		if (!(matrix[i]))
			return (1);
	}
	matrix = fill_matrix(matrix, buffer);
	obs_dic = (struct s_pos *)malloc(sizeof(struct s_pos) * rcnt * ccnt);
	if (!obs_dic)
		return (1);
	obs_dic = put_obstacles(matrix, obs_dic, rcnt, ccnt);
	matrix = put_weight_in_matrix(matrix, obs_dic, rcnt, ccnt);
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
