#pragma once
#include <string>
#include <unordered_map>
#include <memory>
namespace image_viewer_np {
    /*Image manager interface*/
    class IImageHandler {
    public:
        IImageHandler() = default;
        virtual ~IImageHandler() = default;
        virtual bool load(const std::string& file_name, const std::string& key) = 0;
        virtual bool store(const std::string& key, const std::string& file_name) = 0;
        virtual bool blur(const std::string& key_src, const std::string& key_dst, int size) = 0;
        virtual bool resize(const std::string& key_src, const std::string& key_dst, int width, int height) = 0;
    private:
        IImageHandler(const IImageHandler&) = delete;
        IImageHandler(IImageHandler&&) = delete;
        IImageHandler& operator=(const IImageHandler&) = delete;
        IImageHandler& operator=(IImageHandler&&) = delete;
    };
}
