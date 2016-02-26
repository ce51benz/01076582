

var puzzle = [['1','2','3'],['4','5','6'],['7','8',' ']];
var direction = ['U','L','D','R'];
var sol = [];
sol[0] = '\0';
var brow=2,bcol=2;
var finind = 0;

function isFinalStates(){
    return puzzle[0][0] == '1' && puzzle[0][1] == '2' && puzzle[0][2] == '3' && puzzle[1][0] == '4' && puzzle[1][1] == '5' && puzzle[1][2] == '6' && puzzle[2][0] == '7' && puzzle[2][1] == '8' && puzzle[2][2] == ' ';
}

//Update html puzzle table
function updatePuzzle(){
    var i,j;
    for(i=0;i<3;i++){
        for(j=0;j<3;j++){
            document.getElementById(i*3+j+1).innerHTML = puzzle[i][j];
        }
    }
}


function findOppositeDir(d){
    if(d == 'U')return 'D';
    else if(d == 'L')return 'R';
    else if(d == 'D')return 'U';
    else if(d == 'R')return 'L';
    else return ' ';
}


function mvblank(dir){
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


function findSolution(prev,solind,limit){
    if(isFinalStates()){
        sol[solind] = '\0';
        return 1;
    }
    else if(solind < limit){
        var i;
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


function randomPuzzle(){
    finind = 0;
    sol[0] = '\0';
    document.getElementById("prevbtt").disabled = true;
    document.getElementById("nextbtt").disabled = true;
    var i;
    document.getElementById("solution").innerHTML = "No solution to answer.";
    
    for(i=0;i<10000;i++){
        mvblank(direction[Math.floor(Math.random()*4)]);
    }
    updatePuzzle();
}

function solvePuzzle(){
    finind = 0;
    document.getElementById("randbtt").disabled = true;
    var i = 1;
    while(1){
        if(findSolution('0',0,i++))break;
    }
    i=0;
    if(sol[i] == '\0'){
        document.getElementById("solution").innerHTML = "The puzzle stayed in goal state.";
        document.getElementById("prevbtt").disabled = true;
        document.getElementById("nextbtt").disabled = true;
        }
    else{
        document.getElementById("solution").innerHTML = "";
        document.getElementById("prevbtt").disabled = false;
        document.getElementById("nextbtt").disabled = false;
        while(sol[i] != '\0'){
            var s = document.createElement("span");
            s.id = "s"+i;
            s.innerHTML = sol[i++];
            document.getElementById("solution").appendChild(s);
        }
    }
    document.getElementById("randbtt").disabled = false;
}

function simulateNext(){
    if(sol[finind]!= '\0'){
        document.getElementById("s"+finind).style.color = "red";
        mvblank(sol[finind++]);
        updatePuzzle();
    }
}

function simulatePrev(){
    if(finind > 0){
        document.getElementById("s"+(finind-1)).style.color = "black";
        mvblank(findOppositeDir(sol[--finind]));
        updatePuzzle();
    }
}
