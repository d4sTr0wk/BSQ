#ifndef BSQ_H
# define BSQ_H

# include <fcntl.h>
# include <stdlib.h>
# include <unistd.h>
# include "bsq_algorithm_functions.h"
# include "bsq_calcweight_functions.h"
# include "bsq_readfile_functions.h"

#define BUFFER_SIZE 2147483647

struct			s_pos
{
	int			rp;
	int			cp;
};

struct			s_param
{
	int			num_lines;
	char		empty;
	char		obs;
	char		fill;
};

int	main(int argc, char *argv[]);
int	algorithm(struct s_pos counter, char *buffer, struct s_param params);
int	read_file(char *file, struct s_pos *counter, char **buffer, struct s_param *p);

#endif
