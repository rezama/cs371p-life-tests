// ------------------------------------
// projects/allocator/TestAllocator.c++
// Copyright (C) 2011
// Glenn P. Downing
// ------------------------------------

/**
 * To test the program:
 *     g++ -ansi -pedantic -lcppunit -ldl -Wall TestAllocator.c++ -o TestAllocator.app
 *     valgrind TestAllocator.app >& TestAllocator.out
 */

// --------
// includes
// --------

#include <algorithm> // count
#include <memory>    // allocator

#include "cppunit/extensions/HelperMacros.h" // CPPUNIT_TEST, CPPUNIT_TEST_SUITE, CPPUNIT_TEST_SUITE_END
#include "cppunit/TestFixture.h"             // TestFixture
#include "cppunit/TextTestRunner.h"          // TestRunner

#define private public
#include "Allocator.h"

// -------------
// TestAllocator
// -------------

template <typename A>
struct TestAllocator : CppUnit::TestFixture {
    // --------
    // typedefs
    // --------

    typedef typename A::value_type      value_type;
    typedef typename A::difference_type difference_type;
    typedef typename A::pointer         pointer;

    // --------
    // test_one
    // --------

    void test_one () {
        A x;
        const difference_type s = 1;
        const value_type      v = 2;
        const pointer         p = x.allocate(s);
        x.construct(p, v);
        CPPUNIT_ASSERT(*p == v);
        x.destroy(p);
        x.deallocate(p, s);}

    // --------
    // test_ten
    // --------

    void test_ten () {
        A x;
        const difference_type s = 10;
        const value_type      v = 2;
        const pointer         b = x.allocate(s);
              pointer         e = b + s;
              pointer         p = b;
        try {
            while (p != e) {
                x.construct(p, v);
                ++p;}}
        catch (...) {
            while (b != p) {
                --p;
                x.destroy(p);}
            x.deallocate(b, s);
            throw;}
        CPPUNIT_ASSERT(std::count(b, e, v) == s);
        while (b != e) {
            --e;
            x.destroy(e);}
        x.deallocate(b, s);}
        
    void test_twoBlocks() {
        A x;
        const value_type v = 4;
        const difference_type s = 5;
        const difference_type t = 1;
        const pointer b1 = x.allocate(s);
              pointer e1 = b1 + s;
              pointer p1 = b1;
        const pointer b2 = x.allocate(t);
              pointer e2 = b2 + t;
              pointer p2 = b2;
        
        try{
            while(p1 != e1){
                x.construct(p1,v);
                ++p1;
            }
        }catch(...){
            while (b1 != p1) {
                --p1;
                x.destroy(p1);}
            x.deallocate(b1, s);
            throw;
        }
        CPPUNIT_ASSERT(std::count(b1, e1, v) == s);
        try{
            while(p2 != e2){
                x.construct(p2,v);
                ++p2;
            }
        }catch(...){
            while (b2 != p2) {
                --p2;
                x.destroy(p2);}
            x.deallocate(b2, t);
            throw;
        }
        CPPUNIT_ASSERT(std::count(b2, e2, v) == t);
        
        while (b1 != e1) {
            --e1;
            x.destroy(e1);}
        x.deallocate(b1, s);
        
        while (b2 != e2) {
            --e2;
            x.destroy(e2);}
        x.deallocate(b2, t);
    }
    
    void test_coaelsce () {
        A x;
        const difference_type s = 1;
        const value_type      v = 2;
        const pointer         b1 = x.allocate(s);
        const pointer         b2 = x.allocate(s);
        const pointer         b3 = x.allocate(s);
              pointer         e1 = b1 + s;
              pointer         e2 = b3 + s;
              pointer         e3 = b2 + s;
        
        x.deallocate(b1,s);
        x.deallocate(b2,s);
        x.deallocate(b3,s);
        CPPUNIT_ASSERT(x.view(0) == x.view(96));
    }

    // -----
    // suite
    // -----

    CPPUNIT_TEST_SUITE(TestAllocator);
    CPPUNIT_TEST(test_one);
    CPPUNIT_TEST(test_ten);
    CPPUNIT_TEST(test_twoBlocks);
    CPPUNIT_TEST_SUITE_END();
    
    };
    
template <typename A>
struct PersonalAllocator : CppUnit::TestFixture {
    // --------
    // typedefs
    // --------

    typedef typename A::value_type      value_type;
    typedef typename A::difference_type difference_type;
    typedef typename A::pointer         pointer;
    
    void test_max () {
        A x;
        const difference_type s = 23;
        const value_type      v = 2;
        const pointer         b = x.allocate(s);
              pointer         e = b + s;
              pointer         p = b;
        try {
            while (p != e) {
                x.construct(p, v);
                ++p;}}
        catch (...) {
            while (b != p) {
                --p;
                x.destroy(p);}
            x.deallocate(b, s);
            throw;}
        CPPUNIT_ASSERT(std::count(b, e, v) == s);
        while (b != e) {
            --e;
            x.destroy(e);}
        x.deallocate(b, s);}
        
    void test_coaelsce_left () {
        A x;
        const difference_type s = 1;
        const pointer         b1 = x.allocate(s);
        const pointer         b2 = x.allocate(s);
        
        x.deallocate(b1,s);
        x.deallocate(b2,s);
        
        CPPUNIT_ASSERT(x.view(0) == x.view(96));
    }
    
    void test_coaelsce_right () {
        A x;
        const difference_type s = 1;
        const pointer         b1 = x.allocate(s);
        const pointer         b2 = x.allocate(s);
        
        x.deallocate(b2,s);
        x.deallocate(b1,s);
        
        CPPUNIT_ASSERT(x.view(0) == x.view(96));
    }
    
    void test_coaelsce_left_right () {
        A x;
        const difference_type s = 1;
        const pointer         b1 = x.allocate(s);
        const pointer         b2 = x.allocate(s);
        const pointer         b3 = x.allocate(s);
        
        x.deallocate(b2,s);
        x.deallocate(b1,s);
        x.deallocate(b3,s);
        
        CPPUNIT_ASSERT(x.view(0) == x.view(96));
    }
    
    void test_put () {
        A x;
        int i = 15;
        x.put(i,0);
        int actual = (x.a[0] << 24) | (x.a[1] << 16) | (x.a[2] << 8) | (x.a[3]);
        CPPUNIT_ASSERT(actual == i);
        CPPUNIT_ASSERT(x.view(0) == i);
    }
    
    void test_put2 () {
        A x;
        int i = -15;
        x.put(i,0);
        int actual = (x.a[0] << 24) | (x.a[1] << 16) | (x.a[2] << 8) | (x.a[3]);
        CPPUNIT_ASSERT(actual == i);
        CPPUNIT_ASSERT(x.view(0) == i);
    }
    
    void test_put3 () {
        A x;
        int i = 75;
        x.put(i,15);
        int actual = (x.a[15] << 24) | (x.a[16] << 16) | (x.a[17] << 8) | (x.a[18]);
        CPPUNIT_ASSERT(actual == i);
        CPPUNIT_ASSERT(x.view(15) == i);
    }
    
    void test_view () {
        A x;
        int i = 15;
        x.put(i,0);
        CPPUNIT_ASSERT(x.view(0) == i);
    }
    
    void test_view2 () {
        A x;
        int i = -15;
        x.put(i,0);
        CPPUNIT_ASSERT(x.view(0) == i);
    }
    
    void test_view3 () {
        A x;
        int i = 75;
        x.put(i,15);
        CPPUNIT_ASSERT(x.view(15) == i);
    }

    // -----
    // suite
    // -----
    
    CPPUNIT_TEST_SUITE(PersonalAllocator);
    CPPUNIT_TEST(test_max);
    CPPUNIT_TEST(test_coaelsce_left);
    CPPUNIT_TEST(test_coaelsce_right);
    CPPUNIT_TEST(test_coaelsce_left_right);
    CPPUNIT_TEST(test_put);
    CPPUNIT_TEST(test_put2);
    CPPUNIT_TEST(test_put3);
    CPPUNIT_TEST(test_view);
    CPPUNIT_TEST(test_view2);
    CPPUNIT_TEST(test_view3);
    CPPUNIT_TEST_SUITE_END();
    
    };

// ----
// main
// ----

int main () {
    using namespace std;
    ios_base::sync_with_stdio(false);    // turn off synchronization with C I/O
    cout << "TestAllocator.c++" << endl;

    CppUnit::TextTestRunner tr;

    tr.addTest(TestAllocator< std::allocator<int> >::suite());
    tr.addTest(TestAllocator< Allocator<int, 100> >::suite());

    tr.addTest(TestAllocator< std::allocator<double> >::suite());
    tr.addTest(TestAllocator< Allocator<double, 100> >::suite()); 

    tr.run();
    
    CppUnit::TextTestRunner tr2;
    tr2.addTest(PersonalAllocator<Allocator<int,100> >::suite());
    
    tr2.run();

    cout << "Done." << endl;
    return 0;}
