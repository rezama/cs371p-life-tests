// --------------------------
// projects/life/TestLife.c++
// Copyright (C) 2012
// --------------------------

/**
 * To test the program:
 *     g++ -std=c++0x -pedantic -lcppunit -ldl -Wall TestLife.c++ -o TestLife.app
 *     valgrind TestLife.app >& TestLife.out
 */

// --------
// includes
// --------
#include "cppunit/extensions/HelperMacros.h" // CPPUNIT_TEST, CPPUNIT_TEST_SUITE, CPPUNIT_TEST_SUITE_END
#include "cppunit/TestFixture.h"             // TestFixture
#include "cppunit/TextTestRunner.h"          // TestRunner
#include <iostream>
#define private public
#define protected public
#include <vector>
#include "AbstractCell.h"
#include "ConwayCell.h"
#include "FredkinCell.h"
#include "Cell.h"
#include "Life.h"

// --------------
// TestConwayCell
// --------------
struct TestConwayCell : CppUnit::TestFixture 
{
    void test_constructor_1()
    {
        ConwayCell cw(false);
        CPPUNIT_ASSERT(false == cw.is_alive);
    }

    void test_constructor_2()
    {
        ConwayCell cw(true);
        CPPUNIT_ASSERT(true == cw.is_alive);
    }

    void test_constructor_3()
    {
        ConwayCell cw(false);
        CPPUNIT_ASSERT(false == cw.is_alive);
    }

    void test_neighbor_count_update_1()
    {
        ConwayCell cw(true);
        CPPUNIT_ASSERT(0 == cw.neighbors_count);
        cw.update(5);
        CPPUNIT_ASSERT(5 == cw.neighbors_count);
    }

    void test_neighbor_count_update_2()
    {
        ConwayCell cw(true);
        CPPUNIT_ASSERT(0 == cw.neighbors_count);
        cw.update(34);
        CPPUNIT_ASSERT(34 == cw.neighbors_count);
    }
    void test_neighbor_count_update_3()
    {
        ConwayCell cw(true);
        CPPUNIT_ASSERT(0 == cw.neighbors_count);
        cw.update(59);
        CPPUNIT_ASSERT(59 == cw.neighbors_count);
    }

    void test_apply_update_1()
    {
        ConwayCell cw(false);
        cw.update(3);
        cw.apply_update();
        CPPUNIT_ASSERT(true == cw.alive());
    }

    void test_apply_update_2()
    {
        ConwayCell cw(false);
        cw.update(1);
        cw.apply_update();
        CPPUNIT_ASSERT(false == cw.alive());
    }

    void test_apply_update_3()
    {
        ConwayCell cw(true);
        cw.update(5);
        cw.apply_update();
        CPPUNIT_ASSERT(false == cw.alive());
    }

    void test_print_1()
    {
        ConwayCell cw(true);
        CPPUNIT_ASSERT("*" == cw.print());
    }

    void test_print_2()
    {
        ConwayCell cw(false);
        CPPUNIT_ASSERT("." == cw.print());
    }

    void test_print_3()
    {
        ConwayCell cw(true);
        CPPUNIT_ASSERT("*" == cw.print());
        cw.update(5);
        cw.apply_update();
        CPPUNIT_ASSERT("." == cw.print());
    }

    void test_clone_1()
    {
        ConwayCell cw(true);
        AbstractCell* cloned = cw.clone();
        CPPUNIT_ASSERT(cloned != &cw);
        delete(cloned);
    }

    void test_clone_2()
    {
        ConwayCell cw(true);
        AbstractCell* cloned = cw.clone();
        CPPUNIT_ASSERT(cloned->alive() == true);
        delete(cloned);
    }

    void test_clone_3()
    {
        ConwayCell cw(false);
        AbstractCell* cloned = cw.clone();
        CPPUNIT_ASSERT(cloned->alive() == false);
        delete(cloned);
    }

    CPPUNIT_TEST_SUITE(TestConwayCell);

    
    CPPUNIT_TEST(test_constructor_1);
    CPPUNIT_TEST(test_constructor_2);
    CPPUNIT_TEST(test_constructor_3);
    CPPUNIT_TEST(test_neighbor_count_update_1);
    CPPUNIT_TEST(test_neighbor_count_update_2);
    CPPUNIT_TEST(test_neighbor_count_update_3);
    CPPUNIT_TEST(test_apply_update_1);
    CPPUNIT_TEST(test_apply_update_2);
    CPPUNIT_TEST(test_apply_update_3);
    CPPUNIT_TEST(test_print_1);
    CPPUNIT_TEST(test_print_2);
    CPPUNIT_TEST(test_print_3);
    CPPUNIT_TEST(test_clone_1);
    CPPUNIT_TEST(test_clone_2);
    CPPUNIT_TEST(test_clone_3);

    CPPUNIT_TEST_SUITE_END();
};

// ---------------
// TestFredkinCell
// ---------------
struct TestFredkinCell : CppUnit::TestFixture 
{

    void test_constructor_1()
    {
        FredkinCell cw(false,23);
        CPPUNIT_ASSERT(false == cw.is_alive);
        CPPUNIT_ASSERT(23 == cw.age);
    }

    void test_constructor_2()
    {
        FredkinCell cw(true,2);
        CPPUNIT_ASSERT(true == cw.is_alive);
        CPPUNIT_ASSERT(2 == cw.age);
    }

    void test_constructor_3()
    {
        FredkinCell cw(false,4);
        CPPUNIT_ASSERT(false == cw.is_alive);
        CPPUNIT_ASSERT(4 == cw.age);
    }

    void test_neighbor_count_update_1()
    {
        FredkinCell cw(false,4);
        CPPUNIT_ASSERT(0 == cw.neighbors_count);
        cw.update(5);
        CPPUNIT_ASSERT(5 == cw.neighbors_count);
    }

    void test_neighbor_count_update_2()
    {
        FredkinCell cw(false,4);
        CPPUNIT_ASSERT(0 == cw.neighbors_count);
        cw.update(34);
    }
    void test_neighbor_count_update_3()
    {
        FredkinCell cw(false,4);
        CPPUNIT_ASSERT(0 == cw.neighbors_count);
        cw.update(59);
        CPPUNIT_ASSERT(59 == cw.neighbors_count);
    }

    void test_apply_update_1()
    {
        FredkinCell cw(false,4);
        cw.update(3);
        cw.apply_update();
        CPPUNIT_ASSERT(true == cw.alive());
        CPPUNIT_ASSERT(4 == cw.age);
    }

    void test_apply_update_2()
    {
        FredkinCell cw(true,4);
        cw.update(2);
        cw.apply_update();
        CPPUNIT_ASSERT(false == cw.alive());
        CPPUNIT_ASSERT(4 == cw.age);
    }

    void test_apply_update_3()
    {
        FredkinCell cw(true,4);
        cw.update(1);
        cw.apply_update();
        CPPUNIT_ASSERT(true == cw.alive());
        CPPUNIT_ASSERT(5 == cw.age);
    }

    void test_print_1()
    {
        FredkinCell cw(true,4);
        CPPUNIT_ASSERT("4" == cw.print());
    }

    void test_print_2()
    {
        FredkinCell cw(false,4);
        CPPUNIT_ASSERT("-" == cw.print());
    }

    void test_print_3()
    {
        FredkinCell cw(true,12);
        CPPUNIT_ASSERT("+" == cw.print());
    }

    void test_clone_1()
    {
        FredkinCell cw(true,12);
        AbstractCell* cloned = cw.clone();
        CPPUNIT_ASSERT(cloned != &cw);
        delete(cloned);
    }

    void test_clone_2()
    {
        FredkinCell cw(true,12);
        AbstractCell* cloned = cw.clone();
        CPPUNIT_ASSERT(cloned->alive() == true);
        delete(cloned);
    }

    void test_clone_3()
    {
        FredkinCell cw(true,12);
        AbstractCell* cloned = cw.clone();
        FredkinCell* const q = dynamic_cast<FredkinCell*>(cloned);
        CPPUNIT_ASSERT(q->age == 12);
        delete(cloned);
    }

    CPPUNIT_TEST_SUITE(TestFredkinCell);

    
    CPPUNIT_TEST(test_constructor_1);
    CPPUNIT_TEST(test_constructor_2);
    CPPUNIT_TEST(test_constructor_3);
    CPPUNIT_TEST(test_neighbor_count_update_1);
    CPPUNIT_TEST(test_neighbor_count_update_2);
    CPPUNIT_TEST(test_neighbor_count_update_3);
    CPPUNIT_TEST(test_apply_update_1);
    CPPUNIT_TEST(test_apply_update_2);
    CPPUNIT_TEST(test_apply_update_3);
    CPPUNIT_TEST(test_print_1);
    CPPUNIT_TEST(test_print_2);
    CPPUNIT_TEST(test_print_3);
    CPPUNIT_TEST(test_clone_1);
    CPPUNIT_TEST(test_clone_2);
    CPPUNIT_TEST(test_clone_3);

    CPPUNIT_TEST_SUITE_END();
};

// --------
// TestCell
// --------
struct TestCell : CppUnit::TestFixture 
{
    void test_constructor_1()
    {
        Cell c = new ConwayCell(true);
        CPPUNIT_ASSERT(true == c.cell->is_alive);

    }

    void test_constructor_2()
    {
        Cell c = new FredkinCell(true,23);
        CPPUNIT_ASSERT(true == c.cell->is_alive);
        FredkinCell* const q = dynamic_cast<FredkinCell*>(c.cell);
        CPPUNIT_ASSERT(23 == q->age);

    }

    void test_constructor_3()
    {
        Cell c = new FredkinCell(false,2);
        CPPUNIT_ASSERT(false == c.cell->is_alive);
        FredkinCell* const q = dynamic_cast<FredkinCell*>(c.cell);
        CPPUNIT_ASSERT(2 == q->age);

    }

    void test_neighbor_count_update_1()
    {
        Cell c = new ConwayCell(true);
        CPPUNIT_ASSERT(0 == c.neighbor_count());
        c.update(5);
        CPPUNIT_ASSERT(5 == c.neighbor_count());
    }

    void test_neighbor_count_update_2()
    {
        Cell c = new FredkinCell(false,4);
        CPPUNIT_ASSERT(0 == c.neighbor_count());
        c.update(5);
        CPPUNIT_ASSERT(5 == c.neighbor_count());
    }

    void test_neighbor_count_update_3()
    {
        Cell c = new FredkinCell(false,4);
        CPPUNIT_ASSERT(0 == c.neighbor_count());
        c.update(59);
        CPPUNIT_ASSERT(59 == c.neighbor_count());
    }

    void test_apply_update_1()
    {
        Cell c = new ConwayCell(true);
        c.update(5);
        c.apply_update();
        CPPUNIT_ASSERT(false == c.alive());
    }

    void test_apply_update_2()
    {
        Cell c = new FredkinCell(true,4);
        c.update(2);
        c.apply_update();
        CPPUNIT_ASSERT(false == c.alive());
        FredkinCell* const q = dynamic_cast<FredkinCell*>(c.cell);
        CPPUNIT_ASSERT(4 == q->age);
    }

    void test_apply_update_3()
    {
        Cell c = new FredkinCell(true,4);
        c.update(1);
        c.apply_update();
        CPPUNIT_ASSERT(true == c.alive());
        FredkinCell* const q = dynamic_cast<FredkinCell*>(c.cell);
        CPPUNIT_ASSERT(5 == q->age);
    }

    void test_print_1()
    {
        Cell c = new ConwayCell(true);
        CPPUNIT_ASSERT("*" == c.print());
    }

    void test_print_2()
    {
        Cell c = new FredkinCell(false,4);
        CPPUNIT_ASSERT("-" == c.print());
    }

    void test_print_3()
    {
        Cell c = new FredkinCell(true,12);
        CPPUNIT_ASSERT("+" == c.print());
    }

    void test_clone_1()
    {
        Cell c = new ConwayCell(true);
        Cell* cloned = c.clone();
        CPPUNIT_ASSERT(cloned != &c);
        delete(cloned);
    }

    void test_clone_2()
    {
        Cell c = new FredkinCell(true,12);
        Cell* cloned = c.clone();
        CPPUNIT_ASSERT(cloned->alive() == true);
        delete(cloned);
    }

    void test_clone_3()
    {
        Cell c = new FredkinCell(true,12);
        Cell* cloned = c.clone();
        FredkinCell* const q = dynamic_cast<FredkinCell*>(cloned->cell);
        CPPUNIT_ASSERT(q->age == 12);
        delete(cloned);
    }

    void test_evolve_1()
    {
        Cell c = new FredkinCell(true,1);
        c.evolve();
        if(ConwayCell* const q = dynamic_cast<ConwayCell*>(c.cell))
            CPPUNIT_ASSERT(true);
        else
            CPPUNIT_ASSERT(false);
    }

    void test_evolve_2()
    {
        Cell c = new FredkinCell(true,43);
        c.evolve();
        if(ConwayCell* const q = dynamic_cast<ConwayCell*>(c.cell))
            CPPUNIT_ASSERT(true);
        else
            CPPUNIT_ASSERT(false);
    }

    void test_evolve_3()
    {
        Cell c = new FredkinCell(true,34);
        c.evolve();
        if(ConwayCell* const q = dynamic_cast<ConwayCell*>(c.cell))
            CPPUNIT_ASSERT(true);
        else
            CPPUNIT_ASSERT(false);
    }

    CPPUNIT_TEST_SUITE(TestCell);
    CPPUNIT_TEST(test_constructor_1);
    CPPUNIT_TEST(test_constructor_2);
    CPPUNIT_TEST(test_constructor_3);
    CPPUNIT_TEST(test_neighbor_count_update_1);
    CPPUNIT_TEST(test_neighbor_count_update_2);
    CPPUNIT_TEST(test_neighbor_count_update_3);
    CPPUNIT_TEST(test_apply_update_1);
    CPPUNIT_TEST(test_apply_update_2);
    CPPUNIT_TEST(test_apply_update_3);
    CPPUNIT_TEST(test_print_1);
    CPPUNIT_TEST(test_print_2);
    CPPUNIT_TEST(test_print_3);
    CPPUNIT_TEST(test_clone_1);
    CPPUNIT_TEST(test_clone_2);
    CPPUNIT_TEST(test_clone_3);
    CPPUNIT_TEST(test_evolve_1);
    CPPUNIT_TEST(test_evolve_2);
    CPPUNIT_TEST(test_evolve_3);
    CPPUNIT_TEST_SUITE_END();
};

// ----
// main
// ----
int main () 
{
    using namespace std;
    ios_base::sync_with_stdio(false); // turn off synchronization with C I/O
    cout << "TestLife.c++" << endl;

    cout << "\nTestConwayCell::suite()" << endl;
    CppUnit::TextTestRunner tcc;
    tcc.addTest(TestConwayCell::suite());
    tcc.run();

    cout << "\nTestFredkinCell::suite()" << endl;
    CppUnit::TextTestRunner tfc;
    tfc.addTest(TestFredkinCell::suite());
    tfc.run();

    cout << "\nTestCell::suite()" << endl;
    CppUnit::TextTestRunner tc;
    tc.addTest(TestCell::suite());
    tc.run();
    
    cout << "Done." << endl;
    return 0;
}