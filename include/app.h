#pragma once
#include <string>
#include <unordered_map>
#include <memory>
#include <functional>
#include "iimagehandler.h"

namespace image_viewer_np {
    /*User interface (there could be gui). All texts set as params*/
    class App {
    public:
        enum class COMMAND_TYPE { UNDEFINED, LOAD, STORE, BLUR, RESIZE, HELP, CLOSE };
        using CommandNames = std::unordered_map<std::string, App::COMMAND_TYPE>;
        using CommandErrors = std::unordered_map<App::COMMAND_TYPE, std::string>;
        explicit App(std::unique_ptr<IImageHandler>&& handler, const CommandNames& commands, const CommandErrors& errors, const std::string& help_str);
        ~App();
        void run();
        void stop();
    private:
        App(const App&) = delete;
        App(App&&) = delete;
        App& operator=(const App&) = delete;
        App& operator=(App&&) = delete;
        COMMAND_TYPE getCommandType();
        std::unordered_map<COMMAND_TYPE, std::function<void()>> commands_;
        std::unique_ptr<IImageHandler> img_handler_;
        bool is_run;
        CommandNames command_names_;
        CommandErrors errors_;
        std::string help_str_;
    };
}
