#include <stdio.h>
#include <glob.h>

// run like...
// gcc -o glob glob.c
// ./glob *.c
int main(int argc, char *argv[]) {

	int i;
	glob_t	g;

	switch(glob(argv[1], NULL, NULL, &g)) {
		case GLOB_NOSPACE:
			printf("ran out of memory\n");
			break;
		case GLOB_ABORTED:
			printf("read error\n");
			break;
		case GLOB_NOMATCH:
			printf("no matches found\n");
			break;
		default:
			for(i=0; i<g.gl_pathc; i++) {
				printf("%s\n", g.gl_pathv[i]);
			}
	}

}