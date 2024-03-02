#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct {
	char **array;
	size_t size;
	size_t used;
} CharArray;

void char_array_init(CharArray *ca, size_t initial_size) {
	ca->array = malloc(initial_size * sizeof(char *));
	ca->size = initial_size;
	ca->used = 0;
}

void char_array_insert(CharArray *ca, char *element) {
	if (ca->used == ca->size) {
		ca->size *= 2;
		ca->array = realloc(ca->array, ca->size * sizeof(char *));
	}
	ca->array[ca->used] = malloc(strlen(element) + 1);
	strcpy(ca->array[ca->used], element);
	ca->used++;
}

void char_array_cleanup(CharArray *ca) {
	for (size_t i = 0; i < ca-> used; i++) {
		free(ca->array[i]);
	}
	free(ca->array);
}

int main() {
	printf("hello world !\n");

	FILE *fp = fopen("test-file.txt", "r");
	if (fp == NULL) {
		printf("could not open file\n");
		return 1;
	}

	CharArray lines;
	char_array_init(&lines, 1);

	char buffer[512];
	while (fgets(buffer, 512, fp)) {
		char_array_insert(&lines, buffer);
	}
	
	fclose(fp);

	for (size_t i = 0; i < lines.used; i++) {
		printf("%s", lines.array[i]);
	}

	char_array_cleanup(&lines);
	return 0;
}
