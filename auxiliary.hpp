class point_2d
{
    public:
        float x;
        float y;
        point_2d()
        {
            x = 0;
            y = 0;
        };
        point_2d(float x_, float y_)
        {
            x = x_;
            y = y_;
        };
        ~point_2d(){};
};
class Node_kdtree
{
    public:
        point_2d coords;
        int parent;
        int left;
        int right;
        int depth;
        float median;
        char name_median;
        Node_kdtree()
        {
            parent = -1;
            left = -1;
            right = -1;
            depth = 0;
            median = 0;
            name_median = ' ';
        }
        Node_kdtree(point_2d coords_) 
        {
            parent = -1;
            left = -1;
            right = -1;
            depth = 0;
            median = 0;
            name_median = ' ';
            coords = coords_;
        }
        Node_kdtree(point_2d coords_, int parent_,int left_, int right_, 
            int Pos_in_graph_, int depth_, float median_, char name_median_)
        {
            coords = coords_;
            parent = parent_;
            left = left_;
            right = right_;
            depth = depth_;
            median = median_;
            name_median = name_median_;
        }
        ~Node_kdtree(){}
        float dist_squared(point_2d &pos)
        {
            return (pow(coords.x - pos.x, 2)+pow(coords.y - pos.y, 2));
        }
};
class Region
{
    public:
        float x_min;
        float x_max;
        float y_min;
        float y_max;
        ~Region(){};
        Region()
        {
            x_min = 0;
            x_max = 0;
            y_min = 0;
            y_max = 0;
        };
        Region(float x_min_, float x_max_, float y_min_, float y_max_)
        {
            x_min = x_min_;
            x_max = x_max_;
            y_min = y_min_;
            y_max = y_max_;
        };
        int region(Node_kdtree &Node)
        {
            int b = 0;
            if(Node.name_median == 'x')
            {
                if(Node.median>=x_min && Node.median<=x_max)
                {
                    b = 2;
                }
                else
                {
                    if(Node.median>x_min)
                    {
                        b=1;
                    }
                    else
                    {
                        b=3;
                    }
                }
            }
            if( Node.name_median == 'y')
            {
                if(Node.median>=y_min && Node.median<=y_max)
                {
                    b = 2;
                }
                else
                {
                    if(Node.median>y_min){
                        b=1;
                    }
                    else{
                        b=3;
                    }
                }
            }
            return b;
        }
        bool in_region(point_2d &Pos)
        {
            if( (Pos.x<=x_max && Pos.x>=x_min) && (Pos.y<=y_max && Pos.y>=y_min) )
            {
                return true;
            }
            else
            {
                return false;
            }
        }
};
