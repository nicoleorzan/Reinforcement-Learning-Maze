#include "Experiment.h"
#include <iostream>
#include "stdlib.h"

Experiment::Experiment(int n_r){ 
    n_runs = n_r;
};

void Experiment::single_run_Boltzmann(Agent &ag, Environment &env, double T){

    int a = 0, a_new = 0;
    int s = 0, s_new = 0;
    std::vector<int> allow_act;
    double rew = 0;

    s = ag.get_initial_state();
    //std::cout<<"initial state="<<s<<std::endl; 
    allow_act = env.allowed_actions(s);
    /*std::cout<<"allowed actions:"<<std::endl; 
    for (std::vector<int>::const_iterator i = allow_act.begin(); i != allow_act.end(); ++i)
        std::cout << *i << ' ';
    std::cout<<std::endl;*/
    a = ag.agent_Boltzmann_exploration(s, allow_act, T);  
    //std::cout<<"chosen initial action="<<a<<std::endl;
    int i=1;
    while (i){

        rew = env.sample_reward(s);
        if (s == env.get_final_state()){
            //std::cout<<"s="<<s<<std::endl;
            ag.SARSA_final(s, a, rew);
            break;
        }

        s_new = env.next_state(s, a);
        //std::cout<<"s="<<s_new<<std::endl; 
        allow_act = env.allowed_actions(s_new);
        /*for (std::vector<int>::const_iterator i = allow_act.begin(); i != allow_act.end(); ++i)
            std::cout << *i << ' ';
        std::cout<<std::endl;*/
        a_new = ag.agent_Boltzmann_exploration(s, allow_act, T); 
        ag.SARSA(s, a, rew, s_new, a_new);
        a = a_new;
        s = s_new;       
        i += 1;
        //std::cout<<"chosen action="<<a<<std::endl;
    }
};

void Experiment::single_run(Agent &ag, Environment &env){

    int a = 0, a_new = 0;
    int s = 0, s_new = 0;
    std::vector<int> allow_act;
    double rew = 0;

    s = ag.get_initial_state();
    allow_act = env.allowed_actions(s);
    a = ag.agent_step_epsilon_greedy(s, allow_act); 
    /*std::cout<<"initial state="<<s<<std::endl; 
    std::cout<<"sx="<<s%8<<", sy="<<s/8<<std::endl; 
    std::cout<<"allowed actions:"<<std::endl; 
    for (std::vector<int>::const_iterator i = allow_act.begin(); i != allow_act.end(); ++i)
        std::cout << *i << ' ';
    std::cout<<std::endl;
    std::cout<<"initial action="<<a<<std::endl; */
    int i=1;
    while (i){

        rew = env.sample_reward(s);
        if (s == env.get_final_state()){
            //std::cout<<"s="<<s<<std::endl;
            ag.SARSA_final(s, a, rew);
            break;
        }

        s_new = env.next_state(s, a);
        allow_act = env.allowed_actions(s_new);
        a_new = ag.agent_step_epsilon_greedy(s_new, allow_act);
        ag.SARSA(s, a, rew, s_new, a_new);
        a = a_new;
        s = s_new;       
        i += 1;
        /*std::cout<<"s="<<s<<std::endl; 
        std::cout<<"sx="<<s%8<<", sy="<<s/8<<std::endl; 
        for (std::vector<int>::const_iterator i = allow_act.begin(); i != allow_act.end(); ++i)
            std::cout << *i << ' ';
        std::cout<<std::endl;
        std::cout<<"a="<<a<<std::endl; */
    }
};

void Experiment::more_runs(Agent &ag, Environment &env){

    for (int run_number=0; run_number<n_runs; run_number++){
        //std::cout<<"\nRun="<<run_number<<std::endl;
        this->single_run(ag, env);
    }
};

void Experiment::more_Boltzmann_exploration_runs(Agent &ag, Environment &env, double T){

    for (int run_number=0; run_number<n_runs; run_number++){
        //std::cout<<"\nRun="<<run_number<<std::endl;
        this->single_run_Boltzmann(ag, env, T);
    }
};


void Experiment::evaluation(Agent &ag, Environment &env){

    int s = 0, a = 0;
    std::vector<int> allow_act;

    s = ag.get_initial_state();
    allow_act = env.allowed_actions(s);
    a = ag.agent_step_epsilon_greedy(s, allow_act); 
    std::cout<<"s="<<s<<", a="<<a<<std::endl;  
    int i=1;
    while (i){

        if (s == env.get_final_state()){
            break;
        }
        s = env.next_state(s, a);
        allow_act = env.allowed_actions(s);
        a = ag.agent_step_epsilon_greedy(s, allow_act);     

        std::cout<<"s="<<s<<", a="<<a<<std::endl;    
        i += 1;
    }

}