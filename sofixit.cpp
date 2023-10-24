#include <iostream>
#include <vector>
#include <stack>

long long material(std::vector<int> spaceship){
    if(spaceship.size() == 0)
        return 0;
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
            if(largest_to_right[i] > i){
                long long volume = (long long)(largest_to_right[i] - i - 1) * spaceship[largest_to_right[i]] - (prefix_sum[largest_to_right[i]-1] - prefix_sum[i]);
                water += volume;
                // jump to the largest element to the right
                i = largest_to_right[i] - 1;
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