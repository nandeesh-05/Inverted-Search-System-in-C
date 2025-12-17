#include "header.h"

// function defnition to error function
void errorfun()
{
    printf(""CYAN"\n-----------------------------------------------------------------------------\n");
printf(RED"📘 Input usage for Inverted Search\n"RESET);
printf(RED"➡️  ./a.out  <file1.txt>  <file2.txt>  ...\n"RESET);
printf(""CYAN"-----------------------------------------------------------------------------\n");

printf("📁 "YELLOW"All input files must be of type"RESET" "GREEN".txt\n");
printf("🚫 "YELLOW"Other file formats like"RESET" "GREEN".c .pdf .jpg"RESET" "YELLOW"are not allowed\n"RESET);
printf("⚠️ "YELLOW"Files that do not exist or are empty will be skipped\n"RESET);

printf("📌 "YELLOW"Minimum requirement: At least ONE valid .txt file\n"RESET);

printf(""CYAN"-----------------------------------------------------------------------------\n");
printf("🔍 "YELLOW"Example:\n"RESET);
printf(GREEN"      ./a.out  data1.txt  notes.txt  input.txt\n"RESET);
printf(""CYAN"-----------------------------------------------------------------------------\n");

}







// function defnition to valiadate database
int read_validation(int argc, char *argv[], file_list **files)
{
    
    int i=1;
    char filename[20];
    FILE *fptr;
    int valid= 0;  
    while(i<=argc && argv[i]!=NULL)
    {
        strcpy(filename,argv[i]);
        char *str=strtok(filename,".");
        str=strtok(NULL,"."); // to get txt
        
        if(strcmp(str,"txt")==0)
        {
            
            fptr=fopen(argv[i],"r");
            if(fptr!=NULL)   // to validate whether file present in current working directory
            {

                if(ftell(fptr)!=EOF) // to check file empty or not
                {
                    
                     Insert_at_filelist(files,argv[i]);
                     valid++;


                }
                else{
                    printf(YELLOW"⚠️ Warning: The file '%s' exists, but it is empty. Skipping...\n"RESET, argv[i]);
                    
                }
                   
            }
            else
            {
               printf(RED"❌ Error: File '%s' not present in the current working directory.\n"RESET, argv[i]);
               
               

            }
            
            
        }
        else
        {
            printf(RED"❌ Error: Invalid file '%s'. Only .txt files are allowed.\n"RESET, argv[i]);
           
        }
        
        
        i++;
        if (fptr != NULL) 
        {
             fclose(fptr);
        }
        if(valid==0)
        return valid;
        
    }
    return valid;
}

// function defnition to Insert valiadted file names to linked list at last
int Insert_at_filelist(file_list **head, char *arr)
{
    // remove duplicate files
    file_list *temp = *head;
    while (temp != NULL)
    {
        if (strcmp(temp->file_name, arr) == 0)  
        {
            return 2;  
        }
        temp = temp->link;
    }

    
    file_list *new = malloc(sizeof(file_list));
    if (new == NULL)
        return FAILURE;

    strcpy(new->file_name, arr);
    new->link = NULL;

   
    if (*head == NULL)
    {
        *head = new;
        return SUCCESS;
    }

    
    temp = *head;

    while (temp->link != NULL)   
    {
        temp = temp->link;
    }

    temp->link = new;
    return SUCCESS;
}
// function defnition to print linked list
void print_list(file_list *head)
{
	if (head == NULL)
	{
		printf("INFO : List is empty\n");
	}
    else
    {
	    while (head)		
	    {
		    printf("%s -> ", head ->file_name);
		    head = head -> link;
	    }

	    printf("NULL\n");
    }
}


// function defnition to create database
int Create_database(Hash *h_table, file_list **head)
{
    file_list *temp=*head;
    char str[100];
    char ch;
    int i=0;
    while(temp!=NULL)
    {
        // finding the index to save in hashtable
        FILE * fptr=fopen(temp->file_name,"r");
        while(fscanf(fptr, "%s", str) == 1 && ftell(fptr)!=EOF)
        {
            if(isalpha(str[0]))
            {
               i=tolower(str[0])- 'a';
            }
            else if(isdigit(str[0]))
            {
                i=26;
            }
            else
            {
                i=27;
            }
            // create main node
            if(h_table[i].next_main==NULL)
            {
                
                Main_list *mainnew=malloc(sizeof(Main_list));
                if(mainnew==NULL)
                {
                    printf("Memory not allocated for main node\n");
                    return FAILURE;
                }
                mainnew->file_count=1;
                strcpy(mainnew->word,str);
                
               
                Sub_list *subnew=malloc(sizeof(Sub_list));
                if(subnew==NULL)
                {
                    printf("Memory not alloacted for subnode\n");
                    return FAILURE;
                }
                // create sub node
                subnew->word_count=1;
                strcpy(subnew->filename,temp->file_name);
                subnew->next_sub=NULL;
                
                
                mainnew->sub_link=subnew;
                mainnew->main_link=NULL;
                h_table[i].next_main=mainnew;

               
              
            }
            else
            {
                Main_list *maintemp=h_table[i].next_main;
               // Sub_list *subtemp=maintemp->sub_link;
               Main_list *mainprev=NULL;
               Sub_list *subtemp;
               Sub_list *subprev;
               int flag=1;
                while(maintemp!=NULL)
                {
                    if(strcmp(maintemp->word,str)==0)
                    {
                        subtemp=maintemp->sub_link;
                        subprev=NULL;

                        while(subtemp!=NULL)
                        {

                          if(strcmp(subtemp->filename,temp->file_name)==0)
                          {
                             subtemp->word_count++;
                             flag=0;
                          }
                          subprev=subtemp;
                          subtemp=subtemp->next_sub;
                        }
                    
                        if(flag!=0)
                        {
                            Sub_list *subnew=malloc(sizeof(Sub_list));
                            if(subnew==NULL)
                             {
                                   printf("Memory not alloacted for subnode\n");
                                     return FAILURE;
                             }
                            subnew->word_count=1;
                            strcpy(subnew->filename,temp->file_name);
                            subnew->next_sub=NULL;
                            
                            // subtemp->next_sub=subnew;
                            maintemp->file_count++;
                            subprev->next_sub=subnew;
                            flag=0;
                        }
                        
                    }  
                   mainprev=maintemp;
                   maintemp=maintemp->main_link;
                }



                if(flag==1)
                {

                Main_list *mainnew=malloc(sizeof(Main_list));
                if(mainnew==NULL)
                {
                    printf("Memory not allocated for main node\n");
                    return FAILURE;
                }
                mainnew->file_count=1;
                strcpy(mainnew->word,str);
                
               
                Sub_list *subnew=malloc(sizeof(Sub_list));
                if(subnew==NULL)
                {
                    printf("Memory not alloacted for subnode\n");
                    return FAILURE;
                }
                subnew->word_count=1;
                strcpy(subnew->filename,temp->file_name);
                subnew->next_sub=NULL;
                mainnew->sub_link=subnew;
                mainnew->main_link=NULL;
                mainprev->main_link=mainnew;

                }

            }
            
        }
        temp=temp->link;
    }
    
}


// function defnition to search database
int Search_Data(Hash *HT)
{
    char name[20];
    printf(YELLOW"🔍 Enter the word to search in database: "RESET);
    scanf("%s", name);

    int index;

    if (isalpha(name[0]))
        index = tolower(name[0]) - 'a';
    else if (isdigit(name[0]))
        index = 26;
    else
        index = 27;

    Main_list *maintemp = HT[index].next_main;

    while (maintemp != NULL)
    {
        if (strcmp(maintemp->word, name) == 0)
        {
           

            int flag = 0;
            Sub_list *subtemp = maintemp->sub_link;
            printf("\n\u2705 Word found in database!\n\n");
                printf("Index      : %d\n", index);
                printf("Word       : %s\n", maintemp->word);
                printf("FileCount  : %d\n\n", maintemp->file_count);
                printf("Files:\n");

            while (subtemp != NULL)
            {
                

                if (flag == 0)
                {
                   // First file → print index, word, filecount above
                   printf("- %s  →  %d times\n", subtemp->filename, subtemp->word_count);
                }
               else
               {
                // Remaining files printed one by one
                  printf("- %s  →  %d times\n", subtemp->filename, subtemp->word_count);
               }
                flag = 1;
                subtemp = subtemp->next_sub;
            

              
            }
         // ✔️ STOP the flow when found
           return SUCCESS;
        }
            maintemp = maintemp->main_link;
    
       }

    // If not found
    printf(RED "\ngiven '%s' not present in database\n" RESET, name);
    return FAILURE;
}



// function defnition to display database
int Display(Hash *HT)
{
    int count = 1;

    printf(MAGENTA"%-5s %-7s %-15s %-10s %-20s %-10s\n" RESET,"S.NO", "Index", "Word", "FileCount", "Filename", "WordCount");


    for (int i = 0; i < 28; i++)
    {
        
        // if (HT[i].next_main == NULL)
        //     continue;

        Main_list *maintemp = HT[i].next_main;

        while (maintemp != NULL)
        {
            int flag=0;
            Sub_list *subtemp = maintemp->sub_link;  // reset for each word
            printf(BLUE"%-5d %-7d %-15s %-10d",count++,i,maintemp->word,maintemp->file_count);
            while (subtemp != NULL)
            {
                if(flag ==0)
                printf("%-15s %10d\n"RESET ,subtemp->filename,subtemp->word_count);
                else
                printf(BLUE"%40s%-15s %10d\n"RESET ,"",subtemp->filename,subtemp->word_count);
                flag=1;
                subtemp = subtemp->next_sub;
            }

            maintemp = maintemp->main_link;
        }
    }

    return SUCCESS;
}
// function defnition to savedase to hash table to file
int Save_Database(Hash *HT)
{

    int res = 0;
    char outfile[50];
    char ch;

    do {
        printf("📁 Enter the filename to save database: ");
        scanf("%49s", outfile);
        char temp[50];
        strcpy(temp, outfile);
        char *str = strtok(temp, ".");
        str = strtok(NULL, ".");
        if (str && strcmp(str, "txt") == 0) 
        {
            FILE *fptr = fopen(outfile, "r");

            if (fptr != NULL) 
            {
                fseek(fptr, 0, SEEK_END);
                long size = ftell(fptr);
                fclose(fptr);

                if (size > 0) 
                {
                    printf("⚠️  Warning: File already exists in the current directory.\n");
                    printf("Overwrite the file? (y = yes, n = create separate file): ");

                    scanf(" %c", &ch);
                    if (ch == 'y' || ch == 'Y') 
                    {
                        res = 1;   
                    } else 
                    {
                        res = 0;   
                    }
                } 
                else 
                {
                    res = 1;
                }
            } 
            else 
            {
                res = 1;
            }

        } 
        else 
        {
            printf("❌ Error: Output file must have a .txt extension.\n");
            res = 0; 
        }

    } while (res != 1);

   FILE *fptr1 = fopen(outfile, "w");
if (fptr1 == NULL) {
    printf("❌ Error: Could not open file for writing.\n");
    return 1;
}

for (int i = 0; i < 28; i++) {
    Main_list *maintemp = HT[i].next_main;

    while (maintemp != NULL) {

        
        fprintf(fptr1, "#%d;%s;%d",i,maintemp->word,maintemp->file_count);

        
        Sub_list *subtemp = maintemp->sub_link;
        while (subtemp != NULL) {
            fprintf(fptr1, ";%s;%d",subtemp->filename,subtemp->word_count);
            subtemp = subtemp->next_sub;
        }
        
        fprintf(fptr1, "#\n");

        maintemp = maintemp->main_link;
    }
}

  fclose(fptr1);
}

// function defnition to update database
int Update_database(Hash *HT,file_list **head)
{
    char dupfilename[100];
    printf(BLUE "📂 Enter the file name to load the database: " RESET);
    scanf("%s",dupfilename);
    char name[90];
    strcpy(name,dupfilename);
    char * str=strtok(name,".");
    str=strtok(NULL,".");
    int flag=0;
    if(strcmp(str,"txt")==0)
    {
        
            FILE *fptr = fopen(dupfilename, "r");
            if (fptr != NULL) 
            {
                fseek(fptr, 0, SEEK_END);
                long size = ftell(fptr);
                if(size!=0)
                {
                    fseek(fptr, 0, SEEK_SET);
                    char ch1=fgetc(fptr);
                   fseek(fptr, size - 1, SEEK_SET);
                    char ch2=fgetc(fptr);
                    
                    
                    if(ch1==ch2)
                    {
                        flag=1;
                    }
                    else
                    {
                        printf(RED "❌ Error: The given file is not a saved database file.\n" RESET);
                        return FAILURE;
                    }

                    rewind(fptr);

                }
                else
                {
                    printf(YELLOW "⚠️  Warning: File is empty.\n" RESET);
                    return FAILURE;
                }

            }
            else
            {
                printf(RED "❌ Error: File not present in the current working directory.\n" RESET);
                return FAILURE;

            }


    }
    else
    {

        printf(RED "❌ Error: Output file must have a .txt extension.\n" RESET);
        return FAILURE;

    }

    if(flag==1)
    {
        FILE * fptr1=fopen(dupfilename, "r");
        int i;
        char wordname[100];
        int filecount;
        int wordcount;
        char file[100];
        
        while(fscanf(fptr1, "#%d;%[^;];%d;", &i, wordname, &filecount)!=EOF)
        {
            
            
            Main_list * mainnew=malloc(sizeof(Main_list));
            strcpy(mainnew->word,wordname);
            mainnew->file_count=filecount;
            mainnew->main_link=NULL;
            mainnew->sub_link=NULL;
            
            for(int j=0;j<filecount;j++)
            {
                fscanf(fptr1,"%[^;];%d;",file,&wordcount);
                Sub_list *subnew=malloc(sizeof(Sub_list));
                strcpy(subnew->filename,file);
                
                subnew->word_count=wordcount;
                sl_delete_node(head, file);

                  subnew->next_sub=mainnew->sub_link;
                 mainnew->sub_link=subnew;
                    

            }
            mainnew->main_link=HT[i].next_main;
           HT[i].next_main=mainnew;
           fscanf(fptr1,"#\n");
             

            

            
        }
        fclose(fptr1);
        
    }
}
// function defnition to delete linked list
int sl_delete_node(file_list **head, char *filename)
{
    if (*head == NULL)
        return FAILURE;

    file_list *temp = *head;

    // If first node must be deleted
    if (strcmp(temp->file_name, filename) == 0) {
        *head = temp->link;
        free(temp);
        return SUCCESS;
    }

    file_list *prev = temp;
    temp = temp->link;

    while (temp != NULL)
    {
        if (strcmp(temp->file_name, filename) == 0)
        {
            prev->link = temp->link;
            free(temp);
            return SUCCESS;
        }
        prev = temp;
        temp = temp->link;
    }

    return FAILURE;
}


