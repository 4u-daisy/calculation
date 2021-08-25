#include "token.h"

double number_token::get_value() const
{
    return _value;
}
token* number_token::parse(std::string& line) const
{
    if (line.empty()) {
        return nullptr;
    }
    std::stringstream ss(line);
    double value = 0;
    if (ss >> value) {
        std::string s;
        ss >> s;
        line = s;
        return new number_token(value);
    }
    return nullptr;
}
std::string number_token::type_token() const
{
    return "number";
}


token* operation_plus_token::parse(std::string& line) const
{
    if (line.empty()) return nullptr;
    if (line[0] == '+') {
        line = line.substr(1);
        return new operation_plus_token;
    }
    return nullptr;
}
std::string operation_plus_token::type_token() const
{
    return "binary operation: minimal priority";
}
double operation_plus_token::compute_value_binary(const double& lhs, const double& rhs) const
{
    return lhs + rhs;
}

token* operation_minus_token::parse(std::string& line) const
{
    if (line.empty()) return nullptr;
    if (line[0] == '-') {
        line = line.substr(1);
        return new operation_minus_token;
    }
    return nullptr;
}
std::string operation_minus_token::type_token() const
{
    return "binary operation: minimal priority";
}
double operation_minus_token::compute_value_binary(const double& lhs, const double& rhs) const
{
    return lhs - rhs;
}

token* operation_multiply_token::parse(std::string& line) const
{
    if (line.empty()) return nullptr;
    if (line[0] == '*') {
        line = line.substr(1);
        return new operation_multiply_token;
    }
    return nullptr;
}
std::string operation_multiply_token::type_token() const
{
    return "binary operation: middle priority";
}
double operation_multiply_token::compute_value_binary(const double& lhs, const double& rhs) const
{
    return lhs * rhs;
}

token* operation_share_token::parse(std::string& line) const
{
    if (line.empty()) return nullptr;
    if (line[0] == '/') {
        line = line.substr(1);
        return new operation_share_token;
    }
    return nullptr;
}
std::string operation_share_token::type_token() const
{
    return "binary operation: middle priority";
}
double operation_share_token::compute_value_binary(const double& lhs, const double& rhs) const
{
    return lhs / rhs;
}

token* pow_token::parse(std::string& line) const
{
    if (line.empty()) return nullptr;
    if (line[0] == '^') {
        line = line.substr(1);
        return new pow_token;
    }
    return nullptr;
}
std::string pow_token::type_token() const
{
    return "binary operation: max priority";
}
double pow_token::compute_value_binary(const double& lhs, const double& rhs) const
{
    return std::pow(lhs, rhs);
}


token* round_right_bracket_token::parse(std::string& line) const
{
    if (line.empty()) return nullptr;
    if (line[0] == ')') {
        line = line.substr(1);
        return new round_right_bracket_token;
    }
    return nullptr;
}
std::string round_right_bracket_token::type_token() const
{
    return "right bracket";
}
std::string round_right_bracket_token::type_bracket() const
{
    return "round right bracket";
}

token* round_left_bracket_token::parse(std::string& line) const
{
    if (line.empty()) return nullptr;
    if (line[0] == '(') {
        line = line.substr(1);
        return new round_left_bracket_token;
    }
    return nullptr;
}
std::string round_left_bracket_token::type_token() const
{
    return "left bracket";
}
bool round_left_bracket_token::check_correctly_bracket(right_bracket* close_bracket) const
{
    if (close_bracket->type_bracket() == "round right bracket")
        return true;
    return false;
}


token* factorial_token::parse(std::string& line) const
{
    if (line.empty()) return nullptr;
    if (line[0] == '!') {
        line = line.substr(1);
        return new factorial_token;
    }
    return nullptr;
}
std::string factorial_token::type_token() const
{
    return "unary operation";
}
double factorial(const double N) {
    if (N < 0)
        return 0;
    if (N == 0)
        return 1;
    else
        return N * factorial(N - 1); // делаем рекурсию.
}
double factorial_token::compute_value_unary(const double& lhs) const
{
    return factorial(lhs);
}

token* sqrt_token::parse(std::string& line) const
{
    if (line.empty()) return nullptr;
    if (line.compare(0, 4, "sqrt") == 0) {
        line = line.substr(4);
        return new sqrt_token;
    }
    return nullptr;
}
std::string sqrt_token::type_token() const
{
    return "unary operation";
}
double sqrt_token::compute_value_unary(const double& lhs) const
{
    return sqrt(lhs);
}

token* natural_log_token::parse(std::string& line) const
{
    if (line.empty()) return nullptr;
    if (line.compare(0, 2, "ln") == 0) {
        line = line.substr(2);
        return new natural_log_token;
    }
    return nullptr;
}
std::string natural_log_token::type_token() const
{
    return "unary operation";
}
double natural_log_token::compute_value_unary(const double& lhs) const
{
    return std::log(lhs);
}

token* ten_log_token::parse(std::string& line) const
{
    if (line.empty()) return nullptr;
    if (line.compare(0, 3, "log") == 0) {
        line = line.substr(3);
        return new ten_log_token;
    }
    return nullptr;
}
std::string ten_log_token::type_token() const
{
    return "unary operation";
}
double ten_log_token::compute_value_unary(const double& lhs) const
{
    return std::log10(lhs);
}

token* sin_token::parse(std::string& line) const
{
    if (line.empty()) return nullptr;
    if (line.compare(0, 3, "sin") == 0) {
        line = line.substr(3);
        return new sin_token;
    }
    return nullptr;
}
std::string sin_token::type_token() const
{
    return "unary operation";
}
double sin_token::compute_value_unary(const double& lhs) const
{
    return std::sin(lhs);
}

token* cos_token::parse(std::string& line) const
{
    if (line.empty()) return nullptr;
    if (line.compare(0, 3, "cos") == 0) {
        line = line.substr(3);
        return new cos_token;
    }
    return nullptr;
}
std::string cos_token::type_token() const
{
    return "unary operation";
}
double cos_token::compute_value_unary(const double& lhs) const
{
    return std::cos(lhs);
}

token* tg_token::parse(std::string& line) const
{
    if (line.empty()) return nullptr;
    if (line.compare(0, 2, "tg") == 0) {
        line = line.substr(2);
        return new tg_token;
    }
    return nullptr;
}
std::string tg_token::type_token() const
{
    return "unary operation";
}
double tg_token::compute_value_unary(const double& lhs) const
{
    return std::tan(lhs);
}

token* ctg_token::parse(std::string& line) const
{
    if (line.empty()) return nullptr;
    if (line.compare(0, 3, "ctg") == 0) {
        line = line.substr(3);
        return new ctg_token;
    }
    return nullptr;
}
std::string ctg_token::type_token() const
{
    return "unary operation";
}
double ctg_token::compute_value_unary(const double& lhs) const
{
    return 1 / std::tan(lhs);
}

token* remainder_of_the_division::parse(std::string& line) const
{
    if (line.empty()) return nullptr;
    if (line[0] == '%') {
        line = line.substr(1);
        return new remainder_of_the_division;
    }
    return nullptr;
}
std::string remainder_of_the_division::type_token() const
{
    return "binary operation: middle priority";
}
double remainder_of_the_division::compute_value_binary(const double& lhs, const double& rhs) const
{
    return (int)lhs%(int)rhs;
}
