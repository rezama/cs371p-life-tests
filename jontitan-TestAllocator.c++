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
        
        void test_constructor_1(){
            A x;
            // not going to fail valid
        }
        
        void test_constructor_2(){
            A x;
            CPPUNIT_ASSERT(x.a[0] == 92);
        }
        
        void test_constructor_3(){
            A x;
            CPPUNIT_ASSERT(x.a[96] == 92);
        }
        
        void test_allocate_1(){
            A x;
            try{
                x.allocate(30);
                CPPUNIT_ASSERT(false);
            } catch (std::bad_alloc& ba){
                //do nothing
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
                } else if(typeid(value_type) == typeid(double)) {
                    CPPUNIT_ASSERT(x.a[0] == -8);
                    CPPUNIT_ASSERT(x.a[12] == -8);
                    CPPUNIT_ASSERT(x.a[16] == 76);
                } else CPPUNIT_ASSERT(false);
        }
        
        void test_allocate_3(){
            A x;
            try{
                if(typeid(value_type) == typeid(int)){
                    const pointer b = x.allocate(23);
                    CPPUNIT_ASSERT(b != 0);
                    CPPUNIT_ASSERT(x.a[0] == -92);
                    CPPUNIT_ASSERT(x.a[96] == -92);
                } else if(typeid(value_type) == typeid(double)) {
                    x.allocate(23);
                    CPPUNIT_ASSERT(false);
                } else CPPUNIT_ASSERT(false);
            } catch (std::bad_alloc& ba){
                //do nothing
            }
        }
        
        void test_allocate_4(){
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
        
        void test_construct_1(){
            A x;
            const pointer b = x.allocate(1);
            x.construct(b, 21);
            CPPUNIT_ASSERT(*b == 21);
        }
        
        void test_construct_2(){
            A x;
            const pointer b = x.allocate(8);
            pointer p = b;
            const pointer e = b + 8;
            while(p != e){
                x.construct(p, 21);
                ++p;
            }
            CPPUNIT_ASSERT(std::count(b, e, 21) == 8);
        }
        
        void test_construct_3(){
            A x;
            const pointer b1 = x.allocate(3);
            const pointer b2 = x.allocate(3);
            pointer p1 = b1;
            pointer p2 = b2;
            const pointer e1 = b1 + 3;
            const pointer e2 = b2 + 3;
            while(p1 != e1){
                x.construct(p1, 21);
                x.construct(p2, 12);
                ++p1;
                ++p2;
            }
            CPPUNIT_ASSERT(std::count(b1, e1, 21) == 3);
            CPPUNIT_ASSERT(std::count(b2, e2, 12) == 3);
        }
        
         void test_destroy_1(){
            A x;
            const pointer b = x.allocate(1);
            x.construct(b, 21);
            CPPUNIT_ASSERT(*b == 21);
            x.destroy(b);
            try{
                value_type v = *b;
                ++v;
                CPPUNIT_ASSERT(false);
            } catch(...){
                CPPUNIT_ASSERT(true);
            }
        }
        
        void test_destroy_2(){
            A x;
            const pointer b = x.allocate(8);
            pointer p = b;
            const pointer e = b + 8;
            while(p != e){
                x.construct(p, 21);
                ++p;
            }
            p = b;
            while(p != e){
                x.destroy(p);
                ++p;
            }
            try{
                value_type v = *(b+3);
                ++v;
                CPPUNIT_ASSERT(false);
            } catch(...){
                CPPUNIT_ASSERT(true);
            }
        }
        
        void test_destroy_3(){
            A x;
            const pointer b = x.allocate(1);
            x.construct(b, 200);
            CPPUNIT_ASSERT(*b == 200);
            x.destroy(b);
            try{
                value_type v = *b;
                ++v;
                CPPUNIT_ASSERT(false);
            } catch(...){
                CPPUNIT_ASSERT(true);
            }
        }
        
        void test_deallocate_1(){
            A x;
            const pointer b = x.allocate(1);
            x.deallocate(b);
            CPPUNIT_ASSERT(x.a[0] == 92);
            CPPUNIT_ASSERT(x.a[96] == 92);
        }
        
        void test_deallocate_2(){
            A x;
            const pointer b1 = x.allocate(1);
            x.allocate(2);
            x.deallocate(b1);
            if(typeid(value_type) == typeid(int)){
                    CPPUNIT_ASSERT(x.a[0] == 4);
                    CPPUNIT_ASSERT(x.a[8] == 4);
                    CPPUNIT_ASSERT(x.a[12] == -8);
                } else if(typeid(value_type) == typeid(double)) {
                    CPPUNIT_ASSERT(x.a[0] == 8);
                    CPPUNIT_ASSERT(x.a[12] == 8);
                    CPPUNIT_ASSERT(x.a[16] == -16);
                } else CPPUNIT_ASSERT(false);
        }
        
        void test_deallocate_3(){
            A x;
            const pointer b = x.allocate(10);
            x.deallocate(b);
            CPPUNIT_ASSERT(x.a[0] == 92);
            CPPUNIT_ASSERT(x.a[96] == 92);
        }


    // -----
    // suite
    // -----

    CPPUNIT_TEST_SUITE(TestAllocator);
    CPPUNIT_TEST(test_one);
    CPPUNIT_TEST(test_ten);
    CPPUNIT_TEST(test_constructor_1);
    CPPUNIT_TEST(test_constructor_2);
    CPPUNIT_TEST(test_constructor_3);
    CPPUNIT_TEST(test_allocate_1);
    CPPUNIT_TEST(test_allocate_2);
    CPPUNIT_TEST(test_allocate_3);
    CPPUNIT_TEST(test_allocate_4);
    CPPUNIT_TEST(test_construct_1);
    CPPUNIT_TEST(test_construct_2);
    CPPUNIT_TEST(test_construct_3);
    CPPUNIT_TEST(test_destroy_1);
    CPPUNIT_TEST(test_destroy_2);
    CPPUNIT_TEST(test_destroy_3);
    CPPUNIT_TEST(test_deallocate_1);
    CPPUNIT_TEST(test_deallocate_2);
    CPPUNIT_TEST(test_deallocate_3);
    CPPUNIT_TEST_SUITE_END();};

// ----
// main
// ----

int main () {
    using namespace std;
    ios_base::sync_with_stdio(false);    // turn off synchronization with C I/O
    cout << "TestAllocator.c++" << endl;

    CppUnit::TextTestRunner tr;

//    tr.addTest(TestAllocator< std::allocator<int> >::suite());
  tr.addTest(TestAllocator< Allocator<int, 100> >::suite()); // uncomment!

//    tr.addTest(TestAllocator< std::allocator<double> >::suite());
  tr.addTest(TestAllocator< Allocator<double, 100> >::suite()); // uncomment!

    tr.run();

    cout << "Done." << endl;
    return 0;}
