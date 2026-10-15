#ifndef ENTITY_H
#define ENTITY_H

#include <string>
using namespace std;

class Entity {
protected:
    string maID;

public:
    Entity() : maID("") {}
    virtual ~Entity() {}
    void setMaID(const string& id);
    string const getMaID();

    // BẮT BUỘC phải có các hàm ảo này ở lớp cha thì lớp con mới dùng được 'override'
    virtual void nhap() = 0;                              
    virtual void xuat() const = 0;                        
    virtual string toFileRecord() const = 0;              
    virtual void fromFileRecord(const string& record) = 0;
};


#endif
