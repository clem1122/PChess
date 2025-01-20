#include <iostream>
#include <string>
#include <cmath>

int char_to_value(char c) {
    if (c >= '0' && c <= '9') {
        return c - '0';  // Pour les chiffres
    } else if (c >= 'A' && c <= 'Z') {
        return c - 'A' + 10;  // Pour les lettres A-Z
    } else if (c >= 'a' && c <= 'z') {
        return c - 'a' + 10;  // Pour les lettres a-z (si nécessaire)
    }
    return -1; // Cas d'erreur pour les caractères invalides
}

int from_base_to_decimal(const std::string& number, int base) {
    int decimal_value = 0;
    int power = 0;

    // Parcours du nombre de droite à gauche (du chiffre de poids faible au plus élevé)
    for (int i = number.length() - 1; i >= 0; --i) {
        char c = number[i];
        int value = char_to_value(c);
        
        if (value < 0 || value >= base) {
            std::cerr << "Invalid character in number: " << c << std::endl;
            return -1; // Erreur si un caractère ne correspond pas à la base
        }

        decimal_value += value * std::pow(base, power);
        power++;
    }

    return decimal_value;
}

std::string to_base(int number,int base) {
    if (base < 2 || base > 36) {
        throw std::invalid_argument("Base must be in the range [2, 36]");
    }

    const char* digits = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    std::string result;

    do {
        result = digits[number % base] + result;
        number /= base;
    } while (number > 0);

    return result;
}

int main() {

    std::string result = to_base(123456789, 19);
    std::cout << "The number " << "123459789" << " in base " << 24 << " is " << result << " in decimal." << std::endl;
    

    return 0;
}
