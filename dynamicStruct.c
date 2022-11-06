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
    //TODO ask jeeho how to allocate memory for this Student array.
    Student* student = (Student*) malloc(sizeof(Student));
    
    ///To cpature line by line from file.
    char *buffer = (char*) malloc(sizeof(char*));

    FILE* file = fopen(argv[1], "r");

    //TODO Also ask jee ho what to put an the place of 200.
    fgets(buffer, 200, file);
    int i = 0;

    while(!feof(file)){
        //Giving memory address to student linked list
        Student *s = student + i;
        //Hence both the data'ss are char, malloc should also be char.
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
