#include "ZLog.h"
#include <errno.h>
#include <iostream>
#include <unistd.h>

int main(int argc, char *argv[])
{
    for (int i = 0; i<10000; ++i)
    {
        LOGINFO("hello, %d, %s", 10001, "zlj");
        LOGWARNING("hello, %d, %s", 10002, "zlj");
        LOGERROR("hello, %d, %s", 10003, "zlj");
    }

    //errno = ENOENT;
    //SYSERROR("file ");

    /*int a = 12;
    int *new_a = new int(13);
    static int b = 14;
    static int *new_b = new int(15);

    using namespace std;
    cout << "a address : " << &a <<endl;
    cout << "new_a address : " << new_a <<endl;
    cout << "b address : " << &b <<endl;
    cout << "new_b address : " << new_b <<endl;*/


    return 0;
}
