#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv)
{	
	if (argc < 2 || argc > 4) {
		printf("Please give correct amount of arguments\n");
	} else {
		int start = 0, end = 0, step = 1;
		switch (argc)
		{
			case 2:
	        	end = atoi(argv[1]);
				break;
			case 3:
				start = atoi(argv[1]);
				end = atoi(argv[2]);
				break;
			case 4:
				start = atoi(argv[1]);
				end = atoi(argv[2]);
				step = atoi(argv[3]);
				break;
		}
		if ((start - end) * step > 0 ) {
			printf("Please give correct step value\n");
		} else {
			for (int i = start; i < end; i += step) {
				printf("%d\n", i);
			}
		}
	}
	return 0;
}
