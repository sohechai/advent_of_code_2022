#define BUFFER_SIZE 10000 // Tableau de taille 1000
#include <stdio.h>
# include <string.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>

int main (int ac, char **av)
{
	FILE*	file = NULL;
	char	buf[BUFFER_SIZE] = "";
	int		sum = 0;

    file = fopen(av[1], "r+");
    if (file != NULL)
    {
		while (fgets(buf, BUFFER_SIZE, file) != NULL)
		{
			if ((buf[0] == 'C' && buf[2] == 'X') || (buf[0] == 'A' && buf[2] == 'Y') || (buf[0] == 'B' && buf[2] == 'Z')) // win
				sum += 6;
			else if ((buf[0] == 'A' && buf[2] == 'X') || (buf[0] == 'B' && buf[2] == 'Y') || (buf[0] == 'C' && buf[2] == 'Z')) // draw
				sum += 3;
			if (buf[2] == 'X')
				sum += 1;
			else if (buf[2] == 'Y')
				sum += 2;
			else if (buf[2] == 'Z')
				sum += 3;
		}
		fclose(file);
    }
    else
    {
        printf("Impossible d'ouvrir le fichier %s\n", av[1]);
    }
	
	printf("sum = %d\n", sum);
    return 0;
}

// A X = ROCK = 1
// B Y = PAPER = 2
// C Z = SCISSORS = 3

// WIN = 6
// DRAW = 3
// LOOSE = 0