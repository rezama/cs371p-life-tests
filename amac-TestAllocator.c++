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
#include <stdexcept>

#define private public
#define protected public
#define class struct

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
    // test_allocate
    // --------

    //test too small of allocator
    void test_allocate_1 () {
        A x;
        const difference_type s = 0;
        try {
            x.allocate(s);
        }
        catch (std::bad_alloc& e) {
            CPPUNIT_ASSERT(true);
        }}


    //test filled allocator
    void test_allocate_2 () {
        A x;
        int max = (100 - sizeof(value_type) - (4 * sizeof(int)));
        const difference_type s = (max / sizeof(value_type));
        const value_type      v = 2;
        const pointer         b = x.allocate(s);
              pointer         e = b + s;
              pointer         p = b;
        try {
            while(p != e) {
                x.construct(p, v);
                CPPUNIT_ASSERT(*p == v); // tests construct
                ++p;
            }
        }
        catch(...) {
            while(b != p)
                x.destroy(--p);
            
            x.deallocate(b, s);
            throw;
        }
        CPPUNIT_ASSERT(std::count(b, e, v) == s);
        while (b != e)
            x.destroy(--e);
            
        x.deallocate(b, s);}


    //test overfill
    void test_allocate_3 () {
        A x;
        const difference_type s = 10000;
        try {
              x.allocate(s);
        }
        catch(std::bad_alloc& e) {
            CPPUNIT_ASSERT(true);
        }}

    // --------
    // test_valid
    // --------

    //test easy valid
    void test_valid_1 () {
        Allocator<int, 100> x;
        int* b = (int*) &x.a[0];
        *b = 92;
        b += 96;
        *b = 92;
        const bool result = x.valid();
        CPPUNIT_ASSERT(result == true);
    }

    //test hard valid
    void test_valid_2 () {
        Allocator<int, 100> x;
        int* b = (int*) &x.a[0];
        *b = -40;
        b = (int*) &x.a[44];
        *b = -40;
        b = (int*) &x.a[48];
        *b = -10;
        b = (int*) &x.a[62];
        *b = -10;
        b = (int*) &x.a[66];
        *b = 26;
        b = (int*) &x.a[96];
        *b = 26;
        const bool result = x.valid();
        CPPUNIT_ASSERT(result == true);
    }

    //test invalid
    void test_valid_3 () {
        Allocator<double, 100> x;
        int* b = (int*) &x.a[0];
        *b = -40;
        b = (int*) &x.a[44];
        *b = -40;
        b = (int*) &x.a[48];
        *b = -100;
        const bool result = x.valid();
        CPPUNIT_ASSERT(result == false);
    }

    // --------
    // test_deallocate
    // --------

    //test easy deallocate
    void test_deallocate_1 () {
        A x;
        int max = (100 - sizeof(value_type) - (4 * sizeof(int)));
        const difference_type s = (max / sizeof(value_type));
        pointer ptr_a = x.allocate(s);
        x.deallocate(ptr_a, s);
        pointer ptr_b = x.allocate(s);
        CPPUNIT_ASSERT(*ptr_a == *ptr_b);
    }

    //test med deallocate
    void test_deallocate_2 () {
        A x;
        x.allocate(1);
        pointer ptr_b = x.allocate(2);
        //coalesce right
        x.deallocate(ptr_b, 2);
        pointer ptr_c = x.allocate(2);
        CPPUNIT_ASSERT(*ptr_b == *ptr_c);
    }

    //test hard deallocate
    void test_deallocate_3 () {
        A x;
        pointer ptr_a = x.allocate(1);
        pointer ptr_b = x.allocate(1);
        pointer ptr_c = x.allocate(1);
        x.deallocate(ptr_a, 1);
        x.deallocate(ptr_c, 1);
        //this should coalesce left and right
        x.deallocate(ptr_b, 1);
        int max = (100 - sizeof(value_type) - (4 * sizeof(int)));
        const difference_type s = (max / sizeof(value_type));
        pointer ptr_d = x.allocate(s);
        CPPUNIT_ASSERT(*ptr_a == *ptr_d);
    }
    
    // --------
    // test
    // construct 
    // --------

    void test_construct_1 () {
        A x;
        int max = (100 - sizeof(value_type) - (4 * sizeof(int)));
        const difference_type s = (max / sizeof(value_type));
        const value_type      v = 10;
        const pointer         b = x.allocate(s);
              pointer         e = b + s;
              pointer         p = b;
        try {
            while(p != e) {
                x.construct(p, v);
                CPPUNIT_ASSERT(*p == v); // tests construct
                ++p;
            }
        }
        catch(...) {
            while(b != p)
                x.destroy(--p);
            
            x.deallocate(b, s);
            throw;
        }
        CPPUNIT_ASSERT(std::count(b, e, v) == s);
        while (b != e)
            x.destroy(--e);
            
        x.deallocate(b, s);}


    void test_construct_2 () {
        A x;
        const difference_type s = 3;
        const value_type      v = -7;
        const pointer         b = x.allocate(s);
              pointer         e = b + s;
              pointer         p = b;
        try {
            while(p != e) {
                x.construct(p, v);
                CPPUNIT_ASSERT(*p == v); // tests construct
                ++p;
            }
        }
        catch(...) {
            while(b != p)
                x.destroy(--p);
            
            x.deallocate(b, s);
            throw;
        }
        CPPUNIT_ASSERT(std::count(b, e, v) == s);
        while (b != e)
            x.destroy(--e);
            
        x.deallocate(b, s);}


    void test_construct_3 () {
        A x;
        const difference_type s = 3;
        const value_type      v = 122;
        const pointer         b = x.allocate(s);
              pointer         e = b + s;
              pointer         p = b;
        try {
            while(p != e) {
                x.construct(p, v);
                CPPUNIT_ASSERT(*p == v); // tests construct
                ++p;
            }
        }
        catch(...) {
            while(b != p)
                x.destroy(--p);

            x.deallocate(b, s);
            throw;
        }
        CPPUNIT_ASSERT(std::count(b, e, v) == s);
        while (b != e)
            x.destroy(--e);
            
        x.deallocate(b, s);}


    // --------
    // test
    // destroy
    // --------

    void test_destroy_1(){
        A x;
        const difference_type s = 10;
        const value_type      v = 122;
        const pointer         b = x.allocate(s);
              pointer         e = b + s;
              pointer         p = b;

        while(p != e) {
            x.construct(p, v);
            CPPUNIT_ASSERT(*p == v); // tests construct
            ++p;
        }
        CPPUNIT_ASSERT(std::count(b, e, v) == s);
        while (b != e)
            x.destroy(--e);

        ///now do it all over again, should fail if not properly destroyed

        p = b;
        e = b + s;
        while(p != e) {
            x.construct(p, v);
            CPPUNIT_ASSERT(*p == v); // tests construct
            ++p;
        }
        CPPUNIT_ASSERT(std::count(b, e, v) == s);
        while (b != e)
            x.destroy(--e);
            
        x.deallocate(b, s);
    }
    
    void test_destroy_2(){
        A x;
        const difference_type s = 3;
        const pointer         p = x.allocate(s);
        value_type      v = 122;

        x.construct(p, v);
        CPPUNIT_ASSERT(*p == v);
        x.destroy(p);
        try{
            //should throw an error since it is unitialized
            v = *p;
            CPPUNIT_ASSERT(false);
        } catch(...){
            //this error generates a ton of valgrind output
            CPPUNIT_ASSERT(true);
        }
    }
    
    void test_destroy_3(){
        A x;
        const difference_type s = 10;
        const pointer         b = x.allocate(s);
              pointer         e = b + s;
              pointer         p = b;
        value_type      v = 10;

        while(p != e) {
            x.construct(p, v);
            CPPUNIT_ASSERT(*p == v); // tests construct
            ++p;
        }
        CPPUNIT_ASSERT(std::count(b, e, v) == s);
        while (b != e) {
            x.destroy(--e);
            try {
                //should throw an error since it is unitialized
                v = *p;
                CPPUNIT_ASSERT(false);
            } catch(...) { }
        }

        CPPUNIT_ASSERT(true);
    }

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

    // -----
    // suite
    // -----

    CPPUNIT_TEST_SUITE(TestAllocator);
    CPPUNIT_TEST(test_allocate_1);
    CPPUNIT_TEST(test_allocate_2);
    CPPUNIT_TEST(test_allocate_3);
    CPPUNIT_TEST(test_deallocate_1);
    CPPUNIT_TEST(test_deallocate_2);
    CPPUNIT_TEST(test_deallocate_3);
    CPPUNIT_TEST(test_valid_1);
    CPPUNIT_TEST(test_valid_2);
    CPPUNIT_TEST(test_valid_3);
    CPPUNIT_TEST(test_construct_1);
    CPPUNIT_TEST(test_construct_2);
    CPPUNIT_TEST(test_construct_3);
    CPPUNIT_TEST(test_destroy_1);
    CPPUNIT_TEST(test_destroy_2);
    CPPUNIT_TEST(test_destroy_3);
    CPPUNIT_TEST(test_one);
    CPPUNIT_TEST(test_ten);
    CPPUNIT_TEST_SUITE_END();};

// ----
// main
// ----

int main () {
    using namespace std;
    ios_base::sync_with_stdio(false);    // turn off synchronization with C I/O
    cout << "TestAllocator.c++" << endl;

    CppUnit::TextTestRunner tr;

    /* 
     *     Unit tests cause a memory leak when used with std::alocator. 
     *     Disable the TestRunner for the std::allocator to isolate any
     *     memleaks related to this heap allocator. Valgrind detects no 
     *     memleaks when std::alocator is commented out.
     */

    //tr.addTest(TestAllocator< std::allocator<int> >::suite());
    tr.addTest(TestAllocator< Allocator<int, 100> >::suite()); // uncomment!

    //tr.addTest(TestAllocator< std::allocator<double> >::suite());
    tr.addTest(TestAllocator< Allocator<double, 100> >::suite()); // uncomment!

    tr.run();

    cout << "Done." << endl;
    return 0;}
