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
        double delta;
        double lambda;
        int starting_state;

        double *Q;
        double *V;
        double *et;
        double *QA;
        double *QB;
        //double *Q_temperature;

    Agent(int n_stat, int n_act, double e, double l, double d, int s, int lam);

    ~Agent();

    int get_initial_state();

    int agent_step_epsilon_greedy(int state, std::vector<int> allowed_actions, int algorithm);

    void update_Q_SARSA(int s, int a, double reward, int s_next, int a_next);

    void update_Q_Learning(int s, int a, double reward, int s_next,  std::vector<int> allowed_actions);

    void update_Q_final(int s, int a, double reward);

    void update_QA_QB(int s, int a, double reward, int s_next, std::vector<int> allowed_actions, int update_index);

    void update_QA_QB_final(int s, int a, double reward);

    void update_QV(int s, int a, double reward, int s_new);  
    
    void update_QV_final(int s, int a, double reward);


    void print_Q();

    void initialize_Q();

    void initialize_QA_QB();

    void initialize_V();

    //int agent_Boltzmann_exploration(int state, std::vector<int> allowed_actions, double T);
};

#endif