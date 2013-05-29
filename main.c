#ifdef __cplusplus
extern "C" {
#endif
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#define input_buf_size 80
#define SIZE( x ) (sizeof( x )/sizeof( *x ))

    char spis_1[]="f_bin";
    char spis_2[]="f_txt";

    FILE *open_file(char*file, char*code)
    {
        FILE*f;
        if(!(f = fopen(file,code))) {
            puts("Error!");
            exit(1);
        }
        else return f; 
    }

    void check_help(void)
    {
        printf
            ("=============================================================================================================\n"
            "MANUAL:\n"
            "enter the number, \n"
            "=================================OPTIONS=====================================================================\n"
            "1. To enter numbers into a text and binary file(��� ��������� ���� ������� - 0)\n"
            "2. To view the text and binary file\n"
            "3. To view the text after removing it from the elements\n"
            "4. Help\n"
            "5. Exit\n"
            "=============================================================================================================\n");


    }

    int menu_select()
    {
        char s[input_buf_size];
        int c;
        puts("1. Write the numbers in the text and binary file ");
        puts("2. View text and binary file ");
        puts("3. From a text file to remove the numbers contained in a binaryfile "); 
        puts("4. To exit ");
        puts("5. Help ");
        do{
            printf("\nEnter the number of the desired item\n");
            gets_s(s, input_buf_size);
            c = atoi(s);
        }
        while (c < 0 || c > 6);

        return c;
    }

    int* read_text_file(char*file_name, int number_of_elements_text_file, int *txt)
    {
        FILE *f;
        f = open_file(spis_2,"r");
        int i;
        for (i = 0; i < number_of_elements_text_file; i++) {
            fscanf(f,"%d",&txt[i]);
            if (feof(f)) {
                break;
            }
        }
        return txt;
    }

    int* read_bin_f(char*binary_file_name ,int number_of_elements_binary_file,int *binary)
    {
        FILE *fb;
        fb = open_file(spis_1,"rb");
        int i;
        for (i = 0; i< number_of_elements_binary_file; i++) {
            fread(&binary[i],sizeof(int),1,fb);
            if (feof(fb)) {
                break;
            }
        }
        return binary;
    }

    int * delete_the_item (int *binary,int *txt,int* number_of_elements_text_file,int number_of_elements_binary_file)
    {
        int i, j, delete_the_item_txt;
        for(i = 0; i < number_of_elements_binary_file; i++){
            for(j = 0; j < *number_of_elements_text_file; j++){
                if(txt[j] == binary[i]){
                    for(delete_the_item_txt = j; delete_the_item_txt < (*number_of_elements_text_file-1); delete_the_item_txt++){
                        txt[delete_the_item_txt] = txt[delete_the_item_txt +1];
                    }
                    *number_of_elements_text_file-=1;

                }
            }
        }
        return txt;
    }

    int loading_the_text_file(char* file_name)
    {
        FILE * f;  
        int i1, number_of_elements_text_file = 0;
        f = open_file(spis_2,"w+");
        puts("Enter a number in a TEXT file");
        puts("To exit, press - 0");
        while(1){
            scanf("%d",&i1);
            if(i1 == 0){
                break;
            }
            number_of_elements_text_file++;
            fprintf(f,"%3d",i1);
        }
        fclose(f);
        return number_of_elements_text_file;
    }

    int loading_the_binary_file(char* binary_file_name )
    {
        int i2,number_of_elements_binary_file=0;
        FILE * fb;
        fb= open_file(spis_1,"w+b");
        puts("Enter a number in the BINARY file");
        puts("To exit, press - 0");
        while(1){
            scanf("%d",&i2);
            if(i2 == 0){
                break;
            }
            number_of_elements_binary_file ++;
            fwrite(&i2,sizeof(int),1,fb);
        }
        fclose(fb);
        return number_of_elements_binary_file;
    }

    void print_bin_file(char* binary_file_name,int number_of_elements_binary_file)
    {
        int i;
        int * bin_ms;
        bin_ms = (int *) calloc(number_of_elements_binary_file, sizeof(int));
        FILE * fb;
        fb = open_file(spis_1,"rb");
        printf ("BINARY FILE");
        for(i = 0; i < number_of_elements_binary_file; i ++) {
            fread(&bin_ms[i], sizeof(int), 1, fb);
            if(feof(fb)) {
                break;
            }
        }
        printf ("\n");
        for(i = 0; i < number_of_elements_binary_file; i++) {
            printf("%d",bin_ms[i]);
        }
        printf ("\n");
        fclose(fb);
    }

    void printf_txt_file(char*file_name ,int number_of_elements_text_file) {
        int i;
        int *t_ms;
        t_ms = (int *) calloc(number_of_elements_text_file, sizeof(int));
        FILE * f;
        f = open_file(spis_2,"r");
        printf ("TEXT FILE");
        for(i = 0; i < number_of_elements_text_file; i ++) {
            fscanf(f, "%2d", &t_ms[i]);
            if(feof(f)) {
                break;
            }
        }
        printf ("\n");
        for(i = 0; i < number_of_elements_text_file; i++) {
            printf("%d",t_ms[i]);
        }
        printf ("\n");
        fclose(f);
    }

    int * search_of_the_same_elem(char*file_name ,int number_of_elements_text_file,char* binary_file_name,int number_of_elements_binary_file)
    {
        FILE *f,*fb;
        int i_txt;
        int *txt;
        int *binary;
        txt = (int *) calloc(number_of_elements_text_file, sizeof(int));
        binary = (int *) calloc(number_of_elements_binary_file, sizeof(int));
        fb = open_file(spis_1,"rb");
        f = open_file(spis_2,"r");
        read_text_file(file_name ,number_of_elements_text_file,txt);
        read_bin_f(binary_file_name , number_of_elements_binary_file, binary);
        rewind(f);
        rewind(fb);
        txt= delete_the_item (binary,txt, &number_of_elements_text_file, number_of_elements_binary_file);
        f = open_file(spis_2,"r");
        for(i_txt = 0; i_txt < number_of_elements_text_file; i_txt++){
            fprintf(f,"%2d",&txt[i_txt]);
        }
        printf_txt_file(file_name , number_of_elements_text_file);
        fclose(f);
        fclose(fb);
        return 0;
    }

    int main(int argc, char **argv)
    {

        FILE *f,*fb;
        int number_of_elements_text_file=0,number_of_elements_binary_file=0;
        fb = open_file(spis_1,"w+b");
        f = open_file(spis_2,"w+");
        char* file_name = (char *) calloc(10, sizeof(char));
        char* binary_file_name = (char *) calloc(10, sizeof(char));
        if (argc == 3) {
            strcpy(file_name, argv[1]);
            strcpy(binary_file_name, argv[2]);
        }
        char choice;
        while(1){
            choice = menu_select();
            switch(choice){
            case 1 :
                number_of_elements_text_file = loading_the_text_file(file_name);
                number_of_elements_binary_file = loading_the_binary_file(binary_file_name);
                break;
            case 2 :
                print_bin_file( binary_file_name, number_of_elements_binary_file);
                printf ("\n");
                printf_txt_file(file_name, number_of_elements_text_file);
                printf ("\n");
                break;
            case 3 :
                search_of_the_same_elem(file_name , number_of_elements_text_file, binary_file_name, number_of_elements_binary_file);
                break;
            case 4 :
                exit(0);break;
            case 5 :
                check_help();break;

            }
        }
    }

#ifdef __cplusplus
}
#endif
