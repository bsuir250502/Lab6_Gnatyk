#ifdef __cplusplus
extern "C" {
#endif
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <malloc.h>
#define N 150
#define input_buf_size 80
#define SIZE( x ) (sizeof( x )/sizeof( *x ))
    struct tree{
        char* data;
        struct tree * left;
        struct tree * right;
        int n;

    };

    void clear_screen()
    {
#ifdef _WIN32
        system("cls");
#else
        system("clear");
#endif
    }

    char*gets_s(char *s, size_t buf_size)
    {
        char *result;
        result = fgets(s, buf_size, stdin);
        result[strlen(s) - 1] = '\0';
        return result;
    }
    tree* create_a_tree( struct tree* tree)
    {
        if(tree){
            return(tree);
        }
        if(!(tree = (struct tree *)calloc(1,sizeof(struct tree)))){
            puts("There is no free memory");
            return NULL;
        }
        puts("Click any number,to fill the root of the tree");
        tree->data = (char*)calloc(1,sizeof(char)*N);
        gets_s(tree->data,N);
        tree->n = 1;
        return tree;
    }

    void add_nodes_to_the_tree(struct tree* tree)
    {
        struct tree *tr1, *tr2;
        char * st;
        int k;
        int flag;
        int st_size = SIZE(st);
        if(!tree){
            puts("no root\n");
            return;
        }
        do{
            puts("enter the informationfor the end of write- ex");
            st = (char*)calloc(1,sizeof(char)*N);
            gets_s(st,st_size);
            if(!strcmp(st,"ex")){
                return;
            }
            if(!*st)return;
            tr1 = tree;
            flag = 0;
            do{
                if(!(k = strcmp(st,tr1->data))){
                    tr1->n++;
                    flag = 1;
                }
                else{
                    if(k < 0){
                        if(tr1->left){
                            tr1 = tr1->left;
                        }
                        else flag = 1;
                    }
                    else{
                        if(tr1->right){
                            tr1= tr1->right;
                        }
                        else flag = 1;
                    }
                }
            }
            while( flag == 0);
            if(k)
            {
                if(!(tr2 = (struct tree *)calloc(1,sizeof(struct tree)))){
                    puts("There is no free memory\n");
                    return;
                }
                if(k < 0){
                    tr1->left = tr2;
                }
                else{
                    tr1->right = tr2;
                }
                tr2->data = (char*)calloc(1,sizeof(char)*N);
                strcpy(tr2->data,st);
                tr2->n = 1;
            }
            free(st);
        }while(1);
    }

    void checkHelp(void)
    {
        printf
            ("=============================================================================================================\n"
            "MANUAL:\n"
            "filling the tree information \n"
            "=================================OPTIONS=====================================================================\n"
            "1. input tree root\n"
            "2. tree view\n"
            "3. maximum viewing element node\n"
            "4. Help\n"
            "5. Exit\n"
            "=============================================================================================================\n");
        exit(0);

    }

    int menu_select()
    {
        char s[input_buf_size];
        int c;
        puts("1. add information");
        puts("2. see details ");
        puts("3. search max");
        puts("4. Help"); 
        puts("5. to exit");
        do{
            printf("\nEnter the number of the desired item\n");
            gets_s(s, input_buf_size);
            c = atoi(s);
        }
        while (c < 0 || c > 5);
        clear_screen();
        return c;
    }

    void see_tree (struct tree * tr1,int level)
    {
        if(tr1){
            see_tree(tr1->right,level+5);
        }
        for(int i = 0; i < level; ++i){
            printf("   ");
        }
        if(tr1){
            printf("%s\n",tr1->data);
        }
        else printf("\n");
        if(tr1){
            see_tree(tr1->left,level+5);
        }
    }


    tree * search_node_maximum_value(struct tree * current,struct tree*max) 
    {
        if(current->data > max->data){
            max = current;
        }
        if(current->left){ 
            max = search_node_maximum_value(current->left,max); 
        }
        if(current->right){
            max = search_node_maximum_value(current->right,max); 
        }
        return max;
    }

    int main()
    {
        int level = 0;
        struct tree* max=0;
        struct tree* tree = NULL;
        tree = create_a_tree(tree);
        char choice;
        while(1){
            choice = menu_select();

            switch (choice){
            case 1 : 
                add_nodes_to_the_tree( tree);
                break;
            case 2 : 
                see_tree(tree,level);break;
            case 3 :
                max = search_node_maximum_value(tree,tree);
                printf("maximym: %s\n ", max->data );break;
            case 4 :
                checkHelp();break;
            case 5 :
                exit(0);break;
            }
        }
    }


#ifdef __cplusplus
}
#endif
