
/*
NAME:Nandeesh
Project:Inverted Search
*/


#include"header.h"
int main(int argc,char *argv[])
{
    if(argc==1)
    {
        errorfun();
        return 0;
    }
    file_list *head=NULL;
    Hash h_table[28];
    int i=0;
        for(int i=0;i<28;i++)
        {
           h_table[i].index=i;
           h_table[i].next_main=NULL;
        }
    // function call for the validation
    // file should be .txt, not empty, present in current working directorary
    int res=read_validation(argc,argv,&head);
    if(res==0)
    {
        
        printf(RED"❌ Validation not completed due to errors. Please check input files.\n"RESET);
       print_list(head);
       return 0;
    }
    else
    {
        printf(GREEN"✔️ Validation completed successfully.\n"RESET);
        printf(GREEN"📁 Number of valid files: %d\n"RESET, res);
        print_list(head);
       
    }
    int choice;
    int savecount=0;
    int updatecount=0;
    
do
{
    printf(""CYAN"---------------------------------------------------------------\n");
printf(MAGENTA"📘 Inverted Search Menu\n"RESET);
printf(""CYAN"---------------------------------------------------------------\n");

printf(YELLOW"1️⃣  Create Database\n"RESET);
printf(YELLOW"2️⃣  Update Database\n"RESET);
printf(YELLOW"3️⃣  Search Database\n"RESET);
printf(YELLOW"4️⃣  Display Database\n"RESET);
printf(YELLOW"5️⃣  Save Database\n"RESET);

printf(""CYAN"---------------------------------------------------------------\n");
printf(GREEN"👉 Enter your choice: "RESET);
scanf("%d",&choice);

switch(choice)
{
    case 1:
      if(savecount!=1 || updatecount==1)
      {
        // function call to create data base
        Create_database(h_table, &head);
        savecount=1;
        printf(GREEN "✅ Database created successfully.\n" RESET);
      }
      else
      {
        printf(RED "❌ Error: Database is already created.\n" RESET);

      }
    break;
    case 2:
         if(savecount!=1 && updatecount!=1)
         {
          // function call to update database

            Update_database(h_table ,&head);
            printf(GREEN "✅ Database updated successfully.\n" RESET);
            updatecount=1;
         }
         else{
            printf(RED "❌ Error: Database is already updated.\n" RESET);

         }
    break;
    case 3:
      if(savecount==0 && updatecount==0)
      {
        printf(RED "❌ Error: Database is not created. Cannot perform this operation.\n" RESET);

      }
      else
      {
        // function call to search database
         Search_Data(h_table);
      }
    break;
    case 4:
         if(savecount==0 && updatecount==0)
         {
             printf(RED "❌ Error: Database is not created. Cannot perform this operation.\n" RESET);
         }
         else
         {
                // function call to display the database
                 Display(h_table);
         }
    break;
    case 5:
       if(savecount==0 && updatecount==0)
       {
         printf(RED "❌ Error: Database is not created. Cannot perform this operation.\n" RESET);

       }
       else{
        // function call to save database
        Save_Database(h_table);
        printf(GREEN "💾 Database saved successfully.\n" RESET);
       }
    break;
    default:
     printf(RED"❌ Invalid choice! Please enter a valid option from the menu.\n"RESET);


}
}while(choice<=5);



        
        

}