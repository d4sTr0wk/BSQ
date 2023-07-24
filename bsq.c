/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bsq.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxgarci <maxgarci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/24 13:28:41 by maxgarci          #+#    #+#             */
/*   Updated: 2023/07/25 00:26:08 by maxgarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define BUFFER_SIZE 2147483647

struct			s_pos
{
	int			row_pos;
	int			column_pos;
};

void	print_matrix(char **matrix, int row_count, int column_count)
{
	int i;
	
	printf ("Matriz copiada:\n");
	i = 0;
	int j;
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
}

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

struct s_pos find_c_obs(int column_pos, int row_pos, struct s_pos *obs_dic)
{
	int	it;
	int found;
	struct s_pos obs_pos;

	it = -1;
	found = 0;
	obs_pos.column_pos = -1;
	obs_pos.row_pos = -1;
	while (!found && obs_dic[++it].column_pos != -1)
	{
		if (obs_dic[it].column_pos == column_pos && obs_dic[it].row_pos >= row_pos)
		{
			found = 1;
			obs_pos.column_pos = obs_dic[it].column_pos;
			obs_pos.row_pos = obs_dic[it].row_pos;
		}
	}
	return (obs_pos);
}

void	calc_weight(char **m, struct s_pos *obs_dic, int rc, int cc, struct s_pos res_p)
{
	int	row_pos;
	int	column_pos;
	int	greater_weight;
	int	candidate_weight;
	struct s_pos obs_pos;
	
	greater_weight = 0;
	row_pos = -1;
	column_pos = -1;
	while (++column_pos < cc)
	{
		row_pos = -1;
		while (++row_pos < rc)
		{
			if (m[row_pos][column_pos] != 'o')
			{
				obs_pos = find_c_obs(column_pos, row_pos, obs_dic);
				if (obs_pos.column_pos == -1)
					candidate_weight = rc - row_pos;
				else
					candidate_weight = obs_pos.row_pos - row_pos;
				if (greater_weight < candidate_weight)
				{
					int it;
					
					it = column_pos + 1;
					while (candidate_weight >= (it - column_pos + 1) && it < cc)
					{
						obs_pos = find_c_obs(it, row_pos, obs_dic);
						if ((obs_pos.row_pos != -1) && ((obs_pos.row_pos - row_pos) < candidate_weight))
							candidate_weight = obs_pos.row_pos - row_pos;
						it++;
					}
					if (candidate_weight > greater_weight && (it - column_pos) == candidate_weight && (((obs_pos.row_pos - row_pos) >= candidate_weight) || (obs_pos.row_pos == -1)))
					{
						greater_weight = candidate_weight;
						res_p.column_pos = column_pos;
						res_p.row_pos = row_pos;
					}
					else
					{
						candidate_weight = obs_pos.column_pos - column_pos;
						if (greater_weight < candidate_weight)
						{
							greater_weight = candidate_weight;
							res_p.column_pos = column_pos;
							res_p.row_pos = row_pos;
						}
					}
				}
			}
		}
	}
	//printf("weight: %d, row: %d, column: %d", greater_weight, res_p.row_pos, res_p.column_pos);
	printf("rc: %d, cc: %d\n", rc, cc);
	print_matrix(write_x_in_matrix(m, greater_weight, res_p), rc, cc);	
}

struct s_pos	*put_obstacles(char **matrix, struct s_pos *obs_dic, int rcnt, int ccnt)
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
	struct s_pos	res_p;

	i = -1;
	res_p.column_pos = -1;
	res_p.row_pos = -1;
	matrix = (char **)malloc(sizeof(char *) * rcnt);
	if (!matrix)
		return (1);
	while (++i < ccnt)
	{
		matrix[i] = (char *)malloc(sizeof(char) * ccnt);
		if (!(matrix[i]))
			return (1);
	}
	matrix = fill_matrix(matrix, buffer, rcnt);
	obs_dic = (struct s_pos *)malloc(sizeof(struct s_pos) * rcnt * ccnt);
	if (!obs_dic)
		return (1);
	obs_dic = put_obstacles(matrix, obs_dic, rcnt, ccnt);
	calc_weight(matrix, obs_dic, rcnt, ccnt, res_p);
	return (0);
}

int	main(int argc, char *argv[])
{
	int		row_count;
	int		column_count;
	int		cont;
	char	*buffer;

	cont = 1;
	// argc = 2;
	// argv[1] = "example5_file";
	buffer = (char *)malloc(sizeof(char) * BUFFER_SIZE);
	if (!argc)
		return (1);
	while (cont < argc)
	{	
		row_count = -1;
		column_count = 0;
		if (read_file(argv[cont], &row_count, &column_count, &buffer) == (-1))
			return (1);
		if (algorithm(row_count, column_count, buffer))
			return (1);
		write(1, "\n", 1);
		cont++;
	}
	return (0);
}
