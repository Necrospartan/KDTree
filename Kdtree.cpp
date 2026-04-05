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
	list<int> list_n;

        if ( n == -1 ) return;
        
	list_n.push_back( n );
	int tem_n;

	while( !list_n.empty() )
	{
	    tem_n = list_n.back();
	    list_n.pop_back();
	    if( tem_n != -1 )
	    {
		d = kd_tree[ tem_n ].dist_squared( point );
        
		if ( best_ == -1 || d < best_dist_ ) 
		{
		    best_dist_ = d;
		    best_ = tem_n;
		}

		if ( best_dist_ == 0 ) break;
        
		kd_tree[ tem_n ].name_median == 'x' ? dx = kd_tree[ tem_n ].coords.x - point.x : 
		    dx = kd_tree[ tem_n ].coords.y - point.y;

		dx > 0 ? list_n.push_back( kd_tree[ tem_n ].left ) : list_n.push_back( kd_tree[ tem_n ].right );
        
		if ( dx * dx < best_dist_ )
		    dx > 0 ? list_n.push_back( kd_tree[ tem_n ].right ) : list_n.push_back( kd_tree[ tem_n ].left );
	    }
	}
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
	list<int> list_n;
	list_n.push_back( n );
	int tem_n;
	while( !list_n.empty() )
	{
	    tem_n = list_n.back();
	    list_n.pop_back();
	    if( tem_n != -1 )
	    {
		switch( region.region( kd_tree[ tem_n ] ) )
		{
		    case 1://left
			if( kd_tree[ tem_n ].left != -1 ) list_n.push_back( kd_tree[ tem_n ].left ) ;//left
			break;
		    case 2://center
			if( kd_tree[ tem_n ].left != -1 ) list_n.push_back( kd_tree[ tem_n ].left );//left
			if( kd_tree[ tem_n ].right != -1 ) list_n.push_back( kd_tree[ tem_n ].right );//right
			if( region.in_region( kd_tree[ tem_n ].coords ) )
			    List_Point.push_back( tem_n );
			break;
		    case 3://right
			if( kd_tree[ tem_n ].right != -1 ) list_n.push_back( kd_tree[ tem_n ].right );//right
			break;
		    default:
			std::cout<<"Error Range_search"<<std::endl;
			break;
		}
	    }
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
