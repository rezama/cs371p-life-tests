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
        x.deallocate(p, s);
        }
        
        
    // --------
    // test_two
    // --------

    void test_two () {
        
            A x;
            const difference_type s = 1;
            const value_type      v = 2;
            const pointer         p = x.allocate(s);
            x.construct(p, v);
            CPPUNIT_ASSERT(*p == v);
	
	        const pointer 	      p1 = x.allocate(s);
	        x.construct(p1, v);
	        CPPUNIT_ASSERT(*p1 == v);
        try {
	        const pointer         p2 = x.allocate(15);
	        x.destroy(p2);
	        x.deallocate(p2, 15);
        }
        catch(std::bad_alloc& e){
            CPPUNIT_ASSERT(true);
        }
        x.destroy(p);
        x.destroy(p1);
        x.deallocate(p, s);
        x.deallocate(p1, s);
    }
    
    // --------
    // test_three
    // --------

    void test_three () {
        
        A x;
        const difference_type s = 1;
        const value_type      v = 2;
        const pointer         p = x.allocate(s);
        x.construct(p, v);
        CPPUNIT_ASSERT(*p == v);
	
	    const pointer 	      p1 = x.allocate(s);
	    x.construct(p1, v);
	    CPPUNIT_ASSERT(*p1 == v);
        
	    const pointer         p2 = x.allocate(s);
	    x.construct(p2, v);
	    CPPUNIT_ASSERT(*p2 == v);
	    
	    x.destroy(p2);
	    x.deallocate(p2, s);
        x.destroy(p);
        x.deallocate(p, s);
        x.destroy(p1);
        x.deallocate(p1, s);
    }
    
    // --------
    // test_four
    // --------

    void test_four () {
        
        A x;
        const difference_type s = 1;
        const value_type      v = 2;
        const pointer         p = x.allocate(s);        
        x.construct(p, v);
        CPPUNIT_ASSERT(*p == v);
        x.destroy(p);
        x.deallocate(p, s);
	
	    const pointer 	      p1 = x.allocate(6);
	    x.construct(p1, v);
	    CPPUNIT_ASSERT(*p1 == v);
	    x.destroy(p1);
        x.deallocate(p1, 6);
        
	    const pointer         p2 = x.allocate(8);
	    x.construct(p2, v);
	    CPPUNIT_ASSERT(*p2 == v);
	    x.destroy(p2);
	    x.deallocate(p2, 8);
    }
    
    // --------
    // test_five
    // --------

    void test_five () {
        
        A x;
        const difference_type s = 1;
        const value_type      v = 2;
        const pointer         p = x.allocate(s);        
        x.construct(p, v);
        x.deallocate(p, s);
        
	
	    const pointer 	      p1 = x.allocate(6);
        x.deallocate(p1, 6);
        
	    try {
	        const pointer         p2 = x.allocate(23);
	        x.deallocate(p2, 23);
	        const pointer         p3 = x.allocate(1);
	        x.deallocate(p3, 1);
        }
        catch(std::bad_alloc& e){
            CPPUNIT_ASSERT(typeid(value_type) == typeid(double));
        }
    }
    
    // --------
    // test_six
    // --------

    void test_six () {
        
        A x;
        const difference_type s = 1;
        const value_type      v = 2;
        const pointer         p = x.allocate(s);        
        x.construct(p, v);
        x.deallocate(p, s);
        
	    const pointer 	      p1 = x.allocate(6);
        x.deallocate(p1, 6);
        
	    try {
	        const pointer         p2 = x.allocate(21);
	        x.deallocate(p2, 21);
	        const pointer         p3 = x.allocate(1);
	        x.deallocate(p3, 1);
        }
        catch(std::bad_alloc& e){
            CPPUNIT_ASSERT(typeid(value_type) == typeid(double));
        }
    }
    
    // --------
    // test_seven
    // --------

    void test_seven () {
        
        A x;
        const difference_type s = 1;
        const value_type      v = 2;
        const pointer         p = x.allocate(s);        
        x.construct(p, v);
        x.deallocate(p, s);
        
	    const pointer 	      p1 = x.allocate(6);
	    for(int i = 0; i < 6; ++i){
	        x.construct(p1 + i, i + v);
	        CPPUNIT_ASSERT(*(p1 + i) == i + v);
	        x.destroy(p1 + i);
	    }
	    
        x.deallocate(p1, 6);
        
    }
    
    // --------
    // test_eight
    // --------

    void test_eight () {
        
        A x;
        const difference_type s = 1;
        const value_type      v = 2;
        const pointer         p = x.allocate(s);        
        x.construct(p, v);
        x.deallocate(p, s);
        
	    const pointer 	      p1 = x.allocate(6);
        x.deallocate(p1, 6);
	    try {

	        const pointer         p2 = x.allocate(22);
	        x.deallocate(p2, 22);
	        const pointer         p3 = x.allocate(1);
	        x.deallocate(p3, 1);
        }
        catch(std::bad_alloc& e){
            CPPUNIT_ASSERT(true);
        }
    }
    
    // --------
    // test_nine
    // --------

    void test_nine () {
        
        A x;
        const difference_type s = 1;
        const value_type      v = 2;
        
        const pointer         p1 = x.allocate(s);        
        x.construct(p1, v);
        
        const pointer         p2 = x.allocate(s);        
        x.construct(p2, v);
        
        const pointer         p3 = x.allocate(s);        
        x.construct(p3, v);
        
        const pointer         p4 = x.allocate(s);        
        x.construct(p4, v);
        
        const pointer         p5 = x.allocate(s);        
        x.construct(p5, v);
        try{
            const pointer         p6 = x.allocate(s);        
            x.construct(p6, v);
            x.destroy(p6);
        
            const pointer         p7 = x.allocate(s);        
            x.construct(p7, v);
            x.destroy(p7);
            x.deallocate(p7, s);
            x.deallocate(p6, s);
        }
        catch(std::bad_alloc& e){
            CPPUNIT_ASSERT(typeid(value_type) == typeid(double));
        }
        x.destroy(p2);
        x.destroy(p5);
        x.destroy(p3);
        x.destroy(p4);
        x.destroy(p1);
       
        x.deallocate(p4, s);
        x.deallocate(p1, s);
        x.deallocate(p2, s);
        x.deallocate(p5, s);
        x.deallocate(p3, s);  
    }

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
        x.deallocate(b, s);
		}

    // --------
    // test_eleven
    // --------

    void test_eleven () {
        
        A x;
        const difference_type s = 1;
        const value_type      v = 2;
        
        const pointer         p1 = x.allocate(s);        
        x.construct(p1, v);
        
        const pointer         p2 = x.allocate(s);        
        x.construct(p2, v + 1);
        
        const pointer         p3 = x.allocate(s);        
        x.construct(p3, v + 2);
        
        const pointer         p4 = x.allocate(s);        
        x.construct(p4, v + 3);
        
        const pointer         p5 = x.allocate(s);        
        x.construct(p5, v + 4);
        try{
            const pointer         p6 = x.allocate(s);        
            x.construct(p6, v + 5);
            x.destroy(p6);
        
            const pointer         p7 = x.allocate(s);        
            x.construct(p7, v + 6);
            x.destroy(p7);
            x.deallocate(p7, s);
            x.deallocate(p6, s);
        }
        catch(std::bad_alloc& e){
            CPPUNIT_ASSERT(typeid(value_type) == typeid(double));
        }
        x.destroy(p4);
        x.deallocate(p4, s);
        CPPUNIT_ASSERT(*p3 == v + 2);
        CPPUNIT_ASSERT(*p5 == v + 4);
        
        x.destroy(p3);
        x.deallocate(p3, s);
        CPPUNIT_ASSERT(*p2 == v + 1);
        CPPUNIT_ASSERT(*p5 == v + 4);
        
        x.destroy(p5);
        x.destroy(p2);
        x.destroy(p1);
       
        x.deallocate(p1, s);
        x.deallocate(p5, s);
        x.deallocate(p2, s);  
    }
    
    // --------
    // test_eleven
    // --------

    void test_twelve () {
        A x;
        
        const pointer         p1 = x.allocate(7);        
        x.deallocate(p1, 7); 
    }
    

    // -----
    // suite
    // -----

    CPPUNIT_TEST_SUITE(TestAllocator);
    CPPUNIT_TEST(test_one);
    CPPUNIT_TEST(test_two);
    CPPUNIT_TEST(test_three);
    CPPUNIT_TEST(test_four);
    CPPUNIT_TEST(test_five);
    CPPUNIT_TEST(test_six);
    CPPUNIT_TEST(test_seven);
    CPPUNIT_TEST(test_eight);
    CPPUNIT_TEST(test_nine);
    CPPUNIT_TEST(test_ten);
    CPPUNIT_TEST(test_eleven);
    CPPUNIT_TEST(test_twelve);
    CPPUNIT_TEST_SUITE_END();};

// ----
// main
// ----

int main () {
    using namespace std;
    ios_base::sync_with_stdio(false);    // turn off synchronization with C I/O
    cout << "TestAllocator.c++" << endl;

    CppUnit::TextTestRunner tr;

    tr.addTest(TestAllocator< std::allocator<int> >::suite());
    tr.addTest(TestAllocator< Allocator<int, 100> >::suite()); // uncomment!

    tr.addTest(TestAllocator< std::allocator<double> >::suite());
    tr.addTest(TestAllocator< Allocator<double, 100> >::suite()); // uncomment!

    tr.run();

    cout << "Done." << endl;
    return 0;}
