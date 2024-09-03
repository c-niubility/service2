#include <iostream>
#include "httplib.h"

using namespace httplib;
using namespace std;

void handle_post(const Request& req, Response& res) {
    // 获取请求体数据
    string body = req.body;

    // 在服务器端打印请求体数据
    cout << "Received POST request with body: " << body << endl;

    // 设置响应内容
    res.set_content("POST request received", "application/json");
}

int main() {
    Server svr;
  
    svr.Get("/QueryFirmwareVersion", [](const Request& req, Response& res) {
        res.set_content("{\"Top\":{\"breath\":[\"1.0.bin\",\"2.0.bin\"],\"height\":[\"1.0.bin\",\"2.0.bin\"],\"human\":[\"1.0.bin\",\"2.0.bin\",\"3.0.bin\"]}}", "application/json");
        });

    svr.Get("/about", [](const Request& req, Response& res) {
        res.set_content("About page", "text/plain");
        });

    svr.Get("/breath.1", [](const Request& req, Response& res) {
        res.set_content("breath 1.0版本的固件网址：breath 1.0.com", "text/plain");
        });
    
    svr.Get("/breath.2", [](const Request& req, Response& res) {
        res.set_content("breath 2.0版本的固件网址：breath 2.0.com", "text/plain");
        });
    
    svr.Get("/height.1", [](const Request& req, Response& res) {
        res.set_content("height 1.0版本的固件网址：height 1.0.com", "text/plain");
        });

    svr.Get("/height.2", [](const Request& req, Response& res) {
        res.set_content("height 2.0版本的固件网址：height 2.0.com", "text/plain");
        });

    svr.Get("/human.1", [](const Request& req, Response& res) {
        res.set_content("human 1.0版本的固件网址：human 1.0.com", "text/plain");
        });

    svr.Get("/human.2", [](const Request& req, Response& res) {
        res.set_content("human 2.0版本的固件网址：human 2.0.com", "text/plain");
        });

    svr.Get("/human.3", [](const Request& req, Response& res) {
        res.set_content("human 3.0版本的固件网址：human 3.0.com", "text/plain");
        });


    
    
    svr.Post("/api/users", handle_post);



    
    // 文件上传
    svr.Post("/upload", [](const Request& req, Response& res) {
        if (req.files.empty()) {
            res.set_content("No file uploaded", "text/plain");
            return;
        }

        const auto& file = req.files.begin()->second;
        std::ofstream ofs(file.filename, std::ios::binary);
        ofs.write(file.content.data(), file.content.size());
        ofs.close();

        res.set_content("File uploaded successfully", "text/plain");
        });


    // 文件下载
    svr.Get("/download", [](const Request& req, Response& res) {
        std::ifstream file("example.txt", std::ios::binary);
        if (!file.is_open()) {
            res.set_content("File not found", "text/plain");
            return;
        }

        file.seekg(0, std::ios::end);
        std::string data = std::string(std::istreambuf_iterator<char>(file), std::istreambuf_iterator<char>());
        file.close();

        res.set_content(data, "text/plain");
        });

 
    cout << "Server started on port 8080" << endl;
    svr.listen("localhost", 8080);
   
    
    return 0;
}
