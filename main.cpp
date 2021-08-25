#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>
#include "token.h"
#include "function.h"
#include <exception>   

int main() {
    int flag = 0;
    do {
        std::vector<token*> v = input();
        tree* _tree = create_tree();

        fill_tree(v, _tree);
        double result = 0;
        try {
            result = compute(_tree);
        }
        catch (std::exception& e) {
            std::cerr << "Caught: " << e.what() << std::endl;
            std::cerr << "Type: " << typeid(e).name() << std::endl;
        }
        std::cout << "\n" << result;

        clear_tree(_tree);
        v.clear();

        std::cout << "\nYou want to contine the program and input new data?\nif yes, enter 1, else 0    ";
        std::cin >> flag;
    } while (flag);
	return 0;
}