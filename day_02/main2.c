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
			if (buf[2] == 'Y')
				sum += 3;
			else if (buf[2] == 'Z')
				sum += 6;
			
			if (buf[2] == 'X') {
				if (buf[0] == 'A')
					sum += 3;
				else if (buf[0] == 'B')
					sum += 1;
				if (buf[0] == 'C')
					sum += 2;
			}
			else if (buf[2] == 'Z') {
				if (buf[0] == 'A')
					sum += 2;
				else if (buf[0] == 'B')
					sum += 3;
				if (buf[0] == 'C')
					sum += 1;
			}
			else {
				if (buf[0] == 'A')
					sum += 1;
				else if (buf[0] == 'B')
					sum += 2;
				if (buf[0] == 'C')
					sum += 3;
			}
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

// A = ROCK = 1
// B = PAPER = 2
// C = SCISSORS = 3

// WIN = Z = 6
// DRAW = Y = 3
// LOOSE = X = 0