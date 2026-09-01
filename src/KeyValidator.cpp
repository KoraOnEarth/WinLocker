#include "KeyValidator.h"

bool KeyValidator::ValidateKey(const std::string& key) const
{
    return this->key == key;
}
