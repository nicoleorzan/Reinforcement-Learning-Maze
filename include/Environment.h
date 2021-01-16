#ifndef ENVIRONMENT
#define ENVIRONMENT
#include <vector>

// let's start working on a fixed maze
class Environment{

    public:
    int N;
    int final_state; // final state defined by user
    int *maze;
    std::vector<int> walls;

    Environment(int n, int fs, std::vector<int> w);

    ~Environment();

    double reward_func1(int state);

    double reward_func2(int state);

    double sample_reward(int state, int reward_strategy);

    int next_state(int state, int action);

    int random_start();

    int get_final_state();

    void set_final_state(int fs);

    std::vector<int> allowed_actions(int state);

    void fill_maze();

    void display_maze();

    void print_policy(double *Q);

};


#endif