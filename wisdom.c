/* Copyright (C) 2025 therealblue24 under the MIT license */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

static size_t count_lines(FILE *f)
{
	rewind(f);
	size_t lines = 0;
	while(!feof(f)) {
		lines += (fgetc(f) == '\n');
	}
	return lines;
}

static void print_line(FILE *f, size_t line)
{
	rewind(f);
	size_t lines_cur = 0;
	while(!feof(f) && lines_cur != line) {
		lines_cur += (fgetc(f) == '\n');
	}
	int c = fgetc(f);
	do {
		putchar(c);
	} while((c = fgetc(f)) != '\n');
	return;
}

int main(int argc, char *argv[])
{
	(void)argc;
	(void)argv;

	/* execute for random amount of time */

	volatile uint64_t counter = 1 + clock();

	for(int i = 0; i < 100; i++) {
		counter *= counter + 1;
		if(counter & 1) {
			counter >>= 1;
		} else {
			counter = (counter * 3) + 1;
		}
	}

	srand(time(NULL) + clock() + counter);

	FILE *wisdom = fopen("wisdomfile", "r");
	size_t lines = count_lines(wisdom);
	size_t line_to_print = rand() % lines;
	print_line(wisdom, line_to_print);
	putchar('\n');

	fclose(wisdom);
	return 0;
}
