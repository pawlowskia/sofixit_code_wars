#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include "sofixit.cpp"
#include "brute.cpp"

#define NUM_TESTS 100

int main() {
    for(int i = 1; i <= NUM_TESTS; i++) {
        std::ifstream test_file("./tests/test" + std::to_string(i) + ".txt");

        int N;
        test_file >> N;

        std::vector<int> spaceship(N);
        for(int j = 0; j < N; j++) {
            test_file >> spaceship[j];
        }

        test_file.close();

        int material_result = material(spaceship);
        int material_brute_result = material_brute(spaceship);
        
        std::cout << "test" << i << ": ";
        if(material_result == material_brute_result) {
            std::cout << "ok" << std::endl;
        } else {
            std::cout << "error, material outputed: " << material_result << " and brute outputed: " \
            << material_brute_result << std::endl;
        }
    }
    return 0;
}