#include "Arknights.h"
#include <iostream>
#include <fstream>
#include <sys/utsname.h>

using namespace std;

#define GREEN "\033[32m"
#define RESET "\033[0m"

// 读取文件的第一行内容
static string readFileFirstLine(const string& filePath) {
    ifstream file(filePath);
    string line;
    if (file.is_open()) {
        getline(file, line);
        file.close();
    }
    return line;
}

string Arknights::getOSInfo() {
    return readFileFirstLine("/etc/os-release");
}

string Arknights::getKernelInfo() {
    struct utsname buffer;
    if (uname(&buffer) == 0) {
        return buffer.release;
    }
    return "Unknown Kernel";
}

string Arknights::getCPUInfo() {
    ifstream file("/proc/cpuinfo");
    string line, model;
    while (getline(file, line)) {
        if (line.find("model name") != string::npos) {
            model = line.substr(line.find(":") + 2);
            break;
        }
    }
    return model.empty() ? "Unknown CPU" : model;
}

string Arknights::getMemoryInfo() {
    ifstream file("/proc/meminfo");
    string line, mem;
    while (getline(file, line)) {
        if (line.find("MemTotal") != string::npos) {
            mem = line.substr(line.find(":") + 2);
            break;
        }
    }
    return mem.empty() ? "Unknown Memory" : mem;
}

void Arknights::printLogo() {
    cout << GREEN << Arknights_LOGO << RESET << endl;
    cout << GREEN << "OS: " << RESET << getOSInfo() << endl;
    cout << GREEN << "Kernel: " << RESET << getKernelInfo() << endl;
    cout << GREEN << "CPU: " << RESET << getCPUInfo() << endl;
    cout << GREEN << "Memory: " << RESET << getMemoryInfo() << endl;
}
