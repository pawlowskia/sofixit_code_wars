#include <iostream>
#include <vector>

long long material_brute(std::vector<int> spaceship){
    // O(n^2)
    if(spaceship.size() == 0)
        return 0;

    int highest = 0;
    for(int i = 0; i < spaceship.size(); i++)
        highest = std::max(highest, spaceship[i]);

    long long water = 0;
    // shoot beams from left to right for each height
    for(int i = highest; i >= 0; i--){
        // left beam 
        int L = 0;
        while(spaceship[L] < i && L < spaceship.size())
            L++;

        // right beam
        int R = spaceship.size() - 1;
        while(spaceship[R] < i && L >= 0)
            R--;

        // now we know that the water cannot exist where the beams are, otherwise it would flow out,
        // so we can calculate the volume of water between the beams
        // and substract the total volume of the spaceship's parts in between
        if (L > R) continue;
        long long volume = (long long)(R - L - 1);
        if(volume <= 0) continue;

        for(int j = L + 1; j < R; j++){
            if (spaceship[j] >= i)
                volume--;
        }
        water += volume;
    }
    return water;
}