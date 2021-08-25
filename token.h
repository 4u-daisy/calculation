#pragma once
#include <string>
#include <sstream>
#include <string_view>

class token {
public:
    virtual token* parse(std::string& line) const = 0;
    virtual std::string type_token() const = 0;
};

class number_token : public token {
private:
    double _value;

public:
    number_token() : _value(0) { }
    number_token(double value) : _value(value) { }

    double get_value() const;
    token* parse(std::string& line) const override;
    std::string type_token() const override;
};


class operation : public token {};

class binary_operation : public operation {
public:
    virtual double compute_value_binary(const double& lhs, const double& rhs) const = 0;
};

class operation_plus_token : public binary_operation {

public:
    token* parse(std::string& line) const override;
    std::string type_token() const override;
    double compute_value_binary(const double& lhs, const double& rhs) const override;
};
class operation_minus_token : public binary_operation {

public:
    token* parse(std::string& line) const override;
    std::string type_token() const override;
    double compute_value_binary(const double& lhs, const double& rhs) const override;

};
class operation_multiply_token : public binary_operation {

public:
    token* parse(std::string& line) const override;
    std::string type_token() const override;
    double compute_value_binary(const double& lhs, const double& rhs) const override;

};
class operation_share_token : public binary_operation {

public:
    token* parse(std::string& line) const override;
    std::string type_token() const override;
    double compute_value_binary(const double& lhs, const double& rhs) const override;

};
class remainder_of_the_division : public binary_operation {
    token* parse(std::string& line) const override;
    std::string type_token() const override;
    double compute_value_binary(const double& lhs, const double& rhs) const override;
};
class pow_token : public binary_operation {
    token* parse(std::string& line) const override;
    std::string type_token() const override;
    double compute_value_binary(const double& lhs, const double& rhs) const override;
};


class right_bracket : public token {
public:
    virtual std::string type_bracket() const = 0;
};
class round_right_bracket_token : public right_bracket {
public:
    token* parse(std::string& line) const override;
    std::string type_token() const override;
    std::string type_bracket() const override;
};

class left_bracket : public token {
public:
    virtual bool check_correctly_bracket(right_bracket* close_bracket) const = 0;
};
class round_left_bracket_token : public left_bracket {
public:
    token* parse(std::string& line) const override;
    std::string type_token() const override;
    bool check_correctly_bracket(right_bracket* close_bracket) const override;

};


// 3!, sin(...), sqrt
class unary_operation : public operation {
public:
    virtual double compute_value_unary(const double& lhs) const = 0;
};

class factorial_token : public unary_operation {
public:
    token* parse(std::string& line) const override;
    std::string type_token() const override;
    double compute_value_unary(const double& lhs) const override;
};
class sqrt_token : public unary_operation {
    token* parse(std::string& line) const override;
    std::string type_token() const override;
    double compute_value_unary(const double& lhs) const override;
};
class natural_log_token : public unary_operation {
    token* parse(std::string& line) const override;
    std::string type_token() const override;
    double compute_value_unary(const double& lhs) const override;
};
class ten_log_token : public unary_operation {
    token* parse(std::string& line) const override;
    std::string type_token() const override;
    double compute_value_unary(const double& lhs) const override;
};
class sin_token : public unary_operation {
    token* parse(std::string& line) const override;
    std::string type_token() const override;
    double compute_value_unary(const double& lhs) const override;
};
class cos_token : public unary_operation {
    token* parse(std::string& line) const override;
    std::string type_token() const override;
    double compute_value_unary(const double& lhs) const override;
};
class tg_token : public unary_operation {
    token* parse(std::string& line) const override;
    std::string type_token() const override;
    double compute_value_unary(const double& lhs) const override;
};
class ctg_token : public unary_operation {
    token* parse(std::string& line) const override;
    std::string type_token() const override;
    double compute_value_unary(const double& lhs) const override;
};

