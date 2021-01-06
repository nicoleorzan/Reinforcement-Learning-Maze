#ifndef ENVIRONMENT
#define ENVIRONMENT
#include <vector>

// let's start working on a fixed maze
class Environment{

    public:
    int N; // size of maze
    int initial_state;
    int final_state; // final state defined by user
    int *maze;

    Environment(int n, int is, int fs);

    ~Environment();

    double sample_reward(int state);

    int next_state(int state, int action);

    int random_start();

    int get_final_state();

    std::vector<int> allowed_actions(int state);

    void fill_maze();

    void display_maze();

    void print_policy(double *Q);

};


#endif