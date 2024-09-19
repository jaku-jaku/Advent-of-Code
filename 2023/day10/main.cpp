/* [ Advent of Code - Day 8 ]
 *
 * author: Jack (Jianxiang) Xu
 * Date of completion: Sept. 18, 2024
 *
 * Debug: Debug prints can be enabled by flagging `ENABLE_DEBUG_PRINT` to `ENABLE`
 */

#include <fstream>  // ifstream
#include <sstream>  // getfile
#include <string> 
#include <iostream> // cerr
#include <unordered_map>

/* Feature Flag */
#define ENABLE                      (1)
#define DISABLE                     (0)
#ifndef ENABLE_DEBUG_PRINT
#   define ENABLE_DEBUG_PRINT       (DISABLE) // USER: debugging mode
#endif // !ENABLE_DEBUG_PRINT

/* MACRO - Printing */
#define PRINT_ERROR_IN_RED(message) (std::cerr << "\033[31m [ERROR] " << (message) << "\033[0m" << std::endl);
#if ENABLE_DEBUG_PRINT
#   define DEBUG_PRINT(message)     (std::cerr << "\033[33m [DEBUG] " << (message) << "\033[0m" << std::endl);
#else
#   define DEBUG_PRINT(message)     // DO NOTHING!
#endif // ENABLE_DEBUG_PRINT

/*
        N
    W       E
        S
    
    .-> +1
    |
    +1
*/
struct vec {
    int x = 0;
    int y = 0;
    
    inline std::string to_string(){
        return "(" + std::to_string(x) + "," + std::to_string(y) + ")";
    }
    
    inline vec operator+ (vec other){
        return vec(other.x+x, other.y+y);
    }
    
    inline bool is_inbound(const size_t w, const size_t h){
        return (0 <= x && x < int(w)) && (0 <= y && y < int(h));
    }
};

// SO2 x R2 :
using Dir = vec;
using Pos = vec;

// Direction:
constexpr Dir NORTH = { 0, -1};
constexpr Dir SOUTH = { 0, +1};
constexpr Dir EAST  = {+1,  0};
constexpr Dir WEST  = {-1,  0};
constexpr Dir INVALID = {-1,  -1};

bool is_reversed(const Dir& d1, const Dir& d2) {
    return (d1.x == - d2.x) && (d1.y == - d2.y);
}

// Symbol to direction pair
std::unordered_map<char, std::pair<Dir, Dir>> direction_symbols = {
    {'|', {NORTH, SOUTH}},
    {'-', { EAST,  WEST}},
    {'L', {NORTH,  EAST}},
    {'J', {NORTH,  WEST}},
    {'7', {SOUTH,  WEST}},
    {'F', {SOUTH,  EAST}},
};
#define GROUND ('.')
#define STARTS ('S')

int main() {
    std::ifstream infile("./test.txt");
    std::string line;
    std::vector<std::string> map;
    
    // 0. load the map
    while (std::getline(infile, line))
    {        
        map.push_back(line);
        // DEBUG_PRINT(line);
    }
    
    // 1. finding the starting point
    const size_t H = map.size();
    const size_t W = map[0].size();
    
    Pos start{-1,-1};
    for (size_t j = 0; j < H; j ++)
    {
        for (size_t i = 0; i < W; i ++)
        {
            if (map[j][i] == STARTS)
            {
                start.x = i;
                start.y = j;
                DEBUG_PRINT("Found Starting Point: " + start.to_string());
                break;
            }
        }
    }
    
    if (start.x < 0 && start.y < 0) {
        PRINT_ERROR_IN_RED("X- Invalid Starting Point: " + start.to_string());
        return EXIT_FAILURE;
    }
    
    // 2. traversing from the starting point 
    const std::vector<Dir> start_directions = {EAST, SOUTH, WEST, NORTH};
    std::vector<Pos> max_trajectory;
    
    for (Dir dir: start_directions)
    {
        // DEBUG_PRINT(dir.to_string());
        std::vector<Pos> trajectory;
        Pos next_pos = start + dir;
        
        if (!next_pos.is_inbound(W, H)) 
        {
            DEBUG_PRINT("Index Out of Range");
            continue;
        }
        
        char next_char = map[next_pos.y][next_pos.x];
        
        while (next_char != STARTS && next_char != GROUND)
        {
            if (direction_symbols.contains(next_char))
            {
                DEBUG_PRINT(next_char);
                DEBUG_PRINT(dir.to_string());
                
                std::pair<Dir, Dir> next_dirs = direction_symbols[next_char];
                DEBUG_PRINT(next_dirs.first.to_string());
                DEBUG_PRINT(next_dirs.second.to_string());
                // determine the next move:
                Dir next_dir = INVALID;
                DEBUG_PRINT("stepping " + next_char);
                if (!is_reversed(dir, next_dirs.first))
                    next_dir = next_dirs.first;
                else if (!is_reversed(dir, next_dirs.second))
                    next_dir = next_dirs.second;
                else{
                    PRINT_ERROR_IN_RED("Invalid direction!");
                    return EXIT_FAILURE;
                }
                trajectory.push_back(next_pos);
                // update the move:
                dir = next_dir; // cache for the next move
                next_pos = next_pos + next_dir;
                // inbound check:
                if (!next_pos.is_inbound(W, H)) 
                {
                    DEBUG_PRINT("Index Out of Range");
                    break;
                }
                next_char = map[next_pos.y][next_pos.x];
            }
            else
            {
                break; // Hit the wall
            }
        }
        
        if (next_char == STARTS)
        {
            DEBUG_PRINT("Reached the goal!");
            if (max_trajectory.size() < trajectory.size())
            {
                max_trajectory = trajectory;
            }
        }
        else
        {
            DEBUG_PRINT("Not the goal!");
        }
    }
    
    // 3. print out the distance from the furthest point to the starting point
    DEBUG_PRINT(max_trajectory.size());
    std::cout << "> Furthest Distance is: " << std::ceil(max_trajectory.size()/2) + 1 << std::endl;
    
    return EXIT_SUCCESS;
}