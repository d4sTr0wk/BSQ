#ifndef BSQ_READFILE_FUNCTIONS_H
# define BSQ_READFILE_FUNCTIONS_H

#include "bsq.h"

struct s_param;

int	ft_atoi(char *str, int pos);
struct s_param	attributes(char *buffer);
int long_lines(char *buffer, struct s_param *params, int *pos, int i);
int	valid_map(char *buffer, struct s_param *params, int row_count);

#endif