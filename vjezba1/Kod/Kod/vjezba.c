#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#define N 20


typedef struct{
	char name[N];
	char surname[N];
	int points;
} Student;

int countStudents();
int loadStudents(Student *student, int total);
int outputStudents(Student* student, int total);

int main() {
	int total;
	Student *student;

	total = countStudents();
	if (total == 0) { return 0; }
	student = (Student*)malloc(total * sizeof(Student));
	loadStudents(student, total);
	outputStudents(student, total);

	free(student);
	return 0;
}

int countStudents() {
	int br = 0;
	char c;
	FILE* file;
	file = fopen("C:/Users/Marko - Faks/Desktop/strukture/vjezbe i ostalo/vjezba1/studenti.txt", "r");
	
	if (file == NULL) {
		puts("Datoteka studenti.txt ne moze se otvoriti.");
		return 0;
	}
	while ((c = fgetc(file)) != EOF) {
		if (c == '\n') {
			br++;
		}
	}
	
	fclose(file);
	return br;
}
int loadStudents(Student *student, int total) {
	FILE* file;
	file = fopen("C:/Users/Marko - Faks/Desktop/strukture/vjezbe i ostalo/vjezba1/studenti.txt", "r");

	if (file == NULL) {
		puts("Datoteka studenti.txt ne moze se otvoriti.");
		return 0;
	}

	for (int i = 0; i < total; i++) {
		fscanf(file, "%s %s %d", student[i].name, student[i].surname, &student[i].points);
	}


	fclose(file);
	return 0;
}
int outputStudents(Student* student, int total) {
	int max = 0;
	for (int i = 0; i < total; i++) {
		if (max < student[i].points) {
			max = student[i].points;
		}
	}

	puts("Ime\tPrezime\tAps\tRel\n");
	for (int i = 0; i < total; i++) {
		printf("%s\t%s\t%d\t%.2f\n", student[i].name, student[i].surname, student[i].points, (float)student[i].points/max*100);
	}
	return 0;
}