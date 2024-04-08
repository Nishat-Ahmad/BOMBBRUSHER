#include<iostream>
#include<ctime>
#include<iomanip>
using namespace std;

enum Mine{MINE, SPACE, FLAG};
class Board{
public:
    int total_mines = 0;
protected:
    int board[10][10];
    Mine mine[10][10];
    char augmented_board[10][10];
public:
    Board(){
        srand(time(0));
        randomizeMines();
        initializeBoard();
        initializeAugmented();
    }
    void randomizeMines(){
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
    void initializeBoard(){
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
    void initializeAugmented(){
        for(int i = 0; i < 10; i++){
            for(int j = 0; j < 10; j++){
                augmented_board[i][j] = '-';
            }
        }
    }
    void print(){
        cout<<"\t";
        for(int i = 0; i < 10; i++)
        cout<<i + 1<<" ";
        cout<<endl<<endl;
        for(int i = 0; i < 10; i++){
            cout<<i+1<<"\t";
            for(int j = 0; j < 10; j++){
                if(augmented_board[i][j] == '-' || augmented_board[i][j] == 'F')
                cout<<augmented_board[i][j]<<" ";
                else
                cout<<int(augmented_board[i][j])<<" ";
            }
            cout<<endl;
        }
    }
};

class bombCheck: public Board{
private:
    int choice;
    bool isMine;
    int x, y;
public:
    int checkBomb();
        void Play(){
        print();
        do{
            int mine_Counter;
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
                    if(mine[x][y] == MINE){
                    total_mines--;
                    mine[x][y] = FLAG;
                    augmented_board[x][y] = 'F';
                    }
                    break;
                case 2:
                    if(mine[x][y] == SPACE)
                    augmented_board[x][y] = board[x][y];
                    break;
                case 3:
                    mine_Counter = checkBomb();
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
                    else if(mine_Counter == 9){
                        cout<<"Cannot Expand. You are not expanding a revealed space."<<endl;
                    }
                    else
                    cout<<"Cannot Expand."<<endl;
                    break;
                case 4:
                    if(augmented_board[x][y] == 'F'){
                        augmented_board[x][y] = '-';
                        if(mine[x][y] == FLAG)
                        mine[x][y] = MINE;
                    }
                    break;
                default:
                    cout<<"Invalid Input."<<endl;
            }
            print();
            for(int i = 0; i < 10; i++){
                for(int j = 0; j < 10; j++){
                    if(total_mines == 0 && augmented_board[i][j] != '-')
                    break;
                }
            }
        }while(true);
    }
};

int bombCheck::checkBomb(){
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
