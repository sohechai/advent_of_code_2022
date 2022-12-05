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
	int		max = 0;
    file = fopen(av[1], "r+");
    if (file != NULL)
    {
		while (fgets(buf, BUFFER_SIZE, file) != NULL)
		{	
			if (buf[0] == '\n')
			{
				if (max < sum)
					max = sum;
				sum = 0;
			}
			sum += atoi(buf);
		}
		fclose(file);
    }
    else
    {
        printf("Impossible d'ouvrir le fichier %s\n", av[1]);
    }
	
	printf("max = %d\n", max);
    return 0;
}

// len = strlen de buf 