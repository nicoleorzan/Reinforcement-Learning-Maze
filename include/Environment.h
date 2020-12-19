#ifndef ENVIRONMENT
#define ENVIRONMENT


// let's start working on a fixed maze
class Environment{

    public:
    int N; // size of maze
    int final_state; // final state defined by user

    Environment(int n, int fs);

    double sample_reward(int state);

    int sample_next_state(int state, int action);

};


#endif