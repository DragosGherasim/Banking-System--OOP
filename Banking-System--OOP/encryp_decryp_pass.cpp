#include <string>
using namespace std;

std::string encrypted_pass(std::string pass, std::string key, std::string alphabet)
{
    std::string encrypted_pass;

    for (int i{ 0 }; i < pass.length(); ++i)
        encrypted_pass += key.at(alphabet.find(pass.at(i)));

    return encrypted_pass;
}

std::string decrypted_pass(std::string encrypted_pass, std::string key, std::string alphabet)
{
    std::string decrypted_pass;

    for (int i{ 0 }; i < encrypted_pass.length(); ++i)
        decrypted_pass += alphabet.at(key.find(encrypted_pass.at(i)));

    return decrypted_pass;
}