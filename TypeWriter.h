#pragma once
#include <string>

class TypeWriter
{
private:
    int delay; // The delay between each letter
    bool enabled; // Whether the effect/animation is active

public:
    TypeWriter(int ms = 40, bool animation = true);

    void print(const std::string& text) const;

    void setDelay(int ms);
    void enableAnimation(bool value);
};