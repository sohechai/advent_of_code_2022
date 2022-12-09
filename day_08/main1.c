#define BUFFER_SIZE 10000
#define COLUMNS 99
#define ROW 99
# include <stdio.h>
# include <string.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
#include <stdbool.h>     

int		checkRightRow(int **tab, int columns, int row)
{
	int		val = tab[columns][row];
	row++;
	while (row < ROW)
	{
		if (tab[columns][row] >= val) // tree higher than current val
			return (1); // cant see
		row++;
	}
	return (0);
}

int		checkLeftRow(int **tab, int columns, int row)
{
	int		val = tab[columns][row];
	row--;
	while (row >= 0)
	{
		if (tab[columns][row] >= val)
			return (1); // cant see
		row--;
	}
	return (0);
}

int		checkDownColumns(int **tab, int columns, int row)
{
	int		val = tab[columns][row];
	columns++;
	while (columns < COLUMNS)
	{
		if (tab[columns][row] >= val)
			return (1); // cant see
		columns++;
	}
	return (0); // can see
}

int		checkUpColumns(int **tab, int columns, int row)
{
	int		val = tab[columns][row];
	columns--;
	while (columns >= 0)
	{
		if (tab[columns][row] >= val)
			return (1); // cant see
		columns--;
	}
	return (0); // can see
}

int		main (int ac, char **av)
{
	FILE*	file = NULL;
	char	buf[BUFFER_SIZE] = "";
	int		row = ROW;
	int		col = COLUMNS;
	int		x = 0;
	int		y = 0;
	int		tree = 0;
	int		**forest = malloc(sizeof(*forest) * row);
	for (int i = 0; i < col; i++) {
		forest[i] = malloc(sizeof(**forest) * col);
	}
    file = fopen(av[1], "r+");
    if (file != NULL) {
		while (fgets(buf, BUFFER_SIZE, file) != NULL )
		{
			for (int i = 0; buf[i]; i++) {
				forest[x][y] = (int)buf[i] - '0';
				y++;
			}
			y = 0;
			x++;
		}
		fclose(file);
   	} else {
        printf("Impossible d'ouvrir le fichier %s\n", av[1]);
    }

	for(int	x = 0; x < row; x++) {
		for(int y = 0; y < col; y++) {
			if (x == 0 || y == 0 || x == COLUMNS - 1 || y == ROW - 1)
				tree++;
			else if (checkRightRow(forest, x, y) == 0)
				tree++;
			else if (checkLeftRow(forest, x, y) == 0) 
				tree++;
			else if (checkUpColumns(forest, x, y) == 0)
				tree++;
			else if (checkDownColumns(forest, x, y) == 0)
				tree++;
		}
	}

	printf("[%d]\n", tree);

	for (int i = 0; i < col; i++) {
		free(forest[i]);
	}
	free(forest);

    return (0);
}
