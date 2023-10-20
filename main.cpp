#include <iostream>
#include <vector>
#include <stack>

long long material(std::vector<int> spaceship);

int main(){
    std::vector<int> spaceship;
//    spaceship.push_back(4);
//    spaceship.push_back(3);
//    spaceship.push_back(4);
//    spaceship.push_back(5);
//    spaceship.push_back(2);
//    spaceship.push_back(1);
//    spaceship.push_back(0);

    //  spaceship.push_back(8);
    //  spaceship.push_back(1);
    //  spaceship.push_back(3);


    // material([6, 4, 2, 0, 3, 2, 0, 3, 1, 4, 5, 3, 2, 7, 5, 3, 0, 1, 2, 1, 3, 4, 6, 8, 1, 3])
   int test[] = {6, 4, 2, 0, 3, 2, 0, 3, 1, 4, 5, 3, 2, 7, 5, 3, 0, 1, 2, 1, 3, 4, 6, 8, 1, 3};
   for(int i = 0; i < 26; i++)
       spaceship.push_back(test[i]);

    std::cout << material(spaceship);
    return 0;
}

long long material(std::vector<int> spaceship){
    std::stack<std::pair<int, int> > s;
    std::vector<int> result(spaceship.size(), -1);
    s.push(std::make_pair(spaceship[0], 0));

    // generate next bigger element for each element in the spaceship
    for(int i = 1; i < spaceship.size(); i++){
        if(s.empty()){
            s.push(std::make_pair(spaceship[i], i));
            continue;
        }

        while(!s.empty() && s.top().first <= spaceship[i]){
            result[s.top().second] = i;
            s.pop();
        }

        s.push(std::make_pair(spaceship[i], i));
    }

    // for (int i = 0; i < result.size(); i++)
    //     std::cout << result[i] << " ";

    // make prefix sum of the spaceship
    std::vector<int> prefix_sum(spaceship.size(), 0);
    prefix_sum[0] = spaceship[0];
    for(int i = 1; i < spaceship.size(); i++)
        prefix_sum[i] = prefix_sum[i-1] + spaceship[i];

    // make the largest to the right array
    std::vector<int> largest_to_right(spaceship.size(), -1);
    for(int largest = -1, i = spaceship.size() - 2; i >= 0; i--){
        if(spaceship[i+1] > largest){
            largest = spaceship[i+1];
            largest_to_right[i] = i+1;
        }
        else
            largest_to_right[i] = largest_to_right[i+1];
    }
    
    // calculate the volume of water
    long long water = 0;
    for(int i = 0; i < spaceship.size(); i++){
        // there is no next bigger element, water would flow to the end
        if(result[i] == -1){
            // std::cout << "result[i], i: " << result[i] << " " << i << " " << std::endl;
            // std::cout << "spaceship[i]: " << spaceship[i] << " " << std::endl;
            // std::cout << "largest_to_right[i]: " << largest_to_right[i] << std::endl;
            // calculate the volume of water between current element and the largest element to the right
            if(largest_to_right[i] != -1){
                long long volume = (long long)(largest_to_right[i] - i - 1) * spaceship[largest_to_right[i]] - (prefix_sum[largest_to_right[i]-1] - prefix_sum[i]);
                water += volume;
            }
            continue;
        }

        // calculate the volume of water between current element and next bigger element
        long long volume = (long long)(result[i] - i - 1) * spaceship[i] - (prefix_sum[result[i]-1] - prefix_sum[i]);
        water += volume;

        // make the jump to next bigger element
        i = result[i] - 1;
        // std::cout << "result[i], i: " << result[i] << " " << i << " " << std::endl;
        // std::cout << "spaceship[i]: " << spaceship[i] << " " << std::endl;
        // std::cout << "prefix_sum[result[i] - 1], prefix_sum[i]: " << prefix_sum[result[i]-1] << " " << prefix_sum[i] << std::endl;
    }
    return water;
}

