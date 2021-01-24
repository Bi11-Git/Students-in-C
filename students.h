//
// Created by bi11 on 24/1/21.
//

#ifndef STUDENT_H
#define STUDENT_H
#define MAXSTRING 50

typedef struct _list* list;
typedef struct _node* node;

typedef struct
{
    char name[MAXSTRING];
    int id;
}student;

struct _node
{
    node next;
    student *st;
};

struct _list
{
    node head, tail;
};

void printMenu();

void print(student );

void printstudents(list );

node load(char *);//ανάκτηση λίστας φοιτητών από αρχείο

void save(char *, list ); //αποθήκευση λίστας φοιτητών σε αρχείο

int addStudent(student , list );//προσθήκη νέου student

student *findStudent(int , list );//αναζήτηση του student από το list με βάση το id

int deleteStudent(student , list ); //διαγραφή με βάση το st.id

int updateStudent(student , list );//ανανέωση με βάση το st.id


node createstudent(list );//

student *loadstudents(FILE *);//

void listdestroy(list );//

void freenode(node );//

void findtail(list );//

int addnewid();//

void saveonestudent(char *, list, int);//

#endif