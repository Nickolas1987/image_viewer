#pragma once
#include <string>
#include <unordered_map>
#include <memory>
#include "iimagehandler.h"
#include "iimage.h"
namespace image_viewer_np {
    /*Image manager interface implementation. Created as template to not bind with real image class, 
    only with interface*/
    template<typename T, typename = std::enable_if<std::is_base_of<IImage,T>::value>>
    class ImageHandler : public IImageHandler {
    public:
        bool ImageHandler::load(const std::string& file_name, const std::string& key) override{
            try {
                images_[key] = std::move(std::make_unique<T>(file_name));
            }
            catch (std::runtime_error&) {
                return false;
            }
            return true;
        }
        bool ImageHandler::store(const std::string& key, const std::string& file_name) override{
            if (!images_.contains(key)) {
                return false;
            }
            return images_.at(key)->save(file_name);
        }
        bool ImageHandler::blur(const std::string& key_src, const std::string& key_dst, int size) override{
            if (!images_.contains(key_src)) {
                return false;
            }
            if (key_src != key_dst) {
                images_[key_dst] = images_.at(key_src)->clone();
            }
            return images_.at(key_dst)->blur(size);
        }
        bool ImageHandler::resize(const std::string& key_src, const std::string& key_dst, int width, int height) override{
            if (!images_.contains(key_src)) {
                return false;
            }
            if (key_src != key_dst) {
                images_[key_dst] = images_.at(key_src)->clone();
            }
            return images_.at(key_dst)->resize(width, height);
        }
    private:
        std::unordered_map<std::string, std::unique_ptr<IImage>> images_;
    };
}
