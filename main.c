#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STUDENTS 100
#define MAX_SUBJECTS 5
#define MAX_NAME 50

typedef struct {
    char name[MAX_NAME];
    int age;
    char id[MAX_NAME];
    char email[MAX_NAME];
    char address[MAX_NAME];
    float grades[MAX_SUBJECTS];
} Student;

void registerStudent(Student* student, int* numStudents) {
    if (*numStudents < MAX_STUDENTS) {
        Student newStudent;
        printf("Student name: ");
        fgets(newStudent.name, MAX_NAME, stdin);
        printf("Age: ");
        scanf("%d", &newStudent.age);
        getchar();  
        printf("ID: ");
        scanf("%s", newStudent.id);
        getchar();  
        printf("Email: ");
        scanf("%s", newStudent.email);
        getchar();  
        printf("Address: ");
        fgets(newStudent.address, MAX_NAME, stdin); 
        for (int i = 0; i < MAX_SUBJECTS; i++) {
            printf("Subject %d grade: ", i + 1);
            scanf("%f", &newStudent.grades[i]);
            getchar();
            if (newStudent.grades[i] < 0 || newStudent.grades[i] > 10) {
                printf("Grades must be in an interval of 0 to 10.\n");
                return;
            }
        }
        student[*numStudents] = newStudent;
        (*numStudents)++;
        printf("Student registered successfully!\n");
    } else {
        printf("Max ammount of students met.\n");
    }
}


float calAverage(const Student* aluno) {
    float soma = 0;
    for (int i = 0; i < MAX_SUBJECTS; i++) {
        soma += aluno->grades[i];
    }
    return soma / MAX_SUBJECTS;
}


void printStudent(const Student* aluno) {
    printf("Name: %s\n", aluno->name);
    printf("Age: %d\n", aluno->age);
    printf("ID: %s\n", aluno->id);
    printf("Email: %s\n", aluno->email);
    printf("Address: %s\n", aluno->address);
    printf("Grades:\n");
    for (int i = 0; i < MAX_SUBJECTS; i++) {
        printf("Subject %d: %.2f\n", i + 1, aluno->grades[i]);
    }
    printf("Grades average: %.2f\n", calAverage(aluno));
}


void printStudentList(const Student* students, int num) {
    for (int i = 0; i < num; i++) {
        printf("Student %d:\n", i + 1);
        printStudent(&students[i]);
        printf("\n");
    }
}


void saveData(const Student* students, int num) {
    FILE* file = fopen("students.dat", "wb");
    if (file == NULL) {
        printf("Error while trying to write the file.\n");
        return;
    }
    fwrite(&num, sizeof(int), 1, file);
    fwrite(students, sizeof(Student), num, file);
    fclose(file);
    printf("Students saved successfully.\n");
}

void carregarDados(Student* students, int* num) {
    FILE* file = fopen("students.dat", "rb");
    if (file == NULL) {
        return;
    }
    fread(num, sizeof(int), 1, file);
    fread(students, sizeof(Student), *num, file);
    fclose(file);
    printf("Students loaded successfully.\n");
}

int main() {
    Student alunos[MAX_STUDENTS];
    int numAlunos = 0;
    carregarDados(alunos, &numAlunos);

    int escolha;
    do {
        printf("Select an operation:\n");
        printf("1. Register new student\n");
        printf("2. Calculate average grade\n");
        printf("3. Show student list\n");
        printf("4. Save data\n");
        printf("5. exit\n");
        scanf("%d", &escolha);
        getchar();
        switch (escolha) {
            case 1:
                registerStudent(alunos, &numAlunos);
                break;
            case 2: {
                char name[MAX_NAME];
                printf("Type the student name: ");
                fgets(name, MAX_NAME, stdin);
                int encontrado = 0;
                for (int i = 0; i < numAlunos; i++) {
                    if (strcmp(alunos[i].name, name) == 0) {
                        printf("%s average grades: %.2f\n", name, calAverage(&alunos[i]));
                        encontrado = 1;
                        break;
                    }
                }
                if (!encontrado) {
                    printf("Student not found.\n");
                }
                break;
            }
            case 3:
                printStudentList(alunos, numAlunos);
                break;
            case 4:
                saveData(alunos, numAlunos);
                break;
            case 5:
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid option.\n");
                break;
        }
    } while (escolha != 5);

    return 0;
}
