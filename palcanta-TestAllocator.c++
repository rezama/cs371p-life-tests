// ------------------------------------
// projects/allocator/TestAllocator.c++
// Copyright (C) 2011
// Glenn P. Downing
// ------------------------------------

/**
* To test the program:
* g++ -ansi -pedantic -lcppunit -ldl -Wall TestAllocator.c++ -o TestAllocator.app
* valgrind TestAllocator.app >& TestAllocator.out
*/

// --------
// includes
// --------
#define private public
#define protected public

#include <algorithm> // count
#include <memory> // allocator

#include "cppunit/extensions/HelperMacros.h" // CPPUNIT_TEST, CPPUNIT_TEST_SUITE, CPPUNIT_TEST_SUITE_END
#include "cppunit/TestFixture.h" // TestFixture
#include "cppunit/TextTestRunner.h" // TestRunner

#include "Allocator.h"

// -------------
// TestAllocator
// -------------
template <typename A>
struct TestUserAllocator : CppUnit::TestFixture {
    // --------
    // typedefs
    // --------

    typedef typename A::value_type value_type;
    typedef typename A::difference_type difference_type;
    typedef typename A::pointer pointer;

        void test_valid_1 () {
            A x;
            *((int *) &x.a[0])  = -40;
            *((int *) &x.a[44]) = -40;
            *((int *) &x.a[48]) = -24;
            *((int *) &x.a[76]) = -24;
            *((int *) &x.a[80]) =  12;
            *((int *) &x.a[96]) =  12;
            const bool result = x.valid();
            CPPUNIT_ASSERT(result == true);
            
        }

        void test_valid_2 () {
            A x;
            *((int *) &x.a[0]) = -4;
            *((int *) &x.a[8]) = -4;
            *((int *) &x.a[12]) = 80;
            *((int *) &x.a[96]) = 80;
            const bool result = x.valid();
            CPPUNIT_ASSERT(result == true);
        }

        void test_valid_3 () {
            A x;
            *((int *) &x.a[0]) = 0;
            *((int *) &x.a[76]) = 0;            
            *((int *) &x.a[80]) = -12;
            *((int *) &x.a[96]) =  -12;
            const bool result = x.valid();
            CPPUNIT_ASSERT(result == false);
        }


        void test_allocate_1(){
            A x;
            x.allocate((100 - 2*sizeof(int)) / sizeof(value_type));
            CPPUNIT_ASSERT(x.a[0] == -92);
            CPPUNIT_ASSERT(x.a[96] == -92);
        }
        
        void test_allocate_2(){
            A x;
            CPPUNIT_ASSERT(x.allocate(0) == NULL);
            
        }

                void test_deallocate_coalesce_left(){
            A x;
            const difference_type s = 5;
            const pointer b = x.allocate(s);
                  pointer e = b + s;
                  char* sentinel1a = ((char*) b)-4;
                  char* sentinel1b = ((char*) e);

            const pointer b1 = x.allocate(1); 
                  pointer e1 = b1 + 1;
                  char* sentinel2b = ((char*) e1);

            const pointer b2 = x.allocate(1); 
                  //pointer e2 = b2 + 1;
                  char* sentinel1c = ((char*) b2)-4;
                CPPUNIT_ASSERT(*(sentinel1c-4) == *sentinel2b);


                x.deallocate(b);
                CPPUNIT_ASSERT((int) *sentinel1a == 5*sizeof(value_type));
                CPPUNIT_ASSERT((int) *sentinel1b == 5*sizeof(value_type));
                x.deallocate(b1);
                CPPUNIT_ASSERT((int) *sentinel1a == 8+6*sizeof(value_type));
                CPPUNIT_ASSERT((int) *sentinel2b == 8+6*sizeof(value_type));
        }

        void test_deallocate_coalesce_right(){
            A x;
            const difference_type s = 5;
            const pointer b = x.allocate(s);
                  char* sentinel1a = ((char*) b)-4;

            const pointer b1 = x.allocate(1); 
                  pointer e1 = b1 + 1;
                  char* sentinel2a = ((char*) b1)-4;
                  char* sentinel2b = ((char*) e1);

            const pointer b2 = x.allocate(1); 
                  //pointer e2 = b2 + 1;
                  char* sentinel1c = ((char*) b2)-4;
                CPPUNIT_ASSERT(*(sentinel1c-4) == *sentinel2b);


                x.deallocate(b1);
                CPPUNIT_ASSERT((int) *sentinel2a == sizeof(value_type));
                CPPUNIT_ASSERT((int) *sentinel2b == sizeof(value_type));
                x.deallocate(b);
                CPPUNIT_ASSERT((int) *sentinel1a == 8+6*sizeof(value_type));
                CPPUNIT_ASSERT((int) *sentinel2b == 8+6*sizeof(value_type));
        }

        void test_deallocate_coalesce_both() {
        A x;
        const difference_type s = 5;
        const pointer b = x.allocate(s);
              pointer e = b + s;
              char* sentinel1a = ((char*) b)-4;
              char* sentinel2a = ((char*) e);

        const pointer b1 = x.allocate(1); 
              pointer e1 = b1 + 1;
              char* sentinel1b = ((char*) b1)-4;
              char* sentinel2b = ((char*) e1);
              CPPUNIT_ASSERT(*sentinel1b == *sentinel2b);

              const pointer b2 = x.allocate(1); 
              pointer e2 = b2 + 1;
              char* sentinel1c = ((char*) b2)-4;
              char* sentinel2c = ((char*) e2);

              const pointer b3 = x.allocate(1); 
              //pointer e3 = b3 + 1;
              char* sentinel1d = ((char*) b3)-4;
              char* sentinel2d = sentinel1d + 4 + -((int) (*sentinel1d));
              CPPUNIT_ASSERT((int) *sentinel1d == (int) *sentinel2d);

              x.deallocate(b, 5); //Deallocate the left of b1
              CPPUNIT_ASSERT((( (int) *(sentinel1a)) == (s*sizeof(value_type))));
              CPPUNIT_ASSERT((( (int) *(sentinel2a)) == (s*sizeof(value_type))));
            
              x.deallocate(b2, 1); //Deallocate the right of b1
              CPPUNIT_ASSERT((( (int) *(sentinel1c)) == (1*sizeof(value_type))));
              CPPUNIT_ASSERT((( (int) *(sentinel2c)) == (1*sizeof(value_type))));


              x.deallocate(b1, 1); //Deallocate b1, force coalesce 

              CPPUNIT_ASSERT((( (int) *(sentinel1a)) == (7*sizeof(value_type)) + 16)); //7 objects, 4 sentries
              CPPUNIT_ASSERT((( (int) *(sentinel2c)) == (7*sizeof(value_type)) + 16));
    }

    CPPUNIT_TEST_SUITE(TestUserAllocator);
    CPPUNIT_TEST(test_allocate_1);
    CPPUNIT_TEST(test_allocate_2);
    CPPUNIT_TEST(test_valid_1);
    CPPUNIT_TEST(test_valid_2);
    CPPUNIT_TEST(test_valid_3);
    CPPUNIT_TEST(test_deallocate_coalesce_left);
    CPPUNIT_TEST(test_deallocate_coalesce_right);
    CPPUNIT_TEST(test_deallocate_coalesce_both);
    CPPUNIT_TEST_SUITE_END();

};

template <typename A>
struct TestAllocator : CppUnit::TestFixture {
    // --------
    // typedefs
    // --------

    typedef typename A::value_type value_type;
    typedef typename A::difference_type difference_type;
    typedef typename A::pointer pointer;

    // --------
    // test_one
    // --------

    void test_one () {
        A x;
        const difference_type s = 1;
        const value_type v = 2;
        const pointer p = x.allocate(s);
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
        const value_type v = 2;
        const pointer b = x.allocate(s);
              pointer e = b + s;
              pointer p = b;
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


        void test_allocate_3(){
            A x;
            bool result = false;
            try{
                x.allocate(-1);
            }
            catch(std::bad_alloc& e){
                result = true;
            }
            CPPUNIT_ASSERT(result);
        }



        void test_construct_1(){
            A x;
            const pointer b = x.allocate(1);
            const value_type v = 1337;
            pointer p = b;
            x.construct(p, v);
            CPPUNIT_ASSERT(*p == v);
            x.destroy(p);
            x.deallocate(p,1);
        }

        void test_construct_2(){
            A x;
            const pointer b = x.allocate(10);
            value_type v = 20;
            pointer p = b;
            pointer e = b+10;
            try{
                while(p != e){
                    x.construct(p++, v--);
                }
            }
            catch(...){
                while(b != p){
                    --p;
                }
                x.deallocate(b, 10);
                throw;
            }
            while(b!=e){
                CPPUNIT_ASSERT((*(--e) == (++v)));
                x.destroy(e);
            }
            x.deallocate(b, 10);
        }

        void test_construct_3(){
            A x;
            const difference_type s = 11;
            const value_type v = 42;
            const pointer b = x.allocate(s);
                  pointer e = b + s;
                  pointer p = b;
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
    
    void test_destroy_1(){
        A x;
        const pointer b = x.allocate(1);
        const value_type v = 42;
        x.construct(b, v);
        x.destroy(b);
        try{
            value_type v1 = *b;
            ++v1;
            CPPUNIT_ASSERT(false);

        }catch(...){
            CPPUNIT_ASSERT(true);
        }
    }

    void test_destroy_2(){
        A x;
        const pointer b = x.allocate(5);
        const value_type v = 42;
        x.construct(b, v);
        x.construct(b+1, v);
        x.construct(b+2, v);
        x.construct(b+3, v);
        x.construct(b+4, v);
        x.destroy(b+4);
        try{
            value_type v1 = *(b+4);
            ++v1;
            CPPUNIT_ASSERT(false);

        }catch(...){
            CPPUNIT_ASSERT(true);
        }
    }

    void test_destroy_3(){
        A x;
        const pointer b = x.allocate(5);
        const value_type v = 1337;
        x.construct(b, v);
        x.construct(b+1, v);
        x.construct(b+2, v);
        x.construct(b+3, v);
        x.construct(b+4, v);
        x.destroy(b+1);
        x.destroy(b+4);
        x.destroy(b+3);
        try{
            value_type v1 = *(b+3);
            ++v1;
            CPPUNIT_ASSERT(false);

        }catch(...){
            CPPUNIT_ASSERT(true);
        }
    }

    // -----
    // suite
    // -----

    CPPUNIT_TEST_SUITE(TestAllocator);
    CPPUNIT_TEST(test_one);
    CPPUNIT_TEST(test_ten);
    

    CPPUNIT_TEST(test_allocate_3);

    CPPUNIT_TEST(test_construct_1);
    CPPUNIT_TEST(test_construct_2);
    CPPUNIT_TEST(test_construct_3);

    CPPUNIT_TEST(test_destroy_1);
    CPPUNIT_TEST(test_destroy_2);
    CPPUNIT_TEST(test_destroy_3);
    CPPUNIT_TEST_SUITE_END();};

// ----
// main
// ----

int main () {
    using namespace std;
    ios_base::sync_with_stdio(false); // turn off synchronization with C I/O
    cout << "TestAllocator.c++" << endl;

    CppUnit::TextTestRunner tr;

    tr.addTest(TestAllocator< std::allocator<int> >::suite());
 tr.addTest(TestAllocator< Allocator<int, 100> >::suite()); // uncomment!

    tr.addTest(TestAllocator< std::allocator<double> >::suite());
 tr.addTest(TestAllocator< Allocator<double, 100> >::suite()); // uncomment!

    tr.run();

    CppUnit::TextTestRunner tr1;
    tr1.addTest(TestAllocator< Allocator<int, 100> >::suite());
    tr1.addTest(TestAllocator< Allocator<double, 100> >::suite());

    tr1.run();

    cout << "Done." << endl;
    return 0;}