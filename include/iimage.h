#pragma once
#include <string>
#include <memory>
namespace image_viewer_np {
    /*Image interface*/
    class IImage {
    public:
        virtual ~IImage() = default;
        virtual std::unique_ptr<IImage> clone() const = 0;
        virtual bool save(const std::string&) = 0;
        virtual bool blur(int size) = 0;
        virtual bool resize(int width, int height) = 0;
    };
}