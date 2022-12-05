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
	int		first = 0;
	int		second = 0;
	int		third = 0;
    file = fopen(av[1], "r+");
    if (file != NULL)
    {
		while (fgets(buf, BUFFER_SIZE, file) != NULL)
		{	
			if (buf[0] == '\n')
			{
				if (first < sum)
					first = sum;
				sum = 0;
			}
			sum += atoi(buf);
		}
		fclose(file);
		file = fopen(av[1], "r+");
		while (fgets(buf, BUFFER_SIZE, file) != NULL)
		{
			if (buf[0] == '\n')
			{
				if (sum < first && second < sum)
					second = sum;
				sum = 0;
			}
			sum += atoi(buf);
		}
		fclose(file);
		file = fopen(av[1], "r+");
		while (fgets(buf, BUFFER_SIZE, file) != NULL)
		{	
			if (buf[0] == '\n')
			{
				if (sum < second && third < sum)
					third = sum;
				sum = 0;
			}
			sum += atoi(buf);
			printf("%d\n", sum);
		}
		fclose(file);
    }
    else
    {
        printf("Impossible d'ouvrir le fichier %s\n", av[1]);
    }

	printf("first = %d\n", first);
	printf("second = %d\n", second);
	printf("third = %d\n", third);
	printf("total = %d\n", first + second + third);
    return 0;
}

// len = strlen de buf 