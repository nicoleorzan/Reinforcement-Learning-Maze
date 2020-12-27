#include "Random_maze.h"
#include <iostream>
#include <random>
#include <algorithm>


Random_maze::Random_maze(int n, int is, int fs){
    N = n;
    maze = new int[N*N];
    initial_state = is;
    final_state = fs; // if here the simulation terminates
    //create();
};

Random_maze::~Random_maze(){
    delete[] maze;
};

std::vector<int> Random_maze::state_to_state(int init_x, int init_y, int fin_x, int fin_y){

    std::vector<int> states_tmp;
    int ix = init_x;
    int iy = init_y;
    int fx = fin_x;
    int fy = fin_y;

    //std::cout<<ix<<", "<<iy<<", "<<fx<<", "<<fy<<std::endl;
    if (fin_x < init_x){
        for (int i=fx; i<ix; i++){
            states_tmp.push_back(iy*N+i);
            //std::cout<<"iy*N+i="<<iy*N+i<<std::endl;
        }
    } else {
        for (int i=ix; i<fx; i++){
            states_tmp.push_back(iy*N+i);
            //std::cout<<"iy*N+i="<<iy*N+i<<std::endl;
        }
    }

    if (fin_y < init_y){
        for (int j=fy; j<=iy; j++){
            states_tmp.push_back(j*N+fx);
            //std::cout<<"j*N+ix="<<j*N+fx<<std::endl;
        }
    } else {
        for (int j=iy; j<=fy; j++){
            states_tmp.push_back(j*N+fx);
            //std::cout<<"j*N+ix="<<j*N+fx<<std::endl;
        }
    }
    return states_tmp;
};


std::vector<int> Random_maze::create(){

    int init_y = initial_state/N;
    int init_x = initial_state%N;
    int fin_y = final_state/N;
    int fin_x = final_state%N;
    srand (time(NULL));
    /*std::cout<<"init_x="<<init_x<<"\n";
    std::cout<<"init_y="<<init_y<<"\n";
    std::cout<<"fin_x="<<fin_x<<"\n";
    std::cout<<"fin_y="<<fin_y<<"\n";
    */

    int step_x = N/8; 

    std::vector<int> states_x;
    std::vector<int> states_y;
    std::vector<int> states;

    states_x.push_back(init_x);
    states_y.push_back(init_y);

    int i_x = 0, i_y =0 ;
    while(i_x < N){
        states_x.push_back(i_x);
        i_x += step_x;
    }
    while(states_y.size() < states_x.size()){
        i_y = rand() % N;
        states_y.push_back(i_y);
    }

    states_x.push_back(fin_x);
    states_y.push_back(fin_y);

    /*for (std::vector<int>::const_iterator i = states_x.begin(); i != states_x.end(); ++i)
        std::cout << *i << ' ';
    std::cout<<std::endl;

    for (std::vector<int>::const_iterator i = states_y.begin(); i != states_y.end(); ++i)
        std::cout << *i << ' ';
    std::cout<<std::endl;
    */

    std::vector<int> states_tot;
    std::vector<int> tmp;
    tmp = state_to_state(init_x, init_y, fin_x, fin_y);
    states_tot.insert(states_tot.end(), tmp.begin(), tmp.end());
    for (size_t i=0; i<states_x.size()-1; i++){
        tmp = state_to_state(states_x.at(i), states_y.at(i), states_x.at(i+1), states_y.at(i+1));
        states_tot.insert(states_tot.end(), tmp.begin(), tmp.end());
    }

    return states_tot;

    /*    
    for (int i=0; i<N; i++){
        for (int j=0; j<N; j++){
            if (std::find_if(states_tot.begin(), states_tot.end(), compare(i*N+j)) != states_tot.end()){
                maze[i*N+j] = 0;
            }
            else {
                maze[i*N+j] = 1;
            }
        }
    }
    
    for (int i=0; i<N; i++){
        for (int j=0; j<N; j++){  
            std::cout<<maze[i*N+j]<<" ";
        }
        std::cout<<std::endl;
    }*/

};