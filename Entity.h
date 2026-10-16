#ifndef ENTITY_H
#define ENTITY_H

#include <string>

using namespace std;

class Entity {
protected:
    string maID;

public:
    Entity();
    Entity(const string& id);
    virtual ~Entity();

    string getMaID() const;
    void setMaID(const string& id);

    virtual void nhap() = 0;
    virtual void xuat() const = 0;
    virtual string toFileRecord() const = 0;
    virtual void fromFileRecord(const string& record) = 0;
};

#endif
