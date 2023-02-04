#include<stdio.h>
#include<stdlib.h>
#include<dir.h>
#include<sys/stat.h>
#include<string.h>
#include<stdbool.h>
#include<dirent.h>
#include<sys/types.h>
#include <errno.h>

#define MAX 10000000

/*  void path_checker()  //function for analysis the given path/filename
  {
      char str[MAX];
      const char s[2] = "/";
      char *token;
      gets(str);
      token = strtok(str, s);
      printf("%s",token);
      while( token != NULL ) {

          create_folder(token);
          token = strtok(NULL, s);
          printf("%s\n",token);

      }
  }*/


void create_folder(char *ptr) { // function for creating folder.

    char *arr = (char *) malloc(MAX * sizeof(char));
    char *text = (char *) malloc(MAX * sizeof(char));
    int counter = 0, counter1 = 0, j = 0;
    int length_of_command = strlen(ptr);

    if (ptr[0] == '/') {
        for (int i = 1; i < length_of_command; i++) {
            if (ptr[i] == ' ') {
                ptr[i] = '\0';
            }
            arr[j] = ptr[i];
            j++;
            i++;

            while (ptr[i] != '/' && i <= length_of_command) {
                if (ptr[i] == '/') {
                    ptr[i] = '\0';
                    arr[j] = ptr[i];
                    break;
                }
                if (ptr[i] == ' ') {
                    ptr[i] = '\0';
                }

                arr[j] = ptr[i];
                i++;
                j++;
            }

            if (chdir(arr) != 0) {
                mkdir(arr);
            }
            chdir(arr);
            counter++;
            strcpy(text, arr);
            memset(arr, 0, length_of_command);
            j = 0;
        }
        chdir("..");
        _rmdir(text);
        create_file(text);

        for (int h = 1; h < counter; h++) {
            chdir("..");
        }

    } else if (ptr[0] == '"') {

        for (int i = 2; i < length_of_command; i++) {
            arr[j] = ptr[i];
            j++;
            i++;

            while (ptr[i] != '/' && i <= length_of_command && ptr[i] != '"') {
                if (ptr[i] == '/') {
                    ptr[i] = '\0';
                    arr[j] = ptr[i];
                    i++;
                    j++;
                    break;
                }

                arr[j] = ptr[i];
                i++;
                j++;
            }

            if (chdir(arr) != 0) {

                mkdir(arr);
            }

            chdir(arr);
            counter1++;
            counter++;
            strcpy(text, arr);
            memset(arr, 0, j);
            j = 0;
        }
        if (counter1 > 1) {
            chdir("..");
            _rmdir(text);
            create_file(text);
        }


        for (int h = 1; h < counter; h++) {
            chdir("..");
        }
    }

}



//------------------------------------------------------

void create_file(char *file_name) {

    FILE *write_file = fopen(file_name, "w");

    fclose(write_file);
}

//-------------------------------------------------------
void cat(char *filename) {
    char c;
    FILE *fptr;
    fptr = fopen(filename+1, "r");
    if (fptr == NULL) {
        printf("\nError Message: %s", strerror(errno));
    } else {
        c = fgetc(fptr);
        printf("File Data : ");
        while (c != EOF) {
            printf("%c", c);
            c = fgetc(fptr);
        }
        printf("\n");
        fclose(fptr);
    }
}


void insert(char *filename, char *str, int y, int x) {

    int length = strlen(str), length_file;
    int k, i = 0, counter = 1, before, after;
    char c[1000];
    char *arr = (char *) malloc(MAX * (sizeof(char)));
    char *last_arr = (char *) malloc(MAX * (sizeof(char)));
    FILE *textfile;
    char *text;
    long numbytes;

    FILE *first = fopen(filename+1, "r");

    if (first == NULL) {
        printf("\nError Message: %s\n", strerror(errno));
        return;
    }


    fseek(first, 0, SEEK_END);
    length_file = ftell(first);
    fclose(first);

    textfile = fopen(filename+1, "r");

    fseek(textfile, 0L, SEEK_END);
    numbytes = ftell(textfile);
    fseek(textfile, 0L, SEEK_SET);

    text = (char *) calloc(numbytes, sizeof(char));

    fread(text, sizeof(char), numbytes, textfile);
    fclose(textfile);

    if (length_file == 0 && x == 0 && y == 1) {
        strcpy(last_arr, str);
        first = fopen(filename+1, "w");
        fputs(last_arr, first);
        fclose(first);
        return;
    }
    if (length == 0) {
        printf("Please enter string after (--str).\n");
        return;
    }

    for (int l = 0; l < length_file; l++) {
        if (text[l] == '\n')
            counter++;

    }
    if (counter < y) {
        printf("There not enough line in this File.\n");
        return;
    } else {

        counter = 1;
        i = 0;
        int m = 0;
        for (m = 0; m < length_file + length; m++) {
            last_arr[m] = text[m];
            if (last_arr[m] == '\n') {

                counter++;
            }

            if (counter == y) {
                before = m;
                m++;

                while (text[m+1] != '\n') {
                    i++;
                    m++;

                }
                /* for(int j=0 ,  j< length ; j++){

                     if ((str[j]== '\\') && (str[j+1] =='n'))
                     {
                         str[j]='\n';
                         str[j+1]='\0';
                         j+=2;
                     }
                    else if ((str[j]== '\\') && (str[j+2] =='n') && (str[j+1] =='\\'))
                     {
                         str[j]='\0';
                         j+=1;

                     }

                 }*/
                if (i + 1 < (x) ) {
                    printf("There are not enough character in this file.\n");
                    return;
                } else {
                    /* if (  y ==1){
                             i=before;

                          for (; i < before + x ; i++) {

                         last_arr[i] = text[i];
                     }

                     for (k = 0; k < length; k++) {

                         last_arr[i + k] = str[k];
                     }
                     k = i + k;
                     for (; k < length + length_file; k++) {

                         last_arr[k] = text[i];
                         i++;
                     }
                         return;
                     }*/

                    i = before;
                    for (; i <= before + x; i++) {

                        last_arr[i] = text[i];
                    }

                    for (k = 0; k < length; k++) {

                        last_arr[i + k] = str[k];
                    }
                    k = i + k;
                    for (; k < length + length_file; k++) {

                        last_arr[k] = text[i];
                        i++;
                    }

                    m = k;

                    first = fopen(filename+1, "w");
                    fputs(last_arr, first);
                    fclose(first);
                }
            }

        }

    }






    //insertstr --file /b.txt --str salam --pos 0:1
}


void removestr(char *filename, int y, int x, int size, char *direction1) {
    char direction=direction1[1];
    int length = size, length_file;
    int k, i = 0, counter = 1, before, after;
    char c[1000];
    char *arr = (char *) malloc(MAX * (sizeof(char)));
    char *last_arr = (char *) malloc(MAX * (sizeof(char)));
    FILE *textfile;
    char *text;
    long numbytes;

    FILE *first = fopen(filename+1, "r");

    if (first == NULL) {
        printf("\nError Message: %s\n", strerror(errno));
        return;
    }


    fseek(first, 0, SEEK_END);
    length_file = ftell(first);
    fclose(first);

    textfile = fopen(filename+1, "r");

    fseek(textfile, 0L, SEEK_END);
    numbytes = ftell(textfile);
    fseek(textfile, 0L, SEEK_SET);

    text = (char *) calloc(numbytes, sizeof(char));

    fread(text, sizeof(char), numbytes, textfile);
    fclose(textfile);

    if (length_file == 0) {
        printf("This file is empty.\n");
        return;
    }
    if (length == 0) {

        printf("Please enter Numbers bigger than 0.\n");
        return;
    }

    for (int l = 0; l < length_file; l++) {
        if (text[l] == '\n')
            counter++;

    }
    if (counter < y) {
        printf("There not enough line in this File.\n");
        return;
    } else {
        counter = 1;
        i = 0;
        int m = 0;
        for (m = 0; m < length_file - length; m++) {
            last_arr[m] = text[m];
            if (last_arr[m] == '\n'){

                counter++;
            }

            if (counter == y) {
                before = m;
                m++;

                while (text[m+1] != '\n'){
                    i++;
                    m++;

                }

                if (direction == 'f') {
                    if (i+1 < (x) + size) {
                        printf("There are not enough character in this line.\n");
                        return;
                    } else {

                        i = before;
                        for (; i <= before + x; i++) {
                            last_arr[i] = text[i];
                        }

                        k = i;
                        i += length;
                        for (; k < length_file - length; k++) {
                            last_arr[k] = text[i];
                            i++;
                        }

                        m = k;

                        first = fopen(filename+1, "w");
                        fputs(last_arr, first);
                        fclose(first);
                    }
                } else if (direction == 'b') {
                    if (i+1 < (x)+size) {
                        printf("There are not enough character in this line.\n");
                        return;
                    } else {


                        i = before;
                        for (; i <= before + x - length; i++) {

                            last_arr[i] = text[i];
                        }

                        k = i;
                        i += length;
                        for (; k < length_file - length; k++) {

                            last_arr[k] = text[i];
                            i++;
                        }

                        m = k;

                        first = fopen(filename+1, "w");
                        fputs(last_arr, first);
                        fclose(first);
                    }


                }

            }

        }


    }


}

void copystr(char *filename, int y, int x, int size, char *direction1){
    char direction=direction1[1];
    int length = size, length_file;
    int k, i = 0, counter = 1, before, after;
    char c[1000];
    char *arr = (char *) malloc(MAX * (sizeof(char)));
    char *last_arr = (char *) malloc(MAX * (sizeof(char)));
    FILE *textfile;
    char *text;
    long numbytes;

    FILE *first = fopen(filename+1, "r");

    if (first == NULL) {
        printf("\nError Message: %s\n", strerror(errno));
        return;
    }


    fseek(first, 0, SEEK_END);
    length_file = ftell(first);
    fclose(first);

    textfile = fopen(filename+1, "r");

    fseek(textfile, 0L, SEEK_END);
    numbytes = ftell(textfile);
    fseek(textfile, 0L, SEEK_SET);

    text = (char *) calloc(numbytes, sizeof(char));

    fread(text, sizeof(char), numbytes, textfile);
    fclose(textfile);

    if (length_file == 0) {
        printf("This file is empty.\n");
        return;
    }
    if (length == 0) {

        printf("Please enter Numbers bigger than 0.\n");
        return;
    }

    for (int l = 0; l < length_file; l++) {
        if (text[l] == '\n')
            counter++;


    }
    if (counter < y) {
        printf("There not enough line in this File.\n");
        return;
    } else {
        counter = 1;
        i = 0;
        int m = 0;
        for (m = 0; m < length_file ; m++) {

            last_arr[m] = text[m];
            if (last_arr[m] == '\n') {

                counter++;
            }

            if (counter == y) {
                before = m;
                m++;

                while (text[m+1] != '\n') {
                    i++;
                    m++;

                }
                if (direction == 'f') {
                    if (i+1 < (x) + size) {
                        printf("There are not enough character in this line.\n");
                        return;
                    } else {
                        i = before + x+1;
                        memset(last_arr,0,m);
                        k=0;
                        for (; i < before +x +length+1 ; i++) {
                            last_arr[k] = text[i];
                            k++;
                        }


                        char clipboard[100] = "clipboard.txt";
                        FILE *betoche = fopen(clipboard, "w");
                        fputs(last_arr, betoche);
                        fclose(betoche);
                        return;
                    }
                } else if (direction == 'b') {

                    if (i+1 < (x)+size) {
                        printf("There are not enough character in this line.\n");
                        return;
                    } else {
                        memset(last_arr,0,m);
                        i = before+x-length;
                        k=0;
                        for (; i < before + x  ; i++) {
                            last_arr[k] = text[i];
                            k++;
                            printf("%d %d\n",k,i);
                        }

                        char clipboard[100] = "clipboard.txt";
                        FILE *betoche = fopen(clipboard, "w");
                        fputs(last_arr, betoche);
                        fclose(betoche);
                        return;
                    }


                }

            }

        }


    }
}

void cutstr(char *filename, int y, int x, int size, char *direction){

                copystr(filename, y, x, size, direction);
                removestr(filename, y, x, size, direction);


    }

        void pastestr(char *filename,int y, int x){

            FILE *textfile;
            char *text;
            long numbytes;

            FILE *first = fopen(filename+1, "r");

            if (first == NULL) {
                printf("\nError Message: %s\n", strerror(errno));
                return;
            }


            textfile = fopen("clipboard.txt", "r");
            fseek(textfile, 0L, SEEK_END);
            numbytes = ftell(textfile);
            fseek(textfile, 0L, SEEK_SET);

            text = (char *) calloc(numbytes, sizeof(char));
            fread(text, sizeof(char), numbytes, textfile);
            fclose(textfile);
            insert(filename,text,y,x);


        }




//pastestr --file /root/a.txt --pos 2:1 -size 3 -b

//--------------------------------------------------
int main() {



    //declare variables.
    char *input = (char *) malloc(MAX * (sizeof(char)));
    char *command = (char *) malloc(MAX * (sizeof(char)));
    char *ptr = (char *) malloc(MAX * (sizeof(char)));
    char *path = (char *) malloc(MAX * (sizeof(char)));
    char *filename = (char *) malloc(MAX * (sizeof(char)));
    char *str = (char *) malloc(MAX * (sizeof(char)));
    char *pos = (char *) malloc(MAX * (sizeof(char)));
    char direction[3];
    int x, y, size;
    char del;
//---------------------------------------------------

    while (1) {
        scanf("%s", input);

        if (strcmp(input, "exit") == 0)
            break;

        else if (strcmp(input, "createfile") == 0) {
            scanf("%s", command);
            if (strcmp(command, "--file") == 0) {
                scanf(" %[^\n]%*c", path);
                if ((path[0] != '/') && (path[0] != '"')) {
                    printf("please start path with (/) or double quotation\n");
                } else {
                    create_folder(path);
                    printf("creating file was successful.\n");
                }
            } else
                printf("please enter (--file) after (createfile)...\n");
        } else if (strcmp(input, "cat") == 0) {
            scanf("%s", command);
            if (strcmp(command, "--file") == 0) {               //function for printing content of file

                //scanf("%[^\n]%*c",filename);
                scanf(" %s", filename);
                cat(filename);

            } else
                printf("please enter (--file) after (cat)...\n");
        } else if (strcmp(input, "insertstr") == 0) {
            scanf("%s", command);
            if (strcmp(command, "--file") == 0) {          //function for inserting content in file

                scanf("%s", filename);
                scanf("%s", str);
                if (strcmp(str, "--str") == 0) {
                    memset(str, 0, 5);
                    scanf("%s", str);
                    scanf("%s", pos);
                    if (strcmp(pos, "--pos") == 0) {
                        scanf("%d%c%d", &y, &del, &x);
                        insert(filename, str, y, x);
                        printf("insert successfully done.\n");

                    } else
                        printf("please enter (--pos) after (str)...\n");

                } else
                    printf("please enter (--str) after (filename)...\n");
            } else
                printf("please enter (--file) after (insertstr)...\n");


        } else if (strcmp(input, "removestr") == 0) {
            scanf("%s", command);
            if (strcmp(command, "--file") == 0) {

                scanf("%s", filename);
                scanf("%s", pos);
                if (strcmp(pos, "--pos") == 0) {
                    scanf("%d%c%d", &y, &del, &x);
                    scanf("%s", str);
                    if (strcmp(str, "-size") == 0) {

                        scanf("%d", &size);
                        scanf("%s", direction);
                        removestr(filename, y, x, size, direction);

                    } else
                        printf("please enter (-size) after (pos)...\n");
                } else
                    printf("please enter (--pos) after (filename)...\n");


            } else
                printf("please enter (--file) after (removestr)...\n");
        }

        else if (strcmp(input,"copystr")==0){

            scanf("%s",command);
            if (strcmp(command,"--file")==0){

                scanf("%s", filename);
                scanf("%s", pos);
                 if (strcmp(pos, "--pos") == 0) {
                    scanf("%d%c%d", &y, &del, &x);
                    scanf("%s", str);
                    if (strcmp(str, "-size") == 0) {

                        scanf("%d", &size);
                        scanf("%s", direction);
                        copystr(filename, y, x, size, direction);

                    } else
                        printf("please enter (-size) after (pos)...\n");
                } else
                    printf("please enter (--pos) after (filename)...\n");


            } else
                printf("please enter (--file) after (copystr)...\n");
        }
        else if (strcmp(input, "cutstr") == 0) {
            scanf("%s", command);
            if (strcmp(command, "--file") == 0) {

                scanf("%s", filename);
                scanf("%s", pos);
                if (strcmp(pos, "--pos") == 0) {
                    scanf("%d%c%d", &y, &del, &x);
                    scanf("%s", str);
                    if (strcmp(str, "-size") == 0) {

                        scanf("%d", &size);
                        scanf("%s", direction);
                        cutstr(filename, y, x, size, direction);

                    } else
                        printf("please enter (-size) after (pos)...\n");
                } else
                    printf("please enter (--pos) after (filename)...\n");


            } else
                printf("please enter (--file) after (cutstr)...\n");
        }
         else if (strcmp(input, "cutstr") == 0) {
            scanf("%s", command);
            if (strcmp(command, "--file") == 0) {

                scanf("%s", filename);
                scanf("%s", pos);
                if (strcmp(pos, "--pos") == 0) {
                    scanf("%d%c%d", &y, &del, &x);
                    scanf("%s", str);
                    if (strcmp(str, "-size") == 0) {

                        scanf("%d", &size);
                        scanf("%s", direction);
                        cutstr(filename, y, x, size, direction);

                    } else
                        printf("please enter (-size) after (pos)...\n");
                } else
                    printf("please enter (--pos) after (filename)...\n");


            } else
                printf("please enter (--file) after (cutstr)...\n");
        }

        else if (strcmp(input, "pastestr") == 0) {
            scanf("%s", command);
            if (strcmp(command, "--file") == 0) {

                scanf("%s", filename);
                scanf("%s", pos);
                if (strcmp(pos, "--pos") == 0) {
                    scanf("%d%c%d", &y, &del, &x);

                        pastestr(filename, y, x);


                } else
                    printf("please enter (--pos) after (filename)...\n");


            } else
                printf("please enter (--file) after (pastestr)...\n");
        }
















            else if (strcmp(input,"1")==0){

                printf("createfile\n");
                printf("cat\n");
                printf("insertstr\n");
                printf("copystr\n");
                printf("pastestr\n");
                printf("cutstr\n");
                printf("undo\n");
                printf("removestr\n");

            }


            else {
            while (1) {
                if (getchar() == '\n') {
                    printf("invalid command\nfor seeing all the available commands enter 1.\n");
                    break;
                }
            }
        }
    }
}

