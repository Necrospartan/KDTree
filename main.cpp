#include <algorithm>
#include <array>
#include <cmath>
#include <iostream>
#include <random>
#include <vector>
#include "Kdtree.cpp"
#include <list>
#include <ctime>

int main()
{
    unsigned t0, t1, t2, t3;
    //srand (time(NULL));
    srand(50);
    int Num_max = 500000;
    float max_x = 100;
    float max_y = 100;
    point_2d point_root( (((float) rand() / (RAND_MAX)))*max_x, (((float) rand() / (RAND_MAX)))*max_y );
    Node_kdtree* Kd_tree = new Node_kdtree[Num_max];
    int root = 0;
    float time_kd_tree = 0;
    float time_fuerza_bruta = 0;

    for(int j = 0; j<Num_max; j++)
    {
        point_2d tem_point( (((float) rand() / (RAND_MAX)))*max_x, (((float) rand() / (RAND_MAX)))*max_y );
        //std::cout<<tem_point.x<<" , "<<tem_point.y<<std::endl;
        Kdtree::Insert_Node(Kd_tree, tem_point, j, Num_max);
    }
    
    point_2d Busqueda( (((float) rand() / (RAND_MAX)))*max_x, (((float) rand() / (RAND_MAX)))*max_y );
    int best = -1;
    float best_dist = 1000000;
    t0 = clock();
    Kdtree::nearest(Kd_tree, root , Busqueda, best, best_dist);
    t1 = clock();
    time_kd_tree = (float(t1-t0)/CLOCKS_PER_SEC);
        
    int best_f = -1;
    float best_dist_f = 100000;
    t2 = clock();
    Kdtree::fuerza_bruta(Kd_tree, Busqueda, Num_max, best_f, best_dist_f);
    t3 = clock();
    time_fuerza_bruta = (float(t3-t2)/CLOCKS_PER_SEC);
    std::cout<<"----------------------"<<std::endl;
    std::cout<<"kd-tree: "<<Kd_tree[best].coords.x<<" , "<<Kd_tree[best].coords.y<<std::endl;
    std::cout<<"Fuerza breta: "<<Kd_tree[best_f].coords.x<<" , "<<Kd_tree[best_f].coords.y<<std::endl;
    
    std::cout<<"----------------------"<<std::endl;
    std::cout<<"time_kd_tree: "<<time_kd_tree<<std::endl;
    std::cout<<"time_fuerza_bruta: "<<time_fuerza_bruta<<std::endl;
    std::cout<<"time_fuerza_bruta/time_kd_tree = "<<time_fuerza_bruta/time_kd_tree<<std::endl;
    std::cout<<"----------------------------------------------------"<<std::endl;

    float r_max = 0.5;
    point_2d random_point( (((float) rand() / (RAND_MAX)))*max_x, (((float) rand() / (RAND_MAX)))*max_y );
    float random_r((((float) rand() / (RAND_MAX)))*r_max);
    Region region(random_point.x-random_r, random_point.x+random_r, random_point.y-random_r, random_point.y+random_r);
    std::cout<<"region->x_min: "<<region.x_min<<std::endl;
    std::cout<<"region->x_max: "<<region.x_max<<std::endl;
    std::cout<<"region->y_min: "<<region.y_min<<std::endl;
    std::cout<<"region->y_max: "<<region.y_max<<std::endl;
    std::cout<<"random_r: "<<random_r<<std::endl;
    std::cout<<"----------------------------------------------------"<<std::endl;

    std::list<int> List_Point;
    std::list<int> List_Point_f;
    t0 = clock();
    Kdtree::Range_search(Kd_tree, root, region, Num_max, List_Point);
    t1 = clock();
    time_kd_tree = (float(t1-t0)/CLOCKS_PER_SEC);

    t2 = clock();
    Kdtree::Range_search_fuerza_bruta(Kd_tree, region, Num_max, List_Point_f);
    t3 = clock();
    time_fuerza_bruta = (float(t3-t2)/CLOCKS_PER_SEC);

    std::cout<<"rango time_kd_tree: "<<time_kd_tree<<std::endl;
    std::cout<<"rango time_fuerza_bruta: "<<time_fuerza_bruta<<std::endl;
    std::cout<<"rango time_fuerza_bruta/time_kd_tree = "<<time_fuerza_bruta/time_kd_tree<<std::endl;

    std::list <int> :: iterator it;
    std::cout<<"Range_search: "<<List_Point.size()<<std::endl;
    std::cout<<"Range_search_fuerza_bruta: "<<List_Point_f.size()<<std::endl;

    delete []Kd_tree;
};
