#ifndef AGENT
#define AGENT

class Agent{

    public:
        int n_actions;
        int n_states;
        double epsilon;
        double learning_rate;
        double discount_rate;
        int starting_state;

        double *Q;

    Agent(int n_stat, int n_act, double e, double l, double d, int s);

    ~Agent();

    int get_initial_state();

    int agent_start();

    int from_ij_to_idx(int state_i, int state_j);

    int agent_step_epsilon_greedy(int state);

    void SARSA(int s, int a, double reward, int s_next, int a_next);

    void SARSA_final(int s, int a, double reward);
};

#endif