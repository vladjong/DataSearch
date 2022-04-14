#include "view.h"

int main() {
    Model model;
    Controller controller(&model);
    View view(&controller);
    view.startEventLoop();
    return 0;
}
