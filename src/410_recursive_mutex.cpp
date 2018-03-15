//============================================================================
// Name        : 410_recursive_mutex.cpp
// See https://baptiste-wicht.com/posts/2012/04/c11-concurrency-tutorial-advanced-locking-and-condition-variables.html
//============================================================================

#include <iostream>
#include <thread>
#include <mutex>

using namespace std;
struct Complex {
	//change to recursive_mutex and it all works
	recursive_mutex m;
//    mutex m;
    int i;

    Complex() : i(0) {}

    void mul(int x){
        lock_guard<recursive_mutex> lock(m);
//        lock_guard<mutex> lock(m);
        i *= x;
    }

    void div(int x){
        lock_guard<recursive_mutex> lock(m);
//    	lock_guard<mutex> lock(m);
        i /= x;
    }
    
    void both(int x, int y){
        lock_guard<recursive_mutex> lock(m);
//    	lock_guard<mutex> lock(m);
    	mul(x);
        div(y);
    }
};

void func(){
    Complex complex;
    complex.both(32, 23);
}
int main(){
	
	thread t1(func);
	t1.join();

}
