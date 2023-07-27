#include "bsq.h"

char    **ft_stdin(char **argv, int *argc)
{
    *argc = 2;
    argv[1] = 0;
    return (argv);
}

int read_file(char *file_name, struct s_pos *counter,
	char **buffer, struct s_param *params)
{
    int file;
    int i;
    int len;
    if (file_name != 0)
    {
        file = open(file_name, O_RDONLY);
        if (file == -1)
            return (-1);
    }
    else
        file = 0;
    len = read(file, *buffer, BUFFER_SIZE);
    if (len == -1)
    {
        close(file);
        return (-1);
    }
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

int	algorithm(struct s_pos counter, char *buffer, struct s_param params)
{
	char			**matrix;
	int				i;
	struct s_pos	*obs_dic;
	struct s_pos	res_p;

	i = -1;
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
	obs_dic = (struct s_pos *)malloc(sizeof(struct s_pos) * (counter.rp) * (counter.cp));
	if (!obs_dic)
		return (1);
	obs_dic = put_obstacles(matrix, obs_dic, counter, params);
	calc_weight(matrix, obs_dic, counter, res_p, params);
	free_mat(matrix, obs_dic, counter.rp);
	return (0);
}

int	main(int argc, char *argv[])
{
	struct s_pos	counter;
	int				cont;
	int				error;
	char			*buffer;
	struct s_param	params;

	cont = 1;
	buffer = (char *)malloc(sizeof(char) * BUFFER_SIZE);
	if (buffer == NULL)
		return (1);
	if (!argc)
		return (1);
	if (argc == 1)
        argv = ft_stdin(argv, &argc);
	while (cont < argc)
	{
		counter.rp = -1;
		counter.cp = 0;
		error = read_file(argv[cont], &counter, &buffer,
				&params);
		if (error == (-1))
			return (1);
		else if (error == (-2))
		{
			write(2, "map error\n", 11);
			return (1);
		}
		if (algorithm(counter, buffer, params))
			return (1);
		write(1, "\n", 1);
		cont++;
	}
	free(buffer);
	return (0);
}
