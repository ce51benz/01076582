/*******************************************
* 01076582 - Assignment 2                  *
* Members:                                 *
* 1.55010006 Kanokporn   Chuangcham        *
* 2.55010977 Maturose    Kappako           *
* 3.55011362 Suratchanan Kraidech          *
*******************************************/
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <ctype.h>

#define SIZE 500000
typedef struct _pzstate{
    char sol[40];
    char cappz[3][3];
    int sollen;
    int fn;
}pzstate;


//OK
typedef struct _arrpos{
    int r;
    int c;
}arrpos;

//OK
typedef struct _pzqueue{
    long front;
    long rear;
    long size;
    pzstate *q;    
}puzzleQueue;

//OK
void extendQueue(puzzleQueue *queue){
    pzstate *temp = queue->q;
    int i,bfsize = queue->size;

    queue->size = queue->size * 2;

    queue->q = (pzstate*)malloc(sizeof(pzstate)*queue->size);
    for(i = 0;i < bfsize;i++){
        queue->q[i] = temp[i];
        
    }
    free(temp);
}

//OK
void initQueue(puzzleQueue *queue){
    queue->front = 0;
    queue->rear = -1;
    queue->size = SIZE;
    queue->q = (pzstate*)malloc(sizeof(pzstate)*queue->size);
}

//OK
int isQueueFull(puzzleQueue *queue){
    return queue->rear + 1 == queue->size;
}

//OK
void enQueue(puzzleQueue *queue,pzstate data){
    if(isQueueFull(queue))
        extendQueue(queue);
    queue->q[++(queue->rear)] = data;
}

//OK
pzstate deQueue(puzzleQueue *queue){
    return queue->q[(queue->front)++];
}

void merge(pzstate *,int,int,int,int);
void mergesort(pzstate *list,int left,int right){
    if(left != right){
        if(left+1 != right){
            mergesort(list,left,(left+right)/2);
            mergesort(list,(left+right)/2+1,right);
        }
        merge(list,left,(left+right)/2,(left+right)/2+1,right);
    }
}

void merge(pzstate *list,int l1,int r1,int l2,int r2){
    int p1 = l1,p2 = l2,ind = 0;
    pzstate temp[r2-l1+1];
    while(p1 <= r1 && p2 <= r2){
        if(list[p1].fn <= list[p2].fn){
            temp[ind++] = list[p1++];
        }
        else{
            temp[ind++] = list[p2++];
        }
    } 
    if(p1 <= r1){
         while(p1 <= r1)
            temp[ind++] = list[p1++];
    }
    else{
        while(p2 <= r2)
            temp[ind++] = list[p2++];
    }
    ind--;
    for(p1 = r2;p1 >= l1;p1--)
        list[p1] = temp[ind--];
}



char puzzle[3][3] = {{'1','2','3'},{'4','5','6'},{'7','8',' '}};
char goal[3][3] = {{'1','2','3'},{'4','5','6'},{'7','8',' '}};
char start[3][3];
//char puzzle[3][3] = {{'1','2','3'},{'4','5','6'},{'7',' ','8'}};

//char puzzle[3][3] = {{'8','6','7'},{'2','5','4'},{'3',' ','1'}};

char direction[4] = {'U','L','D','R'};
char sol[100];
//int brow=2,bcol=1;
int brow=2,bcol=2;

int mhtdis();
int wrongtiledis();

int isDuplicate(puzzleQueue *queue){
    long i,j,k;
    for(i = 0;i <= queue->rear;i++){
    
        for(j = 0;j < 3;j++)
            for(k = 0;k < 3;k++)
                if(puzzle[j][k] != (queue->q[i]).cappz[j][k]) goto checkpoint;
    return 1;
    checkpoint:
        continue;
    }
    return 0;
}


arrpos findPos(int type,char ch){
    int i,j;
    arrpos ans;
    ans.r = 0;
    ans.c = 0;
    if(type == 0){
        for(i = 0;i < 3;i++){
            for(j = 0;j < 3;j++){    
                if(puzzle[i][j] == ch){
                    ans.r = i;
                    ans.c = j;
                    return ans;
                }
            }
        }
    }
    else{
        for(i = 0;i < 3;i++){
            for(j = 0;j < 3;j++){    
                if(goal[i][j] == ch){
                    ans.r = i;
                    ans.c = j;
                    return ans;
                }
            }
        }
    }
    return ans;
}

int isFinalStates(){
    return puzzle[0][0] == '1' && puzzle[0][1] == '2' && puzzle[0][2] == '3' && puzzle[1][0] == '4' && puzzle[1][1] == '5' && puzzle[1][2] == '6' && puzzle[2][0] == '7' && puzzle[2][1] == '8' && puzzle[2][2] == ' ';
}
void printPuzzle(){
    int i,j;
    for(i=0;i<3;i++){
        printf(" ");
        for(j=0;j<3;j++){
            printf("%c",puzzle[i][j]);
            if(j+1<3)printf(" | ");
        }
        printf("\n");
    }
    printf("\n");
}

void printStartPuzzle(){
    int i,j;
    for(i=0;i<3;i++){
        printf(" ");
        for(j=0;j<3;j++){
            printf("%c",start[i][j]);
            if(j+1<3)printf(" | ");
        }
        printf("\n");
    }
    printf("\n");
}

int mvblank(char dir){
    if(dir == 'U'){
        if (brow > 0){
            puzzle[brow][bcol] = puzzle[brow-1][bcol];
            brow--;
            puzzle[brow][bcol] = ' ';
            return 1;
        }
        return 0;
    }
    else if(dir == 'L'){
        if (bcol > 0){
            puzzle[brow][bcol] = puzzle[brow][bcol-1];
            bcol--;
            puzzle[brow][bcol] = ' ';
            return 1;
        }
        return 0;
    }
    else if(dir == 'D'){
        if(brow < 2){
            puzzle[brow][bcol] = puzzle[brow+1][bcol];
            brow++;
            puzzle[brow][bcol] = ' ';
            return 1;
        }
        return 0;
    }
    else{
        if (bcol < 2){
            puzzle[brow][bcol] = puzzle[brow][bcol+1];
            bcol++;
            puzzle[brow][bcol] = ' ';
            return 1;
        }
        return 0;
    }

}

void randomPuzzle(){
    srand((int)time(NULL));
    int i;
    for(i=0;i<10000;i++){
        mvblank(direction[rand()%4]);
    }
}

char findOppositeDir(char d){
    if(d == 'U')return 'D';
    else if(d == 'L')return 'R';
    else if(d == 'D')return 'U';
    else if(d == 'R')return 'L';
    else return ' ';
}

       
void findSolution(){
    int i,j,k;
    arrpos ar;
    puzzleQueue queue;
    initQueue(&queue);
    pzstate st;
    st.sollen = 0;  //sollen act as gn
    st.sol[0] = '\0';
    
    //Duplicate puzzle state
    for(i = 0;i< 3;i++)
        for(j = 0;j < 3;j++)
            st.cappz[i][j] = puzzle[i][j];
    
    enQueue(&queue,st);
    while(1){
        //dequeue to retrieve best path
        st = deQueue(&queue);
        //When dequeue,set solution(length sollen),puzzle state with the position of blank char.
        for(i = 0;i < st.sollen;i++){
            sol[i] = st.sol[i];
        }
        sol[i] = '\0';
        for(i = 0;i< 3;i++)
            for(j = 0;j < 3;j++)
               puzzle[i][j] = st.cappz[i][j];
        ar = findPos(0,' ');
        brow = ar.r;bcol = ar.c;
        
        //check is it goal state
        if(isFinalStates()){
            //if yes
                //return that state snapshot as answer
            return;
            }
        else{
            //if no
                //go down in 4 way,capture puzzle state,capture solution,calculate fn,add each of way to queue
                //then sort queue
            for(i = 0;i < 4;i++){
                if(st.sollen > 0)
                    if(findOppositeDir(st.sol[st.sollen-1]) == direction[i])continue;
                if(mvblank(direction[i])){
                    if(isDuplicate(&queue)){ //Prevent A* search to expand already 'expanded' state.
                        mvblank(findOppositeDir(direction[i]));
                        continue;
                    }
                    st.sol[st.sollen] = direction[i];
                    for(j = 0;j < 3;j++)
                        for(k = 0;k < 3;k++)
                            st.cappz[j][k] = puzzle[j][k];
                    st.sollen++;
                    st.fn = st.sollen + mhtdis() + wrongtiledis(); //more hn value result in less expand node.
                    enQueue(&queue,st);
                    st.sollen--;
                    mvblank(findOppositeDir(direction[i]));
                    
                }
            }
                mergesort(queue.q,queue.front,queue.rear);
        }
            
    }
              
}


int mhtdis(){
    int i,j,sum = 0;
    arrpos pos1,pos2;
    for(i = 0;i < 3;i++){
        for(j = 0;j < 3;j++){
            pos1 = findPos(0,puzzle[i][j]);
            pos2 = findPos(1,puzzle[i][j]);
            sum = sum + abs(pos1.r-pos2.r) + abs(pos1.c-pos2.c);
        }
    }

    return sum;
}

int wrongtiledis(){
    int i,j,sum = 0;
    for(i = 0;i < 3;i++)
        for(j = 0;j < 3;j++)
            if(puzzle[i][j] != goal[i][j])sum++;
    return sum;
}
int main(){
    int i,j;
    char ch;
    randomPuzzle();
    for(i = 0;i < 3;i++)
        for(j = 0;j < 3;j++)
            start[i][j] = puzzle[i][j];
    findSolution();
    i=0;
    while(sol[i] != '\0')
        printf("%c",sol[i++]);
    if(i < 2)
        printf("\n%d move.\n",i);
    else
        printf("\n%d moves.\n",i);
    
    for(i = 0;i < 3;i++)
        for(j = 0;j < 3;j++)
            puzzle[i][j] = start[i][j];
    arrpos ar = findPos(0,' ');
    brow = ar.r;bcol = ar.c;
    printPuzzle();
    
    i=0;
    printf("Press R to move next\nPress L to move prev\nPress S to view start state\nPress T to view solution\n");
    printf("Press Q to quit.\n");
    while(1){
        ch = getchar();
        if(toupper(ch) == 'L'){
            if(i > 0){
                printf("UNDO STEP %d\n",i);
                mvblank(findOppositeDir(sol[--i]));
                printPuzzle();
            }
        }
        else if(toupper(ch) == 'R'){
            if(sol[i] != '\0'){
                printf("STEP %d:%c\n",i+1,sol[i]);
                mvblank(sol[i++]);
                printPuzzle();
            }
        }
        else if(toupper(ch) == 'S'){
            printf("\nSTART STATE:\n");
            printStartPuzzle();
        }
        else if(toupper(ch) == 'T'){
            j = 0;
            while(sol[j] != '\0')
                printf("%c",sol[j++]);
            if(j < 2)
                printf("\n%d move.\n",j);
            else
                printf("\n%d moves.\n",j);
            printf("\n");
        }
        else if(toupper(ch) == 'Q'){
            break;
        }
    }
    return 0;
}

