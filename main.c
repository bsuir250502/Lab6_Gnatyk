#ifdef __cplusplus
extern "C" {
#endif
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#define input_buf_size 80
#define SIZE( x ) (sizeof( x )/sizeof( *x ))

    void clear_screen()
    {
#ifdef _WIN32
        system("cls");
#else
        system("clear");
#endif
    }

    char Spis1[]="f_t";
    char Spis2[]="f_bin";

    FILE *Open_file(char*file,char*code)
    {
        FILE*f;
        if(!(f = fopen(file,code))){
            puts("Error!");
            exit(1);
        }
        else return f; 
    }

    void checkHelp(void)
    {
        printf
            ("=============================================================================================================\n"
            "MANUAL:\n"
            "enter the number, \n"
            "=================================OPTIONS=====================================================================\n"
            "1. To enter numbers into a text and binary file(для окончания ввод нажмите - 0)\n"
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
        clear_screen();
        return c;
    }

    int* peresap_tex_f(char*file_name ,int koll_t,int *txt)
    {
        FILE *f;
        f = Open_file(Spis2,"r");
        int i;
        for (i = 0; i < koll_t; i++) {
            fscanf(f,"%d",&txt[i]);
            if (feof(f)) {
                break;
            }
        }
        return txt;
    }

    int* peresap_bin_f(char*binary_file_name ,int koll_bin,int *binary)
    {
        FILE *fb;
        fb = Open_file(Spis1,"rb");
        int i;
        for (i = 0; i< koll_bin; i++) {
            fread(&binary[i],sizeof(int),1,fb);
            if (feof(fb)) {
                break;
            }
        }
        return binary;
    }

    int * del (int *binary,int *txt,int* koll_t,int koll_bin)
    {
        int i,j,del_txt;
        for(i = 0; i < koll_bin; i++){
            for(j = 0; j < *koll_t; j++){
                if(txt[j] == binary[i]){
                    for(del_txt = j; del_txt < (*koll_t-1); del_txt++){
                        txt[del_txt] = txt[del_txt +1];
                    }
                    *koll_t-=1;

                }
            }
        }
        return txt;
    }

    int f_creat(char* file_name)
    {
        FILE * f;  
        int i1,koll_t=0;
        f= Open_file(Spis2,"w+");
        puts("Enter a number in a TEXT file");
        puts("To exit, press - 0");
        while(1){
            scanf("%d",&i1);
            if(i1 == 0){
                break;
            }
            koll_t++;
            fprintf(f,"%3d",i1);
        }
        fclose(f);
        return koll_t;
    }

    int fb_creat(char* binary_file_name )
    {
        int i2,koll_bin=0;
        FILE * fb;
        fb= Open_file(Spis1,"w+b");
        puts("Enter a number in the BINARY file");
        puts("To exit, press - 0");
        while(1){
            scanf("%d",&i2);
            if(i2 == 0){
                break;
            }
            koll_bin ++;
            fwrite(&i2,sizeof(int),1,fb);
        }
        fclose(fb);
        return koll_bin;
    }

    void print_binFile(char* binary_file_name,int koll_bin)
    {
        int i;
        int * bin_ms;
        bin_ms = (int *) calloc(koll_bin, sizeof(int));
        FILE * fb;
        fb = Open_file(Spis1,"rb");
        printf ("BINARY FILE");
        for(i = 0; i < koll_bin; i ++) {
            fread(&bin_ms[i], sizeof(int), 1, fb);
            if(feof(fb)) {
                break;
            }
        }
        printf ("\n");
        for(i = 0; i < koll_bin; i++) {
            printf("%d",bin_ms[i]);
        }
        printf ("\n");
        fclose(fb);
    }

    void printf_txtFIle(char*file_name ,int koll_t) {
        int i;
        int *t_ms;
        t_ms = (int *) calloc(koll_t, sizeof(int));
        FILE * f;
        f = Open_file(Spis2,"r");
        printf ("TEXT FILE");
        for(i = 0; i < koll_t; i ++) {
            fscanf(f, "%2d", &t_ms[i]);
            if(feof(f)) {
                break;
            }
        }
        printf ("\n");
        for(i = 0; i < koll_t; i++) {
            printf("%d",t_ms[i]);
        }
        printf ("\n");
        fclose(f);
    }

    int * search_of_the_same_elem(char*file_name ,int koll_t,char* binary_file_name,int koll_bin)
    {
        FILE *f,*fb;
        int i_txt,i_b,del_txt;
        int i,j;
        int *txt;
        int *binary;
        txt = (int *) calloc(koll_t, sizeof(int));
        binary = (int *) calloc(koll_bin, sizeof(int));
        fb = Open_file(Spis1,"rb");
        f = Open_file(Spis2,"r");
        peresap_tex_f(file_name ,koll_t,txt);
        peresap_bin_f(binary_file_name , koll_bin, binary);
        rewind(f);
        rewind(fb);
        txt= del (binary,txt, &koll_t, koll_bin);
        f = Open_file(Spis2,"r");
        for(i_txt = 0; i_txt < koll_t; i_txt++){
            fprintf(f,"%2d",&txt[i_txt]);
        }
        printf_txtFIle(file_name , koll_t);
        fclose(f);
        fclose(fb);
        return 0;
    }

    int main(int argc, char **argv)
    {

        FILE *f,*fb;
        int  koll_t=0,koll_bin=0;
        fb=Open_file(Spis1,"w+b");
        f=Open_file(Spis2,"w+");
        char*  file_name = (char *) calloc(10, sizeof(char));
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
                koll_t=f_creat(file_name);
                koll_bin=fb_creat(binary_file_name);
                break;
            case 2 :
                print_binFile( binary_file_name, koll_bin);
                printf ("\n");
                printf_txtFIle(file_name, koll_t);
                printf ("\n");
                break;
            case 3 :
                search_of_the_same_elem(file_name , koll_t, binary_file_name, koll_bin);
                break;
            case 4 :
                exit(0);break;
            case 5 :
                checkHelp();break;

            }
        }
    }

#ifdef __cplusplus
}
#endif
