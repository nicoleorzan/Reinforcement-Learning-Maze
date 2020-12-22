#ifndef ENVIRONMENT
#define ENVIRONMENT


// let's start working on a fixed maze
class Environment{

    public:
    int N; // size of maze
    int final_state; // final state defined by user
    int *maze;

    Environment(int n, int fs);

    ~Environment();

    double sample_reward(int state);

    int next_state(int state, int action);

    void fill_maze();

    void display_maze();

};


#endif