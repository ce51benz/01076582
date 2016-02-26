#include <stdio.h>
#include <time.h>
#include <stdlib.h>



//char puzzle[3][3] = {{'1','2','3'},{'4','5','6'},{'7','8',' '}};
//char puzzle[3][3] = {{'8','6','7'},{'2','5','4'},{'3',' ','1'}};
char puzzle[3][3] = {{'8','6','7'},{' ','1','5'},{'2','3','4'}};
char direction[4] = {'U','L','D','R'};
char sol[10000];
int brow=1,bcol=0;
//int brow=2,bcol=2;



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
int findSolution(char prev,int solind,int limit){
    if(isFinalStates()){
        sol[solind] = '\0';
        return 1;
    }
    else if(solind < limit){
        int i;
        for(i=0;i<4;i++){
            if(direction[i] != findOppositeDir(prev)){
                if(mvblank(direction[i])){
                    sol[solind] = direction[i];
                    if(findSolution(sol[solind],solind+1,limit)){
                         mvblank(findOppositeDir(direction[i]));
                         return 1;
                    }
                    mvblank(findOppositeDir(direction[i]));
                }
            }
            
        }
    }

    return 0;
}




int main(){
    int i = 1;
    //randomPuzzle();

    while(1){
        if(findSolution('0',0,i++))break;
    }
    i=0;
    while(sol[i] != '\0')
        printf("%c",sol[i++]);
    printf("\n");
    printPuzzle();
    
    return 0;
}

