# CMakeList.txt: проект CMake для image_viewer; включите исходный код и определения,
# укажите здесь логику для конкретного проекта.
#
cmake_minimum_required (VERSION 3.8)

project ("image_viewer")

find_package(OpenCV REQUIRED COMPONENTS core imgproc highgui) 

include_directories( ${PROJECT_SOURCE_DIR}/include/ ${OpenCV_INCLUDE_DIRS} )
link_directories(img_viewer ${OpenCV_INSTALL_PATH}/lib/)
# Добавьте источник в исполняемый файл этого проекта.
add_executable (image_viewer "src/main.cpp" "src/app.cpp"  "src/image.cpp")
target_link_libraries( image_viewer ${OpenCV_LIBS})
# TODO: Добавьте тесты и целевые объекты, если это необходимо.
target_compile_features(image_viewer PUBLIC cxx_std_20)
