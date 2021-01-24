#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "students.h"

int main(int argc, char *argv[])
{
    list l = malloc(sizeof(struct _list));
    if (l == NULL)
    {
        printf("\nCould not allocate memory!\n");
        exit(1);
    }

    l->head = NULL;
    l->tail = NULL;
    student st;

    int x, y = 2;

    char *filename;

    if (argc > 1)
    {
        filename = malloc(sizeof(argv[1]));
        if (filename == NULL)
        {
            printf("\nCould not allocate memory!\n");
            exit(1);
        }

        filename = argv[1];
        l->head = load(filename);
        findtail(l);
        save(filename, l);
    }
    else
    {
        filename = malloc(50 * sizeof(char));
        if (filename == NULL)
        {
            printf("\nCould not allocate memory!\n");
            exit(1);
        }

        printf("Give the name of the file :~$ ");
        scanf("%s", filename);

        save(filename, l);
    }

    do
    {
        printMenu();

        while (scanf("%d", &x) != 1 || (x < 0 && x > 7))
        {
            printf("wrong input!\n");
            printf("\nPlease choose an option :~$ ");
            while (getchar() != '\n')
                ;
        }

        if (x == 1)
        {
            y = addStudent(st, l);
            if (y != 0)
            {
                saveonestudent(filename, l, y);
            }
        }
        else if (x == 2)
        {
            if (deleteStudent(st, l))
            {
                save(filename, l);
            }
        }
        else if (x == 3)
        {
            y = updateStudent(st, l);
            if (y != 0)
            {
                saveonestudent(filename, l, y);
            }
        }
        else if (x == 4)
        {
            int id = addnewid();
            student *p = findStudent(id, l);
            if (p == NULL)
            {
                printf("\nThis student doesnt exist!\n");
            }
            else
            {
                st.id = p->id;
                strcpy(st.name, p->name);

                print(st);
            }
        }
        else if (x == 5)
        {
            printstudents(l);
        }

    } while (x != 6);

    listdestroy(l);

    return 0;
}