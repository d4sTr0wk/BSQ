#ifndef BSQ_H
# define BSQ_H

# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include "bsq_algorithm_functions.h"
# include "bsq_calcweight_functions.h"
# include "bsq_readfile_functions.h"

#define BUFFER_SIZE 2147483647

struct			s_pos
{
	int			row_pos;
	int			column_pos;
};

struct			s_param
{
	int			num_lines;
	char		empty;
	char		obs;
	char		fill;
};

int	main(int argc, char *argv[]);
int	algorithm(int rcnt, int ccnt, char *buffer, struct s_param params);
int	read_file(char *file, int *rc, int *cc, char **buffer, struct s_param *p);

#endif
