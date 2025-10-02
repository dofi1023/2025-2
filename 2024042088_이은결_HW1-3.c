#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

/**
 * Auto-generated code below aims at helping you parse
 * the standard input according to the problem statement.
**/

typedef struct{
    char title[1025];
    int rank;
    int tbr;
} Book;

int compare(const void* a, const void* b){
    return strcmp(((Book*)a)->title, ((Book*)b)->title);
}

int findbook(Book books[], int count, char* title){
    for(int i = 0;i <count; i++){
        if(strcmp(books[i].title, title) == 0){
            return i;
        }
    }
    return -1;
}

int main()
{
    int b,n; //새 책의 갯수
    char newbooks[1025][1025];
    Book bookshelf[1025];

    scanf("%d", &b); fgetc(stdin); //책 개수를 받아서

    
    for (int i = 0; i < b; i++) { //새 책의 제목 받기
        scanf("%[^\n]", newbooks[i]); fgetc(stdin);
    }

    scanf("%d", &n); fgetc(stdin); 

    for (int i = 0; i < n; i++) { //입력받기
        char name[1025];
        scanf("%[^\n]", name); fgetc(stdin); //한 줄 입력 받고

        char * last = strrchr(name, ' ');
        char * rankstr = last + 1;
        *last = '\0';
        strcpy(bookshelf[i].title, name);

        if(strcmp(rankstr, "None") == 0){
            bookshelf[i].rank = -1;
            bookshelf[i].tbr = 1;

        }
        else {
            bookshelf[i].rank = atoi(rankstr);
            bookshelf[i].tbr = 0;
        }
    }
    
    int maxr = -2;
    for(int i = 0; i<n ;i++){
        if(bookshelf[i].tbr == 0 && bookshelf[i].rank > maxr){
            maxr = bookshelf[i].rank;
        }
    }

    Book temp[1025];
    int tmpc = 0;
    for(int i =0 ; i<n;i++){
        temp[tmpc] = bookshelf[i];
        tmpc++;
    }


    
    //새 책부터 먼저 중복이 있는지 해줘야함
    //중복 삭제하기
    for(int i = 0 ; i < b; i++){

        int a = findbook(temp, tmpc, newbooks[i]);
       
            if(a == -1) //중복및, tbr아님, 최고랭크 아님
            {  
                strcpy(temp[tmpc].title, newbooks[i]);
                temp[tmpc].rank = -1;
                temp[tmpc].tbr = 1;
                tmpc++;
                
            }
            else{
                temp[a].rank = -1;
                temp[a].tbr = 1;
            }
        
    }

    //가장 낮은 랭크 삭제하기, tbr은 지우지 않기
    int need = tmpc;

    if(need > n){
        while(need > n && tmpc > 0){
            int minrank = 11;
            for(int i = 0; i< tmpc;i++){
                if(temp[i].tbr == 0 && temp[i].rank != maxr){
                    if(temp[i].rank < minrank){
                        minrank = temp[i].rank;
                    }
                }
            }

            if(minrank == 11){
                break;
            }

            Book newtemp[1025];
            int newtc = 0;
            for(int i = 0; i < tmpc ; i++){
                if(temp[i].tbr == 1 || temp[i].rank == maxr || temp[i].rank != minrank){
                    newtemp[newtc] = temp[i];
                    newtc++;
                }
            }

            tmpc = newtc;
            for(int i=0; i<tmpc ;i++){
                temp[i] = newtemp[i];
            }
            need = tmpc;
        }
    }

    if(need > n){
        printf("Your TBR is out of control Clara!\n");
        return 0;
    }
    
    Book lastbook[1025];
    int cnt = tmpc;

    for(int i =0 ;i < tmpc; i++){
        lastbook[i] = temp[i];
    }

    qsort(lastbook, cnt, sizeof(Book), compare);
    for(int i=0; i< cnt; i++){
        printf("%s\n", lastbook[i].title);
    }
    return 0;

    // Write an answer using printf(). DON'T FORGET THE TRAILING \n
    // To debug: fprintf(stderr, "Debug messages...\n");

}