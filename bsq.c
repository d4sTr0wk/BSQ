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

#include "bsq.h"

char	**ft_stdin(char **argv, int *argc)
{
	*argc = 2;
	argv[1] = 0;
	return (argv);
}

int	read_file(char *file_name, struct s_pos *counter, char **buffer,
		struct s_param *params)
{
	int	file;
	int	i;
	int	len;

	file = ft_file(file_name, &len, buffer);
	if (file == -1)
		return (-1);
	i = -1;
	*params = attributes(*buffer);
	if (params->num_lines == -1)
		return (-2);
	while (++i < len)
	{
		if (*(*buffer + i) == '\n')
			(counter->rp)++;
		else if (!counter->rp)
			counter->cp++;
	}
	if (!valid_map(*buffer, params, counter->rp))
		return (-2);
	if (close(file) == -1 && *file_name != '0')
		return (-1);
	return (0);
}

int	algorithm(struct s_pos counter, char *buffer, struct s_param params, int i)
{
	char			**matrix;
	struct s_pos	*obs_dic;
	struct s_pos	res_p;

	res_p.cp = -1;
	res_p.rp = -1;
	matrix = (char **)malloc(sizeof(char *) * (counter.rp));
	if (matrix == NULL)
		return (1);
	while (++i < counter.rp)
	{
		matrix[i] = (char *)malloc(sizeof(char) * (counter.cp));
		if (matrix[i] == NULL)
			return (1);
	}
	matrix = fill_matrix(matrix, buffer, counter.rp, params);
	obs_dic = (struct s_pos *)malloc(sizeof(struct s_pos) * (counter.rp)
			* (counter.cp));
	if (!obs_dic)
		return (1);
	obs_dic = put_obstacles(matrix, obs_dic, counter, params);
	calc_weight(matrix, obs_dic, counter, res_p, params);
	free_mat(matrix, obs_dic, counter.rp);
	return (0);
}

struct s_all	ini(struct s_all types, char **argv, int *ok)
{
	types.counter.rp = -1;
	types.counter.cp = 0;
	types.error = read_file(argv[types.cont], &types.counter, &types.buffer,
			&types.params);
	if (types.error == (-1))
		*ok = 1;
	else if (types.error == (-2))
	{
		write(2, "map error\n", 11);
		*ok = 1;
	}
	return (types);
}

int	main(int argc, char *argv[])
{
	struct s_all	types;
	int				ok;

	ok = 0;
	types.cont = 1;
	types.buffer = (char *)malloc(sizeof(char) * BUFFER_SIZE);
	if (types.buffer == NULL)
		return (1);
	if (!argc)
		return (1);
	if (argc == 1)
		argv = ft_stdin(argv, &argc);
	while (types.cont < argc)
	{
		types = ini(types, argv, &ok);
		if (ok)
			return (1);
		if (algorithm(types.counter, types.buffer, types.params, -1))
			return (1);
		write(1, "\n", 1);
		types.cont++;
	}
	free(types.buffer);
	return (0);
}
