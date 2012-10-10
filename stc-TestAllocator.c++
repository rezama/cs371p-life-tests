// ------------------------------------
// projects/allocator/TestAllocator.c++
// Copyright (C) 2011
// Glenn P. Downing
// ------------------------------------

// Stephen Cook
// stc493

/**
*@file Testing program for custom allocator and std allocator.
*/

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


#define private public //allows for testing of private methods
#define protected public
#define class struct
#include "Allocator.h"

// -------------
// TestAllocator
// -------------

template <typename A>
struct TestMyAllocator : CppUnit::TestFixture {
    // --------
    // typedefs
    // --------

    typedef typename A::value_type      value_type;
    typedef typename A::difference_type difference_type;
    typedef typename A::pointer         pointer;

    void test_one () {
using namespace std;
	cout << "TEST_ONE" << endl;
        A x;
		try{
        const difference_type s = 5;
        //const value_type      v = 2;
        while(true)
		{
			x.allocate(s);
		}
        //x.construct(p, v);
        //CPPUNIT_ASSERT(*p == v);
        //x.destroy(p);
        //x.deallocate(p, s);

		}
		catch(std::bad_alloc& e)
		{
			CPPUNIT_ASSERT(true);
			return;
		}
		CPPUNIT_ASSERT(false);
	}

	void test_small(){
		A x;
	}

	void test_easy_valid() {
		std::cout << "TEST_EASY_VALID" << std::endl;
		A x;
		CPPUNIT_ASSERT(x.valid());
	}

	void test_easy_invalid() {
		std::cout << "TEST_EASY_INVALID" << std::endl;
		try{
		A x;
		x.allocate(4);
		x.a[0]=0;
		//bool b = x.valid();
		//CPPUNIT_ASSERT(!b);
		}
		catch(...)
		{}
	}


	void test_zero_invalid() {
using namespace std;
	cout << "TEST_ZERO_INVALID" << endl;
        A x;
        const difference_type s = 0;
        //const value_type      v = 99999;
        const pointer p = x.allocate(s);
        //cout << "WAWDAW " << p << ", " << x.a << endl;
		*((int*)p) = 2;
		
	//	x.write_sentinel(x.a, 99);
	//	CPPUNIT_ASSERT(99 == *(reinterpret_cast<int*>(x.a)));
		CPPUNIT_ASSERT(!x.valid());
		//x.construct(p, v);
	}

	
    void test_error1 () {
using namespace std;
	cout << "TEST_ERROR1" << endl;
        A x;
        const difference_type s = x.SIZE * 2;
		try{

        	x.allocate(s);
		}
		catch(std::bad_alloc& e)
		{
			CPPUNIT_ASSERT(true);
			return;
		}

		CPPUNIT_ASSERT(false);
	}



    void test_one_valid () {
using namespace std;
	cout << "TEST_ONE_VALID" << endl;
        A x;
        const difference_type s = 1;
        const value_type      v = 2;
        const pointer         p = x.allocate(s);
   
		CPPUNIT_ASSERT(x.valid());
	    x.construct(p, v);
		CPPUNIT_ASSERT(x.valid());
        CPPUNIT_ASSERT(*p == v);
        x.destroy(p);
		CPPUNIT_ASSERT(x.valid());
        x.deallocate(p, s);
		CPPUNIT_ASSERT(x.valid());
	}

	void test_write1 () {
		A x;
		x.write_sentinel(x.a, 1);
		CPPUNIT_ASSERT(1 == *(reinterpret_cast<int*>(x.a)));
	}

	void test_write2 () {
		A x;
		x.write_sentinel(x.a, 0);
		CPPUNIT_ASSERT(0 == *(reinterpret_cast<int*>(x.a)));
	}
	void test_write3 () {
		A x;
		x.write_sentinel(x.a, 1000);
		CPPUNIT_ASSERT(1000 == *(reinterpret_cast<int*>(x.a)));
	}


    CPPUNIT_TEST_SUITE(TestMyAllocator);
 
	//CPPUNIT_TEST(test_one);
	CPPUNIT_TEST(test_small);
	CPPUNIT_TEST(test_easy_valid);
	CPPUNIT_TEST(test_zero_invalid);
    CPPUNIT_TEST(test_easy_invalid);
    CPPUNIT_TEST(test_one_valid);
    CPPUNIT_TEST(test_write1);
    CPPUNIT_TEST(test_write2);
    CPPUNIT_TEST(test_write3);
    CPPUNIT_TEST(test_error1);
    CPPUNIT_TEST_SUITE_END();

};


template <typename A>
struct TestAllocator : CppUnit::TestFixture {
    // --------
    // typedefs
    // --------

    typedef typename A::value_type      value_type;
    typedef typename A::difference_type difference_type;
    typedef typename A::pointer         pointer;


	void test_small(){
		A x;
	}
    
	// --------
    // test_one
    // --------

    void test_multiple () {
		using namespace std;
		//cout << "TEST_MULTIPLE: " << endl;

        A x;

        const difference_type s = 1;
        const value_type      v = 2;
        const pointer p = x.allocate(s);
        x.construct(p, v);
        CPPUNIT_ASSERT(*p == v);
        const pointer p2 = x.allocate(s);
        x.construct(p2, v);
        CPPUNIT_ASSERT(*p2 == v);
        const pointer p3 = x.allocate(s);
        x.construct(p3, v);
        CPPUNIT_ASSERT(*p3 == v);
        x.destroy(p3);
	    x.deallocate(p3, s);
        x.destroy(p2);
        x.deallocate(p2, s);
        x.destroy(p);
        x.deallocate(p, s);

		//cout << "TEST_MULTIPLE FINISHED." << endl;
	}

    void test_double_coalesce () {
        A x;
        const difference_type s = 1;
        const value_type      v = 2;
        const pointer p = x.allocate(s);
        x.construct(p, v);
        CPPUNIT_ASSERT(*p == v);
        const pointer p2 = x.allocate(s);
        x.construct(p2, v);
        CPPUNIT_ASSERT(*p2 == v);
        const pointer p3 = x.allocate(s);
        x.construct(p3, v);
        CPPUNIT_ASSERT(*p3 == v);
        const pointer p4 = x.allocate(s);
        x.construct(p4, v);
        CPPUNIT_ASSERT(*p4 == v);

		x.destroy(p);
        x.deallocate(p, s);
        x.destroy(p3);
        x.deallocate(p3, s);
        x.destroy(p2);
        x.deallocate(p2, s);
        x.destroy(p4);
        x.deallocate(p4, s);
	}

    void test_backward_coalesce () {
        A x;
        const difference_type s = 1;
        const value_type      v = 2;
        const pointer         p = x.allocate(s);
        const pointer         p2 = x.allocate(s);
        x.construct(p, v);
        CPPUNIT_ASSERT(*p == v);
        x.construct(p2, v);
        CPPUNIT_ASSERT(*p2 == v);
        x.destroy(p);
        x.deallocate(p, s);
        x.destroy(p2);
        x.deallocate(p2, s);
	}

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
    // ----

    CPPUNIT_TEST_SUITE(TestAllocator);
 
    CPPUNIT_TEST(test_ten);
    CPPUNIT_TEST(test_multiple);
    CPPUNIT_TEST(test_double_coalesce);
    CPPUNIT_TEST(test_backward_coalesce);
    CPPUNIT_TEST_SUITE_END();
};

// ----
// main
// ----

int main () {
    using namespace std;
    ios_base::sync_with_stdio(false);    // turn off synchronization with C I/O
    cout << "TestAllocator.c++" << endl;
	cout << "Both Allocator tests: " << endl;
    CppUnit::TextTestRunner tr;

    tr.addTest(TestAllocator< std::allocator<int> >::suite());
    
	tr.addTest(TestAllocator< Allocator<int, 50> >::suite());
	tr.addTest(TestAllocator< Allocator<int, 100> >::suite());
	tr.addTest(TestAllocator< Allocator<int, 500> >::suite()); // uncomment!

    tr.addTest(TestAllocator< std::allocator<double> >::suite());
    tr.addTest(TestAllocator< Allocator<double, 100> >::suite()); 

    tr.run();

	cout << endl << "My allocator tests: " << endl;

	CppUnit::TextTestRunner tr2;
	//tr2.addTest(TestMyAllocator<Allocator<int, 100> >::suite()); 
	//tr2.addTest(TestMyAllocator<Allocator<double, 100> >::suite());
	tr2.addTest(TestMyAllocator<Allocator<int, 900> >::suite());
	tr2.run();

    cout << "Done." << endl;
    return 0;}

