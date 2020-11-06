
#include <iostream>
#include <limits>
#include "app.h"
#include <stdexcept>

using namespace std;
namespace image_viewer_np{
    App::App(std::unique_ptr<IImageHandler>&& h, const CommandNames& commands, const CommandErrors& errors, const std::string& help_str):img_handler_(std::forward<std::unique_ptr<IImageHandler>>(h)),
                                                                                                            is_run(false), 
                                                                                                            command_names_(commands),
                                                                                                            errors_(errors),
                                                                                                            help_str_(help_str) {
        if (!img_handler_) {
            throw std::runtime_error("bad handler");
        }
        commands_[COMMAND_TYPE::LOAD] = [this] (){
            std::string file_name;
            std::string key;
            std::cin >> file_name >> key;

            if (!img_handler_->load(file_name, key)) {
                std::cout << errors_[COMMAND_TYPE::LOAD] << std::endl;
            }
        };
        commands_[COMMAND_TYPE::STORE] = [this]() {
            std::string file_name;
            std::string key;
            std::cin >> key >> file_name;

            if(!img_handler_->store(key, file_name)){
                std::cout << errors_[COMMAND_TYPE::STORE] << std::endl;
            }
        };
        commands_[COMMAND_TYPE::BLUR] = [this]() {
            std::string key_src;
            std::string key_dst;
            int size{};
            std::cin >> key_src >> key_dst >> size;
 
            if (size <=0 || !img_handler_->blur(key_src, key_dst, size)) {
                std::cout << errors_[COMMAND_TYPE::BLUR] << std::endl;
            }
        };
        commands_[COMMAND_TYPE::RESIZE] = [this]() {
            std::string key_src;
            std::string key_dst;
            int width{};
            int height{};
            std::cin >> key_src >> key_dst >> width >> height;

            if (width <= 0 || height <=0 || !img_handler_->resize(key_src, key_dst, width, height)) {
                std::cout << errors_[COMMAND_TYPE::RESIZE] << std::endl;
            }
        };
        commands_[COMMAND_TYPE::HELP] = [this]() {
            std::cout << help_str_ << std::endl;
        };
        commands_[COMMAND_TYPE::CLOSE] = [this]() {
            stop();
        };
    }

    App::~App() {
        stop();
    }

    void App::stop() {
        is_run = false;
    }

    App::COMMAND_TYPE App::getCommandType() {
        std::string command;
        std::cin >> command;
        if (!command_names_.contains(command)) {
            return COMMAND_TYPE::UNDEFINED;
        }
        return command_names_.at(command);
    }

    void App::run() {
        if (is_run) {
            return;
        }
        is_run = true;

        while (is_run) {
            auto type = getCommandType();
            if (type != COMMAND_TYPE::UNDEFINED) {
                commands_[type]();
            }
            else {
                std::cout << errors_[type] << std::endl;
            }
            cin.clear();
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    }
}
