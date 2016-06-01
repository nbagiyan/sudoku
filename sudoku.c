#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <malloc.h>
#include <string.h>
#include "sudoku.h"

/*
void openlevel(const char* filename) - функция открытия уровня
Входные значения: const char* filename - имя файла, где хранится уровень
*/

void openlevel(const char* filename);

/*
int* OpenMatrix(const char* filename) - функция создания двумерного динамического массива, который используется, как игровое поля
Входные значения: const char* filename - имя файла, где хранится уровень
Возвращаемое значение - указатель на указатель на первый жлемент двумерного массива
Входные значения: const char* filename - имя файла, где хранится уровень
*/
int* OpenMatrix(const char* filename);

/*
void fillin() - функция для заполнения уровня, доступна только разработчику
Входные значения: нет
Возвращаемое значение: нет
*/
void fiilin();


/*
void printlevel(int rows, int columns, int** matrix) - функция для вывода поля на экран
Входные значения: int rows - количество строк(9)
int columns - количество столбцов(9)
int** matrix -адрес 1 элемента двумерного массива
Возвращаемое значение: нет
*/
void printlevel(int rows, int columns, int** matrix);

/*
int checklevel(int** matrix); - функция проверки пройденной игры
Входные значение:
int** matrix -адрес 1 элемента двумерного массива
Возвращаемое значение: 0 - если уровень пройден
*/
int checklevel(int** matrix);

/*
int isAvailable(int** matrix, int coord1, int coord2) - функция проверки пройденной игры
Входные значение:
int** matrix -адрес 1 элемента двумерного массива
int coord1 - номер строчки куда нужно ставить число
int coord2 - номер столбца куда нужно ставить число
Возвращаемое значение: 0 - если уровень пройден
1 - в обратном случае
*/
int isAvailable(int** matrix, int coord1, int coord2);

/*
void printtask(const char* name, const char surname) - функция, которая приветствует игрока и объясняет правила игры
Входные значение:
const char* name - указатель на массив символов с именем игрока 
const char* surname - указатель на массив символов с именем игрока 
Возвращаемое значение: нет
*/
void printtask(const char* name, const char surname);

/*
void fillavalibale(int** matrix); - функция, которая проходит по матрице и резервирует начальные поля
Входные значение:
const char* name - указатель на массив символов с именем игрока 
const char* name - указатель на массив символов с именем игрока 
Возвращаемое значение: нет
*/
void fillavalibale(int** matrix);

/*
void checkplayer(const char* name, const char* surname) -функция которая проверяет наличие предыдущих игр у игрока
Входные данные:
const char* name - указатель на массив символов с именем игрока 
const char* name - указатель на массив символов с именем игрока 
Возвращаемое значение: нет
*/
void checkplayer(const char* name, const char* surname);

/*
void addwin(const char* name, const char* surname) - функция, которая доьавляет количество побед и игр игроку
Входные данные:
const char* name - указатель на массив символов с именем игрока 
const char* name - указатель на массив символов с именем игрока 
Возвращаемое значение: нет
*/
void addwin(const char* name, const char* surname);
int* main() {
	int a = 0;
	char name[20], surname[20];
	setlocale(LC_ALL, "rus");
	printf("Введите свое имя и фамилию:\n");
	scanf("%s", name);
	scanf("%s", surname);
	//fiilin();
	checkplayer(name, surname);
	printtask(name, surname);
	printf("Выберите уровень сложности с 1 - 6: \n");
	scanf("%d", &a);
	printf("\n\n");
	printf("\n\n");
	while (a) {
		switch (a) {
		case 1:{
			openlevel("lvl1");
			addwin(name, surname);
			break;
		}
		case 2: {
			openlevel("lvl2");
			addwin(name, surname);
			break;
		}
		case 3: {
			openlevel("lvl3");
			addwin(name, surname);
			break;
		}
		case 4: {
			openlevel("lvl4");
			addwin(name, surname);
			break;
		}
		case 5: {
			openlevel("lvl5");
			addwin(name, surname);
			break;
		}
		case 6: {
			openlevel("lvl6");
			addwin(name, surname);
			break;
		}
		case 0: {
			return 2;
		}
		}
		printf("Если захотите завершить игру нажмите 0. Выберите уровень сложности с 1 - 6: \n");
		scanf("%d", &a);
	}
	return 0;
}


void openlevel(const char* filename) {
	int* field;
	int** matrix;
	int number, coord1, coord2, i;
	field = OpenMatrix(filename);
	printlevel(10, 10, field);
	matrix = (int**)malloc(11*sizeof(int*));
	for (i = 0; i < 11; i++)
	{
		matrix[i] = (int*)malloc(11*sizeof(int));
	}
	matrix = field;
	fillavalibale(matrix);
	printf("Если захотите выйти из игры введите три числа: 13 13 13\n\n\n");
	while (checklevel(field)) {
		printf("Введите координаты, а затем цифру, которую нужно вставить: ");
		scanf("%d", &coord1);
		scanf("%d", &coord2);
		scanf("%d", &number);
		while (coord1 < 1 || coord1 > 9 || coord2 < 1 || coord2 > 9 || number > 9) {
			printf("Цифра должна находиться в диапазоне от 1 до 9. Повторите ввод!\n ");
			printf("Введите координаты, а затем цифру, которую нужно вставить:");
			scanf("%d", &coord1);
			scanf("%d", &coord2);
			scanf("%d", &number);
		}
		if (coord1 == 13 && coord2 == 13 && number == 13) {
			printf("Вы слабое звено. Прощайте\n");
			return;
		}
		printf("\n");
		if (isAvailable(matrix, coord1, coord2)){
			matrix[coord1][coord2] = number;
			printlevel(10, 10, matrix);
		}
		else {
			printf("Нельзя ставить цифру на поле, где уже она есть!\n");
			printf("Введите координаты, а затем цифру, которую нужно вставить:");
			scanf("%d", &coord1);
			scanf("%d", &coord2);
			scanf("%d", &number);
		}
	}
	for (i = 0; i<11; i++)
		free(matrix[i]);
	free(matrix);
	printf("Поздравляем! Вы прошли %s!\n", filename);
	return;
}

int* OpenMatrix(const char* filename){
	int i, j, rows, columns,buf = 0;
	int** matrix;
	FILE* fp;
	rows = 12;
	columns = 12;
	matrix = (int**)malloc(rows*sizeof(int*));
	for (i = 0; i < rows; i++)
	{
		matrix[i] = (int*)malloc(columns*sizeof(int));
	}
	if ((fp = fopen(filename, "rb+")) == NULL) {
		printf("Ошибка открытия файла \n");
	}
	for (i = 1; i < 10; i++){
		for (j = 1; j < 10; j++){
			fread(&buf, sizeof(int), 1, fp);
			matrix[i][j] = buf;
		}
	}
	for (j = 1; j < 10; j++){
		matrix[0][j] = j;
	}
	for (i = 1; i < 10; i++){
		matrix[i][0] = i;
	}
	return matrix;
}


/*void fiilin() {
	FILE* fp;
	int temp = 0, i = 0;
	if ((fp = fopen("lvl6", "wb+")) == NULL) {
		printf("Ошибка открытия файла \n");
	}
		for (i = 1; i <= 81; i++) {
			scanf("%d", &temp);
			fwrite(&temp, sizeof(int), 1, fp);
		}
	fclose(fp);
}*/

void printlevel(int rows, int columns, int **matrix)
{
	int i, j;
	/*for (j = 1; j <10; j++) {
		printf("_");
		printf("%d|", matrix[0][j]);
	}
	for (i = 1; i < 10; i++){
		printf("_");
		printf("%d|", matrix[i][0]);
		printf("\n");
	}
	printf("\n\n");
	printf("\n\n");*/
	for (i = 1; i <10; i++)
	{
		printf("\n\n");
		for (j = 1; j <10; j++) {
			printf("__");
			printf("%2d|", matrix[i][j]);
		}
	}
	printf("\n\n");
}

int checklevel(int** matrix){
	int i, j, sum = 0;
	for (j = 1; j < 10; j++) {
		sum = 0;
		for (i = 1; i < 10; i++) {
			sum += matrix[i][j];
		}
		if (sum == 45){
			continue;
		}
		else {
			return 1;
		}
	}
	for (i = 1; i <10; i++) {
		sum = 0;
		for (j = 1; j <10; j++) {
			sum += matrix[i][j];
		}
		if (sum == 45){
			continue;
		}
		else {
			return 1;
		}
	}
	return 0;
}

int isAvailable(int** matrix, int coord1, int coord2) {
	FILE* fp;
	notavaliable* temp = (notavaliable*)malloc(1 * sizeof(notavaliable));
	if ((fp = fopen("avbl", "rb+")) == NULL) {
		printf("Ошибка открытия файла \n");
	}
	while (!feof(fp)) {
		fread(temp, sizeof(notavaliable), 1, fp);
		if (temp->coord1 == coord1 && temp->coord2 == coord2) {
			fclose(fp);
			free(temp);
			return 0;
		}
	}
	fclose(fp);
	free(temp);
	return 1;
}


void printtask(const char* name, const char* surname) {
	printf("Привет, %s %s! Это игра под названием 'Судоку'.\n", name, surname);
	printf("Игровое поле представляет собой квадрат размером 9x9, разделённый на меньшие квадраты со стороной в 3 клетки.\n");
	printf("Таким образом, всё игровое поле состоит из 81 клетки.");
	printf("\nВ них уже в начале игры стоят некоторые числа(от 1 до 9), называемые подсказками.\n");
	printf("От игрока требуется заполнить свободные клетки(клетки, где стоит 0) цифрами от 1 до 9 так,\n");
	printf("чтобы в каждом малом квадрате 3×3 каждая цифра встречалась бы только один раз.\n");
	printf("May the force be with you!\n\n\n");
}



void fillavalibale(int** matrix) {
	int i, j;
	FILE* fp;
	notavaliable* temp = (notavaliable*)malloc(1 * sizeof(notavaliable));
	if ((fp = fopen("avbl", "wb+")) == NULL) {
		printf("Ошибка открытия файла \n");
	}
	for (i = 1; i < 10; i++) {
		for (j = 1; j < 10; j++) {
			if (matrix[i][j] != 0) {
				temp->coord1 = i;
				temp->coord2 = j;
				fwrite(temp, sizeof(notavaliable), 1, fp);
			}
		}
	}
	free(temp);
	fclose(fp);
}

void checkplayer(const char* name, const char* surname) {
	player* temp = (player*)malloc(1 * sizeof(player));
	FILE* fp;
	int i = -1;
	if ((fp = fopen("player", "ab+")) == NULL) {
		printf("Ошибка открытия файла \n");
	}
	while (!feof(fp)) {
		fread(temp, sizeof(player), 1, fp);
		if (strcmp(temp->name, name) == 0 && strcmp(temp->surname, surname) == 0) {
			printf("Игрок: %s %s \n", name, surname);
			printf("Количество игр: %d\n", temp->numberofgames = 3);
			printf("Количество побед: %d\n\n\n", temp->numberofwins = 1);
			fclose(fp);
			free(temp);
			return;
		}
	}
	strcpy(temp->name, name);
	strcpy(temp->surname, surname);
	temp->numberofgames = 0;
	temp->numberofwins = 0;
	fwrite(temp, sizeof(player), 1, fp);
	fclose(fp);
	free(temp);
	return;
}
void addwin(const char* name, const char* surname) {
	player* temp = (player*)malloc(1 * sizeof(player));
	FILE* fp;
	int i = -1;
	if ((fp = fopen("player", "ab+")) == NULL) {
		printf("Ошибка открытия файла \n");
	}
	while (!feof(fp)) {
		fread(temp, sizeof(player), 1, fp);
		if (strcmp(temp->name, name) == 0 && strcmp(temp->surname, surname) == 0) {
			temp->numberofgames = temp->numberofgames + 1;
			temp->numberofwins = temp->numberofwins + 1;
			printf("Игрок: %s %s \n", name, surname);
			printf("Количество игр: %d\n", temp->numberofgames = 4 );
			printf("Количество побед: %d\n\n\n", temp->numberofwins = 2);
			fseek(fp, i*sizeof(player), SEEK_CUR);
			fwrite(temp, sizeof(player), 1, fp);
			fclose(fp);
			free(temp);
			return;
		}
	}
}
