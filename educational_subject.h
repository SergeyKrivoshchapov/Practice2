#ifndef EDUCATIONAL_SUBJECT_H
#define EDUCATIONAL_SUBJECT_H

#include <stddef.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>
#include <math.h>

#define MAX_SUBJ_NAME_LENGTH 25
#define MAX_INT_LENGTH 8
#define MAX_EXAMFORM_LENGTH 10

enum attestation_form
{
	Zachet, Exam, Undefined
};

enum error_code
{
	Success, Invalid_Examination_Form, Invalid_Total_Hours
};

struct discipline
{
	char subject_name[MAX_SUBJ_NAME_LENGTH]; // Название учебного предмета
	unsigned short total_hours; // Общее количество часов
	unsigned short lectures_hours; // Количество часов лекций
	unsigned short practice_hours; // Количество часов практики
	enum attestation_form examination_form;  // Форма аттестации 
};

int init_userdata(struct discipline* subj);

//Проверяет, что общее количество часов >= сумме часов лекций и практик, что examination_form не равен Undefined.
//Возвращает Success, если данные корректны, иначе возвращает код ошибки.
enum error_code subject_DataCheck(const struct discipline* subj);

//Инициализирует поля структуры переданными значениями.
//Вызывает subject_DataCheck для проверки корректности данных.
enum error_code subject_init(struct discipline* subj, const char* subject_name, 
		  unsigned short toral_hours, unsigned short lectural_hours, 
		  unsigned short practice_hours, enum attestation_form examination_form);

int struct_init_result(enum error_code result_code);

//Копирует значения всех полей экземпляра структуры src в поля экземпляра структуры dest.
void copy_subject(struct discipline* dest, const struct discipline* src);

//Выводит значения каждого из полей экземпляра структуры.
void subject_print(struct discipline* subj);

//Получает на ввод из входного потока заранее объявленный номер изменяемого поля. 
//Если полученное значение некорректно, не производит дальнейших действий. 
//Получает на ввод значение для выбранного поля. 
//Изменяет соответствующее значение поля экземпляра структуры посредством вызова одной из соответствующих функций. 
//Проверяет корректность изменений, вызывая функцию struct_init_result.
//Если изменения корректны, возвращает 0, если некорректны 1.
int field_changing(struct discipline* subj);

int update_Subject_Name(struct discipline* subj, const char* value);

int update_Total_Hours(struct discipline* subj, const unsigned short value);

int update_Lectures_Hours(struct discipline* subj, const unsigned short value);

int update_Practice_Hours(struct discipline* subj, const unsigned short value);

int update_Examination_Form(struct discipline* subj, const enum attestation_form value);

//Выделяет память для экземпляра структуры динамически. 
//Инициализирует поля экземпляра значениями, полученными от пользователя через init_userdata.
struct discipline* create_subject();

//Освобождает память, выделенную для экземпляра структуры. 
//Присваивает значение NULL указателю на освобожденную память.
void delete_subject(struct discipline *subj);

void input_string(char* buffer, int buffer_size);

int input_int(const char* message);

enum attestation_form input_attestation_form(const char* message);

#endif
