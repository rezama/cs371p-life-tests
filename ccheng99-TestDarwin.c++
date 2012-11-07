
/**
To test the program:
g++ -ansi -pedantic -lcppunit -ldl -Wall TestDarwin.c++ -o TestDarwin.app
valgrind TestDarwin.app >& TestDarwin.out
vi TestDarwin.out

 */
 
#include "cppunit/extensions/HelperMacros.h" // CPPUNIT_TEST, CPPUNIT_TEST_SUITE, CPPUNIT_TEST_SUITE_END
#include "cppunit/TestFixture.h"             // TestFixture
#include "cppunit/TextTestRunner.h"          // TestRunner
#include <exception>
#include "Darwin.h"

struct TestDarwin : CppUnit::TestFixture {

    // -----
    // test_coordinate
    // -----
    void test_calcfront () {
        Coordinate x(2,2);
        Coordinate y = x.calcFront(0);
        CPPUNIT_ASSERT(y.x == 2 && y.y == 1);
        
        
        y = x.calcFront(2);
        CPPUNIT_ASSERT(y.x == 2 && y.y == 3);
        
        y = x.calcFront(3);
        CPPUNIT_ASSERT(y.x == 3 && y.y == 2);
    }
    
    void test_calcfront2 () {
        Coordinate x(2,2);
        Coordinate y = x.calcFront(1);
        CPPUNIT_ASSERT(y.x == 1 && y.y == 2);
    }
    
    void test_calcfront3 () {
        Coordinate x(2,2);
        Coordinate y =  x.calcFront(2);
        CPPUNIT_ASSERT(y.x == 2 && y.y == 3);
        
    }
    
    void test_calcfront4 () {
        Coordinate x(2,2);
        Coordinate y = x.calcFront(3);
        CPPUNIT_ASSERT(y.x == 3 && y.y == 2);        
    }
    
    // ------
    // specie
    // ------
    void test_addAction(){
        Specie s("test");
        s.addAction(HOP, -1);
        Move m = s.processAction(0);
        CPPUNIT_ASSERT(m._action == HOP);
        CPPUNIT_ASSERT(m._line == -1);
    }
    
    void test_addMultiAction(){
        Specie s("test");
        s.addAction(HOP, -1);
        s.addAction(GO, 2);
        s.addAction(INFECT, -1);
        s.addAction(GO, 0);
        Move m = s.processAction(0);
        CPPUNIT_ASSERT(m._action == HOP);
        CPPUNIT_ASSERT(m._line == -1);
        
        m = s.processAction(1);
        CPPUNIT_ASSERT(m._action == GO);
        CPPUNIT_ASSERT(m._line == 2);
        
        m = s.processAction(2);
        CPPUNIT_ASSERT(m._action == INFECT);
        CPPUNIT_ASSERT(m._line == -1);
        
        m = s.processAction(3);
        CPPUNIT_ASSERT(m._action == GO);
        CPPUNIT_ASSERT(m._line == 0);
    }
    
    void test_addMultiAction2(){
        Specie s("test");
        s.addAction(IF_WALL, 2);
        s.addAction(GO, 2);
        s.addAction(INFECT, -1);
        s.addAction(GO, 0);
        Move m = s.processAction(0);
        CPPUNIT_ASSERT(m._action == IF_WALL);
        CPPUNIT_ASSERT(m._line == 2);
        
        m = s.processAction(1);
        CPPUNIT_ASSERT(m._action == GO);
        CPPUNIT_ASSERT(m._line == 2);
        
        m = s.processAction(2);
        CPPUNIT_ASSERT(m._action == INFECT);
        CPPUNIT_ASSERT(m._line == -1);
        
        m = s.processAction(3);
        CPPUNIT_ASSERT(m._action == GO);
        CPPUNIT_ASSERT(m._line == 0);
    }
    
    // --------
    // creature
    // --------
    
    void test_go(){
    
        Specie t("test");
        t.addAction(HOP,-1);
        Creature c(t,0);
        CPPUNIT_ASSERT(c.go(NULL, true));
    }
    
    void test_go_chain(){
    
        Specie t("test");
        t.addAction(HOP,-1);
        t.addAction(HOP,-1);
        t.addAction(IF_EMPTY, 0);
        t.addAction(INFECT, -1);
        t.addAction(GO, 0);
        
        Creature c(t,0);
        CPPUNIT_ASSERT(c.go(NULL, true));
        CPPUNIT_ASSERT(c.go(NULL, true));
        CPPUNIT_ASSERT(c.go(NULL, false)!= true);
        CPPUNIT_ASSERT(c.go(NULL, false)!=true);
        CPPUNIT_ASSERT(c.go(NULL, true));
    }
    
    void test_go_chain2(){
    
        Specie t("test");
        t.addAction(GO,1);
        t.addAction(HOP,-1);
        t.addAction(GO, 0);
        t.addAction(INFECT, -1);
        
        Creature c(t,0);
        CPPUNIT_ASSERT(c.go(NULL, true));
        CPPUNIT_ASSERT(c.go(NULL, true));
        CPPUNIT_ASSERT(c.go(NULL, true));
        CPPUNIT_ASSERT(c.go(NULL, true));
        CPPUNIT_ASSERT(c.go(NULL, false) == false);
    }
    
    // ----
    // grid
    // ----    
    
    void test_put_get(){
        Grid g(4,4);
        Specie hopper("hopper");
        Creature c(hopper,1);
        g.put(c,3,0);
        
        CPPUNIT_ASSERT(g.get(3,0)!=0);
        CPPUNIT_ASSERT(g.get(3,0) == &c);
    }
    
    void test_put_get2(){
        Grid g(4,4);
        Specie trap("trap");
        Creature t(trap,1);
        g.put(t,2,0);
        
        CPPUNIT_ASSERT(g.get(2,0)!=0);
        CPPUNIT_ASSERT(g.get(2,0) == &t);
    }
    
    void test_put_get3(){
        Grid g(4,4);
        Specie hopper("hopper");
        Creature c(hopper,1);
        g.put(c,1,1);
        
        CPPUNIT_ASSERT(g.get(1,1)!=0);
        CPPUNIT_ASSERT(g.get(1,1) == &c);
    }
    
    void test_grid_single(){
        Grid g(4,4);
        Specie hopper("hopper");
        hopper.addAction(HOP, -1);
        hopper.addAction(GO,0);
        
        Creature c(hopper,1);
        g.put(c,3,0);
        
        g.simulate(5,0);
        
        CPPUNIT_ASSERT(g.get(0,0)!=0);
        CPPUNIT_ASSERT(g.get(0,0) == &c);
    }
    
    /*
    .....
    .rS...
    .rN....
    .....
    */
    
    void test_grid_twoRovers(){
        srand(0);
        Grid g(5,5);
        Specie rover("rover");
        rover.addAction(IF_ENEMY, 9);
        rover.addAction(IF_EMPTY, 7);
        rover.addAction(IF_RANDOM, 5);
        rover.addAction(LEFT, -1);
        rover.addAction(GO, 0);
        rover.addAction(RIGHT,-1);
        rover.addAction(GO, 0);
        rover.addAction(HOP, -1);
        rover.addAction(GO, 0);
        rover.addAction(INFECT, -1);
        rover.addAction(GO,0);
        
        Creature cN(rover,1);
        Creature cS(rover,3);
        
        g.put(cS,1,1);
        g.put(cN,2,1);
                
        g.simulate(1,0);
        
        //g.debug();
        CPPUNIT_ASSERT((*g.get(1,1)).direction == 0);
        CPPUNIT_ASSERT((*g.get(2,1)).direction == 0);
        
        g.simulate(1,0);
        CPPUNIT_ASSERT((*g.get(1,0)).direction == 0);
        CPPUNIT_ASSERT((*g.get(2,0)).direction == 0);
        
        g.simulate(1,0);
        CPPUNIT_ASSERT((*g.get(1,0)).direction == 1);
        CPPUNIT_ASSERT((*g.get(2,0)).direction == 1);
      
        g.simulate(1,0);
        CPPUNIT_ASSERT((*g.get(0,0)).direction == 1);
        CPPUNIT_ASSERT((*g.get(1,0)).direction == 1);      
        
        g.simulate(1,0);
        CPPUNIT_ASSERT((*g.get(0,0)).direction == 2);
        CPPUNIT_ASSERT((*g.get(1,0)).direction == 2);  
        
        g.simulate(1,0);
        CPPUNIT_ASSERT((*g.get(0,1)).direction == 2);
        CPPUNIT_ASSERT((*g.get(1,1)).direction == 2);  
    }
    
    // ---------
    // Misc.
    // ---------
    
    void test_infect(){
        srand(0);
        
        Grid g(5,5);
        Specie trap("trap");
        trap.addAction(IF_ENEMY, 3);
        trap.addAction(LEFT,-1);
        trap.addAction(GO, 0);
        trap.addAction(INFECT, -1);
        trap.addAction(GO,0);
        
        Specie food("food");
        food.addAction(LEFT, -1);
        food.addAction(GO, 2);
        
        Creature t(trap,2);
        Creature f(food,3);
        
        g.put(t, 0, 0);
        g.put(f, 0, 1);
        
        g.simulate(1,0);

        CPPUNIT_ASSERT(g.get(0,1)!=0);
        Creature c = *(g.get(0,1)); 
        CPPUNIT_ASSERT(c.symbol == 't');
        CPPUNIT_ASSERT(c.getCounter() == 0);
        CPPUNIT_ASSERT(c.direction == 2);
        CPPUNIT_ASSERT(&f == g.get(0,1));
        
        g.simulate(1,0);
        CPPUNIT_ASSERT((*g.get(0,0)).direction == 1);
        CPPUNIT_ASSERT((*g.get(0,1)).direction == 1);
    }
    
    void test_no_double_move(){
        srand(0);
        
        Grid g(5,5);
        Specie hopper("hopper");
        hopper.addAction(HOP, -1);
        hopper.addAction(GO,0);
        
        Creature c(hopper,3);
        g.put(c,0,0);
        
        g.simulate(1,0);
        CPPUNIT_ASSERT(g.get(1,0) != 0);
        CPPUNIT_ASSERT(g.get(1,0) == &c);
        
        g.simulate(1,0);
        CPPUNIT_ASSERT(g.get(2,0) != 0);
        CPPUNIT_ASSERT(g.get(2,0) == &c);
    }
    
    //Rover should infect the trap first since
    //it is to the left of the trap
    void test_precedence(){
        srand(0);
        
        Grid g(5,5);
        Specie rover("rover");
        rover.addAction(IF_ENEMY, 9);
        rover.addAction(IF_EMPTY, 7);
        rover.addAction(IF_RANDOM, 5);
        rover.addAction(LEFT, -1);
        rover.addAction(GO, 0);
        rover.addAction(RIGHT,-1);
        rover.addAction(GO, 0);
        rover.addAction(HOP, -1);
        rover.addAction(GO, 0);
        rover.addAction(INFECT, -1);
        rover.addAction(GO,0);
        
        Specie trap("trap");
        trap.addAction(IF_ENEMY, 3);
        trap.addAction(LEFT,-1);
        trap.addAction(GO, 0);
        trap.addAction(INFECT, -1);
        trap.addAction(GO,0);
        
        Creature r(rover,2);
        Creature t(trap,0);
        g.put(r,0,0);
        g.put(t,0,1);
        
        g.simulate(1,0);
        CPPUNIT_ASSERT((*g.get(0,0)).direction == 2);
        CPPUNIT_ASSERT((*g.get(0,0)).symbol == 'r'); 
        CPPUNIT_ASSERT((*g.get(0,1)).direction == 1);
        CPPUNIT_ASSERT((*g.get(0,1)).symbol == 'r'); 
        
    }
    // -----
    // suite
    // -----
    
    CPPUNIT_TEST_SUITE(TestDarwin);
    
    CPPUNIT_TEST(test_calcfront);
    CPPUNIT_TEST(test_calcfront2);
    CPPUNIT_TEST(test_calcfront3);
    CPPUNIT_TEST(test_calcfront4);
    
    CPPUNIT_TEST(test_addAction);
    CPPUNIT_TEST(test_addMultiAction);
    CPPUNIT_TEST(test_addMultiAction2);
    
    CPPUNIT_TEST(test_put_get);
    CPPUNIT_TEST(test_put_get2);
    CPPUNIT_TEST(test_put_get3);
    
    CPPUNIT_TEST(test_go);
    CPPUNIT_TEST(test_go_chain);
    CPPUNIT_TEST(test_go_chain2);
    
    CPPUNIT_TEST(test_grid_single);
    CPPUNIT_TEST(test_grid_twoRovers);
    
    CPPUNIT_TEST(test_infect);
    CPPUNIT_TEST(test_no_double_move);
    CPPUNIT_TEST(test_precedence);
    CPPUNIT_TEST_SUITE_END();};

// ----
// main
// ----

int main () {
    using namespace std;
    ios_base::sync_with_stdio(false); // turn off synchronization with C I/O
    cout << "TestDarwin.c++" << endl;

    CppUnit::TextTestRunner tr;
    tr.addTest(TestDarwin::suite());
    tr.run();

    cout << "Done." << endl;
    return 0;}
