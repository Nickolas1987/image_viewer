#pragma once
#include <string>
#include "iimage.h"
#include<opencv2/opencv.hpp>
namespace image_viewer_np {
    /*Image interface implementation*/
    class Image : public IImage{
    public:
        Image(const std::string&);
        Image(const Image&) = default;
        Image& operator=(const Image&) = default;
        Image(Image&&) noexcept = default;
        Image& operator=(Image&&) noexcept = default;
        virtual std::unique_ptr<IImage> clone() const override;
        virtual bool save(const std::string&) override;
        virtual bool blur(int size) override;
        virtual bool resize(int width, int height) override;
    private:
        cv::Mat img_;
    };
}