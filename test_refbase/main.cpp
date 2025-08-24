#include <utils/RefBase.h>
#include <stdio.h>

using namespace android;
using namespace std;

struct A : public RefBase {
    A() {
        printf("|  Create class A: %p\n", this);
    }
    virtual ~A() {
        printf("|  ~ class A: %p\n", this);
    }
};

void test_normal() {
    printf("--------------------------------------\n");
    printf("Func: %s\n", __func__);
    printf("--------------------------------------\n");
    printf("=================\n");
    printf("Create a in Stack\n");
    printf("=================\n");
    A a;
    printf("=================\n");
    printf("Create sp pa(Create A in heap, and assign it to pa)\n");
    printf("=================\n");
    sp<A> pa = new A();
    printf("=================\n");
    printf("Create sp pc\n");
    printf("=================\n");
    sp<A> pc = pa;

    printf("=================\n");
    printf("return\n");
    printf("=================\n");
}

void test_create_in_stack() {
    // WARNING: This will cause issues - never manage stack objects with sp!
    A a;
    {
        sp<A> pa = &a;
    } // pa goes out of scope, tries to delete stack object 'a'
} // Double free occurs here

int main(int argc, char *argv[]) {
    printf("Android RefBase API Test\n");
    printf("========================\n");
    
    test_normal();
    
    // Uncomment the line below to see the double free error
    // test_create_in_stack(); // THIS will cause double free
    
    return 0;
}
