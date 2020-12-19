#ifndef AGENT
#define AGENT

class Agent{

    public:
        int n_actions;
        int n_states;
        double epsilon;
        double learning_rate;
        double discount_rate;

        double *Q;

    Agent(int n_stat, int n_act, double e, double l, double d);

    ~Agent();

    //void agent_init();

    int agent_start(int state);

    int agent_step_epsilon_greedy(double reward, int state);

    void agent_end(double reward);
};

#endif