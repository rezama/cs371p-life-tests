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
#include <string> 
#include <vector>
#include "Darwin.h"

// ----
// main
// ----

int main () 
{
  using namespace std;
  ios_base::sync_with_stdio(false); // turn off synchronization with C I/O

  // ----
  // food
  // ----

  Species food('f');
  food.add_instruction("left");
  food.add_instruction("go 0");

  // ------
  // hopper
  // ------

  Species hopper('h');
  hopper.add_instruction("hop");
  hopper.add_instruction("go 0");

  // -----
  // rover
  // -----

  Species rover('r');
  rover.add_instruction("if_enemy 9");
  rover.add_instruction("if_empty 7");
  rover.add_instruction("if_random 5");
  rover.add_instruction("left");
  rover.add_instruction("go 0");
  rover.add_instruction("right");
  rover.add_instruction("go 0");
  rover.add_instruction("hop");
  rover.add_instruction("go 0");
  rover.add_instruction("infect");
  rover.add_instruction("go 0");

  // ----
  // trap
  // ----

  Species trap('t');
  trap.add_instruction("if_enemy 3");
  trap.add_instruction("left");
  trap.add_instruction("go 0");
  trap.add_instruction("infect");
  trap.add_instruction("go 0");

  // ----
  // best
  // ----

  Species best('b');

  best.add_instruction("if_enemy 6");
  best.add_instruction("if_empty 4");
  best.add_instruction("left");
  best.add_instruction("go 0");
  best.add_instruction("hop");
  best.add_instruction("go 0");
  best.add_instruction("infect");
  best.add_instruction("go 0");


  // ----------
  // darwin 8x8
  // ----------

  try 
  {
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
    cout << "*** Darwin 8x8 ***" << endl;

    Grid<8, 8> g;
    Creature f1(food, 2);
    Creature f2(food, 1);
    Creature h1(hopper, 1);
    Creature h2(hopper, 2);
    Creature h3(hopper, 3);
    Creature h4(hopper, 0);
    g.change(0, 0, f1);
    g.change(3, 3, h1);
    g.change(3, 4, h2);
    g.change(4, 4, h3);
    g.change(4, 3, h4);
    g.change(7, 7, f2);
    cout << "\nTurn: 0";
    g.print();
    for(int i = 0; i < 5; i++)
    {
      g.one_step();
      cout << "\nTurn: " << i + 1;
      g.print();
    }
  }
  catch (const invalid_argument&) 
  {
    assert(false);
  }
  catch (const out_of_range&) 
  {
    assert(false);
  }

  // ----------
  // darwin 7x9
  // ----------

  try 
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
    Grid<7, 9> g;
    Creature t1(trap, 3);
    Creature t2(trap, 0);
    Creature h1(hopper, 2);
    Creature r1(rover, 1);
    g.change(0, 0, t1);
    g.change(6, 8, t2);
    g.change(3, 2, h1);
    g.change(5, 4, r1);
    cout << "\nTurn: 0";
    g.print();
    for(int i = 0; i < 5; i++)
    {
      g.one_step();
      cout << "\nTurn: " << i + 1;
      g.print();
    }
  }
  catch (const invalid_argument&) 
  {
    assert(false);
  }
  catch (const out_of_range&) 
  {
    assert(false);
  }

  // ------------
  // darwin 72x72
  // without best
  // ------------

  try 
  {
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
    cout << "*** Darwin 72x72 without Best ***" << endl;
    srand(0);
    Grid<72, 72> g;
    for (int a = 0; a < 10; a++) 
    {
      int pos = rand();
      Creature creature(food, rand() % 4);
      g.change(pos % 5184 / 72, pos % 5184 % 72, creature);
    }
    for (int b = 0; b < 10; b++) 
    {
      int pos = rand();
      Creature creature(hopper, rand() % 4);
      g.change(pos % 5184 / 72, pos % 5184 % 72, creature);
    }
    for (int c = 0; c < 10; c++) 
    {
      int pos = rand();
      Creature creature(rover, rand() % 4);
      g.change(pos % 5184 / 72, pos % 5184 % 72, creature);
    }
    for (int d = 0; d < 10; d++) 
    {
      int pos = rand();
      Creature creature(trap, rand() % 4);
      g.change(pos % 5184 / 72, pos % 5184 % 72, creature);
    }
    cout << "Turn = 0.";
    g.print();
    for (int e = 1; e < 1001; ++e) 
    {
      g.one_step();
      if (e % 100 == 0)
      {
        cout << "Turn = " << e << ".";
        g.print();
      }
    }
  }
  catch (const invalid_argument&) 
  {
    assert(false);
  }
  catch (const out_of_range&) 
  {
    assert(false);
  }

  // ------------
  // darwin 72x72
  // with best
  // ------------

  try 
  {
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
    cout << "*** Darwin 72x72 with Best ***" << endl;
    srand(0);
    Grid<72, 72> g;
    for (int a = 0; a < 10; a++) 
    {
      int pos = rand();
      Creature creature(food, rand() % 4);
      g.change(pos % 5184 / 72, pos % 5184 % 72, creature);
    }
    for (int b = 0; b < 10; b++) 
    {
      int pos = rand();
      Creature creature(hopper, rand() % 4);
      g.change(pos % 5184 / 72, pos % 5184 % 72, creature);
    }
    for (int c = 0; c < 10; c++) 
    {
      int pos = rand();
      Creature creature(rover, rand() % 4);
      g.change(pos % 5184 / 72, pos % 5184 % 72, creature);
    }
    for (int d = 0; d < 10; d++) 
    {
      int pos = rand();
      Creature creature(trap, rand() % 4);
      g.change(pos % 5184 / 72, pos % 5184 % 72, creature);
    }
    for (int e = 0; e < 10; e++) 
    {
      int pos = rand();
      Creature creature(best, rand() % 4);
      g.change(pos % 5184 / 72, pos % 5184 % 72, creature);
    }
    cout << "Turn = 0.";
    g.print();
    for (int e = 1; e < 1001; ++e) 
    {
      g.one_step();
      if (e % 100 == 0)
      {
        cout << "Turn = " << e << ".";
        g.print();
      }
    }
  }
  catch (const invalid_argument&) 
  {
    assert(false);
  }
  catch (const out_of_range&) 
  {
    assert(false);
  }


  // ----------
  // darwin 8x8
  // ----------

  try 
  {
    cout << "*** Darwin 8x8 ***" << endl;
    
    Grid<8, 8> g;
    for (int a = 0; a < 2; a++) 
    {
      int pos = rand();
      Creature creature(best, rand() % 4);
      g.change(pos % 64 / 8, pos % 64 % 8, creature);
    }
    for (int a = 0; a < 2; a++) 
    {
      int pos = rand();
      Creature creature(hopper, rand() % 4);
      g.change(pos % 64 / 8, pos % 64 % 8, creature);
    }
    cout << "Turn = 0.";
    g.print();
    for (int e = 1; e < 100; ++e) 
    {
      g.one_step();
      cout << "Turn = " << e << ".";
      g.print();
    }
  }
  catch (const invalid_argument&) 
  {
    assert(false);
  }
  catch (const out_of_range&) 
  {
    assert(false);
  }

  // ------------
  // darwin 2 x 2
  // ------------

  try 
  {
    cout << "*** Darwin 2x2 ***" << endl;
    srand(0);

    Grid<2, 2> grid;
    grid.change(0, 0, Creature(rover, 0));
    grid.change(1, 0, Creature(food, 2));
    grid.change(0, 1, Creature(food, 2));
    grid.change(1, 1, Creature(food, 2));
    cout << "\nTurn: 0";
    grid.print();
    for(int i = 0; i < 5; i++)
    {
      grid.one_step();
      cout << "\nTurn: " << i + 1;
      grid.print();
    }
  }
  catch (const invalid_argument&) 
  {
    assert(false);
  }
  catch (const out_of_range&) 
  {
    assert(false);
  }

  // ------------
  // darwin 1 x 1
  // ------------

  try 
  {
    cout << "*** Darwin 1x1 ***" << endl;
    srand(0);

    Grid<1, 1> grid;
    grid.change(0, 0, Creature(food, 0));
    cout << "\nTurn: 0";
    grid.print();
    for(int i = 0; i < 5; i++)
    {
      grid.one_step();
      cout << "\nTurn: " << i + 1;
      grid.print();
    }
  }
  catch (const invalid_argument&) 
  {
    assert(false);
  }
  catch (const out_of_range&)
  {
    assert(false);
  }


  // ------------
  // darwin 5 x 5
  // ------------

  try 
  {
    cout << "*** Darwin 1x1 ***" << endl;
    srand(0);

    Grid<5, 5> grid;
    grid.change(0, 0, Creature(food, 0));
    grid.change(0, 1, Creature(food, 0));
    grid.change(0, 2, Creature(food, 0));
    grid.change(0, 3, Creature(food, 0));
    grid.change(0, 4, Creature(food, 0));
    grid.change(1, 4, Creature(rover, 1));
    cout << "\nTurn: 0";
    grid.print();
    for(int i = 0; i < 5; i++)
    {
      grid.one_step();
      cout << "\nTurn: " << i + 1;
      grid.print();
    }
  }
  catch (const invalid_argument&) 
  {
    assert(false);
  }
  catch (const out_of_range&)
  {
    assert(false);
  }

  // ------------
  // darwin 3 x 3
  // ------------

  try 
  {
    cout << "*** Darwin 1x1 ***" << endl;
    srand(0);

    Grid<3, 3> grid;
    grid.change(0, 0, Creature(food, 0));
    grid.change(0, 1, Creature(food, 0));
    grid.change(0, 2, Creature(food, 0));
    grid.change(1, 2, Creature(trap, 1));
    cout << "\nTurn: 0";
    grid.print();
    for(int i = 0; i < 5; i++)
    {
      grid.one_step();
      cout << "\nTurn: " << i + 1;
      grid.print();
    }
  }
  catch (const invalid_argument&) 
  {
    assert(false);
  }
  catch (const out_of_range&)
  {
    assert(false);
  }

  // ------------
  // darwin 2 x 2
  // ------------

  try 
  {
    cout << "*** Darwin 1x1 ***" << endl;
    srand(0);

    Grid<2, 2> grid;
    grid.change(0, 0, Creature(food, 0));
    grid.change(0, 1, Creature(food, 0));
    grid.change(1, 0, Creature(food, 0));
    grid.change(1, 1, Creature(trap, 1));
    cout << "\nTurn: 0";
    grid.print();
    for(int i = 0; i < 4; i++)
    {
      grid.one_step();
      cout << "\nTurn: " << i + 1;
      grid.print();
    }
  }
  catch (const invalid_argument&) 
  {
    assert(false);
  }
  catch (const out_of_range&)
  {
    assert(false);
  }

  return 0;
}