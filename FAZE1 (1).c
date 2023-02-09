#include<stdio.h>
#include<stdlib.h>
#include<dir.h>
#include<sys/stat.h>
#include<string.h>
#include<stdbool.h>
#include<dirent.h>
#include<sys/types.h>
#include <errno.h>
#include <windows.h>
#define MAX 10000000
#include<math.h>

void create_file(char *file_name);

  char *pathfinder(char* ptr)
  {
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
            strcpy(text, arr);
            memset(arr, 0, length_of_command);
            j = 0;
        }
                return text;
  }
  }

  void helping_undo(char *filename){
    int  length_file;
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

   FILE* feri =fopen(pathfinder(filename),"w");
    fputs(text,first);
    fclose(feri);
  }


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
        rmdir(text);
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
            rmdir(text);
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
        printf("File Data : \n");
        while (c != EOF) {
            printf("%c", c);
            c = fgetc(fptr);
        }
        printf("\n");
        fclose(fptr);
    }
}


void insert(char *filename, char *str, int y, int x) {
    helping_undo(filename);

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




    for (int i = 0; *(str+i)!='\0'; i++) {
       length = strlen(str);
        if (str[i] == 92) {
            if ((str[i+1] == 'n') && (str[i-1] != 92)) {
                str[i] = 10;
                for (int j = i + 1; j < length-1; j++) {
                    str[j] = str[j+1];
                }
                *(str + length-1) = '\0';
                *(str + length) = '\0';
            }
            if ((str[i+1] == 'n') && (str[i-1] == 92)) {

                for (int j = i; j < length-1; j++) {
                    str[j] = str[j+1];
                }
                str[length-1] = '\0';
                str[length] = '\0';
            }
        }
    }


    if (length_file == 0 && x == 0 && y == 1) {
        strcpy(last_arr, str);
        first = fopen(filename+1, "w");
        fputs(last_arr, first);
        fclose(first);
        printf("inserting was successfully done.\n");
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
        printf("There are not enough line in this File.\n");
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

                if (i + 1 < (x) ) {
                    printf("There are not enough character in this File.\n");
                    return;
                } else {
                     if (y ==1){


                          for (i=0; i < x ; i++) {

                         last_arr[i] = text[i];
                     }

                     for (k = 0; k < length; k++) {

                         last_arr[i+k] = str[k];
                     }
                     k = i+k;
                     for (; k < length + length_file; k++) {

                         last_arr[k] = text[i];
                         i++;
                     }
                        first = fopen(filename+1, "w");
                        fputs(last_arr, first);
                        fclose(first);
                        printf("insert was successfully done.\n");
                         return;
                     }

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
                    printf("insert was successfully done.\n");
                }
            }

        }

    }






    //insertstr --file /root/a.txt --str salam --pos 1:0
}


void removestr(char *filename, int y, int x, int size, char *direction1) {
    helping_undo(filename);
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
                        printf("removing was successfully done.\n");
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
                        printf("removing was successfully done.\n");
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

                } else if (direction == 'b') {


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

void cutstr(char *filename, int y, int x, int size, char *direction){
                helping_undo(filename);

                copystr(filename, y, x, size, direction);
                removestr(filename, y, x, size, direction);


    }

        void pastestr(char *filename,int y, int x){
            helping_undo(filename);
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
        void undo(char*filename){


            FILE *textfile,*textfile2;
            char *text,*text2;
            long numbytes,numbytes2;

            FILE *first = fopen(filename+1, "r");

            if (first == NULL) {
                printf("\nError Message: %s\n", strerror(errno));
                return;
            }
            fclose(first);


            textfile = fopen(pathfinder(filename), "r");
            fseek(textfile, 0L, SEEK_END);
            numbytes = ftell(textfile);
            fseek(textfile, 0L, SEEK_SET);

            text = (char *) calloc(numbytes, sizeof(char));
            fread(text, sizeof(char), numbytes, textfile);
            fclose(textfile);

            textfile2 = fopen(filename+1, "r");
            fseek(textfile2, 0L, SEEK_END);
            numbytes2 = ftell(textfile);
            fseek(textfile2, 0L, SEEK_SET);

            text2 = (char *) calloc(numbytes2, sizeof(char));
            fread(text2, sizeof(char), numbytes2, textfile2);
            fclose(textfile2);

            first =fopen(filename+1,"w");
            fputs(text,first);
            fclose(first);
          FILE * first2 =fopen(pathfinder(filename),"w");
            fputs(text2,first2);
            fclose(first2);





        }

        void directory_tree(char *basepath, int current_depth, int depth) {

      if (depth == -1) {
        directory_tree(basepath, current_depth, 1000);
        return;
    }
    if (current_depth > depth) return;
    char path[1000];
    struct dirent *dp;
    DIR *dir = opendir(basepath);
    if (!dir) return;
    while ((dp = readdir(dir)) != NULL) {
        if (strcmp(dp->d_name, ".") != 0 && strcmp(dp->d_name, "..") != 0) {
            printf("|");
            for (int i = 0; i < current_depth; i++) {
                printf("--");
            }
            printf("%s\n", dp->d_name);
            strcpy(path, basepath);
            strcat(path, "/");
            strcat(path, dp->d_name);
            directory_tree(path, current_depth + 1, depth);
        }
    }
    closedir(dir);
    return;
        }


        void compare(char*filename,char* filename2){

        FILE *textfile,*textfile2;
            char *text,*text2,*text3,*text4;
            text3=(char*)malloc(MAX*sizeof(char));
            text4=(char*)malloc(MAX*sizeof(char));
            long numbytes,numbytes2,counter=1,counter2=1;

            FILE *first = fopen(filename+1, "r");

            if (first == NULL) {
                printf("\nError Message: %s\n", strerror(errno));
                return;
            }
            fclose(first);

            FILE *second = fopen(filename2+1, "r");

            if (second == NULL) {
                printf("\nError Message: %s\n", strerror(errno));
                return;
            }
            fclose(first);



            textfile = fopen(filename+1, "r");

            fseek(textfile, 0L, SEEK_END);
            numbytes = ftell(textfile);
            fseek(textfile, 0L, SEEK_SET);

            text = (char *) calloc(numbytes, sizeof(char));
            fread(text, sizeof(char), numbytes, textfile);
            fclose(textfile);

            textfile2 = fopen(filename2+1, "r");
            fseek(textfile2, 0L, SEEK_END);
            numbytes2 = ftell(textfile);
            fseek(textfile2, 0L, SEEK_SET);

            text2 = (char *) calloc(numbytes2, sizeof(char));
            fread(text2, sizeof(char), numbytes2, textfile2);
            fclose(textfile2);
            for (int i =0 ; i < strlen(text); i++){
                if (text[i]=='\n')
                    counter++;
            }
         for (int i =0 ; i < strlen(text2); i++){
                if (text2[i]=='\n')
                    counter2++;
            }




            int max ,j,k,m;
            if(counter2 >= counter && strlen(text2)>= strlen(text)) {
                max = strlen(text2);
            }
            else max=strlen(text);

            int min ;

            if(counter2 <= counter && strlen(text2)<=strlen(text))
                min =strlen(text2);

            else
            min = strlen(text) ;
            counter=1;
            for(int i = 0 ; i < min ; i ++ ){
               if(text[i]=='\n'){
                    counter++;
                    j=i;
                    m=i;
               }

            if(text[i]!=text2[i]){
                    i=0;
                    j++;
                    m++;
                    while(text2[j]!='\n'  )
                    {

                        text4[i]=text2[j];
                        i++;
                        j++;
                    }
                    int n=0;
                    while(text[m]!='\n'){

                        text3[n]=text[m];
                        n++;
                        m++;

                    }
                        k=max(j,m);
                    break;


        }
    }
    printf("*******%d*******\n",counter);
    printf("%s\n%s\n",text3,text4);
    for(int i = k-counter+1 ; i < max  ; i++ ){
       if (max ==strlen(text2))
           printf("%c",text2[i]);

           else if (max==(strlen(text)))
                printf("%c",text[i]);
    }
    printf("\n");

 }






//cutstr --file /root/a.txt --pos 2:1 -size 3 -b

//--------------------------------------------------
int main() {



    //declare variables.
    char *input = (char *) malloc(MAX * (sizeof(char)));
    char *command = (char *) malloc(MAX * (sizeof(char)));
    char *ptr = (char *) malloc(MAX * (sizeof(char)));
    char *path = (char *) malloc(MAX * (sizeof(char)));
    char *filename = (char *) malloc(MAX * (sizeof(char)));
    char *filename2 = (char *) malloc(MAX * (sizeof(char)));
    char *str = (char *) malloc(MAX * (sizeof(char)));
    char *pos = (char *) malloc(MAX * (sizeof(char)));
    char direction[3];
    int x, y, size,depth;
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


        else if (strcmp(input,"tree")==0){


            scanf("%d",&depth);
            if (depth>=-1)
            directory_tree("./root",0,depth);
            else
                printf("Invalid depth\n");
        }

        else if (strcmp(input,"undo")==0){

            scanf("%s",command);
            if (strcmp(command, "--file")==0){
                scanf("%s",filename);
                undo(filename);
            }
            else
                printf("please enter (--file) after (undo)...\n");
        }

            else if(strcmp(input,"compare")==0){

                    scanf("%s",filename);
                    scanf("%s",filename2);
                    compare(filename,filename2);
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
                printf("tree\n");
                printf("compare\n");
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
    return 0;
}
