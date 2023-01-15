#include <colorApp.hpp>

colorApp::colorApp() {
    for(int i = 0; i != 4; i++)
        color[i] = { 1.f, 1.f, 1.f, 1.f };

    for(int j = 0; j != 4; j++)
        type[j] = 0;
}