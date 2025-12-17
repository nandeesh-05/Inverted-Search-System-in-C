#ifndef HEADER
#define HEADER

#define SUCCESS 0
#define FAILURE 1

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <stdio_ext.h>

// macro defnition to colours
#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"
#define BLUE    "\033[34m"
#define MAGENTA "\033[35m"
#define CYAN    "\033[36m"
//o#define UNKNOWN "\033[37m"
#define RESET   "\033[0m"

// structure defnition of filename in linked list
typedef struct file_name
{
    char file_name[20];
    struct file_name *link;
}file_list;
// struture defnition of sub node
typedef struct Sub
{
    int word_count;
    char filename[20];
    struct Sub *next_sub;
}Sub_list;
// structre defnition of main node
typedef struct Main
{
    int file_count;
    char word[20];
    Sub_list *sub_link;
    struct Main *main_link;
}Main_list;
// structure denitions of hashtable
typedef struct hasttable
{
    int index;
    Main_list *next_main;
}Hash;

// function declarations of database
int read_validation(int argc, char *argv[], file_list **files);
int Update_database(Hash *HT,file_list ** head);
int Create_database(Hash *h_table, file_list **head);
int Display(Hash *HT);
int Search_Data(Hash *HT);
int Save_Database(Hash *HT);



void errorfun();
int Insert_at_filelist(file_list **head,char * arr);
int sl_delete_node(file_list **head, char *filename);
void print_list(file_list *head);
#endif