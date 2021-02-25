#include <string>
#include <iostream>
#include <chrono>
#include <thread>

// Note to self:
// - You have to std::flush every time if you want sleep to work.

void set_position(int x, int y){
    printf("\x1b[%d;%dH", y, x);
}

void clear_console(){
    printf("\x1b[2J\x1b[1;1H");
}

class Partical {
    public:
        Partical();
        Partical(double x, double y, double m){
            _x = x;
            _y = y;
            _m = m;
        };

        void setPos(double x, double y){
            _x = x;
            _y = y;
        }

        void show(){
            set_position(_x, _y);
            std::cout << _display;
        }

        void unshow(){
            set_position(_x, _y);
            std::cout << " ";
        }

        void update_position(){
            unshow();

            // Horizontal
            _v[0] = _v[0] + _a[0];
            _x += _v[0];

            // Vertical
            _v[1] = _v[1] + _a[1];
            _y += _v[1];

            show();
            _a[0] = 0;
            _a[1] = 0;
        }

        void apply_horizontal_force(double mag){
            _a[0] += mag/_m;
        }

        void apply_vertical_force(double mag){
            _a[1] += mag/_m;
        }

    private:
        double _x = 0;
        double _y = 0;
        double _m = 0;
        double _v[2] = {0, 0};
        double _a[2] = {0, 0};
        std::string _display = "x";
};

int main(){
    int tick_rate = 300;

    clear_console();

    Partical part(3, 3, 10);

    part.apply_horizontal_force(10);
    part.apply_vertical_force(4);

    for (int i = 0; i < 10; i++){
        part.update_position();


        std::cout.flush();
        std::this_thread::sleep_for(std::chrono::milliseconds(tick_rate)); 
    }

    set_position(0, 100);
    std::cout << "Finished." << std::endl;
    std::cin;
    return 0;
}