#include "Random_maze.h"
#include <iostream>
#include <random>
#include <algorithm>

#define submaze_step 2

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
    std::cout<<std::endl;
    return states_tmp;
};


std::vector<int> Random_maze::create(){

    //MAIN PATH

    std::vector<int> states_tot;

    int init_y = initial_state/N;
    int init_x = initial_state%N;
    int fin_y = final_state/N;
    int fin_x = final_state%N;
    srand (time(NULL));

    nodes_x.push_back(init_x);
    nodes_y.push_back(init_y);

    int i_x = 0, i_y =0 ;
    while(i_x < N){
        nodes_x.push_back(i_x);
        i_x += rand() % 3 +1;
    }
    while(nodes_y.size() < nodes_x.size()){
        i_y = rand() % N;
        nodes_y.push_back(i_y);
    }

    nodes_x.push_back(fin_x);
    nodes_y.push_back(fin_y);

    /*std::cout << "nodes x\n";
    for (std::vector<int>::const_iterator i = nodes_x.begin(); i != nodes_x.end(); ++i)
        std::cout << *i << ' ';
    std::cout<<std::endl;

    std::cout << "nodes y\n";
    for (std::vector<int>::const_iterator i = nodes_y.begin(); i != nodes_y.end(); ++i)
        std::cout << *i << ' ';
    std::cout<<std::endl;
    */

    std::vector<int> tmp;
    for (size_t i=0; i<nodes_x.size()-1; i++){
        tmp = state_to_state(nodes_x.at(i), nodes_y.at(i), nodes_x.at(i+1), nodes_y.at(i+1));
        states_tot.insert(states_tot.end(), tmp.begin(), tmp.end());
        nodes.push_back(nodes_y.at(i)*N+nodes_x.at(i));
    }
    nodes.push_back(nodes_y.back()*N+nodes_x.back());

    /*std::cout << "nodes\n";
    for (std::vector<int>::const_iterator i = nodes.begin(); i != nodes.end(); ++i)
        std::cout << *i << ' ';
    std::cout<<std::endl;
    */
    sort(nodes.begin(), nodes.end()); 

    // END MAIN PATH
    // SUBPATHS


    int num_submazes = N/submaze_step;
    //std::cout<<"num submazes="<<num_submazes<<std::endl;
    int ini, fin;

    for (int i=0; i<num_submazes; i++){S
        ini = nodes.at(rand() % nodes.size());
        fin = nodes.at(rand() % nodes.size());
        //std::cout<<"initial node="<<ini<<::std::endl;
        //std::cout<<"final node="<<fin<<::std::endl;
        tmp = state_to_state(ini%N, ini/N, fin%N, fin/N);
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

/*std::vector<int> Random_maze::create_submaze(int N, int initial, int final){

    int init_y = initial/N;
    int init_x = initial%N;
    int fin_y = final/N;
    int fin_x = final%N;
    srand (time(NULL));

    std::vector<int> states_x;
    std::vector<int> states_y;

    states_x.push_back(init_x);
    states_y.push_back(init_y);

    int i_x = 0, i_y =0 ;
    while(i_x < N){
        states_x.push_back(i_x);
        i_x += rand() % 3; //step_x;
    }
    while(states_y.size() < states_x.size()){
        i_y = rand() % N;
        states_y.push_back(i_y);
    }

    states_x.push_back(fin_x);
    states_y.push_back(fin_y);

    for (std::vector<int>::const_iterator i = states_x.begin(); i != states_x.end(); ++i)
        std::cout << *i << ' ';
    std::cout<<std::endl;

    for (std::vector<int>::const_iterator i = states_y.begin(); i != states_y.end(); ++i)
        std::cout << *i << ' ';
    std::cout<<std::endl;
    std::cout<<std::endl;
    

    std::vector<int> states;
    std::vector<int> tmp;
    for (size_t i=0; i<states_x.size()-1; i++){
        tmp = state_to_state(states_x.at(i), states_y.at(i), states_x.at(i+1), states_y.at(i+1));
        states.insert(states.end(), tmp.begin(), tmp.end());
    }

    return states;

}*/