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

    int agent_start(int state);

    int from_ij_to_idx(int state_i, int state_j);

    int agent_step_epsilon_greedy(double reward, int state);

    void agent_end(double reward);

    void SARSA(int s, int s_next, int a, int a_next, double reward);

    void SARSA_final(int s, int a, double reward);
};

#endif