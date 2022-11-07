#include <stdlib.h>
#include <stdio.h>

///We have to define malloc to the data character so that's why we use pointer sign in front of data char
///Whenever we try to give malloc to a variable, we need that variable to be pointer.
typedef struct Student
{
    char *data;
    int d2;
}Student;

int main(int argc, char **argv){
    ///Now instantiate an struct from variable student.
    //TODO
    Student student[1000];

    ///To cpature line by line from file.
    char *buffer = (char*) malloc(sizeof(char*));

    FILE* file = fopen(argv[1], "r");

    int i = 0;

    while(!feof(file)){
        Student *s = student + i;
        student[i].data = (char*) malloc(sizeof(char*));
        fscanf(file, "%s %d", s->data, &s->d2);
        i++;
    }
    
    for (int j = 0; j < i; ++j) {
        printf("%s %d\n", student[j].data, student[j].d2);
    }
    fclose(file);
}
