#include "educational_subject.h"

int init_userdata(struct discipline* subj)
{
	char subject_name[MAX_SUBJ_NAME_LENGTH];
	printf("Enter subject name: ");
	input_string(subject_name, MAX_SUBJ_NAME_LENGTH);

	unsigned short total_hours = input_int("\nEnter total hours: ");
	unsigned short lectures_hours = input_int("\nEnter lectures hours: ");
	unsigned short practice_hours = input_int("\nEnter practice hours: ");
	enum attestation_form examination_form = input_attestation_form("\nEnter examination form (Zachet/Exam): ");
	
	if (struct_init_result(subject_init(subj, subject_name, total_hours, lectures_hours, practice_hours, examination_form)) != 0) return 1;
	return 0;
}

enum error_code subject_DataCheck(const struct discipline* subj)
{
	if (subj->total_hours < subj->lectures_hours + subj->practice_hours) 
	{
		printf("Entered subject hours information is incorrect.\n");
		return Invalid_Total_Hours;
	}
	if (subj->examination_form == Undefined)
	{
		printf("Entered examination form is incorrect.");
		return Invalid_Examination_Form;
	}
	printf("Entered data is correct!\n");
	return Success; 
}

enum error_code subject_init(struct discipline* subj, const char* subject_name, unsigned short total_hours, unsigned short lectures_hours, unsigned short practice_hours, enum attestation_form examination_form)
{	
	strncpy(subj->subject_name, subject_name, MAX_SUBJ_NAME_LENGTH);
	subj->subject_name[MAX_SUBJ_NAME_LENGTH - 1] = '\0';
	subj->total_hours = total_hours;
	subj->lectures_hours = lectures_hours;
	subj->practice_hours = practice_hours;
	subj->examination_form = examination_form;
	return subject_DataCheck(subj);
}

int struct_init_result(const enum error_code result_code)
{
	switch (result_code)
	{
		case Success:
			printf("Discipline structure initialized successfully.\n");
			return 0;
		default:
			printf("Discipline structure initialization failed.\n");
			return 1;
	}
}

void copy_subject(struct discipline *dest, const struct discipline *src) 
{
	strncpy(dest->subject_name, src->subject_name, MAX_SUBJ_NAME_LENGTH);
	dest->total_hours = src->total_hours;
	dest->lectures_hours = src->lectures_hours;
	dest->practice_hours = src->practice_hours;
	dest->examination_form = src->examination_form;
}

void subject_print(struct discipline* subj)
{
	const char* form;
	switch (subj->examination_form) {
	case Zachet: form = "Zachet"; break;
	case Exam: form = "Exam"; break;
	default: form = "Undefined"; break;}
	printf("Subject - %s . Total hours = %d . Lectures hours = %d . Practice hours = %d . Examination form - %s\n", subj->subject_name, subj->total_hours, subj->lectures_hours, subj->practice_hours, form);
}

int field_changing(struct discipline* subj)
{
	int field_tochange = input_int("\nWhich field you want to change?\n1 - subject name\n2 - total hours value\n3 - lectures hours value\n4 - practice hours value\n5 - examination form\nEnter any other symbol if you won't change anything\n\nEnter only digit: ");

	int init_checkmark;

	switch (field_tochange)
	{
		case 1:
			char subject_name_tochange[MAX_SUBJ_NAME_LENGTH];
			input_string(subject_name_tochange, MAX_SUBJ_NAME_LENGTH);
			init_checkmark = struct_init_result(update_Subject_Name(subj, subject_name_tochange));
			break;
		case 2:
			unsigned short total_hours_tochange = input_int("\nEnter new total hours value: ");
			init_checkmark = struct_init_result(update_Total_Hours(subj, total_hours_tochange));
			break;
		case 3:
			unsigned short lectures_hours_tochange = input_int("\nEnter new lectures hours value: ");
			init_checkmark = struct_init_result(update_Lectures_Hours(subj, lectures_hours_tochange));
			break;
		case 4:
			unsigned short practice_hours_tochange = input_int("\nEnter new practice hours value: ");
			init_checkmark = struct_init_result(update_Practice_Hours(subj, practice_hours_tochange));
			break;
		case 5:
			enum attestation_form examination_form_tochange = input_attestation_form("\nEnter new attestation form: ");
			init_checkmark = struct_init_result(update_Examination_Form(subj, examination_form_tochange));
			break;
		default:
			printf("\nUndefined value received. Nothing will be changed.\n");
			break;
	}

	if (init_checkmark == 0) return 0;

	return 1;
}

int update_Total_Hours(struct discipline* subj, const unsigned short value)
{
	subj->total_hours = value;
	return subject_DataCheck(subj);
}

int update_Subject_Name(struct discipline* subj, const char* value)
{
	strncpy(subj->subject_name, value, MAX_SUBJ_NAME_LENGTH);
	return subject_DataCheck(subj);
}

int update_Lectures_Hours(struct discipline* subj, const unsigned short value)
{
	subj->lectures_hours = value;
	return subject_DataCheck(subj);
}

int update_Practice_Hours(struct discipline* subj, const unsigned short value)
{
	subj->practice_hours = value;
	return subject_DataCheck(subj);
}

int update_Examination_Form(struct discipline* subj, const enum attestation_form value)
{
	subj->examination_form = value;
	return subject_DataCheck(subj);
}

struct discipline* create_subject() 
{
	struct discipline *subj = (struct discipline *)malloc(sizeof(struct discipline));
	
	if (!subj) return NULL;

	if (init_userdata(subj) == 0) return (struct discipline *)subj;

	free(subj);
	subj = NULL;
	return NULL;
}

void delete_subject(struct discipline *subj)
{
	free(subj);
	subj = NULL;
}

void input_string(char* buffer, int buffer_size) 
{
	fgets(buffer, buffer_size, stdin);
	size_t len = strlen(buffer);
	if (len > 1 && buffer[len - 1] == '\n') buffer[len - 1] = '\0';
	else
	{
		printf("Entered value is too long or empty.\n");
		exit(EXIT_FAILURE);
	}
}

int input_int(const char* message) 
{
	char buffer[MAX_INT_LENGTH];
	char temp[MAX_INT_LENGTH];
	printf("%s", message);
	input_string(buffer, MAX_INT_LENGTH);
	snprintf(temp, MAX_INT_LENGTH, "%d", atoi(buffer)); 
	if ((atoi(buffer) == 0 && buffer[0] != '0') || (atoi(buffer) >= USHRT_MAX) || (atoi(buffer) < 0) || (strcmp(buffer, temp) != 0))
	{
		printf("Entered value is incorrect.");
		exit(EXIT_FAILURE);
	}
	return atoi(buffer);
}

enum attestation_form input_attestation_form(const char* message) 
{
	char buffer[MAX_EXAMFORM_LENGTH];

	printf("%s", message);
	input_string(buffer, MAX_EXAMFORM_LENGTH);
	if (strcmp(buffer, "Zachet") == 0) return Zachet;
	if (strcmp(buffer, "Exam") == 0) return Exam;
	return Undefined;
}
