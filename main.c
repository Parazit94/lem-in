#include "./libft/includes/libft.h"
#include <fcntl.h>

int		main(int argc, char **argv)
{
	int	d1;
	int	d2;
	char	*line1;
	char	*line2;
	int		a;
	int		b;

	if (argc == 3)
	{
		d1 = open(argv[1], O_RDONLY);
		d2 = open(argv[2], O_RDONLY);
		while (1)
		{
			if ((a = get_next_line(d1, &line1) <= 0) || (b = get_next_line(d2, &line2) <= 0))
			{
				ft_printf("end d1 = %d, d2 = %d\n%s\n%s\n", a, b, line1, line2);
				return (0);
			}
			else if (ft_strcmp(line1, line2) != 0)
			{
				ft_printf("d1: %s\nd2: %s\n", line1, line2);
				return (0);
			}
			// ft_strdel(&line1);
			// ft_strdel(&line2);
		}
	}
	return (0);
}