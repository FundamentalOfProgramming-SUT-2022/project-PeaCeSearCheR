#include<stdio.h>
#include<stdlib.h>
#include<dir.h>
#include<sys/stat.h>
#include<string.h>
#include<stdbool.h>
#include<dirent.h>
#include<sys/types.h>
#define MAX 500


    void create_folder(char ptr[]){ // function for creating folder.
       char arr[MAX],text[MAX];

       int j=0,counter=-1;
       int length_of_command=strlen(ptr);
        for (int i = 1; i<length_of_command ;i++)
        {
            arr[j] = ptr[i];
            j++;
            i++;

           while (ptr[i] != '/' && i <= length_of_command)
           {
               if (ptr[i]=='/'){
                   ptr[i]=='\0';
                   arr[j]=ptr[i];
                   i++;
                   j++;
                   break;
               }

               arr[j] = ptr[i];
               i++;
               j++;
           }
            if (chdir(arr)!=0){
                mkdir(arr);
            }
            chdir(arr);
            counter++;
            strcpy(text,arr);
            memset(arr , 0 , j);
            j=0;
       }
       chdir("..");
        _rmdir(text);
        create_file(text);

       for(int h=0; h < counter; h++)
       {
           chdir("..");
       }

    }



   void create_file(char file_name[]){

    FILE* write_file = fopen(file_name, "w");

    fputs(file_name,write_file);
    fclose(write_file);

    FILE* read_file = fopen(file_name, "r");

    fclose(read_file);
}
//--------------------------------------------------
int main(){
                                //declare variables.
    char input[MAX];
    char command[MAX];
    char ptr[MAX];
    char path[MAX];
//---------------------------------------------------
    while(1){
        scanf("%s",input);

        if(strcmp(input,"exit")==0)
            break;

        else if(strcmp(input,"createfile")==0){
           scanf("%s",command);
            if (strcmp(command,"--file")==0)
            {
                scanf(" %s",path);
                create_folder(path);       // function for making folder.

            }
            else
                printf("ridi! plz enter <--file> after <createfile>...\n");
        }
         else if(strcmp(input,"")==0){


                }

        else{
            while(1){
                if (getchar()=='\n'){
                printf("invalid command\n");
                break;
                }
            }
        }
    }
}
