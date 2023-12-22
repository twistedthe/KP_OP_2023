#define _CRT_SECURE_NO_DEPRECATE
//подключение необхходимых библиотек
#include <locale.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
//создание структур
struct mobil {
	char name[30];
	char os[30];
	char developer[30];
	char description[200];
	int price;
	char category[30];
};

struct data {
	char name[100];
	char student[50];
	char pole1[30];
	char pole2[41];
	char pole3[30];
	char pole4[30];
	char pole5[30];
	char pole6[30];
};
//создание структурных типов
typedef struct mobil mobile_app_t;
typedef struct data database_t;
//прототипы функций
int action(void);
void add_app(mobile_app_t*, int);
int writefile(char*, mobile_app_t*, int);
void put_app(mobile_app_t*);
int put_from_file(char*, mobile_app_t*, int);
int put_all_app(mobile_app_t*, int, database_t);
void randaznach(mobile_app_t*, int);
int compare_price(const void*, const void*);
int compare_developer(const void*, const void*);
void put_name_table(database_t);
int sort_array(mobile_app_t*, int);
int search_app_name(mobile_app_t*, int, char*);
mobile_app_t* search_app_category(mobile_app_t*, int, char*, int);
int count_category(mobile_app_t*, int, char*);
int change_apps(mobile_app_t*, int);
int delete_app(mobile_app_t*, int);
int append_app(mobile_app_t*, int, int);

int main()
{
	setlocale(LC_ALL, "RUS");
	system("chcp 1251");
	int a = 1, size;
	char fname[] = "database.txt";
	FILE* size_array;
	size_array = fopen(fname, "rb");
	if (size_array == NULL) {
		printf("\n\n\nОшибка открытия файла\n\n\n");
		return 0;
	}
	fscanf(size_array, "%d\n", &size);
	fclose(size_array);
	mobile_app_t* apps = 0;
	database_t my_database = { "Файловая база данных \"Мобильные приложения\"", "Сделал: Гончаров А.Д.","Название","Операционная система","Разработчик","Описание","Цена","Категория" };
	printf("\n%s\t%s\n\n", my_database.name, my_database.student);
	while (a) {
		switch (action()) {
		case 1: {
			printf("\nВведите сколько вы хотите сделать записей: ");
			scanf("%d", &size);
			apps = malloc(sizeof(mobile_app_t) * size);
			if (apps == NULL)
			{
				printf("\n\nОшибка выделения памяти\n\n");
				return 0;
			}
			add_app(apps, size);
		} break;
		case 2: {
			if (!apps)
			{
				printf("\nОперация невозможна, нет данных\n\n");
				break;
			}
			writefile(fname, apps, size);
		} break;
		case 3: {
			if (!apps)
			{
				printf("\nОперация невозможна, нет данных\n\n");
				break;
			}
			put_all_app(apps, size, my_database);
		} break;
		case 4: {
			apps = malloc(sizeof(mobile_app_t) * size);
			if (apps == NULL)
			{
				printf("\n\nОшибка выделения памяти\n\n");
				return 0;
			}
			put_from_file(fname, apps, size);
			put_all_app(apps, size, my_database);
		} break;
		case 5: {
			if (!apps)
			{
				printf("\nОперация невозможна, нет данных\n\n");
				break;
			}
			sort_array(apps, size);
			put_all_app(apps, size, my_database);
		} break;
		case 6: {
			apps = malloc(sizeof(mobile_app_t) * size);
			if (apps == NULL)
			{
				printf("\n\nОшибка выделения памяти\n\n");
				return 0;
			}
			randaznach(apps, size);
		} break;
		case 7: {
			if (!apps)
			{
				printf("\nОперация невозможна, нет данных\n\n");
				break;
			}
			int index = change_apps(apps, size);
			if (index == -1) {
				break;
			}
			else {
				put_app(apps + index);
			}
		} break;
		case 8: {
			if (!apps)
			{
				printf("\nОперация невозможна, нет данных\n\n");
				break;
			}
			char search[31];
			int priznak, index, size_new_array;
			if (size == 0)
			{
				printf("\nПоиск невозможем, нет данных");
				return 0;
			}
			put_from_file(fname, apps, size);
			printf("\nПо какому признаку вы хотите найти мобильное приложение?\n1. Название\n2. Категория\n");
			scanf("%d", &priznak);
			if (priznak == 1)
			{
				printf("\nВведите название мобильного приложения, которое хотите найти: \n");
				scanf("%s", &search);
				index = search_app_name(apps, size, search);
				if (index == -1) {
					printf("\nПриложение не найдено\n\n");
					break;
				}
				else {
					put_name_table(my_database);
					put_app(apps + index);
				}
			}
			else
			{
				printf("\nВведите категорию мобильного приложения, которое хотите найти: \n");
				scanf("%s", &search);
				size_new_array = count_category(apps, size, search);
				if (size_new_array == -1) {
					printf("\nНет приложений с данной категорией, поиск невозможен\n\n");
					break;
				}
				else {
					put_all_app(search_app_category(apps, size, search, size_new_array), size_new_array, my_database);
				}
			}
		} break;
		case 9: {
			if (!apps)
			{
				printf("\nОперация невозможна, нет данных\n\n");
				break;
			}
			size = delete_app(apps, size);
			apps = realloc(apps, sizeof(mobile_app_t) * size);
			if (apps == NULL)
			{
				printf("\n\nОшибка распределения памяти\n\n");
				return 0;
			}
		} break;
		case 10: {
			if (!apps)
			{
				printf("\nОперация невозможна, нет данных, для начала внесите хотябы одно приложение\n\n");
				break;
			}
			int new_size;
			printf("\nВведите сколько приложений вы хотите добавить: ");
			scanf("%d", &new_size);
			new_size += size;
			apps = realloc(apps, new_size * sizeof(mobile_app_t));
			if (apps == NULL)
			{
				printf("\n\nОшибка распределения памяти\n\n");
				return 0;
			}
			size = append_app(apps, size, new_size);
		} break;
		case 11: a = 0; break;
		default: {
			printf("\nНеверное значение, попробуйте еще раз\n\n");
		} break;
		}
	}
}
//функция для работы меню
int action()
{
	int action;
	printf("1. Ввести мобильные приложения\n");
	printf("2. Сохранить данные в файл\n");
	printf("3. Вывести все данные\n");
	printf("4. Вывести данные из файла\n");
	printf("5. Сортировка\n");
	printf("6. Заполнить случайными значениями\n");
	printf("7. Изменить данные\n");
	printf("8. Поиск данных\n");
	printf("9. Удаление данных\n");
	printf("10. Добавить мобильное приложение\n");
	printf("11. Выход\n\n");
	scanf("%d", &action);
	return action;
}
//функция для чтения данных из файла
int writefile(char* fname, mobile_app_t* apps, int size)
{
	FILE* out;
	if ((out = fopen(fname, "w+b")) == NULL)
	{
		printf("Ошибка открытия файла для записи");
		return 0;
	}
	fprintf(out, "%d\n", size);
	for (int i = 0; i < size; i++)
	{
		fprintf(out, "%s %s %s %s %d %s\n", apps->name, apps->os, apps->developer, apps->description, apps->price, apps->category);
		apps++;
	}
	fclose(out);
	printf("\n\nДанные успешно сохранены\n\n");
	return 1;
}
//функция для записи данных из файла
int put_from_file(char* fname, mobile_app_t* apps, int size)
{
	FILE* out;
	int first_string;
	if ((out = fopen(fname, "rb")) == NULL)
	{
		printf("Ошибка открытия файла для чтения");
		return 0;
	}
	printf("\n");
	fscanf(out, "%d\n", &first_string);
	for (int i = 0; i < size; i++)
	{
		fscanf(out, "%s %s %s %s %d %s\n", apps->name, apps->os, apps->developer, apps->description, &apps->price, apps->category);
		apps++;
	}
	fclose(out);
	return 1;

}
//функция для заполнения массива вручную
void add_app(mobile_app_t* apps, int size)
{
	for (int i = 0; i < size; i++) {
		printf("Введите название мобильного приложения: ");
		scanf("%s", apps->name);
		printf("Введите название операционной системы: ");
		scanf("%s", apps->os);
		printf("Введите имя разработчика: ");
		scanf("%s", apps->developer);
		printf("Введите описание: ");
		scanf("%s", apps->description);
		printf("Введите цену: ");
		scanf("%d", &apps->price);
		printf("Введите название категории: ");
		scanf("%s", apps->category);
		printf("\n");
		apps++;
	}


}
//функция для вывода одной структуры
void put_app(mobile_app_t* apps)
{
	printf("| %10s | %20s | %11s | %20s | %7d | %10s |\n", apps->name, apps->os, apps->developer, apps->description, apps->price, apps->category);
}
//функция для вывода названия столбцов таблицы
void put_name_table(database_t my_database)
{
	printf("| %10s | %20s | %10s | %20s | %7s | %10s |\n\n", my_database.pole1, my_database.pole2, my_database.pole3, my_database.pole4, my_database.pole5, my_database.pole6);
}
//функция для вывода массива структур
int put_all_app(mobile_app_t* apps, int size, database_t my_database)
{
	if (size == 0)
	{
		printf("Нет данных которые можно вывести.\n");
		return 0;
	}
	put_name_table(my_database);
	for (int i = 0; i < size; i++)
	{
		put_app(apps);
		apps++;
	}
}
//функция для заполнения массива рандомными значениями
void randaznach(mobile_app_t* apps, int size)
{
	char str[][31] = { {"Петров"},{"Сидоров"},{"Иванов"},{"Нестеров"},{"Игры"},{"Маркет"},{"Плеер"},{"Виндовс"},{"Андроид"},{"Айос"},{"Значение"} };
	char str1[][200] = { {"Петров"},{"Сидоров"},{"Иванов"},{"Нестеров"},{"Игры"},{"Маркет"},{"Плеер"},{"Виндовс"},{"Андроид"},{"Айос"},{"Значение"} };
	for (int i = 0; i < size; i++)
	{
		strcpy(apps->name, str[rand() % 10]);
		strcpy(apps->os, str[rand() % 10]);
		strcpy(apps->developer, str[rand() % 10]);
		strcpy(apps->description, str1[rand() % 10]);
		apps->price = (((rand() + 2) % 100) + 1);
		strcpy(apps->category, str[rand() % 10]);
		apps++;
	}
}
//функция сравнения для qsort
int compare_price(const void* av, const void* bv)
{
	const mobile_app_t* a = av, * b = bv;
	if (a->price < b->price) return -1;
	if (a->price > b->price) return 1;
	return 0;
}

int compare_developer(const void* av, const void* bv)
{
	const mobile_app_t* a = av, * b = bv;
	return -strcmp(a->developer, b->developer);
}
//функция сортировки массива
int sort_array(mobile_app_t* apps, int size)
{
	if (size == 0) {
		printf("Нет данных для сортировки");
		return 0;
	}
	int priznak;
	printf("По какому признаку вы хотите осуществить сортировку?\n");
	printf("1. По разработчику\n2. По цене\n");
	scanf("%d", &priznak);
	if (priznak == 1) {
		qsort(apps, size, sizeof(mobile_app_t), compare_developer);
	}
	else {
		qsort(apps, size, sizeof(mobile_app_t), compare_price);
	}
}
//функция поиска мобильного приложения по названию
int search_app_name(mobile_app_t* apps, int size, char* search)
{
	for (int i = 0; i < size; i++)
	{
		if (!strcmp(apps->name, search)) {
			return i;
		}
		apps++;
	}
	return -1;

}
//функция поиска мобильного приложения по категории
mobile_app_t* search_app_category(mobile_app_t* apps, int size, char* search, int size_new_array)
{
	mobile_app_t* search_category;
	search_category = malloc(sizeof(mobile_app_t) * size_new_array);
	if (search_category == NULL)
	{
		printf("\n\nОшибка выделения памяти\n\n");
		return 0;
	}
	int new_i = 0;

	for (int j = 0; j < size_new_array; j++)
	{
		for (int i = new_i; i < size; i++)
		{
			if (!strcmp(apps[i].category, search))
			{
				search_category[j] = apps[i];
				new_i = i + 1;
				break;
			}

		}
	}
	return search_category;

}
//функция для подсчета количества мобильных приложений с нужной категорией
int count_category(mobile_app_t* apps, int size, char* search)
{
	int count = 0;
	for (int i = 0; i < size; i++)
	{
		if (!strcmp(apps->category, search)) {
			count++;
		}
		apps++;
	}
	if (count == 0) return -1;
	else return count;
}
//функция для изменения мобильных приложений
int change_apps(mobile_app_t* apps, int size)
{
	int changes, index;
	char poisk[31];
	printf("Введите название приложения, которое хотите изменить: ");
	scanf("%s", &poisk);
	index = search_app_name(apps, size, poisk);
	if (index == -1) {
		printf("\nНет приложения с таким названием\n\n");
		return index;
	}
	printf("Выберите что вы хотите изменить\n");
	printf("1. Название\n");
	printf("2. Операционная система\n");
	printf("3. Разработчик\n");
	printf("4. Описание\n");
	printf("5. Цена\n");
	printf("6. Категория\n");
	printf("7. Изменить все\n");
	scanf("%d", &changes);
	switch (changes)
	{
	case 1: {
		printf("Введите новое название: ");
		scanf("%s", (apps + index)->name);
	} break;
	case 2: {
		printf("Введите новую операционную систему: ");
		scanf("%s", (apps + index)->os);
	} break;
	case 3: {
		printf("Введите нового разработчика: ");
		scanf("%s", (apps + index)->developer);
	} break;
	case 4: {
		printf("Введите новое описание: ");
		scanf("%s", (apps + index)->description);
	} break;
	case 5: {
		printf("Введите новую цену: ");
		scanf("%d", &(apps + index)->price);
	} break;
	case 6: {
		printf("Введите новую категорию: ");
		scanf("%s", (apps + index)->category);
	} break;
	case 7: {
		printf("Введите новое название: ");
		scanf("%s", (apps + index)->name);
		printf("Введите новую операционную систему: ");
		scanf("%s", (apps + index)->os);
		printf("Введите нового разработчика: ");
		scanf("%s", (apps + index)->developer);
		printf("Введите новое описание: ");
		scanf("%s", (apps + index)->description);
		printf("Введите новую цену: ");
		scanf("%d", &(apps + index)->price);
		printf("Введите новую категорию: ");
		scanf("%s", (apps + index)->category);
	} break;
	default: printf("Введено неверное значение.\n");
	}
	printf("\nДанные успешно изменены\n");
	return index;
}
//функция для удаления данных
int delete_app(mobile_app_t* apps, int size)
{
	char name[31];
	int index, new_size = size - 1;
	printf("Введите название приложения, которое хотите удалить: ");
	scanf("%s", name);
	index = search_app_name(apps, size, name);
	if (index == -1)
	{
		printf("\nПриложение не найдено\n\n");
		return -1;
	}
	for (int i = index; i < size - 1; i++)
	{
		apps[i] = apps[i + 1];
	}
	printf("\nПриложение успешно удалено\n\n");
	return new_size;
}
//функция для добавления данных к уже имеющимся
int append_app(mobile_app_t* apps, int size, int new_size)
{
	for (int i = size; i < new_size; i++)
	{
		printf("Введите новое название: ");
		scanf("%s", apps[i].name);
		printf("Введите новую операционную систему: ");
		scanf("%s", apps[i].os);
		printf("Введите нового разработчика: ");
		scanf("%s", apps[i].developer);
		printf("Введите новое описание: ");
		scanf("%s", apps[i].description);
		printf("Введите новую цену: ");
		scanf("%d", &apps[i].price);
		printf("Введите новую категорию: ");
		scanf("%s", apps[i].category);
	}
	return new_size;
}