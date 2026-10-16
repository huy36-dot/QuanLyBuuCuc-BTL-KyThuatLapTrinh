#define ENTITY_H

#include <string>
#include <stdexcept>

using namespace std;


// 1. LOP CO SO TRUU TUONG (Entity)

class Entity {
protected:
    string maID;

public:
    Entity() : maID("") {}
    Entity(const string& id) : maID(id) {}
    virtual ~Entity() {}

    string getMaID() const { return maID; }

    void setMaID(const string& id) {
        if (id.empty()) {
            throw invalid_argument("Ma dinh danh khong duoc de trong!");
        }
        maID = id;
    }

    // Cac ham ao thuan tuy: lop con bat buoc phai ghi de (override)
    virtual void nhap() = 0;
    virtual void xuat() const = 0;
    virtual string toFileRecord() const = 0;
    virtual void fromFileRecord(const string& record) = 0;
};

#endif
