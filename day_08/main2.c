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
	int		seen = 0;
	row++;
	while (row < ROW)
	{
		if (tab[columns][row] >= val) // tree higher than current val
			return (seen + 1);
		seen++;
		row++;
	}
	return (seen);
}

int		checkLeftRow(int **tab, int columns, int row)
{
	int		val = tab[columns][row];
	int		seen = 0;
	row--;
	while (row >= 0)
	{
		if (tab[columns][row] >= val)
			return (seen + 1);
		seen++;
		row--;
	}
	return (seen);
}

int		checkDownColumns(int **tab, int columns, int row)
{
	int		val = tab[columns][row];
	int		seen = 0;
	columns++;
	while (columns < COLUMNS)
	{
		if (tab[columns][row] >= val)
			return (seen + 1);
		seen++;
		columns++;
	}
	return (seen);
}

int		checkUpColumns(int **tab, int columns, int row)
{
	int		val = tab[columns][row];
	int		seen = 0;
	columns--;
	while (columns >= 0)
	{
		if (tab[columns][row] >= val)
			return (seen + 1);
		seen++;
		columns--;
	}
	return (seen);
}

int		main (int ac, char **av)
{
	FILE*	file = NULL;
	char	buf[BUFFER_SIZE] = "";
	int		row = ROW;
	int		col = COLUMNS;
	int		x = 0;
	int		y = 0;
	int		scenicScore = 1;
	int		maxScore = 0;

	int		**forest = malloc(sizeof(*forest) * row + 1);
	for (int i = 0; i < col; i++) {
		forest[i] = malloc(sizeof(**forest) * col + 1);
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
				scenicScore *= checkRightRow(forest, x, y);
				scenicScore *= checkLeftRow(forest, x, y);
				scenicScore *= checkUpColumns(forest, x, y);
				scenicScore *= checkDownColumns(forest, x, y);
			if (maxScore < scenicScore)
				maxScore = scenicScore;
			scenicScore = 1;
		}
	}

	printf("max score = [%d]\n", maxScore);

	for (int i = 0; i < col; i++) {
		free(forest[i]);
	}
	free(forest);

    return (0);
}
