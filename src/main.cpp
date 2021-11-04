#include <iostream>
#include <emscripten.h>
#include <emscripten/html5.h>

EM_JS(void, call_alert, (), {
  document.getElementById('my_textbox').value = 'Hello, emscripten world!';
  throw 'all done';
});

int main (int argc, char** argv) {
    std::cout << "Hello world" << std::endl;
    std::cout << EMSCRIPTEN_EVENT_KEYPRESS << std::endl;
    //
    call_alert();
    return EXIT_SUCCESS;
}