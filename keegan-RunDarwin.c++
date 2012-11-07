#include "Darwin.h"

int main(int argc, char *argv[]){
    {
        cout << "*** Darwin 8x8 ***" << endl;
        /*
        8x8 Darwin
        Food,   facing east,  at (0, 0)
        Hopper, facing north, at (3, 3)
        Hopper, facing east,  at (3, 4)
        Hopper, facing south, at (4, 4)
        Hopper, facing west,  at (4, 3)
        Food,   facing north, at (7, 7)
        Simulate 5 moves.
        Print every grid.
        */
        Board B(8,8);
        Food f1;
        B.placeCreature(f1,0,0,EAST);
        Hopper h1;
        B.placeCreature(h1,3,3,NORTH);
        Hopper h2;
        B.placeCreature(h2,3,4,EAST);
        Hopper h3;
        B.placeCreature(h3,4,4,SOUTH);
        Hopper h4;
        B.placeCreature(h4,4,3,WEST);
        Food f2;
        B.placeCreature(f2,7,7,NORTH);
        B.animateBoard(5,1);
    }
    
    {
        /*
        7x9 Darwin
        Trap,   facing south, at (0, 0)
        Hopper, facing east,  at (3, 2)
        Rover,  facing north, at (5, 4)
        Trap,   facing west,  at (6, 8)
        Simulate 5 moves.
        Print every grid.
        */
        cout << "*** Darwin 7x9 ***" << endl;
        Board B(7,9);
        Trap t1;
        B.placeCreature(t1,0,0,SOUTH);
        Hopper h1;
        B.placeCreature(h1,3,2,EAST);
        Rover r1;
        B.placeCreature(r1,5,4,NORTH);
        Trap t2;
        B.placeCreature(t2,6,8,WEST);
        B.animateBoard(5,1);
    }
    
    {
        cout << "*** Darwin 72x72 without Best ***" << endl;
        /*
        Randomly place the following creatures facing randomly.
        Call rand(), mod it with 5184 (72x72), and use that for the position
        in a row-major order grid.
        Call rand() again, mod it with 4 and use that for it's direction with
        the ordering: west, north, east, south.
        Do that for each kind of creature.
        10 Food
        10 Hopper
        10 Rover
        10 Trap
        Simulate 1000 moves.
        Print every 100th grid.
        */
        Board B(72,72);
        vector<Food> fList(10,Food());
        vector<Hopper> hList(10,Hopper());
        vector<Rover> rList(10,Rover());
        vector<Trap> tList(10,Trap());
        for(int i = 0; i < 10; i++){
            int position = rand() % 5184;
            B.placeCreature(fList[i],position/72,position%72,rand()%4);
        }
        for(int i = 0; i < 10; i++){
            int position = rand() % 5184;
            B.placeCreature(hList[i],position/72,position%72,rand()%4);
        }
        for(int i = 0; i < 10; i++){
            int position = rand() % 5184;
            B.placeCreature(rList[i],position/72,position%72,rand()%4);
        }
        for(int i = 0; i < 10; i++){
            int position = rand() % 5184;
            B.placeCreature(tList[i],position/72,position%72,rand()%4);
        }
        B.animateBoard(1000,100);
    }
    
    {
        cout << "*** Darwin 72x72 with Best ***" << endl;
        srand(0);
        /*
        Randomly place the following creatures facing randomly.
        Call rand(), mod it with 5184 (72x72), and use that for the position
        in a row-major order grid.
        Call rand() again, mod it with 4 and use that for it's direction with
        the ordering: west, north, east, south.
        Do that for each kind of creature.
        10 Food
        10 Hopper
        10 Rover
        10 Trap
        10 Best
        Simulate 1000 moves.
        Best MUST outnumber ALL other species for the bonus pts.
        Print every 100th grid.
        */
        Board B(72,72);
        vector<Food> fList(10,Food());
        vector<Hopper> hList(10,Hopper());
        vector<Rover> rList(10,Rover());
        vector<Trap> tList(10,Trap());
        vector<Best> bList(10,Best());
        for(int i = 0; i < 10; i++){
            int position = rand() % 5184;
            B.placeCreature(fList[i],position/72,position%72,rand()%4);
        }
        for(int i = 0; i < 10; i++){
            int position = rand() % 5184;
            B.placeCreature(hList[i],position/72,position%72,rand()%4);
        }
        for(int i = 0; i < 10; i++){
            int position = rand() % 5184;
            B.placeCreature(rList[i],position/72,position%72,rand()%4);
        }
        for(int i = 0; i < 10; i++){
            int position = rand() % 5184;
            B.placeCreature(tList[i],position/72,position%72,rand()%4);
        }
        for(int i = 0; i < 10; i++){
            int position = rand() % 5184;
            B.placeCreature(bList[i],position/72,position%72,rand()%4);
        }
        B.animateBoard(1000,100);
        
    }
    {
        cout << "*** TEST 5 ***" << endl;
        srand(0);
        Board B(10,10);
        vector<Rover> rList(10,Rover());
        for(int i = 0; i < 10; i++){
            int position = rand() % 100;
            B.placeCreature(rList[i],position/10,position%10,rand()%4);
        }
        B.animateBoard(20,1);
        
    }
    {
        cout << "*** TEST 6 ***" << endl;
        srand(0);
        Board B(10,10);
        vector<Rover> rList(1,Rover());
        for(int i = 0; i < 1; i++){
            int position = rand() % 100;
            B.placeCreature(rList[i],position/10,position%10,rand()%4);
        }
        B.animateBoard(20,1);
        
    }
    {
        cout << "*** TEST 7 ***" << endl;
        srand(0);
        Board B(10,10);
        vector<Food> fList(1,Food());
        for(int i = 0; i < 1; i++){
            int position = rand() % 100;
            B.placeCreature(fList[i],position/10,position%10,rand()%4);
        }
        B.animateBoard(5,1);
        
    }
    {
        cout << "*** TEST 8 ***" << endl;
        srand(0);
        Board B(10,10);
        B.animateBoard(3,1);
        
    }
    {
        cout << "*** TEST 9 ***" << endl;
        srand(0);
        Board B(1,1);
        Rover r;
        B.placeCreature(r,0,0,NORTH);
        B.animateBoard(10,1);
        
    }
    {
        srand(0);
        Board B(10,10);
        vector<Rover> rList(40,Rover());
        for(int i = 0; i < 40; i++){
            int position = rand() % 100;
            B.placeCreature(rList[i],position/10,position%10,rand()%4);
        }
        B.animateBoard(20,1);
    }
       
    return 0;
}