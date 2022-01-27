#include <iostream> 
#include <math.h>
#include <list>
#include "auxiliary.hpp"
using namespace std;

class Kdtree
{
    //si Node_kdtree.depth%2 == 0 entonces estamos en x, si no en y
    public:
    static void Insert_Node(Node_kdtree* kd_tree, point_2d &Pos, int i, int Num_max)
    {
        if( i == 0)//root
        {
            kd_tree[i].coords = point_2d(Pos.x, Pos.y);
            kd_tree[i].median = Pos.x;
            kd_tree[i].name_median = 'x';
        }
        else//other node
        {
            bool Bool = true;
            int k = 0;
            while(k!=Num_max && Bool)
            {
                if( kd_tree[k].name_median == 'x')//media x
                { 
                    if( Pos.x <= kd_tree[k].median)//left
                    {
                        if( kd_tree[k].left == -1 )
                        {
                            kd_tree[k].left = i;
                            kd_tree[i].coords = point_2d(Pos.x, Pos.y);
                            kd_tree[i].depth = kd_tree[k].depth + 1;
                            kd_tree[i].median = Pos.y;
                            kd_tree[i].name_median = 'y';
                            kd_tree[i].parent = k;
                            Bool = false;
                        }
                        else
                        {
                            k = kd_tree[k].left;
                        }
                    }
                    else//right
                    {
                        if( kd_tree[k].right == -1 )
                        {
                            kd_tree[k].right = i;
                            kd_tree[i].coords = point_2d(Pos.x, Pos.y);
                            kd_tree[i].depth = kd_tree[k].depth + 1;
                            kd_tree[i].median = Pos.y;
                            kd_tree[i].name_median = 'y';
                            kd_tree[i].parent = k;
                            Bool = false;
                        }
                        else
                        {
                            k = kd_tree[k].right;
                        }
                    }
                }
                else //median y
                {
                    if( Pos.y <= kd_tree[k].median)//left
                    {
                        if( kd_tree[k].left == -1 )
                        {
                            kd_tree[k].left = i;
                            kd_tree[i].coords = point_2d(Pos.x, Pos.y);
                            kd_tree[i].depth = kd_tree[k].depth + 1;
                            kd_tree[i].median = Pos.x;
                            kd_tree[i].name_median = 'x';
                            kd_tree[i].parent = k;
                            Bool = false;
                        }
                        else
                        {
                            k = kd_tree[k].left;
                        }
                    }
                    else//right
                    {
                        if( kd_tree[k].right == -1 )
                        {
                            kd_tree[k].right = i;
                            kd_tree[i].coords = point_2d(Pos.x, Pos.y);
                            kd_tree[i].depth = kd_tree[k].depth + 1;
                            kd_tree[i].median = Pos.x;
                            kd_tree[i].name_median = 'x';
                            kd_tree[i].parent = k;
                            Bool = false;
                        }
                        else
                        {
                            k = kd_tree[k].right;
                        }
                    }                
                }
            }
        }
    }
    static void nearest(Node_kdtree* kd_tree, int n , point_2d& point, int &best_, float &best_dist_) 
    {
        float d, dx;

        if (n == -1) return;
        
	d = kd_tree[n].dist_squared(point);
        
	if (best_ == -1 || d < best_dist_) 
	{
            best_dist_ = d;
            best_ = n;
        }

        if (best_dist_ == 0) return;
        
	if(kd_tree[n].name_median == 'x') dx = kd_tree[n].coords.x - point.x;
        else dx = kd_tree[n].coords.y - point.y;

        nearest(kd_tree, dx > 0 ? kd_tree[n].left : kd_tree[n].right, point, best_, best_dist_);
        
	if (dx * dx >= best_dist_) return;

        nearest(kd_tree, dx > 0 ? kd_tree[n].right : kd_tree[n].left, point, best_, best_dist_);
    }
    static void fuerza_bruta(Node_kdtree* kd_tree, point_2d &point, int Num_max, int &best_, float &best_dist_)
    {
        float d = 0;
        for( int i = 0; i<Num_max; i++)
        {
            d = kd_tree[i].dist_squared(point);
            if(i ==0)
            {
                best_dist_ = d;
                best_ = i;
            }
            else
            {
                if(d<best_dist_)
                {
                    best_dist_ = d;
                    best_ = i;
                }
            }
        }
    }
    static void Range_search(Node_kdtree* kd_tree, int n, Region &region, int Num_max, list<int> &List_Point)
    {
        if(n == -1)
        {
            return;
        }
        
        switch(region.region(kd_tree[n])){
            case 1://left
                Range_search(kd_tree, kd_tree[n].left, region, Num_max, List_Point);//left
                break;
            case 2://center
                Range_search(kd_tree, kd_tree[n].left, region, Num_max, List_Point);//left
                Range_search(kd_tree, kd_tree[n].right, region, Num_max, List_Point);//right
                if(region.in_region(kd_tree[n].coords))
                {
                    List_Point.push_back(n);
                }
                break;
            case 3://right
                Range_search(kd_tree, kd_tree[n].right, region, Num_max, List_Point);//right
                break;
            default:
                std::cout<<"Error Range_search"<<std::endl;
                break;
        }
    }
    static void Range_search_fuerza_bruta(Node_kdtree* kd_tree, Region &region, int Num_max, list<int> &List_Point_f)
    {
        for(int i = 0; i<Num_max; i++)
        {
            if(region.in_region(kd_tree[i].coords))
            {
                List_Point_f.push_back(i);
            }
        }
    }
};
