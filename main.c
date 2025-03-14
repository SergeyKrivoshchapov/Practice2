#include "educational_subject.h"

int main(int argc, char* argv[])
{
	// Создание экземпляров структур на стеке 
	struct discipline subj1;
	struct discipline subj2;
	
	printf("Gets informaions about educational subject.\n");
	printf("Changes it if needs. Outputs result.\n");
	
	// Инициализация экземпляров структуры
	if (init_userdata(&subj1) == 1) return 1; 
	
	if (init_userdata(&subj2) == 1) return 1;
	
	// Вывод сведений о экземплярах структуры
	printf("\nFirst subject:\n");
	subject_print(&subj1);

	printf("\nSecond subject:\n");
	subject_print(&subj2);

	// Инициализация второго экземпляра структуры как копии первого
	copy_subject(&subj2, &subj1); 

	printf("\nFirst subject:\n");
	subject_print(&subj1);

	printf("\nCopy of first subject:\n");
	subject_print(&subj2);

	// Вывов функции изменения поля первого экземпляра структуры
	if (field_changing(&subj1) == 1) return 1;

	printf("\nResult of changes\n");
	subject_print(&subj1);
	
	// Инициализация двух экземпляров структур в динамической пмяти
	printf("Enter data to create first subject.\n");
	struct discipline* subj3 = create_subject();
	
	if (subj3 == NULL) return 1;
	
	printf("Enter data to create second subject.\n");
	struct discipline* subj4 = create_subject();

	if (subj4 == NULL) return 1;

	printf("First: \n");
	subject_print(subj3);

	printf("Second: \n");
	subject_print(subj4);
	
	//Инициализируем второй экземпляр структуры как копию первого
	copy_subject(subj4, subj3);
	
	printf("First: \n");
	subject_print(subj3);

	printf("Copy of first subject\n");
	subject_print(subj4);

	// Вызов функции изменения поля в экземпляре структуры инициализированном в динамической памяти
	if (field_changing(subj3) == 1) return 1;
	
	printf("\nResult of changes\n");
	subject_print(subj3);

	// Удаление экземпляров структуры из динамической памяти
	delete_subject(subj3);
	delete_subject(subj4);

	return 0;
}
