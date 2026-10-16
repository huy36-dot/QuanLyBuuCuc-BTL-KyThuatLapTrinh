#ifndef REPOSITORY_H
#define REPOSITORY_H

#include <vector>
#include <string>
#include <fstream>
#include <filesystem>
#include <algorithm>
#include <stdexcept>

using namespace std;


template <typename T>
class Repository {
private:
    vector<T> data;
    string filePath;

    void kiemTraThuMuc() {
        if (!filesystem::exists("data")) {
            filesystem::create_directories("data");
        }
    }

public:
    Repository(const string& path) : filePath(path) {
        kiemTraThuMuc();
        docFile();
    }

    void docFile() {
        data.clear();
        ifstream file(filePath);
        if (!file.is_open()) return;
        string line;
        while (getline(file, line)) {
            if (line.empty()) continue;
            try {
                T obj;
                obj.fromFileRecord(line);
                data.push_back(obj);
            }
            catch (...) { 
                /* Bo qua dong loi */ }
        }
        file.close();
    }

    void ghiFile() {
        kiemTraThuMuc();
        ofstream file(filePath);
        for (const auto& item : data) {
            file << item.toFileRecord() << "\n";
        }
        file.close();
    }

    // Tra ve danh sach de hien thi / sap xep
    vector<T> getAll() const { return data; }

    // Tim kiem bang ID
    T* findById(const string& id) {
        for (auto& item : data) {
            if (item.getMaID() == id) return &item;
        }
        return nullptr;
    }

    // Them moi
    void add(const T& item) {
        if (findById(item.getMaID()) != nullptr) {
            throw invalid_argument("Ma dinh danh da ton tai!");
        }
        data.push_back(item);
        ghiFile();
    }

    // Cap nhat
    bool update(const string& id, const T& newItem) {
        for (auto& item : data) {
            if (item.getMaID() == id) {
                item = newItem;
                ghiFile();
                return true;
            }
        }
        return false;
    }

    // Xoa
    bool removeById(const string& id) {
        auto it = remove_if(data.begin(), data.end(), [&](const T& item) {
            return item.getMaID() == id;
            });
        if (it != data.end()) {
            data.erase(it, data.end());
            ghiFile();
            return true;
        }
        return false;
    }
};

#endif
