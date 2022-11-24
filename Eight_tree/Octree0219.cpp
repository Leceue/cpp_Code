#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <stdlib.h>

using namespace std;

#define TopLeftFront 0
#define TopRightFront 1
#define BottomRightFront 2
#define BottomLeftFront 3
#define TopLeftBottom 4
#define TopRightBottom 5
#define BottomRightBack 6
#define BottomLeftBack 7

int s = 0;
// Structure of a point
int Tr_level = 0;
//总层数

struct Point
{
    double x;
    double y;
    double z;
    Point()
        : x(-1), y(-1), z(-1) // 初始值
    {
    }
    Point(double a, double b, double c) // 初始化方式
        : x(a), y(b), z(c)
    {
    }
    // 重载==
    bool operator==(const Point &p)
    {
        if (this->x == p.x && this->y == p.y && this->z == p.z)
        {
            return true;
        }
        return false;
    }

    // 重载==
    bool operator!=(const Point p)
    {
        if (this->x != p.x || this->y != p.y || this->z != p.z)
        {
            return true;
        }
        return false;
    }
};

// Octree class
class Octree
{

    // if point != NULL, node is internal node.
    // if point == (-1, -1, -1), node is empty.
    int max_length = 4, max_level = 50;
    int level = 0;
    Point *point;
    // Represent the boundary of the cube
    Point *topLeftFront = NULL;
    Point *bottomRightBack = NULL;

    vector<Point> Parent_Points;
    vector<Octree *> children;

public:
    // Constructor
    Octree()
    {
        // To declare empty node
        point = new Point();
    }

    // Constructor with three arguments
    Octree(double x, double y, double z) // 特意给父节点赋值
    {
        // To declare point node
        point = new Point(x, y, z);
    }

    // Constructor with six arguments
    Octree(double x1, double y1, double z1, double x2, double y2, double z2)
    {
        // This use to construct Octree
        // with boundaries defined
        if (x2 < x1 || y2 < y1 || z2 < z1)
        {
            cout << "bounday points are not valid" << endl;
            return;
        }
        point = nullptr;
        // point = new Point();

        topLeftFront = new Point(x1, y1, z1);
        bottomRightBack = new Point(x2, y2, z2);

        // Assigning null to the children
        children.assign(8, nullptr);
        for (int i = TopLeftFront; i <= BottomLeftBack; ++i)
            children[i] = new Octree();
    }

    void Children_tree_make(int pos, int now_level)
    {
        double midx = (topLeftFront->x + bottomRightBack->x) / 2;
        double midy = (topLeftFront->y + bottomRightBack->y) / 2;
        double midz = (topLeftFront->z + bottomRightBack->z) / 2;
        children[pos]->children.assign(8, nullptr);
        children[pos]->level = now_level + 1;
        for (int i = TopLeftFront; i <= BottomLeftBack; ++i)
            children[pos]->children[i] = new Octree();
        if (pos == TopLeftFront)
        { 
            children[pos]->topLeftFront = new Point(topLeftFront->x, topLeftFront->y, topLeftFront->z);
            children[pos]->bottomRightBack = new Point(midx, midy, midz);
        }
        else if (pos == TopRightFront)
        {
            children[pos]->topLeftFront = new Point(midx,
                                            topLeftFront->y,
                                            topLeftFront->z);
            children[pos]->bottomRightBack = new Point(bottomRightBack->x,
                                            midy,
                                            midz);
        }
        else if (pos == BottomRightFront)
        {
            children[pos]->topLeftFront = new Point(midx,
                                            midy,
                                            topLeftFront->z);
            children[pos]->bottomRightBack = new Point(bottomRightBack->x,
                                            bottomRightBack->y,
                                            midz);
        }
        else if (pos == BottomLeftFront)
        {
            children[pos]->topLeftFront = new Point(topLeftFront->x,
                                            midy,
                                            topLeftFront->z);
            children[pos]->bottomRightBack = new Point(midx,
                                            bottomRightBack->y,
                                            midz);
        }
        else if (pos == TopLeftBottom)
        {
            children[pos]->topLeftFront = new Point(topLeftFront->x,
                                            topLeftFront->y,
                                            midz);
            children[pos]->bottomRightBack = new Point(midx,
                                            midy,
                                            bottomRightBack->z);
        }
        else if (pos == TopRightBottom)
        {
            children[pos]->topLeftFront = new Point(midx,
                                            topLeftFront->y,
                                            midz);
            children[pos]->bottomRightBack = new Point(bottomRightBack->x,
                                            midy,
                                            bottomRightBack->z);
        }
        else if (pos == BottomRightBack)
        {
            children[pos]->topLeftFront = new Point(midx,
                                            midy,
                                            midz);
            children[pos]->bottomRightBack = new Point(bottomRightBack->x,
                                            bottomRightBack->y,
                                            bottomRightBack->z);
        }
        else if (pos == BottomLeftBack)
        {
            children[pos]->topLeftFront = new Point(topLeftFront->x,
                                            midy,
                                            midz);
            children[pos]->bottomRightBack = new Point(midx,
                                            bottomRightBack->y,
                                            bottomRightBack->z);
        }
    }

    // Function to insert a point in the octree
    void insert(double x, double y, double z)
    {
        // topLeftFront = new Point(1, 1, 1);
        // bottomRightBack = new Point(5, 5, 5);

        int pos = -1;
        pos = getIndex(x, y, z);
        s++;
        // std::cout << s << std::endl;

        // 如果子节点非空，已经划分，则查找象限，继续递归调用   !!!!!pos,不是零
        if (children[pos]->topLeftFront != nullptr)
        {
            if (pos != -1)
            {
                children[pos]->insert(x, y, z);
                return; // 表示程序停止不再往后执行，不再添加父节点，只添加子节点
            }
        }
        // 如果子节点是空的，则给父节点赋值
        children[pos]->Parent_Points.push_back(Point(x, y, z));

        // 当插入该节点后父节点数量超数量，找到对应的pos，插入新树
        if (children[pos]->Parent_Points.size() > max_length && (level < max_level))
        {
            Octree *now = children[pos];
            Children_tree_make(pos,level);//构造pos的子树
            Tr_level = max(Tr_level, level+1);
            int i = 0;
            // std::cout << Parent_Points.size() << std::endl;
            // 把之前存储的节点数逐个插入到子节点，之前全在父节点，并删除
            while (i < now->Parent_Points.size())
            {
                // cerr << "delet" << endl;
                // system("pause");
                pos = now->getIndex(now->Parent_Points[i].x, now->Parent_Points[i].y, now->Parent_Points[i].z);
                now->children[pos]->Parent_Points.push_back(now->Parent_Points[i]);
                i++;
            }
            //删除所有储存节点
            now->Parent_Points.clear();
        }
    }

    // Function that returns true if the point
    //(x, y, z) exists in the octree
    int getIndex(double x, double y, double z)
    {
        // topLeftFront = new Point(1, 1, 1);
        // bottomRightBack = new Point(5, 5, 5);
        // Binary search to insert the point(二分法)
        if (x < topLeftFront->x || x > bottomRightBack->x || y < topLeftFront->y || y > bottomRightBack->y || z < topLeftFront->z || z > bottomRightBack->z)
        {
            cout << "Point is out of bound" << endl;
            return -1;
        }
        // Otherwise perform binary search
        // for each ordinate
        double midx = (topLeftFront->x + bottomRightBack->x) / 2;
        double midy = (topLeftFront->y + bottomRightBack->y) / 2;
        double midz = (topLeftFront->z + bottomRightBack->z) / 2;

        int pos = -1;
        // Deciding the position where to move
        if (x <= midx)
        {
            if (y <= midy)
            {
                if (z <= midz)
                    pos = TopLeftFront;
                else
                    pos = TopLeftBottom;
            }
            else
            {
                if (z <= midz)
                    pos = BottomLeftFront;
                else
                    pos = BottomLeftBack;
            }
        }
        else
        {
            if (y <= midy)
            {
                if (z <= midz)
                    pos = TopRightFront;
                else
                    pos = TopRightBottom;
            }
            else
            {
                if (z <= midz)
                    pos = BottomRightFront;
                else
                    pos = BottomRightBack;
            }
        }
        return pos;
    }

    vector<Point> retrieve(Point object)
    {
        // 输入一个点找到同一子节点下所有点
        // std::cout<<topLeftFront->x<<std::endl;
        int index = -1;
        index = getIndex(object.x, object.y, object.z);

        if (children[index]->topLeftFront != nullptr && index != -1)
        {
            return children[index]->retrieve(object);
        }
        // returnpoint.push_back(object); //!!!!
        return children[index]->Parent_Points;
    }

    double query_Min_Point(Point object, Point &min_point)
    {
        double dist = 1e10;
        vector<Point> Min_Point = retrieve(object);
        for(auto point : Min_Point) {
            double x = point.x, y = point.y, z = point.z;
            if(dist > sqrt(pow(object.x-x, 2) + pow(object.y-y, 2) + pow(object.y-y, 2))){
                dist = sqrt(pow(object.x-x, 2) + pow(object.y-y, 2) + pow(object.y-y, 2));
                min_point = point;
            }
            printf("(%lf, %lf, %lf), %lf\n", x, y, z, sqrt(pow(object.x-x, 2) + pow(object.y-y, 2) + pow(object.y-y, 2)));
        }
        return dist;
    }
};

// Driver code
int main()
{
    Octree tree(0, 0, 0, 10, 10, 10);
    double m = 2, n = 3, q = 4, min_dis = 100;
    vector<Point> Point_blade, Return_Point;
    Point a1, a2, a3, a4;
    Point min_point;

    // a1.x = 3.0; a1.y = 4.0;  a1.z = 4.0; a2.x = 4.0; a2.y = 4.0;  a2.z = 4.0;
    // a3.x = 2.0; a3.y = 4.0;  a3.z = 3.0; a4.x = 2.0; a4.y = 3.0;  a4.z = 4.0;

    // Point_blade.push_back(a1); Point_blade.push_back(a2);
    // Point_blade.push_back(a3); Point_blade.push_back(a4);

    for (double i = 1; i <= 5; i = i + 0.01)
    {
        for (double j = 1; j <= 5; j = j + 0.01)
        {
            for (double k = 1; k <= 5; k = k + 0.01)
            {
                tree.insert(i, j, k);
            }
        }
    }

    while(1){
        printf("请输入一个坐标: ");
        double x,y,z;
        scanf("%lf,%lf,%lf",&x,&y,&z);
        Point point;
        double que = tree.query_Min_Point(Point(x, y, z), point);
        printf("最近距离是: %lf, 最近点的坐标是:(%lf, %lf, %lf)\n",que, point.x, point.y, point.z);
    }

    system("pause");
    return 0;
}