#include "image.h"
#include <iostream>

#include <stdexcept>
namespace image_viewer_np { 
    Image::Image(const std::string& n) : img_(cv::imread(n)) {
        if (img_.empty()) {
            throw std::runtime_error("error load");
        }
    }
    std::unique_ptr<IImage> Image::clone() const {
        return std::make_unique<Image>(*this);
    }
    bool Image::save(const std::string& f) {
        return cv::imwrite(f, img_);
    }
    bool Image::blur(int size) {
        try {
            cv::blur(img_, img_, cv::Size(size, size));
        }
        catch (cv::Exception& ) {
            return false;
        }
        return true;
    }
    bool Image::resize(int width, int height) {
        try {
            cv::resize(img_, img_, cv::Size(width, height));
        }
        catch (cv::Exception&) {
            return false;
        }
        return true;
    }
}