#include <string>

class KeyValidator
{
public:
    bool ValidateKey(const std::string& key) const;

private:
    // libsodium-based processing will be implemented here later.
    std::string key = "test";
};
