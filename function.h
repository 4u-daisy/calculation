#pragma once
#include <vector>
#include "token.h"

struct tree;

tree* create_tree();
const std::vector<token*> input();
void create_node_l(tree*& _tree);
void create_node_r(tree*& _tree);

std::vector<token*> parse(std::string line);

void skip_brackets(const std::vector<token*>& v, int& ind);
unsigned int search_minimal_prtiority(const std::vector<token*>& v);
unsigned int search_middle_priority(const std::vector<token*>& v);
unsigned int search_unary_operation(const std::vector<token*>& v);
unsigned int search_index_minimal_priority_operation(const std::vector<token*>& v);

unsigned int search_index_minimal_priority_operation(const std::vector<token*>& v);

bool check_delete_bracket(const std::vector<token*>& v);
void delete_brackets(std::vector<token*>& v);

tree* fill_tree_binary(std::vector<token*>& v, tree* _tree, const unsigned int& index);
tree* fill_tree_unary(std::vector<token*>& v, tree* _tree, const unsigned int& index);
tree* fill_tree(std::vector<token*>& v, tree* _tree);
double compute(const tree* _tree);
void comma_change(std::string& line);
void change_unary_plus_minus(std::vector<token*>& v);
bool correctly_bracket(const std::vector<token*>& v);
void correctly_string(const std::vector<token*>& v);
void clear_tree(tree* _tree);