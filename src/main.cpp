#include "app.h"
#include "imagehandler.h"
#include "image.h"

using namespace std;
using namespace image_viewer_np;
/*Strings for interface*/
const std::unordered_map<std::string, App::COMMAND_TYPE> COMMAND_NAMES{ {"load", App::COMMAND_TYPE::LOAD},
                                                                       {"ld", App::COMMAND_TYPE::LOAD},
                                                                       {"store", App::COMMAND_TYPE::STORE},
                                                                       {"st", App::COMMAND_TYPE::STORE},
                                                                       {"blur", App::COMMAND_TYPE::BLUR},
                                                                       {"resize", App::COMMAND_TYPE::RESIZE},
                                                                       {"help", App::COMMAND_TYPE::HELP},
                                                                       {"h", App::COMMAND_TYPE::HELP},
                                                                       {"exit", App::COMMAND_TYPE::CLOSE},
                                                                       {"quit", App::COMMAND_TYPE::CLOSE},
                                                                       {"q", App::COMMAND_TYPE::CLOSE}
};
const std::unordered_map<App::COMMAND_TYPE, std::string> ERRORS{ {App::COMMAND_TYPE::LOAD, "Load failed"},
                                                                 {App::COMMAND_TYPE::STORE, "Store failed"},
                                                                 {App::COMMAND_TYPE::BLUR, "Blur failed"},
                                                                 {App::COMMAND_TYPE::RESIZE, "Resize failed"},
                                                                 {App::COMMAND_TYPE::UNDEFINED, "Unknown command"},
                                                               };
const std::string HELP_STR = "ld, load filename key  - load image \n" 
                             "st,store key filename - store image\n" 
                             "blur src dst size - blur image \n"
                             "resize src dst width height - resize image \n" 
                             "q, quit - close";
int main(){
    try {
        auto handler = std::unique_ptr<IImageHandler>(new ImageHandler<Image>());
        App app(std::move(handler), COMMAND_NAMES, ERRORS, HELP_STR);
        app.run();
    }
    catch (std::bad_alloc& e) {
        std::cout << e.what() << std::endl;
    }
    catch (std::runtime_error& e) {
        std::cout << e.what() << std::endl;
    }
    return 0;
}
