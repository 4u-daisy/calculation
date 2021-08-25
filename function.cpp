#include <cstdio>
#include <iostream>
#include <stdexcept>
#include <string>
#include <exception>      
#include "function.h"

struct tree {
    token* _token;

    tree* l_descendant;
    tree* r_descendant;
};

tree* create_tree()
{
    tree* _tree;
    _tree = new tree;

    _tree->_token = NULL;
    _tree->l_descendant = NULL;
    _tree->r_descendant = NULL;

    return _tree;
}
const std::vector<token*> input()
{
    std::string s;
    std::vector<token*> v;
    while (true) {
        try {
            std::cout << "errors: operation + ^, example: 7+^4, numb + operation + operation, example 3--, log-numb, example log-2";
            std::cout << "\noperetions: +, -, /, *, %, sin, cos, tg, ctg, ^, sqrt, ln, log(10), !, ()\n";
            std::cout << "input string: ";
            std::cin >> s;
            comma_change(s);
            v = parse(s);
            change_unary_plus_minus(v);
            correctly_bracket(v);
            correctly_string(v);
            break;
        }
        catch (std::exception& e) {
            std::cerr << "Caught: " << e.what() << std::endl;
            std::cerr << "Type: " << typeid(e).name() << std::endl;
        }
    }
    return v;
}

void create_node_l(tree*& _tree) {
    tree* tmp;
    tmp = new tree;
    tmp->_token = NULL;
    _tree->l_descendant = tmp;
}
void create_node_r(tree*& _tree) {
    tree* tmp;
    tmp = new tree;
    tmp->_token = NULL;
    _tree->r_descendant = tmp;
}

const std::vector <token*> registered_token{
    new sin_token(),
    new cos_token(),
    new tg_token(),
    new ctg_token(),
    new pow_token(),
    new factorial_token(),
    new sqrt_token(),
    new natural_log_token(),
    new ten_log_token(),
    new operation_multiply_token(),
    new operation_share_token(),
    new remainder_of_the_division(),
    new operation_plus_token(),
    new operation_minus_token(),
    new round_left_bracket_token(),
    new round_right_bracket_token(),
    new number_token()
};
std::vector<token*> parse(std::string line) {

    std::vector<token*> result;
    while (!line.empty()) {
        token* t = nullptr;
        for (auto token : registered_token) {
            t = token->parse(line);
            if (t) {
                break;
            }
        }
        if (t) {
            result.push_back(t);
        }
        else {
            std::string msg = "Failed to parse: ";
            msg += line;
            throw std::logic_error(msg);
        }
    }
    return result;
}


void skip_brackets(const std::vector<token*>& v, int& ind) {
    std::vector<token*> stack;
    do {
        if (v[ind]->type_token() == "right bracket") {
            stack.push_back(v[ind]);
        }
        if (v[ind]->type_token() == "left bracket") {
            right_bracket* ch = dynamic_cast<right_bracket*>(stack[stack.size() - 1]);
            left_bracket* last_bracket = dynamic_cast<left_bracket*>(v[ind]);
            if (last_bracket->check_correctly_bracket(ch)) {
                stack.pop_back();
            }
            else {
                throw std::logic_error("no correctly bracket!");
            }
        }
        if (ind > 0)
            ind--;
    } while (stack.size() != 0);
}
unsigned int search_minimal_prtiority(const std::vector<token*>& v) {
    for (int i = v.size() - 1; i > 0; i--) {
        if (v[i]->type_token() == "right bracket")
            skip_brackets(v, i);
        if (v[i]->type_token() == "binary operation: minimal priority")
            return i;
    }
    return 0;
}
unsigned int search_middle_priority(const std::vector<token*>& v) {
    for (int i = v.size() - 1; i > 0; i--) {
        if (v[i]->type_token() == "right bracket")
            skip_brackets(v, i);
        if (v[i]->type_token() == "binary operation: middle priority")
            return i;
    }
    return 0;
}
unsigned int search_max_priority(const std::vector<token*>& v) {
    for (int i = v.size() - 1; i > 0; i--) {
        if (v[i]->type_token() == "right bracket")
            skip_brackets(v, i);
        if (v[i]->type_token() == "binary operation: max priority")
            return i;
    }
    return 0;
}
unsigned int search_unary_operation(const std::vector<token*>& v) {
    for (int i = v.size() - 1; i > 0; i--) {
        if (v[i]->type_token() == "right bracket")
            skip_brackets(v, i);
        if (v[i]->type_token() == "unary operation")
            return i;
    }
    return 0;
}
unsigned int search_index_minimal_priority_operation(const std::vector<token*>& v) {
    if (v.size() == 1)
        return 0;
    unsigned int ind = search_minimal_prtiority(v);
    if (ind == 0)
        ind = search_middle_priority(v);
    if (ind == 0)
        ind = search_max_priority(v);
    if (ind == 0)
        ind = search_unary_operation(v);
    return ind;
}


bool check_delete_bracket(const std::vector<token*>& v) {
    unsigned int count = 0;
    for (int i = v.size() - 1; i > 0; i--) {
        if (v[i]->type_token() == "right bracket") {
            count++;
            skip_brackets(v, i);
        }
    }
    if (count == 1) {
        return true;
    }
    return false;
}
void delete_brackets(std::vector<token*>& v) {
    if (v[0]->type_token() == "left bracket" && v[v.size() - 1]->type_token() == "right bracket" && check_delete_bracket(v)) {
        v.erase(v.begin());
        v.pop_back();
    }
}


tree* fill_tree_binary(std::vector<token*>& v, tree* _tree, const unsigned int& index) {
    std::vector<token*> v_l;
    std::vector<token*> v_r;

    for (int i = 0; i < index; i++) {
        v_l.push_back(v[i]);
    }
    for (int i = index + 1; i < v.size(); i++) {
        v_r.push_back(v[i]);
    }

    create_node_l(_tree);
    if (v_l.size() == 1) {
        _tree->l_descendant->_token = v_l[0];
        _tree->l_descendant->l_descendant = NULL;
        _tree->l_descendant->r_descendant = NULL;

    }
    else {
        fill_tree(v_l, _tree->l_descendant);
    }

    create_node_r(_tree);
    if (v_r.size() == 1) {
        _tree->r_descendant->_token = v_r[0];
        _tree->r_descendant->l_descendant = NULL;
        _tree->r_descendant->r_descendant = NULL;
    }
    else {
        fill_tree(v_r, _tree->r_descendant);
    }
    v_l.clear();
    v_r.clear();

    return _tree;
}
tree* fill_tree_unary(std::vector<token*>& v, tree* _tree, const unsigned int& index) {
    std::vector<token*> v_l;
    _tree->r_descendant = NULL;

    if (index == 0) { //index == 0   => this is sqrt(), sin(), cos()...
        for (int i = 1; i < v.size(); i++) {
            v_l.push_back(v[i]);
        }
    }
    else { // ...!
        for (int i = 0; i < v.size() - 1; i++) {
            v_l.push_back(v[i]);
        }
    }
    delete_brackets(v_l);
    create_node_l(_tree);
    if (v_l.size() == 1) {
        _tree->l_descendant->_token = v_l[0];
        _tree->l_descendant->l_descendant = NULL;
        _tree->l_descendant->r_descendant = NULL;
    }
    else {
        fill_tree(v_l, _tree->l_descendant);
    }
    v_l.clear();
    return _tree;
}
tree* fill_tree(std::vector<token*>& v, tree* _tree) {
    delete_brackets(v);

    unsigned int index = search_index_minimal_priority_operation(v);    if (index == 0 && v[index]->type_token() != "unary operation") {
        _tree->_token = v[0];
        return _tree;
    }

    _tree->_token = v[index];
    if (v[index]->type_token() == "binary operation: minimal priority" || v[index]->type_token() == "binary operation: middle priority" || v[index]->type_token() == "binary operation: max priority") {
        fill_tree_binary(v, _tree, index);
    }
    if (v[index]->type_token() == "unary operation") {
        fill_tree_unary(v, _tree, index);
    }
    return _tree;
}

double compute(const tree* _tree) {
    if (_tree->l_descendant == NULL && _tree->r_descendant == NULL) {
        number_token* t = dynamic_cast<number_token*>(_tree->_token);
        return t->get_value();
    }
    else if (_tree->l_descendant != NULL && _tree->r_descendant == NULL) {
        unary_operation* t = dynamic_cast<unary_operation*>(_tree->_token);
        if (t) {
            return t->compute_value_unary(compute(_tree->l_descendant));
        }
    }
    else  if (_tree->l_descendant != NULL && _tree->r_descendant != NULL) {
        binary_operation* t = dynamic_cast<binary_operation*>(_tree->_token);
        if (t) {
            return t->compute_value_binary(compute(_tree->l_descendant), compute(_tree->r_descendant));
        }
    }
    else
        throw std::logic_error("you entered incorrectly!");
}


void comma_change(std::string& line) {
    for (int i = 0; i < line.size(); i++) {
        if (line[i] == ',')
            line[i] = '.';
    }
}
void change_unary_plus_minus(std::vector<token*>& v) {
    if (v[0]->type_token() == "binary operation: minimal priority") {
        v.emplace(v.begin(), new number_token(0));
    }
    for (int i = 0; i < v.size(); i++) {
        if (v[i]->type_token() == "binary operation: minimal priority" && (v[i - 1]->type_token() == "binary operation: minimal priority" || v[i - 1]->type_token() == "binary operation: middle priority")) {
            v.emplace(v.begin() + i, new round_left_bracket_token);
            v.emplace(v.begin() + i + 1, new number_token(0));
            v.emplace(v.begin() + i + 4, new round_right_bracket_token);
        }
    }
}

bool correctly_bracket(const std::vector<token*>& v) {
    std::vector<token*> stack;
    for (int i = 0; i < v.size(); i++) {
        if (v[i]->type_token() == "left bracket") {
            stack.push_back(v[i]);
        }
        if (v[i]->type_token() == "right bracket") {
            if (stack.size() == 0) {
                throw std::logic_error("no correctly bracket!");
            }
            left_bracket* ch = dynamic_cast<left_bracket*>(stack[stack.size() - 1]);
            right_bracket* last_bracket = dynamic_cast<right_bracket*>(v[i]);
            if (ch->check_correctly_bracket(last_bracket)) {
                stack.pop_back();
            }
            else {
                throw std::logic_error("no correctly bracket!");
            }
        }
    }
    if (stack.size() == 0) {
        return true;
    }
    return false;
}
void correctly_string(const std::vector<token*>& v) {
    if (v[v.size() - 1]->type_token() == "binary operation: minimal priority" || v[v.size() - 1]->type_token() == "binary operation: middle priority" || v[v.size() - 1]->type_token() == "binary operation: max priority")
        throw std::logic_error("error: operation at the end");

    for (int i = v.size() - 1; i > 0; i--) {
        if (v[i - 1]->type_token() == "binary operation: minimal priority" && v[i]->type_token() == "binary operation: middle priority") {
            throw std::domain_error("error: incorrect sequence of operations");
        }
        if (v[i - 1]->type_token() == "left bracket" && (v[i]->type_token() == "binary operation: minimal priority" || v[i]->type_token() == "binary operation: middle priority")) {
            throw std::domain_error("error: incorrect sequence of operations");
        }
        if (v[i - 1]->type_token() == "right bracket" && v[i]->type_token() == "number") {
            throw std::logic_error("error: incorrect sequence of operations");
        }
        if (v[i - 1]->type_token() == "number" && v[i]->type_token() == "left bracket") {
            throw std::logic_error("error: incorrect sequence of operations");
        }
        if ((v[i - 1]->type_token() == "binary operation: minimal priority" || v[i - 1]->type_token() == "binary operation: middle priority") && v[i]->type_token() == "unary operation") {
            throw std::logic_error("error: incorrect sequence of operations");
        }
        if (v[i - 1]->type_token() == "binary operation: minimal priority" && v[i]->type_token() == "binary operation: minimal priority") {
            throw std::domain_error("error: incorrect sequence of operations");
        }
        if (v[i - 1]->type_token() == "binary operation: max priority" && (v[i]->type_token() == "binary operation: middle priority" || v[i]->type_token() == "binary operation: minimal priority")) {
            throw std::domain_error("error: incorrect sequence of operations");
        }
    }
}

void clear_tree(tree* _tree) {
    if (_tree->l_descendant != NULL) {
        clear_tree(_tree->l_descendant);
    }
    if (_tree->r_descendant != NULL) {
        clear_tree(_tree->r_descendant);
    }
    delete _tree;
}
