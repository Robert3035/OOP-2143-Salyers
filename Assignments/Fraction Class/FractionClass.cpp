#include <iostream>
#include <numeric>  // For gcd function to simplify fractions

class Fraction {
private:
    int numerator;
    int denominator;

    // Helper function to simplify fractions
    void simplify() {
        int gcd_value = std::gcd(numerator, denominator);  // Simplify the fraction
        numerator /= gcd_value;
        denominator /= gcd_value;
        if (denominator < 0) {  // Ensure denominator is positive
            numerator = -numerator;
            denominator = -denominator;
        }
    }

public:
    // Constructor
    Fraction(int num, int den) : numerator(num), denominator(den) {
        if (denominator == 0) {
            throw std::invalid_argument("Denominator cannot be zero.");
        }
        simplify();
    }

    // Overloaded addition operator
    Fraction operator+(const Fraction& other) {
        // Find Least Common Denominator (LCD)
        int lcd_val = lcd(denominator, other.denominator);

        // Adjust both fractions to have the same denominator
        int num1 = numerator * (lcd_val / denominator);
        int num2 = other.numerator * (lcd_val / other.denominator);

        // Add the numerators
        int result_num = num1 + num2;

        // Return the result as a new fraction and simplify it
        Fraction result(result_num, lcd_val);
        return result;
    }

    // Overloaded subtraction operator
    Fraction operator-(const Fraction& other) {
        int lcd_val = lcd(denominator, other.denominator);
        int num1 = numerator * (lcd_val / denominator);
        int num2 = other.numerator * (lcd_val / other.denominator);

        int result_num = num1 - num2;

        Fraction result(result_num, lcd_val);
        return result;
    }

    // Overloaded multiplication operator
    Fraction operator*(const Fraction& other) {
        int result_num = numerator * other.numerator;
        int result_den = denominator * other.denominator;

        Fraction result(result_num, result_den);
        return result;
    }

    // Overloaded division operator
    Fraction operator/(const Fraction& other) {
        if (other.numerator == 0) {
            throw std::invalid_argument("Cannot divide by zero.");
        }

        int result_num = numerator * other.denominator;
        int result_den = denominator * other.numerator;

        Fraction result(result_num, result_den);
        return result;
    }

    // Overloaded equality operator (==)
    bool operator==(const Fraction& other) const {
        return numerator == other.numerator && denominator == other.denominator;
    }

    // Overload output operator (<<) for printing fractions
    friend std::ostream& operator<<(std::ostream& os, const Fraction& frac) {
        os << frac.numerator << "/" << frac.denominator;
        return os;
    }

    // Function to calculate Least Common Denominator (LCD)
    static int lcd(int a, int b) {
        return std::lcm(a, b);  // Using C++17's std::lcm
    }

    // Function to calculate Least Common Multiple (LCM)
    static int lcm(int a, int b) {
        return std::lcm(a, b);  // Using C++17's std::lcm
    }

    // Getter methods for numerator and denominator
    int getNumerator() const { return numerator; }
    int getDenominator() const { return denominator; }

    // Method to read a fraction from user input
    static Fraction readFraction() {
        int num, den;
        char slash;
        std::cin >> num >> slash >> den;
        if (den == 0) {
            throw std::invalid_argument("Denominator cannot be zero.");
        }
        return Fraction(num, den);
    }
};

int main() {
    try {
        // Reading input for two fractions and an operator
        std::cout << "Enter the first fraction (e.g., 1/2): ";
        Fraction frac1 = Fraction::readFraction();

        std::cout << "Enter the second fraction (e.g., 3/4): ";
        Fraction frac2 = Fraction::readFraction();

        std::cout << "Enter an operator (+, -, *, /): ";
        char op;
        std::cin >> op;

        Fraction result(0, 1);

        // Performing the operation based on user input
        switch(op) {
            case '+':
                result = frac1 + frac2;
                break;
            case '-':
                result = frac1 - frac2;
                break;
            case '*':
                result = frac1 * frac2;
                break;
            case '/':
                result = frac1 / frac2;
                break;
            default:
                std::cout << "Invalid operator!" << std::endl;
                return 1;
        }

        std::cout << "Result: " << result << std::endl;

    } catch (const std::exception& e) {
        std::cout << "Error: " << e.what() << std::endl;
    }

    return 0;
}
