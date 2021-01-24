//
// Created by bi11 on 24/1/21.
//

#include <stdio.h>
#include <stdlib.h>
#include "students.h"

void printMenu()
{
    printf("\n1.  Add new student\n");
    printf("2.  Delete student\n");
    printf("3.  Change student's details\n");
    printf("4.  Find a student\n");
    printf("5.  Print all students\n");
    printf("6.  Exit\n");
    printf("\nPlease choose an option :~$ ");

    return;
}

void print(student st)
{
    printf("\n  id\tname\n");
    printf("%d\t%s\n", st.id, st.name);
    return;
}

void printstudents(list l)
{
    if (l->head == NULL)
    {
        printf("\nList is empty\n");
        return;
    }

    node st = l->head;

    printf("\n  id\tname\n");

    while (st != NULL)
    {
        printf("%d\t%s\n", st->st->id, st->st->name);
        st = st->next;
    }

    return;
}

node load(char *filename)
{
    node start = NULL;
    node end = NULL;

    printf("Loading students from file...%s\n", filename);

    FILE *listfile = fopen(filename, "rb");

    if (listfile == NULL)
    {
        printf("Error! Save file not found!\n");
        return NULL;
    }

    fseek(listfile, 0, SEEK_END);
    long filesize = ftell(listfile);

    rewind(listfile);

    int numbstudents = (int)(filesize / sizeof(student));

    int i;

    student *loadst = NULL;

    for (i = 0; i < numbstudents; i++)
    {
        fseek(listfile, (sizeof(student)) * i, SEEK_SET);

        if (start == NULL)
        {

            start = malloc(sizeof(struct _node));
            if (start == NULL)
            {
                printf("\nCould not allocate memory!\n");
                exit(1);
            }

            start->st = loadstudents(listfile);
            start->next = NULL;

            if (start->st != NULL)
            {

                start->next = NULL;
                end = start;
            }
        }
        else
        {
            loadst = loadstudents(listfile);
            end->next = malloc(sizeof(student));
            if (end->next == NULL)
            {
                printf("\nCould not allocate memory!\n");
                exit(1);
            }

            end->next->st = loadst;
            end->next->next = NULL;

            if (end->next->st != NULL)
            {
                end = end->next;
            }
        }
    }

    printf("%d  students successfully loaded!\n", i);

    return start;
}

void save(char *filename, list l)
{
    FILE *listfile = fopen(filename, "wb");

    if (listfile == NULL)
    {
        printf("ERROR OPEN LIST!\n");
    }

    node current = l->head;

    while (current != NULL)
    {
        fseek(listfile, 0, SEEK_END);
        fwrite(current->st, sizeof(student), 1, listfile);

        current = current->next;
    }

    fclose(listfile);

    return;
}

int addStudent(student st, list l)
{
    if (l->head == NULL)
    {
        l->head = createstudent(l);
        l->tail = l->head;
        if (l->head == NULL)
        {
            return 0;
        }
        else
        {
            return l->head->st->id;
        }
    }
    else
    {
        l->tail->next = createstudent(l);
        if (l->tail->next != NULL)
        {
            l->tail = l->tail->next;
            return l->tail->st->id;
        }
        else
        {
            return 0;
        }
    }
}

student *findStudent(int id, list l)
{
    node currentstudent = l->head;

    while (currentstudent != NULL)
    {
        if (currentstudent->st->id == id)
        {
            return currentstudent->st;
        }
        else
        {

            currentstudent = currentstudent->next;
        }
    }

    return NULL;
}

int deleteStudent(student st, list l)
{
    int id = addnewid();

    node delete = l->head;
    node previous = l->head;

    while (delete->st->id != id)
    {
        if (delete == NULL)
        {
            printf("\nThis student dosen't exist!\n");
            return 0;
        }

        delete = delete->next;

        if (delete == NULL)
        {
            printf("\nThis student dosen't exist!\n");
            return 0;
        }
    }

    if (l->head == delete)
    {
        printf("\nStudent %s deleted successfully\n", delete->st->name);
        l->head = l->head->next;
        free(delete);

        return 1;
    }

    while (previous->next->st->id != id)
    {
        previous = previous->next;
    }

    printf("Student %s deleted successfully!\n", delete->st->name);

    if (delete->next == NULL)
    {
        previous->next = delete->next;
        free(delete);
        l->tail = previous;
        return 1;
    }

    previous->next = delete->next;
    free(delete);

    return 1;
}

int updateStudent(student st, list l)
{
    int id = addnewid();

    student *update = findStudent(id, l);

    if (update == NULL)
    {
        printf("This student dosen't exist!\n");
        return 0;
    }

    int newid = addnewid();
    student *checkifexist = findStudent(newid, l);

    if (newid == id)
    {
        printf("Add student new name :~$ ");
        scanf("%s", update->name);
        printf("Name changed successfully\n");

        return id;
    }
    else if (checkifexist != NULL)
    {
        printf("This student already exist!\n");
        return 0;
    }

    update->id = newid;
    printf("Add student new name :~$ ");
    scanf("%s", update->name);
    printf("Name changed successfully\n");

    return newid;
}

node createstudent(list l)
{
    int id = addnewid();

    node new = NULL;

    if (findStudent(id, l) != NULL)
    {
        printf("\nThis student already exist!\n");
        return NULL;
    }

    new = malloc(sizeof(node));
    if (new == NULL)
    {
        printf("\nCould not allocate memory!\n");
        exit(1);
    }

    new->st = malloc(sizeof(student));
    if (new->st == NULL)
    {
        printf("\nCould not allocate memory!\n");
        exit(1);
    }

    new->next = NULL;

    new->st->id = id;

    printf("Add student name :~$ ");
    scanf("%s", new->st->name);

    return new;
}

student *loadstudents(FILE *listfile)
{
    student *new = NULL;

    new = malloc(sizeof(student));
    if (new == NULL)
    {
        printf("\nCould not allocate memory!\n");
        exit(1);
    }

    fread(new, sizeof(student), 1, listfile);

    return new;
}

void listdestroy(list l)
{
    node dnode = l->head;

    if (l->head == NULL)
    {
        free(l);
        return;
    }
    else if (l->head == l->tail)
    {
        freenode(l->head);
        l->head = NULL;
    }
    else
    {
        dnode = l->head;
        l->head = l->head->next;
        freenode(dnode);
    }
}

void freenode(node n)
{
    n->next = NULL;
    free(n->st);
    free(n);

    return;
}

void findtail(list l)
{
    if (l->head == NULL)
    {
        return;
    }

    l->tail = l->head;

    while (l->tail->next != NULL)
    {
        l->tail = l->tail->next;
    }

    return;
}

int addnewid()
{
    int id;

    printf("Add student id   :~$ ");

    while (scanf("%d", &id) != 1 || id < 1)
    {
        printf("wrong input!\n");
        while (getchar() != '\n')
            ;

        printf("Add student id   :~$ ");
    }

    while (getchar() != '\n')
        ;

    return id;
}

void saveonestudent(char *filename, list l, int id)
{
    node current = l->head;

    if (current == NULL)
    {
        return;
    }

    FILE *listfile = fopen(filename, "r+");

    if (listfile == NULL)
    {
        printf("ERROR OPEN LIST!\n");
    }

    int i = 0;

    while (current->st->id != id)
    {
        current = current->next;
        i++;
    }

    fseek(listfile, (sizeof(student)) * i, SEEK_SET);

    fwrite(current->st, sizeof(student), 1, listfile);

    fclose(listfile);

    return;
}