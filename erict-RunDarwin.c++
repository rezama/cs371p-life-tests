// -----------------------------
// projects/darwin/RunDarwin.c++
// Copyright (C) 2012
// Glenn P. Downing
// -----------------------------

/*
To run the program:
    % g++ -pedantic -std=c++0x -Wall RunDarwin.c++ -o RunDarwin.c++.app
    % valgrind RunDarwin.c++.app > RunDarwin.out

To configure Doxygen:
    doxygen -g
That creates the file Doxyfile.
Make the following edits:
    EXTRACT_ALL            = YES
    EXTRACT_PRIVATE        = YES
    EXTRACT_STATIC         = YES
    GENERATE_LATEX         = NO

To document the program:
    doxygen Doxyfile
*/

// --------
// includes
// --------

#include <cassert>   // assert
#include <cstdlib>   // rand, srand
#include <iostream>  // cout, endl
#include <stdexcept> // invalid_argument, out_of_range
#include "Darwin.h"

// ----
// main
// ----

int main () {
    using namespace std;
    ios_base::sync_with_stdio(false); // turn off synchronization with C I/O

    // ----
    // food
    // ----

    /*
     0: left
     1: go 0
    */

    // ------
    // hopper
    // ------

    /*
     0: hop
     1: go 0
    */

    // -----
    // rover
    // -----

    /*
     0: if_enemy 9
     1: if_empty 7
     2: if_random 5
     3: left
     4: go 0
     5: right
     6: go 0
     7: hop
     8: go 0
     9: infect
    10: go 0
    */

    // ----
    // trap
    // ----

    /*
     0: if_enemy 3
     1: left
     2: go 0
     3: infect
     4: go 0
    */

    // ----------
    // darwin 8x8
    // ----------

    try {
        cout << "*** Darwin 8x8 ***" << endl;
        srand(0);
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
        DungeonKeeper d(8, 8);
        d.makeCreature(&food, east, 0, 0);
        d.makeCreature(&hopper, north, 3, 3);
        d.makeCreature(&hopper, east, 3, 4);
        d.makeCreature(&hopper, south, 4, 4);
        d.makeCreature(&hopper, west, 4, 3);
        d.makeCreature(&food, north, 7, 7); 
        cout << d.drawMap();

        for (int i = 0; i < 5; i++) {
          d.updateMap();
          cout << d.drawMap();
        }

        }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}

    // ----------
    // darwin 7x9
    // ----------

    try {
        cout << "*** Darwin 7x9 ***" << endl;
        srand(0);
        /*
        7x9 Darwin
        Trap,   facing south, at (0, 0)
        Hopper, facing east,  at (3, 2)
        Rover,  facing north, at (5, 4)
        Trap,   facing west,  at (6, 8)
        Simulate 5 moves.
        Print every grid.
        */
        DungeonKeeper d(7, 9);
        d.makeCreature(&trap, south, 0, 0);
        d.makeCreature(&hopper, east, 3, 2);
        d.makeCreature(&rover, north, 5, 4);
        d.makeCreature(&trap, west, 6, 8);

        cout << d.drawMap();

        for (int i = 0; i < 5; i++) {
          d.updateMap();
          cout << d.drawMap();
        }
        }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}

    // ------------
    // darwin 72x72
    // without best
    // ------------

    try {
        cout << "*** Darwin 72x72 without Best ***" << endl;
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
        Simulate 1000 moves.
        Print every 100th grid.
        */
        DungeonKeeper d(72, 72);

        for (int i = 0; i < 10; i++) {
          int pos = rand() % 5184;
          int dir = rand() % 4;
          int x, y, count;
          x = y = count = 0;
          for (int j = 0; j < 72; j++) {
            for (int k = 0; k < 72; k++) {
              if (count++ == pos) {
                x = j;
                y = k;
              }
            }
          }
          d.makeCreature(&food, (dir + 3) % 4, x, y);
        }
        for (int i = 0; i < 10; i++) {
          int pos = rand() % 5184;
          int dir = rand() % 4;
          int x, y, count;
          x = y = count = 0;
          for (int j = 0; j < 72; j++) {
            for (int k = 0; k < 72; k++) {
              if (count++ == pos) {
                x = j;
                y = k;
              }
            }
          }
          d.makeCreature(&hopper, (dir + 3) % 4, x, y);
        }
        for (int i = 0; i < 10; i++) {
          int pos = rand() % 5184;
          int dir = rand() % 4;
          int x, y, count;
          x = y = count = 0;
          for (int j = 0; j < 72; j++) {
            for (int k = 0; k < 72; k++) {
              if (count++ == pos) {
                x = j;
                y = k;
              }
            }
          }
          d.makeCreature(&rover, (dir + 3) % 4, x, y);
        }
        for (int i = 0; i < 10; i++) {
          int pos = rand() % 5184;
          int dir = rand() % 4;
          int x, y, count;
          x = y = count = 0;
          for (int j = 0; j < 72; j++) {
            for (int k = 0; k < 72; k++) {
              if (count++ == pos) {
                x = j;
                y = k;
              }
            }
          }
          d.makeCreature(&trap, (dir + 3) % 4, x, y);
        }


        for (int i = 0; i < 1000; i++) {
          if (i % 100 == 0)
            cout << d.drawMap();

          d.updateMap();
        }

        }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}

    // ------------
    // darwin 72x72
    // with best
    // ------------

    try {
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
        DungeonKeeper d(72, 72);

        for (int i = 0; i < 10; i++) {
          int pos = rand() % 5184;
          int dir = rand() % 4;
          int x, y, count;
          x = y = count = 0;
          for (int j = 0; j < 72; j++) {
            for (int k = 0; k < 72; k++) {
              if (count++ == pos) {
                x = j;
                y = k;
              }
            }
          }
          d.makeCreature(&food, (dir + 3) % 4, x, y);
        }
        for (int i = 0; i < 10; i++) {
          int pos = rand() % 5184;
          int dir = rand() % 4;
          int x, y, count;
          x = y = count = 0;
          for (int j = 0; j < 72; j++) {
            for (int k = 0; k < 72; k++) {
              if (count++ == pos) {
                x = j;
                y = k;
              }
            }
          }
          d.makeCreature(&hopper, (dir + 3) % 4, x, y);
        }
        for (int i = 0; i < 10; i++) {
          int pos = rand() % 5184;
          int dir = rand() % 4;
          int x, y, count;
          x = y = count = 0;
          for (int j = 0; j < 72; j++) {
            for (int k = 0; k < 72; k++) {
              if (count++ == pos) {
                x = j;
                y = k;
              }
            }
          }
          d.makeCreature(&rover, (dir + 3) % 4, x, y);
        }
        for (int i = 0; i < 10; i++) {
          int pos = rand() % 5184;
          int dir = rand() % 4;
          int x, y, count;
          x = y = count = 0;
          for (int j = 0; j < 72; j++) {
            for (int k = 0; k < 72; k++) {
              if (count++ == pos) {
                x = j;
                y = k;
              }
            }
          }
          d.makeCreature(&trap, (dir + 3) % 4, x, y);
        }
        for (int i = 0; i < 10; i++) {
          int pos = rand() % 5184;
          int dir = rand() % 4;
          int x, y, count;
          x = y = count = 0;
          for (int j = 0; j < 72; j++) {
            for (int k = 0; k < 72; k++) {
              if (count++ == pos) {
                x = j;
                y = k;
              }
            }
          }
          d.makeCreature(&best, (dir + 3) % 4, x, y);
        }


        for (int i = 0; i <= 1000; i++) {
          if (i % 100 == 0)
            cout << d.drawMap();

          d.updateMap();
        }

        int numB = 0;
        int numR = 0;
        for (int i = 0; i < 72; i++) {
          for (int j = 0; j < 72; j++) {
            if (d.map[i][j] != -1 && d.creatureList[d.map[i][j]].spec->image == 'b')
              numB++;
            if (d.map[i][j] != -1 && d.creatureList[d.map[i][j]].spec->image == 'r')
              numR++;
          }
        }

        cout << endl << "number of best: " << numB << endl;
        cout << endl << "number of rover: " << numR << endl;

        }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}

    // ------------
    // darwin 40x40
    // with best
    // ------------

    try {
        cout << "*** Darwin - THE GAUNTLET - 40x40 with Best ***" << endl;
        srand(0);
        /*
        Randomly place the following creatures facing randomly.
        Call rand(), mod it with 1600 (40x40), and use that for the position
        in a row-major order grid.
        Call rand() again, mod it with 4 and use that for it's direction with
        the ordering: west, north, east, south.
        Do that for each kind of creature.
        10 Rover
        10 Best
        Simulate 1000 moves.
        Best MUST outnumber ALL other species for the bonus pts.
        Print every 100th grid.
        */
        DungeonKeeper d(40, 40);

        for (int i = 0; i < 10; i++) {
          int pos = rand() % 1600;
          int dir = rand() % 4;
          int x, y, count;
          x = y = count = 0;
          for (int j = 0; j < 40; j++) {
            for (int k = 0; k < 40; k++) {
              if (count++ == pos) {
                x = j;
                y = k;
              }
            }
          }
          if (d.map[x][y] != -1) {
            i--;
            continue;
          }
          d.makeCreature(&rover, (dir + 3) % 4, x, y);
        }
        for (int i = 0; i < 10; i++) {
          int pos = rand() % 1600;
          int dir = rand() % 4;
          int x, y, count;
          x = y = count = 0;
          for (int j = 0; j < 40; j++) {
            for (int k = 0; k < 40; k++) {
              if (count++ == pos) {
                x = j;
                y = k;
              }
            }
          }
          if (d.map[x][y] != -1) {
            i--;
            continue;
          }
          d.makeCreature(&best, (dir + 3) % 4, x, y);
        }


        for (int i = 0; i <= 1000; i++) {
          if (i % 100 == 0)
            cout << d.drawMap();

          d.updateMap();
        }

        int numB = 0;
        int numR = 0;
        for (int i = 0; i < 40; i++) {
          for (int j = 0; j < 40; j++) {
            if (d.map[i][j] != -1 && d.creatureList[d.map[i][j]].spec->image == 'b')
              numB++;
            if (d.map[i][j] != -1 && d.creatureList[d.map[i][j]].spec->image == 'r')
              numR++;
          }
        }

        cout << endl << "number of best: " << numB << endl;
        cout << endl << "number of rover: " << numR << endl;

        }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}

    // ------------
    // darwin 40x40
    // just food
    // ------------

    try {
        cout << "*** Darwin 40x40 just food ***" << endl;
        srand(0);
        /*
        Randomly place the following creatures facing randomly.
        Call rand(), mod it with 1600 (40x40), and use that for the position
        in a row-major order grid.
        Call rand() again, mod it with 4 and use that for it's direction with
        the ordering: west, north, east, south.
        Do that for each kind of creature.
        10 Food
        Simulate 1000 moves.
        Best MUST outnumber ALL other species for the bonus pts.
        Print every 100th grid.
        */
        DungeonKeeper d(40, 40);

        for (int i = 0; i < 10; i++) {
          int pos = rand() % 1600;
          int dir = rand() % 4;
          int x, y, count;
          x = y = count = 0;
          for (int j = 0; j < 40; j++) {
            for (int k = 0; k < 40; k++) {
              if (count++ == pos) {
                x = j;
                y = k;
              }
            }
          }
          if (d.map[x][y] != -1) {
            i--;
            continue;
          }
          d.makeCreature(&food, (dir + 3) % 4, x, y);
        }

        for (int i = 0; i <= 1000; i++) {
          if (i % 100 == 0)
            cout << d.drawMap();

          d.updateMap();
        }

        }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}

    // ------------
    // darwin 40x40
    // with best and trap
    // ------------

    try {
        cout << "*** Darwin 40x40 with Best and trap ***" << endl;
        srand(0);
        /*
        Randomly place the following creatures facing randomly.
        Call rand(), mod it with 1600 (40x40), and use that for the position
        in a row-major order grid.
        Call rand() again, mod it with 4 and use that for it's direction with
        the ordering: west, north, east, south.
        Do that for each kind of creature.
        10 Trap
        10 Best
        Simulate 1000 moves.
        Best MUST outnumber ALL other species for the bonus pts.
        Print every 100th grid.
        */
        DungeonKeeper d(40, 40);

        for (int i = 0; i < 10; i++) {
          int pos = rand() % 1600;
          int dir = rand() % 4;
          int x, y, count;
          x = y = count = 0;
          for (int j = 0; j < 40; j++) {
            for (int k = 0; k < 40; k++) {
              if (count++ == pos) {
                x = j;
                y = k;
              }
            }
          }
          if (d.map[x][y] != -1) {
            i--;
            continue;
          }
          d.makeCreature(&trap, (dir + 3) % 4, x, y);
        }
        for (int i = 0; i < 10; i++) {
          int pos = rand() % 1600;
          int dir = rand() % 4;
          int x, y, count;
          x = y = count = 0;
          for (int j = 0; j < 40; j++) {
            for (int k = 0; k < 40; k++) {
              if (count++ == pos) {
                x = j;
                y = k;
              }
            }
          }
          if (d.map[x][y] != -1) {
            i--;
            continue;
          }
          d.makeCreature(&best, (dir + 3) % 4, x, y);
        }


        for (int i = 0; i <= 1000; i++) {
          if (i % 100 == 0)
            cout << d.drawMap();

          d.updateMap();
        }

        int numB = 0;
        int numR = 0;
        for (int i = 0; i < 40; i++) {
          for (int j = 0; j < 40; j++) {
            if (d.map[i][j] != -1 && d.creatureList[d.map[i][j]].spec->image == 'b')
              numB++;
            if (d.map[i][j] != -1 && d.creatureList[d.map[i][j]].spec->image == 't')
              numR++;
          }
        }

        cout << endl << "number of best: " << numB << endl;
        cout << endl << "number of trap: " << numR << endl;

        }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}

    // ------------
    // darwin 40x40
    // with rover and trap
    // ------------

    try {
        cout << "*** Darwin 40x40 with rover and trap ***" << endl;
        srand(0);
        /*
        Randomly place the following creatures facing randomly.
        Call rand(), mod it with 1600 (40x40), and use that for the position
        in a row-major order grid.
        Call rand() again, mod it with 4 and use that for it's direction with
        the ordering: west, north, east, south.
        Do that for each kind of creature.
        10 Rover
        10 trap
        Simulate 1000 moves.
        Best MUST outnumber ALL other species for the bonus pts.
        Print every 100th grid.
        */
        DungeonKeeper d(40, 40);

        for (int i = 0; i < 10; i++) {
          int pos = rand() % 1600;
          int dir = rand() % 4;
          int x, y, count;
          x = y = count = 0;
          for (int j = 0; j < 40; j++) {
            for (int k = 0; k < 40; k++) {
              if (count++ == pos) {
                x = j;
                y = k;
              }
            }
          }
          if (d.map[x][y] != -1) {
            i--;
            continue;
          }
          d.makeCreature(&rover, (dir + 3) % 4, x, y);
        }
        for (int i = 0; i < 10; i++) {
          int pos = rand() % 1600;
          int dir = rand() % 4;
          int x, y, count;
          x = y = count = 0;
          for (int j = 0; j < 40; j++) {
            for (int k = 0; k < 40; k++) {
              if (count++ == pos) {
                x = j;
                y = k;
              }
            }
          }
          if (d.map[x][y] != -1) {
            i--;
            continue;
          }
          d.makeCreature(&trap, (dir + 3) % 4, x, y);
        }


        for (int i = 0; i <= 1000; i++) {
          if (i % 100 == 0)
            cout << d.drawMap();

          d.updateMap();
        }

        int numB = 0;
        int numR = 0;
        for (int i = 0; i < 40; i++) {
          for (int j = 0; j < 40; j++) {
            if (d.map[i][j] != -1 && d.creatureList[d.map[i][j]].spec->image == 't')
              numB++;
            if (d.map[i][j] != -1 && d.creatureList[d.map[i][j]].spec->image == 'r')
              numR++;
          }
        }

        cout << endl << "number of trap: " << numB << endl;
        cout << endl << "number of rover: " << numR << endl;

        }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}

    // ------------
    // darwin 20x20
    // with hopper and best
    // ------------

    try {
        cout << "*** Darwin 20x20 with hopper and best ***" << endl;
        srand(0);
        /*
        Randomly place the following creatures facing randomly.
        Call rand(), mod it with 400 (20x20), and use that for the position
        in a row-major order grid.
        Call rand() again, mod it with 4 and use that for it's direction with
        the ordering: west, north, east, south.
        Do that for each kind of creature.
        10 hopper
        10 best
        Simulate 1000 moves.
        Best MUST outnumber ALL other species for the bonus pts.
        Print every 100th grid.
        */
        DungeonKeeper d(20, 20);

        for (int i = 0; i < 10; i++) {
          int pos = rand() % 400;
          
          int dir = rand() % 4;
          int x, y, count;
          x = y = count = 0;
          for (int j = 0; j < 20; j++) {
            for (int k = 0; k < 20; k++) {
              if (count++ == pos) {
                x = j;
                y = k;
              }
            }
          }
          if (d.map[x][y] != -1) {
            i--;
            continue;
          }
          d.makeCreature(&best, (dir + 3) % 4, x, y);
        }
        for (int i = 0; i < 10; i++) {
          int pos = rand() % 400;
          int dir = rand() % 4;
          int x, y, count;
          x = y = count = 0;
          for (int j = 0; j < 20; j++) {
            for (int k = 0; k < 20; k++) {
              if (count++ == pos) {
                x = j;
                y = k;
              }
            }
          }
          if (d.map[x][y] != -1) {
            i--;
            continue;
          }
          d.makeCreature(&hopper, (dir + 3) % 4, x, y);
        }


        for (int i = 0; i <= 1000; i++) {
          if (i % 100 == 0)
            cout << d.drawMap();

          d.updateMap();
        }

        int numB = 0;
        int numR = 0;
        for (int i = 0; i < 20; i++) {
          for (int j = 0; j < 20; j++) {
            if (d.map[i][j] != -1 && d.creatureList[d.map[i][j]].spec->image == 'b')
              numB++;
            if (d.map[i][j] != -1 && d.creatureList[d.map[i][j]].spec->image == 'h')
              numR++;
          }
        }

        cout << endl << "number of best: " << numB << endl;
        cout << endl << "number of hopper: " << numR << endl;

        }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}

    // ------------
    // darwin 40x40
    // with rover and hopper
    // ------------

    try {
        cout << "*** Darwin 40x40 with rover and hopper ***" << endl;
        srand(0);
        /*
        Randomly place the following creatures facing randomly.
        Call rand(), mod it with 1600 (40x40), and use that for the position
        in a row-major order grid.
        Call rand() again, mod it with 4 and use that for it's direction with
        the ordering: west, north, east, south.
        Do that for each kind of creature.
        10 Rover
        10 hopper
        Simulate 1000 moves.
        Best MUST outnumber ALL other species for the bonus pts.
        Print every 100th grid.
        */
        DungeonKeeper d(40, 40);

        for (int i = 0; i < 10; i++) {
          int pos = rand() % 1600;
          int dir = rand() % 4;
          int x, y, count;
          x = y = count = 0;
          for (int j = 0; j < 40; j++) {
            for (int k = 0; k < 40; k++) {
              if (count++ == pos) {
                x = j;
                y = k;
              }
            }
          }
          if (d.map[x][y] != -1) {
            i--;
            continue;
          }
          d.makeCreature(&rover, (dir + 3) % 4, x, y);
        }
        for (int i = 0; i < 10; i++) {
          int pos = rand() % 1600;
          int dir = rand() % 4;
          int x, y, count;
          x = y = count = 0;
          for (int j = 0; j < 40; j++) {
            for (int k = 0; k < 40; k++) {
              if (count++ == pos) {
                x = j;
                y = k;
              }
            }
          }
          if (d.map[x][y] != -1) {
            i--;
            continue;
          }
          d.makeCreature(&hopper, (dir + 3) % 4, x, y);
        }


        for (int i = 0; i <= 1000; i++) {
          if (i % 100 == 0)
            cout << d.drawMap();

          d.updateMap();
        }

        int numB = 0;
        int numR = 0;
        for (int i = 0; i < 40; i++) {
          for (int j = 0; j < 40; j++) {
            if (d.map[i][j] != -1 && d.creatureList[d.map[i][j]].spec->image == 'h')
              numB++;
            if (d.map[i][j] != -1 && d.creatureList[d.map[i][j]].spec->image == 'r')
              numR++;
          }
        }

        cout << endl << "number of hopper: " << numB << endl;
        cout << endl << "number of rover: " << numR << endl;

        }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}

    // ------------
    // darwin 20x20
    // with best and trap
    // ------------

    try {
        cout << "*** Darwin 20x20 with best and trap ***" << endl;
        srand(0);
        /*
        Randomly place the following creatures facing randomly.
        Call rand(), mod it with 400 (20x20), and use that for the position
        in a row-major order grid.
        Call rand() again, mod it with 4 and use that for it's direction with
        the ordering: west, north, east, south.
        Do that for each kind of creature.
        10 best
        10 trap
        Simulate 1000 moves.
        Best MUST outnumber ALL other species for the bonus pts.
        Print every 100th grid.
        */
        DungeonKeeper d(20, 20);

        for (int i = 0; i < 10; i++) {
          int pos = rand() % 400;
          int dir = rand() % 4;
          int x, y, count;
          x = y = count = 0;
          for (int j = 0; j < 20; j++) {
            for (int k = 0; k < 20; k++) {
              if (count++ == pos) {
                x = j;
                y = k;
              }
            }
          }
          if (d.map[x][y] != -1) {
            i--;
            continue;
          }
          d.makeCreature(&best, (dir + 3) % 4, x, y);
        }
        for (int i = 0; i < 10; i++) {
          int pos = rand() % 400;
          int dir = rand() % 4;
          int x, y, count;
          x = y = count = 0;
          for (int j = 0; j < 20; j++) {
            for (int k = 0; k < 20; k++) {
              if (count++ == pos) {
                x = j;
                y = k;
              }
            }
          }
          if (d.map[x][y] != -1) {
            i--;
            continue;
          }
          d.makeCreature(&trap, (dir + 3) % 4, x, y);
        }


        for (int i = 0; i <= 1000; i++) {
          if (i % 100 == 0)
            cout << d.drawMap();

          d.updateMap();
        }

        int numB = 0;
        int numR = 0;
        for (int i = 0; i < 20; i++) {
          for (int j = 0; j < 20; j++) {
            if (d.map[i][j] != -1 && d.creatureList[d.map[i][j]].spec->image == 'b')
              numB++;
            if (d.map[i][j] != -1 && d.creatureList[d.map[i][j]].spec->image == 't')
              numR++;
          }
        }
        cout << endl << "number of best: " << numB << endl;
        cout << endl << "number of trap: " << numR << endl << endl;

        }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}

    return 0;}
