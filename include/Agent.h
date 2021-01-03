#ifndef AGENT
#define AGENT

#include <vector>

class Agent{

    public:
        int n_actions;
        int n_states;
        double epsilon;
        double learning_rate;
        double discount_rate;
        int starting_state;

        double *Q;
        double *QA;
        double *QB;
        double *Q_temperature;

    Agent(int n_stat, int n_act, double e, double l, double d, int s);

    ~Agent();

    int get_initial_state();

    int agent_step_epsilon_greedy(int state, std::vector<int> allowed_actions);
    
    int agent_Boltzmann_exploration(int state, std::vector<int> allowed_actions, double T);

    int agent_epsilon_greedy_QA_QB(int state, std::vector<int> allowed_actions);

    void SARSA(int s, int a, double reward, int s_next, int a_next);

    void Update_Q_final(int s, int a, double reward);

    void Update_QA_final(int s, int a, double reward);

    void Update_QB_final(int s, int a, double reward);

    void QL(int s, int a, double reward, int s_next, std::vector<int> allowed_actions);

    void update_QA(int s, int a, double reward, int s_next, std::vector<int> allowed_actions);

    void update_QB(int s, int a, double reward, int s_next, std::vector<int> allowed_actions);

    void print_Q();

    void initialize_Q();
};

#endif