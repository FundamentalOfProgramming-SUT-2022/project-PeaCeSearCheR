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
            printf("%s\n", arr);
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
            printf("%s\n", arr);
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
    char a[500] = "0123456789";
    FILE *write_file = fopen(file_name, "w");
    fputs(a, write_file);
    fclose(write_file);
}

//-------------------------------------------------------
void cat(char *filename) {
    char c;
    FILE *fptr;
    fptr = fopen(filename + 1, "r");
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


void insert(char *filename, char *str, int x, int y) {

    int length = strlen(str), length_file;
    int k, i = 0, counter = 1,before,after;
    char c[1000];
    char *arr = (char *) malloc(MAX * (sizeof(char)));
    char *last_arr = (char *) malloc(MAX * (sizeof(char)));
    FILE *textfile;
    char *text;
    long numbytes;

    FILE *first = fopen(filename + 1, "r");

    if (first == NULL) {
        printf("\nError Message: %s\n", strerror(errno));
        return;
    }


    fseek(first, 0, SEEK_END);
    length_file = ftell(first);
    fclose(first);
    printf("%d\n", length_file);


    textfile = fopen(filename + 1, "r");

    fseek(textfile, 0L, SEEK_END);
    numbytes = ftell(textfile);
    fseek(textfile, 0L, SEEK_SET);

    text = (char *) calloc(numbytes, sizeof(char));

    fread(text, sizeof(char), numbytes, textfile);
    fclose(textfile);
    printf("%s\n", text);

    for (int l = 0; l < length_file; l++) {
        if (text[l] == '\n')
            counter++;
    }
    if (counter < y) {
        printf("There not enough line in this File.\n");
        return;
    } else {
        counter = 1;
        int m = 0;
        for (m = 0; m < length_file; m++) {
                last_arr[m] = text[m];
            if (text[m] == '\n')
                counter++;

            if (counter == y) {
                before=m;

                while (text[m] != '\n') {
                    i++;
                    m++;
                }

                if (i < (x)) {
                    printf("There are not enough character in this file.\n");
                    return;
                } else {
                    i = before;
                    for (; i < before + x; i++) {

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
                    printf("k = %d , i = %d  ,length = %d  , length_file = %d\n", k, i, length, length_file);

                    printf("%s\n", last_arr);
                    first = fopen(filename + 1, "w");
                    fputs(last_arr, first);
                    fclose(first);
                }
                return;
            }

        }

    }






    //insertstr --file /root/b.txt --str salam --pos 0:1
}


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
    int x, y;
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

                //scanf(" %[^\n]%*c",filename);
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
                        scanf("%d%c%d", &x, &del, &y);
                        insert(filename, str, x, y);
                    } else
                        printf("please enter (--pos) after (str)...\n");

                } else
                    printf("please enter (--str) after (filename)...\n");
            } else
                printf("please enter (--file) after (insertstr)...\n");
        } else {
            while (1) {
                if (getchar() == '\n') {
                    printf("invalid command\n");
                    break;
                }
            }
        }
    }
}

