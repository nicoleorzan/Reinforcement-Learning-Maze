#ifndef AGENT
#define AGENT
#include<map>

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
        double *Q_temperature;
        double *pii;
        double *preferences;
        double *UCB_values;
        int *nt;

        //int *dyna_reward;
        //int *dyna_next_state;

        double avg_reward = 0;

        std::vector<int> observed_states;
        std::multimap<int, std::vector<int>> observed_actions_in_states;

        //std::multimap<int, std::multimap<int, double>> model;
        
    Agent(int n_stat, int n_act, double e, double l, double d, int s, double lam);

    ~Agent();

    int get_initial_state();

    void set_initial_state(int s);

    void set_epsilon(double e);
    
    int epsilon_greedy(int state, std::vector<int> allowed_actions, int algorithm);

    int boltzmann_exploration(int state, std::vector<int> allowed_actions, int algorithm, double T);

    int GBA(int state, std::vector<int> allowed_actions, int algorithm);
    
    void update_action_preferences(double r, int state, int a);

    void update_avg_reward(int n, double r);

    int UCB(int state, std::vector<int> allowed_actions, int algorithm, int t, double c);

    int choose_max(int state);

    void update_Q_SARSA(int s, int a, double reward, int s_next, int a_next);

    void update_Q_Learning(int s, int a, double reward, int s_next,  std::vector<int> allowed_actions);

    void update_Q_final(int s, int a, double reward);

    void update_QA_QB(int s, int a, double reward, int s_next, std::vector<int> allowed_actions, int update_index);

    void update_QA_QB_final(int s, int a, double reward);

    void update_V(int s, double reward, int s_next);

    void update_QV(int s, int a, double reward, int s_new);  
    
    void update_QV_final(int s, int a, double reward);

    void update_model(int s, int a, double rew, int s_next);

    double* get_Q();

    double* get_QA();

    double* get_QB();

    void print(double *matrix, int n_rows, int n_cols);

    void print_nt();

    void initialize_Q();

    void initialize_QA_QB();

    void initialize_V();

    //void return_observed_state();

};

#endif
