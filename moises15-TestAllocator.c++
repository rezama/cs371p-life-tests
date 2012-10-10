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
    // test_one
    // --------

    void test_one () {
        A x;
        //printf("test one\n");
        //printf("allocator address %p\n", static_cast<void*>(&x));
        const difference_type s = 1;
        const value_type      v = 2;
        const pointer         p = x.allocate(s);
        x.construct(p, v);
        CPPUNIT_ASSERT(*p == v);
        x.destroy(p);
        x.deallocate(p, s);
        }
        
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
    // test_ten
    // --------

    void test_ten () {
        A x;
        //printf("test ten\n");
        //printf("allocator address %p\n", static_cast<void*>(&x));
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


    void test_allocate_1 () 
    {
        A x;
        const difference_type s = 0;
        try {
            x.allocate(s);
        }
        catch (std::bad_alloc& e) {
            CPPUNIT_ASSERT(true);
        }
    }
    
     void test_allocate_2(){
            A x;
            const pointer b = x.allocate(1);
            CPPUNIT_ASSERT(b != 0);
            if(typeid(value_type) == typeid(int)){
                    CPPUNIT_ASSERT(x.a[0] == -4);
                    CPPUNIT_ASSERT(x.a[8] == -4);
                    CPPUNIT_ASSERT(x.a[12] == 80);
                    CPPUNIT_ASSERT(x.a[96] == 80);
                } else if(typeid(value_type) == typeid(double)) {
                    CPPUNIT_ASSERT(x.a[0] == -8);
                    CPPUNIT_ASSERT(x.a[12] == -8);
                    CPPUNIT_ASSERT(x.a[16] == 76);
                    CPPUNIT_ASSERT(x.a[96] == 76);
                } else CPPUNIT_ASSERT(false);
        }
     void test_allocate_3()
     {
             A x;
            try{
                if(typeid(value_type) == typeid(int)){
                    const pointer b = x.allocate(22);
                    CPPUNIT_ASSERT(b != 0);
                    CPPUNIT_ASSERT(x.a[0] == -92);
                    CPPUNIT_ASSERT(x.a[96] == -92);
                } else if(typeid(value_type) == typeid(double)) {
                    x.allocate(22);
                    CPPUNIT_ASSERT(false);
                } else CPPUNIT_ASSERT(false);
            } catch (std::bad_alloc& ba){
                //do nothing
            }
        }
        
    void test_valid_1 () 
    {
        Allocator<int, 100> x;
        int* b = (int*) &x.a[0];
        *b = 92;
        b += 96;
        *b = 92;
        const bool result = x.valid();
        CPPUNIT_ASSERT(result == true);
    }
    
    void test_valid_2() 
    {
        A x;
        CPPUNIT_ASSERT(x.valid());
        x.allocate(5);
        CPPUNIT_ASSERT(x.valid());
    }
    
    void test_valid_3 () 
    {
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
    
    void test_deallocate_1() {
        A x;
        const difference_type s = 3;
        const pointer p = x.allocate(s);
        x.deallocate(p, s);
        const pointer q = x.allocate(s);
        CPPUNIT_ASSERT(p == q);
        x.deallocate(q, s);
    }
    
    void test_deallocate_2()
    {
            A x;
            const pointer b1 = x.allocate(1);
            x.allocate(2);
            x.deallocate(b1);
            if(typeid(value_type) == typeid(int)){
                    CPPUNIT_ASSERT(x.a[0] == 4);
                    CPPUNIT_ASSERT(x.a[8] == 4);
                    CPPUNIT_ASSERT(x.a[12] == -8);
                    CPPUNIT_ASSERT(x.a[24] == -8);
                } else if(typeid(value_type) == typeid(double)) {
                    CPPUNIT_ASSERT(x.a[0] == 8);
                    CPPUNIT_ASSERT(x.a[12] == 8);
                    CPPUNIT_ASSERT(x.a[16] == -16);
                    CPPUNIT_ASSERT(x.a[36] == -16);
                } else CPPUNIT_ASSERT(false);
        }
        
        void test_deallocate_3()
        {
            A x;
            const pointer b = x.allocate(10);
            x.deallocate(b);
            CPPUNIT_ASSERT(x.a[0] == 92);
            CPPUNIT_ASSERT(x.a[96] == 92);
        }
        
        void test_set_read_footer_header_1()
        {
            A x;
            x.set_header_footer(&x.a[0],66);
            assert(x.read_header(&x.a[0])==66);
            assert(x.read_footer(&x.a[0])==66);
        }
        
        void test_set_read_footer_header_2()
        {
            A x;
            x.set_header_footer(&x.a[34],11);
            assert(x.read_header(&x.a[34])==11);
            assert(x.read_footer(&x.a[34])==11);
        }
        
        void test_set_read_footer_header_3()
        {
            A x;
            x.set_header_footer(&x.a[50],0);
            assert(x.read_header(&x.a[50])==0);
            assert(x.read_footer(&x.a[50])==0);
        }
        
    // -----
    // suite
    // -----

    CPPUNIT_TEST_SUITE(TestAllocator);
    CPPUNIT_TEST(test_one);
    CPPUNIT_TEST(test_two);
    CPPUNIT_TEST(test_three);
    CPPUNIT_TEST(test_ten);
    CPPUNIT_TEST(test_allocate_1);
    CPPUNIT_TEST(test_allocate_2);
    CPPUNIT_TEST(test_allocate_3);
    CPPUNIT_TEST(test_valid_1);
    CPPUNIT_TEST(test_valid_2);
    CPPUNIT_TEST(test_valid_3);
    CPPUNIT_TEST(test_deallocate_1);
    CPPUNIT_TEST(test_deallocate_2);
    CPPUNIT_TEST(test_deallocate_3);
    CPPUNIT_TEST(test_set_read_footer_header_1); //tests set_header_footer, read_footer, and read_header
    CPPUNIT_TEST(test_set_read_footer_header_2); //tests set_header_footer, read_footer, and read_header
    CPPUNIT_TEST(test_set_read_footer_header_3); //tests set_header_footer, read_footer, and read_header
    CPPUNIT_TEST_SUITE_END();};

// ----
// main
// ----

int main () {
    using namespace std;
    ios_base::sync_with_stdio(false);    // turn off synchronization with C I/O
    cout << "TestAllocator.c++" << endl;

    CppUnit::TextTestRunner tr;

//   tr.addTest(TestAllocator< std::allocator<int> >::suite());
    tr.addTest(TestAllocator< Allocator<int, 100> >::suite()); // uncomment!

//    tr.addTest(TestAllocator< std::allocator<double> >::suite());
    tr.addTest(TestAllocator< Allocator<double, 100> >::suite()); // uncomment!

    tr.run();

    cout << "Done." << endl;
    return 0;
}
