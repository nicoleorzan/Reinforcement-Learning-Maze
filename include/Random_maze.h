#ifndef R_MAZE
#define R_MAZE
#include <vector>

class Random_maze{

    public:
    int N; // size of maze
    int *maze;
    int initial_state;
    int final_state; // final state defined by user

    Random_maze(int n, int is, int fs);

    ~Random_maze();

    //void display_maze();

    std::vector<int> create();

    std::vector<int> state_to_state(int init_x, int init_y, int fin_x, int fin_y);

};


#endif