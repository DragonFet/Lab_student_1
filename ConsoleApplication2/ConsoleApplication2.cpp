#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <Windows.h>
#include <locale.h>
#define NUMBER_STUDENT 100										              
#define START_NUMBER_STUDENT 1										          
#define MAX_BUF_STRING 80										              
char name_file[] = "data.txt";                                                

typedef struct _student
{
    char* fam;											                      
    char* name;											                      
    char* faculty;										                      
    int grup;											                      
} student;

void init_student(student& stud_p);							                  
bool check_words(char* word);                                                 
void show_scrin();			                                                  
void show_headline();			                                              
void show_all_student(student* stud_p, int size);                             
void show_one_student(student* stud_p_p);	                                  
void find_fam(student* stud_p, int size);                                     
void find_grup(student* stud_p, int size);                                    
void sort(student* stud_p, int size);                                        
bool check_name(student* stud_p, int size, student& stud_p_name);            
void save_student(student* stud_p, int size);                                 
int load_student(student* stud_p);                                            
void show_intro();		                                                      


int main()
{
    SetConsoleCP(1251);                                                       
    SetConsoleOutputCP(1251);                                                 
    setlocale(LC_ALL, "Rus");                                                 
    student* stud_pointer = (student*)calloc(NUMBER_STUDENT, sizeof(student));
    int student_count = 0;                                 
    int choice;                                                               
    bool flag_scrin = false;                                                 
    FILE* file;

    show_intro();		                                                      

    if (fopen_s(&file, name_file, "r") != NULL)                               
    {
        printf("\n\tФайла нет, инициализация с клавиатуры.");
        printf("\n\tВведите изначальные данные о %d студенте/студентах.", START_NUMBER_STUDENT);
        for (; student_count < START_NUMBER_STUDENT;)
        {
            init_student(stud_pointer[student_count++]);                      
            if (check_name(stud_pointer, student_count, stud_pointer[student_count - 1]))
            {
                printf("\n\t!!!Данный пользователь уже есть в базе данных!!! ");
                student_count--;
            }
        }
    }
    else
    {
        fclose(file);                                                         
        student_count = load_student(stud_pointer);                           
    }

    while (1)
    {
        if (!flag_scrin)show_scrin();

        while (scanf_s("%d", &choice) != 1)                                  
        {
            printf("\tВы ошиблись вводе, введите заново свой выбор: ");
            while (getchar() != '\n');
        }
        while (getchar() != '\n');

        if (choice == 0)break;                                                
        switch (choice)                                                      
        {
        case 1:
            init_student(stud_pointer[student_count++]);                     
            if (check_name(stud_pointer, student_count, stud_pointer[student_count - 1]))
            {
                printf("\n\t!!!Данный пользователь уже есть в базе данных!!! ");
                student_count--;
            }
            flag_scrin = false;
            break;
        case 2:
            show_all_student(stud_pointer, student_count);                   
            flag_scrin = false;
            break;
        case 3:
            find_fam(stud_pointer, student_count);                           
            flag_scrin = false;
            break;
        case 4:
            find_grup(stud_pointer, student_count);                           
            flag_scrin = false;
            break;
        case 5:
            sort(stud_pointer, student_count);                               
            show_all_student(stud_pointer, student_count);
            flag_scrin = false;
            break;
        default:
            printf("\tТакой функции нет, введите номер другой функции: ");
            flag_scrin = true;
            break;
        }
    }
    save_student(stud_pointer, student_count);                                
    free(stud_pointer);                                                       
    return 0;
}

void init_student(student& stud_p)                                           
{
    char buf_string[MAX_BUF_STRING];		                                  

    printf("\n\n\n\tФамилия студента: ");                                     
    scanf_s("%s", buf_string, (unsigned)_countof(buf_string));                
    while (!check_words(buf_string))                                          
        scanf_s("%s", buf_string, (unsigned)_countof(buf_string));
    stud_p.fam = (char*)malloc(MAX_BUF_STRING + 1);                           
    strcpy_s(stud_p.fam, MAX_BUF_STRING + 1, buf_string);                     
    while (getchar() != '\n');                                                

    printf("\tИмя студента: ");                                              
    scanf_s("%s", buf_string, (unsigned)_countof(buf_string));
    while (!check_words(buf_string))
        scanf_s("%s", buf_string, (unsigned)_countof(buf_string));
    stud_p.name = (char*)malloc(MAX_BUF_STRING + 1);
    strcpy_s(stud_p.name, MAX_BUF_STRING + 1, buf_string);
    while (getchar() != '\n');

    printf("\tНазвание факультета: ");                                        
    scanf_s("%s", buf_string, (unsigned)_countof(buf_string));
    while (!check_words(buf_string))
        scanf_s("%s", buf_string, (unsigned)_countof(buf_string));
    stud_p.faculty = (char*)malloc(MAX_BUF_STRING + 1);
    strcpy_s(stud_p.faculty, MAX_BUF_STRING + 1, buf_string);
    while (getchar() != '\n');

    printf("\tНомер группы: ");                                               
    while (scanf_s("%d", &stud_p.grup) != 1)                                  
    {
        printf("\tВы ошиблись вводе, введите заново: ");
        while (getchar() != '\n');
    }
    while (getchar() != '\n');
}

bool check_words(char* word)                                                 
{
    bool flag = true;
    for (; *word; word++)
    {
        if (!isalpha(*word) && ((*word < 'а' || *word>'я') && (*word < 'А' || *word>'Я')))
        {
            flag = false;
            printf("\tВы ошиблись вводе, введите заново: ");
            break;
        }
    }
    return flag;
}

void show_headline()                                                          
{
    printf("\n===============================================================================\n");
    printf("  Фамилия студента:\tИмя студента:\tНазвание факультета:\tНомер группы:");
    printf("\n===============================================================================\n");
}

void show_one_student(student* stud_p_p)                                     
{
    printf("%19s\t%13s\t%20s\t%13d\n", stud_p_p->fam, stud_p_p->name, stud_p_p->faculty, stud_p_p->grup);
}

void show_all_student(student* stud_p, int size)                             
{
    int i;
    student* stud_p_pointer;
    printf("\n\n\n  Таблица заданных значений:");
    show_headline();
    for (stud_p_pointer = stud_p, i = 0; i < size; stud_p_pointer++, i++)
        show_one_student(stud_p_pointer);
    printf("\n===============================================================================\n");
}

void show_scrin()			                                                  
{
    printf("\n\n\n\tДобавить нового студента    ................1");
    printf("\n\tПосмотреть иформацию о всех студентах   ....2");
    printf("\n\tНайти студента/студентов по фамилии   ......3");
    printf("\n\tНайти студента/студентов по группе   .......4");
    printf("\n\tОтсортировать список по алфавиту    ........5");
    printf("\n\tВыход из программы(сохранение данных)  .....0");
    printf("\n\t.............................................");
    printf("\n\tВведите номер функции: ");
}

void find_fam(student* stud_p, int size)                                     
{
    int i;
    student* stud_p_pointer;
    char buf_string[MAX_BUF_STRING];		                                 

    printf("\n\n\n\tПоиск студента/студентов по фамилии. ");                 
    printf("\n\tВведите фамилию студента/студентов: ");
    scanf_s("%s", buf_string, (unsigned)_countof(buf_string));
    while (!check_words(buf_string))
        scanf_s("%s", buf_string, (unsigned)_countof(buf_string));

    printf("\n\tИнформация о студенте/студентах по фамилии %s", buf_string);
    show_headline();
    for (stud_p_pointer = stud_p, i = 0; i < size; stud_p_pointer++, i++)
        if (strcmp(stud_p_pointer->fam, buf_string) == 0)show_one_student(stud_p_pointer);
    printf("\n===============================================================================\n");
}

void find_grup(student* stud_p, int size)                                    
{
    int i, number;
    student* stud_p_pointer;

    printf("\n\n\n\tПоиск студента/студентов по группе. ");
    printf("\n\tВведите номер группы: ");
    while (scanf_s("%d", &number) != 1)                                      
    {
        printf("\tВы ошиблись вводе, введите заново: ");
        while (getchar() != '\n');
    }
    while (getchar() != '\n');

    printf("\n\tИнформация о студенте/студентах в группе %d", number);
    show_headline();
    for (stud_p_pointer = stud_p, i = 0; i < size; stud_p_pointer++, i++)
        if (stud_p_pointer->grup == number)show_one_student(stud_p_pointer);
    printf("\n===============================================================================\n");

}

void sort(student* stud_p, int size)		                                  
{
    char buf_string1[MAX_BUF_STRING];		                                  	
    char buf_string2[MAX_BUF_STRING];		                                 	

    char buf_string3[MAX_BUF_STRING];		                                 
    char buf_string4[MAX_BUF_STRING];		                                 	

    char buf_string5[MAX_BUF_STRING];		                                  
    char buf_string6[MAX_BUF_STRING];		                                  	

    int buf_int1;                                                             
    int buf_int2;                                                             	

    student* stud_p_pointer;
    int i, j;

    for (i = 0; i < size - 1; i++)                                            
    {
        for (stud_p_pointer = stud_p, j = 0; j < size - 1 - i; stud_p_pointer++, j++)
        {
            strcpy_s(buf_string3, MAX_BUF_STRING, stud_p_pointer->name);      
            strcpy_s(buf_string5, MAX_BUF_STRING, stud_p_pointer->faculty);
            buf_int1 = stud_p_pointer->grup;

            strcpy_s(buf_string1, MAX_BUF_STRING, stud_p_pointer++->fam);

            strcpy_s(buf_string4, MAX_BUF_STRING, stud_p_pointer->name);      
            strcpy_s(buf_string6, MAX_BUF_STRING, stud_p_pointer->faculty);
            buf_int2 = stud_p_pointer->grup;

            strcpy_s(buf_string2, MAX_BUF_STRING, stud_p_pointer--->fam);

            int min_len = (strlen(buf_string1) < strlen(buf_string2)) ? strlen(buf_string1) : strlen(buf_string2);
            int count_letters = 0;

            for (int k = 0; k < min_len; k++)
            {
                if (buf_string1[k] > buf_string2[k])                          
                {
                    strcpy_s(stud_p_pointer->name, MAX_BUF_STRING, buf_string4);
                    strcpy_s(stud_p_pointer->faculty, MAX_BUF_STRING, buf_string6);
                    stud_p_pointer->grup = buf_int2;

                    strcpy_s(stud_p_pointer++->fam, MAX_BUF_STRING, buf_string2);

                    strcpy_s(stud_p_pointer->name, MAX_BUF_STRING, buf_string3);
                    strcpy_s(stud_p_pointer->faculty, MAX_BUF_STRING, buf_string5);
                    stud_p_pointer->grup = buf_int1;

                    strcpy_s(stud_p_pointer--->fam, MAX_BUF_STRING, buf_string1);

                    break;
                }
                else
                {
                    if (buf_string1[k] == buf_string2[k])
                    {
                        count_letters++;
                        continue;
                    }
                    else
                        break;
                }
            }
            if (count_letters == strlen(buf_string2))                        
            {
                strcpy_s(stud_p_pointer->name, MAX_BUF_STRING, buf_string4);
                strcpy_s(stud_p_pointer->faculty, MAX_BUF_STRING, buf_string6);
                stud_p_pointer->grup = buf_int2;

                strcpy_s(stud_p_pointer++->fam, MAX_BUF_STRING, buf_string2);

                strcpy_s(stud_p_pointer->name, MAX_BUF_STRING, buf_string3);
                strcpy_s(stud_p_pointer->faculty, MAX_BUF_STRING, buf_string5);
                stud_p_pointer->grup = buf_int1;

                strcpy_s(stud_p_pointer--->fam, MAX_BUF_STRING, buf_string1);
            }
        }
    }
    for (i = 0; i < size - 1; i++)                                           
    {
        for (stud_p_pointer = stud_p, j = 0; j < size - 1 - i; stud_p_pointer++, j++)
        {
            strcpy_s(buf_string5, MAX_BUF_STRING, stud_p_pointer->faculty);   
            strcpy_s(buf_string1, MAX_BUF_STRING, stud_p_pointer->fam);
            buf_int1 = stud_p_pointer->grup;

            strcpy_s(buf_string3, MAX_BUF_STRING, stud_p_pointer++->name);

            strcpy_s(buf_string6, MAX_BUF_STRING, stud_p_pointer->faculty);   
            strcpy_s(buf_string2, MAX_BUF_STRING, stud_p_pointer->fam);
            buf_int2 = stud_p_pointer->grup;

            strcpy_s(buf_string4, MAX_BUF_STRING, stud_p_pointer--->name);

            int min_len = (strlen(buf_string3) < strlen(buf_string4)) ? strlen(buf_string3) : strlen(buf_string4);
            int count_letters = 0;

            if (strcmp(buf_string1, buf_string2) == 0)
            {
                for (int k = 0; k < min_len; k++)
                {
                    if (buf_string3[k] > buf_string4[k])                    
                    {
                        strcpy_s(stud_p_pointer->faculty, MAX_BUF_STRING, buf_string6);
                        stud_p_pointer->grup = buf_int2;

                        strcpy_s(stud_p_pointer++->name, MAX_BUF_STRING, buf_string4);

                        strcpy_s(stud_p_pointer->faculty, MAX_BUF_STRING, buf_string5);
                        stud_p_pointer->grup = buf_int1;

                        strcpy_s(stud_p_pointer--->name, MAX_BUF_STRING, buf_string3);

                        break;
                    }
                    else
                    {
                        if (buf_string3[k] == buf_string4[k])
                        {
                            count_letters++;
                            continue;
                        }
                        else
                            break;
                    }
                }
                if (count_letters == strlen(buf_string4))                    
                {
                    strcpy_s(stud_p_pointer->faculty, MAX_BUF_STRING, buf_string6);
                    stud_p_pointer->grup = buf_int2;

                    strcpy_s(stud_p_pointer++->name, MAX_BUF_STRING, buf_string4);

                    strcpy_s(stud_p_pointer->faculty, MAX_BUF_STRING, buf_string5);
                    stud_p_pointer->grup = buf_int1;

                    strcpy_s(stud_p_pointer--->name, MAX_BUF_STRING, buf_string3);
                }
            }
        }
    }
}

bool check_name(student* stud_p, int size, student& stud_p_name)              
{
    int i;
    student* stud_p_pointer;

    for (stud_p_pointer = stud_p, i = 0; i < size - 1; stud_p_pointer++, i++)
        if (strcmp(stud_p_pointer->fam, stud_p_name.fam) == 0)
            if (strcmp(stud_p_pointer->name, stud_p_name.name) == 0)
                return true;
    return false;
}
void save_student(student* stud_p, int size)                                  
{
    student* stud_p_pointer;
    FILE* file;

    if (fopen_s(&file, name_file, "w") == NULL)                               
    {
        printf("\n\tДанные успешно сохранены.\n");

        for (stud_p_pointer = stud_p; stud_p_pointer < stud_p + size; stud_p_pointer++)
        {
            fprintf(file, "%s\n", stud_p_pointer->fam);
            fprintf(file, "%s\n", stud_p_pointer->name);
            fprintf(file, "%s\n", stud_p_pointer->faculty);
            fprintf(file, "%d\n", stud_p_pointer->grup);
        }
        fclose(file);                                                         
    }
    else
        printf("\n\t!!!Ошибка открытия файла!!!\n");
}

int load_student(student* stud_p)                                            
{
    int student_count = 0;
    student* stud_p_pointer;
    FILE* file;
    char buf_string[MAX_BUF_STRING];		                                 

    if (fopen_s(&file, name_file, "r") == NULL)                              
    {
        printf("\n\tДанные успешно загружены.\n");

        for (stud_p_pointer = stud_p; !feof(file); stud_p_pointer++)
        {
            fscanf_s(file, "%s\n", buf_string, _countof(buf_string));         
            stud_p_pointer->fam = (char*)malloc(MAX_BUF_STRING + 1);
            strcpy_s(stud_p_pointer->fam, MAX_BUF_STRING + 1, buf_string);

            fscanf_s(file, "%s\n", buf_string, _countof(buf_string));         
            stud_p_pointer->name = (char*)malloc(MAX_BUF_STRING + 1);
            strcpy_s(stud_p_pointer->name, MAX_BUF_STRING + 1, buf_string);

            fscanf_s(file, "%s\n", buf_string, _countof(buf_string));        
            stud_p_pointer->faculty = (char*)malloc(MAX_BUF_STRING + 1);
            strcpy_s(stud_p_pointer->faculty, MAX_BUF_STRING + 1, buf_string);

            fscanf_s(file, "%d\n", &stud_p_pointer->grup);                    
            student_count++;
        }
        fclose(file);                                                         
    }
    else
        printf("\n\t!!!Ошибка открытия файла!!!\n");

    return student_count;
}

void show_intro()			                                                 
{
   
    printf("\t| Программа \"База данных : Студент\".                                               |\n");
    printf("\t| 1)При вводе фамилии, имени и названия факультета, вводятся строки                |\n");
    printf("\t| состоящие только из букв (\"Rus\",\"Eng\").                                          |\n");
    printf("\t| 2)При вводе номера группы и выборе функции, вводится только целое число          |\n");
    printf("\t| (1.2 введётся 1; 1df введётся 1; df1 будет ошибка и вас попросят ввести заново). |\n");
   

}
