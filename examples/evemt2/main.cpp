#include <cstdlib>
#include <event2/event2.h>
#include <string>
#include <iostream>

class A
{
public:
    A() = default;

    gst::event2::event<void(const std::string& msg)> onRun;

    void run()
    {
        onRun("test 123");
    }
};

int main(int argc, char* argv[])
{
    A a;
    a.onRun += [](const std::string& msg) { std::cout << msg << std::endl; };

    a.run();

    return EXIT_SUCCESS;
}
