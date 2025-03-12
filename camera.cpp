#include <opencv2/opencv.hpp>
#include <iostream>
#include <stdexcept>

// 加载人脸检测模型
bool loadFaceCascade(cv::CascadeClassifier& face_cascade, const std::string& model_path) {
    if (!face_cascade.load(model_path)) {
        std::cerr << "错误: 无法加载人脸检测模型!" << model_path << std::endl;
        return false;
    }
    return true;
}

// 初始化摄像头
bool initializeCamera(cv::VideoCapture& cap, const std::string& pipeline) {
    cap.open(pipeline, cv::CAP_GSTREAMER);
    if (!cap.isOpened()) {
        std::cerr << "错误: 无法打开摄像头！" << std::endl;
        return false;
    }
    return true;
}

// 捕获并处理帧
void processFrame(cv::Mat& frame, cv::CascadeClassifier& face_cascade) {
    cv::Mat gray;
    cv::cvtColor(frame, gray, cv::COLOR_BGR2GRAY); // 转换为灰度图

    // 人脸检测
    std::vector<cv::Rect> faces;
    face_cascade.detectMultiScale(gray, faces, 1.1, 3, 0, cv::Size(30, 30));

    // 在图像上绘制检测到的人脸
    for (const auto& face : faces) {
        cv::rectangle(frame, face, cv::Scalar(255, 0, 0), 2);
    }
}

int main() {
    // GStreamer 管道配置（优化分辨率和帧率）
    std::string pipeline = "libcamerasrc ! video/x-raw,width=1280,height=720,framerate=30/1 ! videoconvert ! appsink";
    cv::VideoCapture cap;
    cv::CascadeClassifier face_cascade;

    try {
        // 初始化摄像头
        if (!initializeCamera(cap, pipeline)) {
            throw std::runtime_error("摄像头初始化失败！");
        }

        // 加载人脸检测模型
        std::string model_path = "/usr/share/opencv4/haarcascades/haarcascade_frontalface_default.xml";
        if (!loadFaceCascade(face_cascade, model_path)) {
            throw std::runtime_error("人脸检测模型加载失败！");
        }

        cv::Mat frame;
        while (true) {
            // 捕获帧
            if (!cap.read(frame)) {
                std::cerr << "警告: 无法读取帧！" << std::endl;
                break;
            }

            // 处理帧（人脸检测）
            processFrame(frame, face_cascade);

            // 显示帧
            cv::imshow("Face Detection", frame);

            // 按 ESC 退出
            if (cv::waitKey(30) == 27) {
                std::cout << "程序已退出。" << std::endl;
                break;
            }
        }
    } catch (const std::exception& e) {
        std::cerr << "错误: " << e.what() << std::endl;
        return -1;
    }

    // 释放资源
    cap.release();
    cv::destroyAllWindows();
    return 0;
}