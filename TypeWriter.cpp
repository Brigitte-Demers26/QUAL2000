#include "TypeWriter.h"
#include <iostream>
#include <thread>
#include <chrono>

using namespace std;

// Constructor:
TypeWriter::TypeWriter(int ms, bool animation)
    : delay(ms), enabled(animation) 
{

}

void TypeWriter::print(const string& text) const 
{
    for (char c : text) {
        cout << c;
        if (enabled) {
            this_thread::sleep_for(chrono::milliseconds(delay));
        }
    }
    cout << endl;
}

// Sets the delay for the effect:
void TypeWriter::setDelay(int ms) 
{
    delay = ms;
}

// Enables the typerwriter effect/animation:
void TypeWriter::enableAnimation(bool value) 
{
    enabled = value;
}