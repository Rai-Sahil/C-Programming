#include <stdlib.h>
#include <string.h>
#include <stdio.h>

//We have o define malloc to the data character so that's why we use pointer sign in front of data char
typedef struct Student
{
    char *data;
    int d2;
}Student;

int main(int argc, char **argv){
    Student* student = (Student*) malloc(sizeof(Student));
    char *buffer = (char*) malloc(sizeof(char*));

    FILE* file = fopen(argv[1], "r");

    fgets(buffer, 200, file);
    int i = 0;
    while(!feof(file)){
        Student *s = student + i;
        student[i].data = (char*) malloc(sizeof(char*));
        sscanf(buffer, "%s %d", s->data, &s->d2);
        fgets(buffer, 200, file);
        i++;
    }



    for (int j = 0; j < i; ++j) {
        printf("%s %d\n", student[j].data, student[j].d2);
    }
    fclose(file);
}
