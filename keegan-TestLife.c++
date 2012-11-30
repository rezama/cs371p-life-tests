//TestLife
#include "Life.h"
#include "ConwayCell.h"
#include "Cell.h"
#include <iostream>
#include <vector>
#include <string>

#include "cppunit/extensions/HelperMacros.h" // CPPUNIT_TEST, CPPUNIT_TEST_SUITE, CPPUNIT_TEST_SUITE_END
#include "cppunit/TestFixture.h"             // TestFixture
#include "cppunit/TextTestRunner.h"          // TextTestRunner

void printArray(vector< vector< bool > > g, int a = 3, int b = 3){
    for (int i = 0; i < a; i++){
        cout << endl;
        for(int j = 0; j < b; j++){
            std::cout << g[i][j];
        }
    }    
    cout << endl;
}
struct TestLife : CppUnit::TestFixture {
    //-------------
    //FREDKIN TESTS
    //-------------
    
    //Constructor
    void fConst1 () {
        FredkinCell a(true);
        CPPUNIT_ASSERT(a.aRep == '0');
        CPPUNIT_ASSERT(a.alive);
        CPPUNIT_ASSERT(a.age == 0);
    }
    void fConst2 () {
        FredkinCell a(false);
        CPPUNIT_ASSERT(a.aRep == '-');
        CPPUNIT_ASSERT(!a.alive);
        CPPUNIT_ASSERT(a.age == 0);
    }
    void fConst3 () {
        FredkinCell a('+');
        CPPUNIT_ASSERT(a.aRep == '+');
        CPPUNIT_ASSERT(a.alive);
        CPPUNIT_ASSERT(a.age == 10);
    }
    void fConst4 () {
        FredkinCell a('-');
        CPPUNIT_ASSERT(a.aRep == '-');
        CPPUNIT_ASSERT(!a.alive);
        CPPUNIT_ASSERT(a.age == 0);
    }
    void fConst5 () {
        FredkinCell a('3');
        CPPUNIT_ASSERT(a.aRep == '3');
        CPPUNIT_ASSERT(a.alive);
        CPPUNIT_ASSERT(a.age == 3);
    }
    void fConst6 () {
        FredkinCell t(true);
        FredkinCell a(t);
        CPPUNIT_ASSERT(a.aRep == '0');
        CPPUNIT_ASSERT(a.alive);
        CPPUNIT_ASSERT(a.age == 0);
    }
    void fConst7 () {
        FredkinCell t('+');
        FredkinCell a(t);
        CPPUNIT_ASSERT(a.aRep == '+');
        CPPUNIT_ASSERT(a.alive);
        CPPUNIT_ASSERT(a.age == 10);
    }
    
    //Clone
    void fClone1 () {
        FredkinCell t(true);
        FredkinCell *a = t.clone();
        CPPUNIT_ASSERT(a->aRep == '0');
        CPPUNIT_ASSERT(a->alive);
        CPPUNIT_ASSERT(a->age == 0);
        delete a;
    }
    void fClone2 () {
        FredkinCell t('+');
        FredkinCell *a = t.clone();
        CPPUNIT_ASSERT(a->aRep == '+');
        CPPUNIT_ASSERT(a->alive);
        CPPUNIT_ASSERT(a->age == 10);
        delete a;
    }
    void fClone3 () {
        FredkinCell t('-');
        FredkinCell *a = t.clone();
        CPPUNIT_ASSERT(a->aRep == '-');
        CPPUNIT_ASSERT(!a->alive);
        CPPUNIT_ASSERT(a->age == 0);
        delete a;
    }
    
    //Prep and overwrite
    void fPrep1() {
        FredkinCell t(true);
        int a = 1;
        int b = 1;
        t.prep(a,b);
        CPPUNIT_ASSERT(t.age == 1);
        CPPUNIT_ASSERT(t.aNext == '1');
        CPPUNIT_ASSERT(t.alive == true);
        t.overWrite();
        CPPUNIT_ASSERT(t.alive == true);
    }
    void fPrep2() {
        FredkinCell t(false);
        int a = 1;
        int b = 1;
        t.prep(a,b);
        CPPUNIT_ASSERT(t.age == 0);
        CPPUNIT_ASSERT(t.aNext == '0');
        CPPUNIT_ASSERT(t.alive == false);
        t.overWrite();
        CPPUNIT_ASSERT(t.alive == true);
    }
    void fPrep3() {
        FredkinCell t('4');
        int a = 2;
        int b = 2;
        t.prep(a,b);
        CPPUNIT_ASSERT(t.age == 0);
        CPPUNIT_ASSERT(t.aNext == '-');
        CPPUNIT_ASSERT(t.alive == true);
        t.overWrite();
        CPPUNIT_ASSERT(t.alive == false);
    }
    
    
    //------------
    //CONWAY TESTS
    //------------
    
    //Constructor
    void cConst1 () {
        ConwayCell a(true);
        CPPUNIT_ASSERT(a.aRep == '*');
        CPPUNIT_ASSERT(a.alive);
    }
    void cConst2 () {
        ConwayCell a(false);
        CPPUNIT_ASSERT(a.aRep == '.');
        CPPUNIT_ASSERT(!a.alive);
    }
    void cConst3 () {
        ConwayCell a('*');
        CPPUNIT_ASSERT(a.aRep == '*');
        CPPUNIT_ASSERT(a.alive);
    }
    void cConst4 () {
        ConwayCell a('.');
        CPPUNIT_ASSERT(a.aRep == '.');
        CPPUNIT_ASSERT(!a.alive);
    }
    void cConst5 () {
        ConwayCell t(true);
        ConwayCell a(t);
        CPPUNIT_ASSERT(a.aRep == '*');
        CPPUNIT_ASSERT(a.alive);
    }
    void cConst6 () {
        ConwayCell t('*');
        ConwayCell a(t);
        CPPUNIT_ASSERT(a.aRep == '*');
        CPPUNIT_ASSERT(a.alive);
    }
    
    //Clone
    void cClone1 () {
        ConwayCell t(true);
        ConwayCell *a = t.clone();
        CPPUNIT_ASSERT(a->aRep == '*');
        CPPUNIT_ASSERT(a->alive);
        delete a;
    }
    void cClone2 () {
        ConwayCell t('*');
        ConwayCell *a = t.clone();
        CPPUNIT_ASSERT(a->aRep == '*');
        CPPUNIT_ASSERT(a->alive);
        delete a;
    }
    void cClone3 () {
        ConwayCell t('.');
        ConwayCell *a = t.clone();
        CPPUNIT_ASSERT(a->aRep == '.');
        CPPUNIT_ASSERT(!a->alive);
        delete a;
    }
    
    //Prep and overwrite
    void cPrep1() {
        ConwayCell t(true);
        int a = 1;
        int b = 1;
        t.prep(a,b);
        CPPUNIT_ASSERT(t.aNext == '.');
        CPPUNIT_ASSERT(t.alive == true);
        t.overWrite();
        CPPUNIT_ASSERT(t.alive == false);
    }
    void cPrep2() {
        ConwayCell t(false);
        int a = 1;
        int b = 1;
        t.prep(a,b);
        CPPUNIT_ASSERT(t.aNext == '.');
        CPPUNIT_ASSERT(t.alive == false);
        t.overWrite();
        CPPUNIT_ASSERT(t.alive == false);
    }
    void cPrep3() {
        ConwayCell t('*');
        int a = 3;
        int b = 3;
        t.prep(a,b);
        CPPUNIT_ASSERT(t.aNext == '*');
        CPPUNIT_ASSERT(t.alive == true);
        t.overWrite();
        CPPUNIT_ASSERT(t.alive == true);
    }
    
    
    //------------
    //CELL TESTS
    //------------
    
    //Constructor
    void clConst1 () {
        Cell a(true);
        CPPUNIT_ASSERT(a.aRep == '0');
        CPPUNIT_ASSERT(a.alive);
        
    }
    void clConst2 () {
        Cell a('2');
        CPPUNIT_ASSERT(a.aRep == '2');
        CPPUNIT_ASSERT(a.alive);
    }
    void clConst3 () {
        Cell a('*');
        CPPUNIT_ASSERT(a.aRep == '*');
        CPPUNIT_ASSERT(a.alive);
    }
    void clConst4 () {
        Cell a('0');
        CPPUNIT_ASSERT(a.aRep == '0');
        CPPUNIT_ASSERT(a.alive);
    }
    
    //Prep and overwrite
    void clPrep1() {
        Cell t(true);
        int a = 1;
        int b = 1;
        t.prep(a,b);
        CPPUNIT_ASSERT(t.aRep == '0');
        CPPUNIT_ASSERT(t.alive == true);
        t.overWrite();
        CPPUNIT_ASSERT(t.alive == true);
        CPPUNIT_ASSERT(t.aRep == '1');
    }
    void clPrep2() {
        Cell t('1');
        int a = 1;
        int b = 1;
        t.prep(a,b);
        CPPUNIT_ASSERT(t.aRep == '1');
        CPPUNIT_ASSERT(t.alive == true);
        t.overWrite();
        CPPUNIT_ASSERT(t.alive == true);
        CPPUNIT_ASSERT(t.aRep == '*');
    }
    void clPrep3() {
        Cell t('*');
        int a = 3;
        int b = 3;
        t.prep(a,b);
        CPPUNIT_ASSERT(t.aRep == '*');
        CPPUNIT_ASSERT(t.alive == true);
        t.overWrite();
        CPPUNIT_ASSERT(t.alive == true);
        CPPUNIT_ASSERT(t.aRep == '*');
    }
    
    //-----------
    // LIFE TESTS
    //-----------
    
    //Constructor
    void lconst1(){
        vector< vector < char > > a = {{'.','.','.'},
                                       {'*','*','*'},
                                       {'.','.','.'}};
        Life<ConwayCell> l(3,3,a);
        l.print();
    }
    void lconst2(){
        vector< vector < char > > a = {{'-','-','-'},
                                       {'0','0','0'},
                                       {'-','-','-'}};
        Life<FredkinCell> l(3,3,a);
        l.print();
    }
    void lconst3(){
        vector< vector < char > > a = {{'-','-','-'},
                                       {'0','2','0'},
                                       {'-','0','-'}};
        Life<Cell> l(3,3,a);
        l.print();
    }
    
    //Advance Turn
    void laT1(){
        vector< vector < char > > a = {{'.','.','.'},
                                       {'*','*','*'},
                                       {'.','.','.'}};
        Life<ConwayCell> l(3,3,a);
        l.print();
        l.advanceTurn();
        l.print();
    }
    void laT2(){
        vector< vector < char > > a = {{'-','-','-'},
                                       {'0','0','0'},
                                       {'-','-','-'}};
        Life<FredkinCell> l(3,3,a);
        l.print();
        l.advanceTurn();
        l.print();
    }
    void laT3(){
        vector< vector < char > > a = {{'-','-','-'},
                                       {'0','2','0'},
                                       {'-','0','-'}};
        Life<Cell> l(3,3,a);
        l.print();
        l.advanceTurn();
        l.print();
    }
    
    //Neighbors
    void lNeighbors1(){
        vector< vector < char > > a = {{'.','.','.'},
                                       {'*','*','*'},
                                       {'.','.','.'}};
        Life<ConwayCell> l(3,3,a);
        cout << endl << "Neighbors of center: ";
        printArray(l.neighbors(1,1));
    }
    void lNeighbors2(){
        vector< vector < char > > a = {{'-','-','-'},
                                       {'0','0','0'},
                                       {'-','-','-'}};
        Life<FredkinCell> l(3,3,a);
        cout << endl << "Neighbors of center: ";
        printArray(l.neighbors(1,1));
    }
    void lNeighbors3(){
        vector< vector < char > > a = {{'-','-','-'},
                                       {'0','2','0'},
                                       {'-','0','-'}};
        Life<Cell> l(3,3,a);
        cout << endl << "Neighbors of center: ";
        printArray(l.neighbors(1,1));
    }
    
    
    CPPUNIT_TEST_SUITE(TestLife);
    CPPUNIT_TEST(fConst1);
    CPPUNIT_TEST(fConst2);
    CPPUNIT_TEST(fConst3);
    CPPUNIT_TEST(fConst4);
    CPPUNIT_TEST(fConst5);
    CPPUNIT_TEST(fConst6);
    CPPUNIT_TEST(fConst7);
    CPPUNIT_TEST(fClone1);
    CPPUNIT_TEST(fClone2);
    CPPUNIT_TEST(fClone3);
    CPPUNIT_TEST(fPrep1);
    CPPUNIT_TEST(fPrep2);
    CPPUNIT_TEST(fPrep3);
    CPPUNIT_TEST(cConst1);
    CPPUNIT_TEST(cConst2);
    CPPUNIT_TEST(cConst3);
    CPPUNIT_TEST(cConst4);
    CPPUNIT_TEST(cConst5);
    CPPUNIT_TEST(cConst6);
    CPPUNIT_TEST(cClone1);
    CPPUNIT_TEST(cClone2);
    CPPUNIT_TEST(cClone3);
    CPPUNIT_TEST(cPrep1);
    CPPUNIT_TEST(cPrep2);
    CPPUNIT_TEST(cPrep3);
    CPPUNIT_TEST(clConst1);
    CPPUNIT_TEST(clConst2);
    CPPUNIT_TEST(clConst3);
    CPPUNIT_TEST(clConst4);
    CPPUNIT_TEST(clPrep1);
    CPPUNIT_TEST(clPrep2);
    CPPUNIT_TEST(clPrep3);
    CPPUNIT_TEST(lconst1);
    CPPUNIT_TEST(lconst2);
    CPPUNIT_TEST(lconst3);
    CPPUNIT_TEST(laT1);
    CPPUNIT_TEST(laT2);
    CPPUNIT_TEST(laT3);
    CPPUNIT_TEST(lNeighbors1);
    CPPUNIT_TEST(lNeighbors2);
    CPPUNIT_TEST(lNeighbors3);
    CPPUNIT_TEST_SUITE_END();
};
int main(){
    using namespace std;
    ios_base::sync_with_stdio(false);  // turn off synchronization with C I/O
    cout << "TestDarwin.c++" << endl;

    CppUnit::TextTestRunner tr;
    tr.addTest(TestLife::suite());
    tr.run();

    cout << "Done." << endl;
    return 0;
}