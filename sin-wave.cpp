#include <math.h>
#include <iostream>
#include <chrono>
#include <thread>

#define PI 3.14159265

// Note to self:
// - You have to std::flush every time if you want sleep to work.

void set_position(int x, int y)
{
    printf("\x1b[%d;%dH", y, x);
}

void clear_console()
{
    printf("\x1b[2J\x1b[1;1H");
}

int main()
{
    int tick_rate = 1;
    double pos_array[15];
    double result;

    clear_console();

    while (true)
    {
        for (int i = 0; i < 115; i++)
        {
            if (i >= 15)
            {
                int y = pos_array[(i - 15) % 15];
                set_position(i - 15, y);
                std::cout << " ";
            }

            if (i < 100)
            {
                result = 10 * sin(i / (1.5 * PI));
                result += 15;

                pos_array[i % 15] = (int)result;
                set_position(i, (int)result);
                std::cout << "x";

                // For checking output of sin...
                // std::cout << result << std::endl;
            }
            std::cout.flush();
            std::this_thread::sleep_for(std::chrono::milliseconds(tick_rate));
        }
    }

    set_position(0, 100);
    std::cout << "Finished." << std::endl;
    return 0;
}