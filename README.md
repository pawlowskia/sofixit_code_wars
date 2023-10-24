# sofixit_code_wars

## contents
`sofixit.cpp` contains my solution to the problem 

`brute.cpp` contains a brute force solution to the problem, created for testing purposes

`testing.cpp` is a simple script to compare the two solutions on randomly generated inputs

`test_gen.py` is a script to generate random inputs for testing

## problem
### brute (brute.cpp)
It shoots 'lasers' or 'beams' from both sides for every height. 

Where beams stop, we know that for this height there won't be any liquid it their places since it would flow out. 

Then we count the number of bricks that are left on this height and substract that from the overal length of the spaceship.

*Complexity: O(n^2)*

### the solution (sofixit.cpp)
We make an array where for each element we store the next bigger element to the right of it, and -1 if there is none. 

We also make the prefix sum table, and an array where a[i] is the largest element to the right of spaceship[i], not necessarily bigger one though.

Then we can iterate over the spaceship and for each element we can find the next bigger element to the right of it in O(1) time. 

If such element is found, we can find the sum of all elements between them in O(1) time using the prefix sum table. 

Then we can substract the sum from the length of the spaceship and add the number of bricks that are left on this height.
Note that a jump is made to the next bigger element, so we don't count the bricks that are left on this height twice.

If there is no such element found, we look at the largest element to the right of it.

*Complexity: O(n)*

## testing
Generate random inputs using 
`python3 test_gen.py`

Run the testing script using
`g++ testing.cpp -o testing && ./testing`
