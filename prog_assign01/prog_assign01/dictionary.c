#pragma warning (disable:4996)
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#define buffer_len 30
#define Arr_size 200000

int size=0;
char *dictionary[Arr_size];

void read(char *s);
int read_line(FILE * fp, char str[], int n);
int find();
void upper_lower(char *s);

int main() {
	char command_line[buffer_len];
	char *cmd, *arg;

	while (1) {
		printf("$ ");
		if (read_line(stdin, command_line, buffer_len) <= 0)
			continue;
		cmd = strtok(command_line, " ");
		if (strcmp(cmd, "read") == 0) {
			arg = strtok(NULL, " ");
			if (arg == NULL) continue;
			read(arg);
		}
		else if (strcmp(cmd, "size") == 0)
			printf("%d\n\n", size);
		else if (strcmp(cmd, "exit") == 0)
			exit(1);
		else if (strcmp(cmd, "find") == 0) {
			arg = strtok(NULL, " ");
			find(arg, 0, size-1);
		}
		else printf("Command do not exist.\n\n");
	}
}

int read_line(FILE * fp, char str[], int n)
{
	int ch, i = 0;
	while ((ch = fgetc(fp)) != '\n' && ch != EOF)
		if (i < n)
			str[i++] = ch;
	str[i] = '\0';
	return i;
}

void read(char *s) {
	FILE *fp;
	char buffer[3000];
	int i = 0;

	fp = fopen(s, "r");
	if (fp == NULL) {
		printf("Error!\n\n");
		exit(1);
	}
	else
		printf("File loaded.\n\n");

	while (!feof(fp)) {
		read_line(fp, buffer, 3000);
		if (strcmp(_strdup(buffer),"")==0) continue;
		else {
			dictionary[i] = _strdup(buffer);
			size++;
			i++;
		}
	}
	fclose(fp);
}

int find(char *target, int start, int end) {
	int middle = (start + end) / 2;
	char word[20];
	int i = 0, count = 0;

	upper_lower(target);

	while (dictionary[middle][i] != ' ') {
		word[i] = dictionary[middle][i];
		i++;
	}
	word[i] = '\0';
	i = 0;

	if (start > end) { //찾는 단어가 없음
		char prev[30];
		char next[30];
		int k = 0;

		while (dictionary[middle][k] != ')') {
			prev[k] = dictionary[middle][k];
			k++;
		}
		prev[k] = ')';
		prev[k+1] = '\0';
		k = 0;

		while (dictionary[middle+1][k] != ')') {
			next[k] = dictionary[middle+1][k];
			k++;
		}
		next[k] = ')';
		next[k+1] = '\0';

		printf("Not found.\n");
		printf("%s\n- - -\n", prev);
		printf("%s\n\n", next);

		if(middle>0)
			return middle;
		else return -1;
	}
	if (strcmp(target, word)<0) {
		return find(target, start, middle-1);
	}
	else if (strcmp(target, word) == 0) {
		while (strcmp(target, word) == 0) {
			count++;
			while (dictionary[middle+count][i] != ' ') {
				word[i] = dictionary[middle+count][i];
				i++;
			}
			word[i] = '\0';
			i = 0;
		}
		printf("Found %d items.\n", count);
		for (int j = 0; j < count; j++) {
			printf("%s\n", dictionary[middle+j]);
		}
		printf("\n");
		return middle;
	}
	else {
		return find(target, middle+1, end);
	}
}

void upper_lower(char *s){
	int i = 1;
	char buffer[20];
	if (islower(s[0])) buffer[0] = s[0] - 32;
	else buffer[0] = s[0];
	while (s[i] != '\0') {
		if (isupper(s[i])) buffer[i] = s[i] + 32;
		else buffer[i] = s[i];
		i++;
	}
	buffer[i] = '\0';
	strcpy(s, buffer);
}