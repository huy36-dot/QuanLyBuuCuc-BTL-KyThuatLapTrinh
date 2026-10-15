#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <algorithm>
#include <stdexcept>
#include <filesystem>

using namespace std;

class Entity {
protected:
    string maID;
public:
    Entity() : maID("") {}
    Entity(string id) : maID(id) {}
    virtual ~Entity() {}

    string getMaID() const { return maID; }
    void setMaID(const string& id) {
        if (id.empty()) throw invalid_argument("Mã định danh không được để trống!");
        maID = id;
    }

    virtual void nhap() = 0;
    virtual void xuat() const = 0;
    virtual string toFileRecord() const = 0;
    virtual void fromFileRecord(const string& record) = 0;
};
