#include "Entity.h"
#include <stdexcept>

using namespace std;

Entity::Entity() : maID("") {}

Entity::Entity(const string& id) : maID(id) {}

Entity::~Entity() {}

string Entity::getMaID() const {
    return maID;
}

void Entity::setMaID(const string& id) {
    if (id.empty()) {
        throw invalid_argument("Ma dinh danh khong duoc de trong!");
    }
    maID = id;
}
