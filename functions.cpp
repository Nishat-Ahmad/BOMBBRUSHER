#include<iostream>
#include<ctime>
#include<iomanip>
using namespace std;


enum Mine{MINE, SPACE, FLAG};

class Board{
protected:
    int total_mines = 0;
    int augmented_mines;
    int board[10][10];
    Mine mine[10][10];
    char augmented_board[10][10];
    bool gameRunner = true;
public:
    Board(){
        srand(time(0));
        randomizeMines();
        initializeBoard();
        initializeAugmented();
    }
    void randomizeMines();
    void initializeBoard();
    void initializeAugmented();
    void print();
};

void Board::randomizeMines(){
    for(int i = 0; i < 10; i++){
        for(int j = 0; j < 10; j++){
            if(rand()%5 == 0){
                board[i][j] = 0;
                mine[i][j] = MINE;
                total_mines++;
            }
            else{
                board[i][j] = 0;
                mine[i][j] = SPACE;
            }
        }
    }
}

void Board::initializeBoard(){
    for(int i = 0; i < 10; i++){
        for(int j = 0; j < 10; j++){
            if(mine[i][j] == SPACE){
                for(int k = -1; k <= 1; k++){ 
                    for(int l = -1; l <= 1; l++){ 
                        int y = j + k; 
                        int x = i + l; 
                        if(x >= 0 && x < 10 && y >= 0 && y < 10 && mine[x][y] == MINE){
                            board[i][j]++;
                        }
                    }
                }
            }
        }
    }
}

void Board::initializeAugmented(){
    for(int i = 0; i < 10; i++){
        for(int j = 0; j < 10; j++){
            augmented_board[i][j] = '-';
        }
    }
    augmented_mines = total_mines;
}

void Board::print(){
    cout<<"\t";
    for(int i = 0; i < 10; i++)
    cout<<i + 1<<" ";
    cout<<endl<<endl;
        for(int i = 0; i < 10; i++){
            cout<<i+1<<"\t";
            for(int j = 0; j < 10; j++){
                if(gameRunner == false && mine[i][j] == MINE)
                cout<<"* ";
                else if(augmented_board[i][j] == '-' || augmented_board[i][j] == 'F')
                cout<<augmented_board[i][j]<<" ";
                else
                cout<<int(augmented_board[i][j])<<" ";
            }
            cout<<endl;
        }
    cout<<"A total of "<<augmented_mines<<" mines are remaining\n";
}

class bombCheck: public Board{
private:
    int choice;
    int x, y;
public:
    int checkMine();
    int checkFlag();
    bool revealSpace();
    bool expandSpace();
    void win();
    void lose();
    void removeFlag();
    void gameController();
    void placeFlag();
};

void bombCheck::gameController(){
    do{
        print();
        cout<<"Choose the coordinates (x,y):"<<endl;
        cout<<"x: ";
        cin>>y;
        cout<<"y: ";
        cin>>x;
        x -= 1;
        y -= 1;
        cout<<"1. Flag\n";
        cout<<"2. Reveal\n";
        cout<<"3. Expand\n";
        cout<<"4. Remove Flag\n";
        cin>>choice;
        switch(choice){
            case 1:
                placeFlag();
                break;
            case 2:
                revealSpace();
                break;
            case 3:
                expandSpace();
                break;
            case 4:
                removeFlag();
                break;
            default:
                cout<<"Invalid Input."<<endl;
        }
        if(total_mines == 0)
        win();
    }while(gameRunner == true);
}

void bombCheck::placeFlag(){
    if(mine[x][y] == MINE){
        total_mines--;
        mine[x][y] = FLAG;
    }
    augmented_board[x][y] = 'F';
    augmented_mines--;
}

bool bombCheck::revealSpace(){
    if(mine[x][y] == SPACE){
        augmented_board[x][y] = board[x][y];
        return true;
    }
    else if(mine[x][y] == MINE){
        lose();
        return false;
    }
    else if(mine[x][y] == FLAG){
        cout<<"Invalid command. A flag cannot be revealed"<<endl;
        return true;
    }
}

bool bombCheck::expandSpace(){
    int mine_Counter = checkMine();
    int flag_Counter = checkFlag();
    if(mine_Counter == 0){
        for(int k = -1; k <= 1; k++){
            for(int l = -1; l <= 1; l++){
                int i = x + k;
                int j = y + l;
                if(i >= 0 && i < 10 && j >= 0 && j < 10 && augmented_board[i][j] != 'F')
                augmented_board[i][j] = board[i][j];
            }
        }
    }
    else if(mine_Counter <= flag_Counter){
        lose();
        return false;
    }
    else if(mine_Counter == 9){
        cout<<"Cannot Expand. You are not expanding a revealed space."<<endl;
    }
    else
    cout<<"Cannot Expand."<<endl;
}

void bombCheck::removeFlag(){
    if(augmented_board[x][y] == 'F'){
        augmented_board[x][y] = '-';
        augmented_mines++;
        if(mine[x][y] == FLAG)
        mine[x][y] = MINE;
    }
}

int bombCheck::checkMine(){
    int mine_counter = 0;
    if(mine[x][y] == SPACE && augmented_board[x][y] != '-'){
        for(int k = -1; k <= 1; k++){ 
            for(int l = -1; l <= 1; l++){ 
                int i = x + k; 
                int j = y + l; 
                if(i >= 0 && i < 10 && j >= 0 && j < 10 && mine[i][j] == MINE)
                mine_counter++;
            }
        }
        return mine_counter;
    }
    else{
        return 9;
    }
}

int bombCheck::checkFlag(){
    int flag_Counter = 0;
    for(int k = -1; k <= 1; k++){
        for(int l = -1; l <= 1; l++){
            int i = x + k;
            int j = y + l;
            if(i >= 0 && i < 10 && j >= 0 && j < 10 && augmented_board[i][j] == 'F')
            flag_Counter++;
        }
    }
    return flag_Counter;
}

void bombCheck::lose(){
    cout<<"You have lost. The final board looks like: "<<endl;
    gameRunner = false;
    print();
}

void bombCheck:: win(){
    cout<<"Congratulations! You have won.\nThe final board looks like: "<<endl;
    gameRunner = false;
    print();
}
