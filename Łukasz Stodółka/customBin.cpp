#include <iostream>
#include <string>
#include <algorithm>

class BinaryString {
private:
    std::string value; // Stores the binary number as a string

    // Helper function to remove leading zeros
    void trim_leading_zeros() {
        size_t pos = value.find_first_not_of('0');
        if (pos != std::string::npos) {
            value = value.substr(pos);
        } else {
            value = "0";
        }
    }

    // Helper function for binary addition
    static std::string add_binary(const std::string& a, const std::string& b) {
        std::string result = "";
        int carry = 0, sum = 0;
        int i = a.size() - 1, j = b.size() -1;

        while (i >= 0 || j >= 0 || carry) {
            sum = carry;
            sum += (i >= 0) ? a[i--] - '0' : 0;
            sum += (j >= 0) ? b[j--] - '0' : 0;
            result = char((sum % 2) + '0') + result;
            carry = sum / 2;
        }

        return result;
    }

    // Helper function for binary subtraction (a >= b)
    static std::string subtract_binary(const std::string& a, const std::string& b) {
        std::string result = "";
        int borrow = 0, diff = 0;
        int i = a.size() - 1, j = b.size() -1;

        while (i >= 0) {
            diff = (a[i--] - '0') - borrow;
            if (j >= 0) diff -= (b[j--] - '0');
            if (diff >= 0) {
                result = char(diff + '0') + result;
                borrow = 0;
            } else {
                result = char(diff + 2 + '0') + result;
                borrow = 1;
            }
        }

        // Remove leading zeros
        size_t pos = result.find_first_not_of('0');
        if (pos != std::string::npos) {
            result = result.substr(pos);
        } else {
            result = "0";
        }

        return result;
    }

    // Helper function for binary multiplication
    static std::string multiply_binary(const std::string& a, const std::string& b) {
        std::string result = "0";
        std::string temp_a = a;

        for (int i = b.size() - 1; i >= 0; --i) {
            if (b[i] == '1') {
                result = add_binary(result, temp_a);
            }
            temp_a += '0'; // Shift left
        }

        return result;
    }

    // Helper function for binary division (returns quotient and remainder)
    static std::pair<std::string, std::string> divide_binary(const std::string& dividend, const std::string& divisor) {
        if (divisor == "0") {
            throw std::invalid_argument("Division by zero");
        }

        std::string quotient = "";
        std::string remainder = "";

        for (char bit : dividend) {
            remainder += bit;
            remainder = remainder.substr(remainder.find_first_not_of('0'));

            if (remainder.empty()) remainder = "0";

            if (compare_binary(remainder, divisor) >= 0) {
                remainder = subtract_binary(remainder, divisor);
                quotient += '1';
            } else {
                quotient += '0';
            }
        }

        quotient = quotient.substr(quotient.find_first_not_of('0'));
        if (quotient.empty()) quotient = "0";
        if (remainder.empty()) remainder = "0";

        return { quotient, remainder };
    }

    // Helper function to compare two binary strings
    static int compare_binary(const std::string& a, const std::string& b) {
        if (a.size() > b.size()) return 1;
        if (a.size() < b.size()) return -1;
        return a.compare(b);
    }

    // Helper function for bitwise operations
    static std::string bitwise_operation(const std::string& a, const std::string& b, char op) {
        std::string result = "";
        int max_len = std::max(a.size(), b.size());
        std::string a_padded = std::string(max_len - a.size(), '0') + a;
        std::string b_padded = std::string(max_len - b.size(), '0') + b;

        for (int i = 0; i < max_len; ++i) {
            char bit_a = a_padded[i];
            char bit_b = b_padded[i];
            char res_bit;

            switch (op) {
                case '&':
                    res_bit = ((bit_a - '0') & (bit_b - '0')) + '0';
                    break;
                case '|':
                    res_bit = ((bit_a - '0') | (bit_b - '0')) + '0';
                    break;
                case '^':
                    res_bit = ((bit_a - '0') ^ (bit_b - '0')) + '0';
                    break;
                default:
                    res_bit = '0';
            }

            result += res_bit;
        }

        // Remove leading zeros
        size_t pos = result.find_first_not_of('0');
        if (pos != std::string::npos) {
            result = result.substr(pos);
        } else {
            result = "0";
        }

        return result;
    }

public:
    // Constructors
    BinaryString() : value("0") {}

    BinaryString(const std::string& str) : value(str) {
        // Validate the input
        if (value.find_first_not_of("01") != std::string::npos) {
            throw std::invalid_argument("Invalid binary number");
        }
        trim_leading_zeros();
    }

    // Overload the + operator
    BinaryString operator+(const BinaryString& other) const {
        return BinaryString(add_binary(this->value, other.value));
    }

    // Overload the - operator
    BinaryString operator-(const BinaryString& other) const {
        if (compare_binary(this->value, other.value) < 0) {
            throw std::invalid_argument("Negative result in binary subtraction");
        }
        return BinaryString(subtract_binary(this->value, other.value));
    }

    // Overload the * operator
    BinaryString operator*(const BinaryString& other) const {
        return BinaryString(multiply_binary(this->value, other.value));
    }

    // Overload the / operator
    BinaryString operator/(const BinaryString& other) const {
        return BinaryString(divide_binary(this->value, other.value).first);
    }

    // Overload the % operator (modulo operation)
    BinaryString operator%(const BinaryString& other) const {
        return BinaryString(divide_binary(this->value, other.value).second);
    }

    // Overload the << operator (left shift)
    BinaryString operator<<(int shift) const {
        return BinaryString(this->value + std::string(shift, '0'));
    }

    // Overload the >> operator (right shift)
    BinaryString operator>>(int shift) const {
        if (shift >= value.size()) {
            return BinaryString("0");
        }
        return BinaryString(value.substr(0, value.size() - shift));
    }

    // Overload the & operator (bitwise AND)
    BinaryString operator&(const BinaryString& other) const {
        return BinaryString(bitwise_operation(this->value, other.value, '&'));
    }

    // Overload the | operator (bitwise OR)
    BinaryString operator|(const BinaryString& other) const {
        return BinaryString(bitwise_operation(this->value, other.value, '|'));
    }

    // Overload the ^ operator (bitwise XOR)
    BinaryString operator^(const BinaryString& other) const {
        return BinaryString(bitwise_operation(this->value, other.value, '^'));
    }

    // Overload the ** operator (exponentiation)
    BinaryString operator^(int exponent) const {
        if (exponent < 0) {
            throw std::invalid_argument("Negative exponent not supported");
        }
        BinaryString result("1");
        BinaryString base = *this;
        while (exponent) {
            if (exponent % 2 == 1) {
                result = result * base;
            }
            base = base * base;
            exponent /= 2;
        }
        return result;
    }

    // Overload the output operator
    friend std::ostream& operator<<(std::ostream& os, const BinaryString& b) {
        os << b.value;
        return os;
    }

    // Function to get the binary value
    std::string getValue() const {
        return value;
    }
};

int main() {
    try {
        BinaryString b1("1101");
        BinaryString b2("1011");

        // Addition
        std::cout << b1 << " + " << b2 << " = " << (b1 + b2) << std::endl;

        // Subtraction
        std::cout << b1 << " - " << b2 << " = " << (b1 - b2) << std::endl;

        // Multiplication
        std::cout << b1 << " * " << b2 << " = " << (b1 * b2) << std::endl;

        // Division
        std::cout << b1 << " / " << b2 << " = " << (b1 / b2) << std::endl;

        // Modulo
        std::cout << b1 << " % " << b2 << " = " << (b1 % b2) << std::endl;

        // Left Shift
        std::cout << b1 << " << 2 = " << (b1 << 2) << std::endl;

        // Right Shift
        std::cout << b1 << " >> 2 = " << (b1 >> 2) << std::endl;

        // Bitwise AND
        std::cout << b1 << " & " << b2 << " = " << (b1 & b2) << std::endl;

        // Bitwise OR
        std::cout << b1 << " | " << b2 << " = " << (b1 | b2) << std::endl;

        // Bitwise XOR
        std::cout << b1 << " ^ " << b2 << " = " << (b1 ^ b2) << std::endl;

        // Exponentiation
        std::cout << b1 << " ^ 3 = " << (b1 ^ 3) << std::endl;

    } catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
    } 

    return 0;
}

