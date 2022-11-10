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
struct Point
{
    double x;
    double y;
    double z;
    Point()
        : x(-1), y(-1), z(-1) // ��ʼֵ
    {
    }
    Point(double a, double b, double c) // ��ʼ����ʽ
        : x(a), y(b), z(c)
    {
    }
    // ����==
    bool operator==(const Point &p)
    {
        if (this->x == p.x && this->y == p.y && this->z == p.z)
        {
            return true;
        }
        return false;
    }

    // ����==
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
    Octree(double x, double y, double z) // ��������ڵ㸳ֵ
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

    void Children_tree_make(int pos)
    {
        double midx = (topLeftFront->x + bottomRightBack->x) / 2;
        double midy = (topLeftFront->y + bottomRightBack->y) / 2;
        double midz = (topLeftFront->z + bottomRightBack->z) / 2;
        children[pos]->children.assign(8, nullptr);
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
        std::cout << s << std::endl;

        // ����ӽڵ�ǿգ��Ѿ����֣���������ޣ������ݹ����   !!!!!pos,������
        if (children[pos]->topLeftFront != nullptr)
        {
            if (pos != -1)
            {
                children[pos]->insert(x, y, z);
                return; // ��ʾ����ֹͣ��������ִ�У�������Ӹ��ڵ㣬ֻ����ӽڵ�
            }
        }
        // ����ӽڵ��ǿյģ�������ڵ㸳ֵ
        children[pos]->Parent_Points.push_back(Point(x, y, z));

        // ������ýڵ�󸸽ڵ��������������ҵ���Ӧ��pos����������
        if (children[pos]->Parent_Points.size() > max_length && (level < max_level))
        {
            Octree *now = children[pos];
            Children_tree_make(pos,level);//����pos������
            int i = 0;
            level++;
            // std::cout << Parent_Points.size() << std::endl;
            // ��֮ǰ�洢�Ľڵ���������뵽�ӽڵ㣬֮ǰȫ�ڸ��ڵ㣬��ɾ��
            while (i < now->Parent_Points.size())
            {
                // cerr << "delet" << endl;
                // system("pause");
                pos = now->getIndex(now->Parent_Points[i].x, now->Parent_Points[i].y, now->Parent_Points[i].z);
                now->children[pos]->Parent_Points.push_back(now->Parent_Points[i]);
                i++;
                // if (pos != -1)
                // {
                //     // if (now->children[pos]->Parent_Points.size() == 0)
                //     // {
                //     //     // ��ʼ�����ӽڵ�
                //     //     double midx = (topLeftFront->x + bottomRightBack->x) / 2;
                //     //     double midy = (topLeftFront->y + bottomRightBack->y) / 2;
                //     //     double midz = (topLeftFront->z + bottomRightBack->z) / 2;
                //     //     if (pos == TopLeftFront)
                //     //     {
                //     //         now->children[pos] = new Octree(topLeftFront->x,
                //     //                                         topLeftFront->y,
                //     //                                         topLeftFront->z,
                //     //                                         midx,
                //     //                                         midy,
                //     //                                         midz);
                //     //     }
                //     //     else if (pos == TopRightFront)
                //     //     {
                //     //         now->children[pos] = new Octree(midx,
                //     //                                         topLeftFront->y,
                //     //                                         topLeftFront->z,
                //     //                                         bottomRightBack->x,
                //     //                                         midy,
                //     //                                         midz);
                //     //     }
                //     //     else if (pos == BottomRightFront)
                //     //     {
                //     //         now->children[pos] = new Octree(midx,
                //     //                                         midy,
                //     //                                         topLeftFront->z,
                //     //                                         bottomRightBack->x,
                //     //                                         bottomRightBack->y,
                //     //                                         midz);
                //     //     }
                //     //     else if (pos == BottomLeftFront)
                //     //     {
                //     //         now->children[pos] = new Octree(topLeftFront->x,
                //     //                                         midy,
                //     //                                         topLeftFront->z,
                //     //                                         midx,
                //     //                                         bottomRightBack->y,
                //     //                                         midz);
                //     //     }
                //     //     else if (pos == TopLeftBottom)
                //     //     {
                //     //         now->children[pos] = new Octree(topLeftFront->x,
                //     //                                         topLeftFront->y,
                //     //                                         midz,
                //     //                                         midx,
                //     //                                         midy,
                //     //                                         bottomRightBack->z);
                //     //     }
                //     //     else if (pos == TopRightBottom)
                //     //     {
                //     //         now->children[pos] = new Octree(midx,
                //     //                                         topLeftFront->y,
                //     //                                         midz,
                //     //                                         bottomRightBack->x,
                //     //                                         midy,
                //     //                                         bottomRightBack->z);
                //     //     }
                //     //     else if (pos == BottomRightBack)
                //     //     {
                //     //         now->children[pos] = new Octree(midx,
                //     //                                         midy,
                //     //                                         midz,
                //     //                                         bottomRightBack->x,
                //     //                                         bottomRightBack->y,
                //     //                                         bottomRightBack->z);
                //     //     }
                //     //     else if (pos == BottomLeftBack)
                //     //     {
                //     //         now->children[pos] = new Octree(topLeftFront->x,
                //     //                                         midy,
                //     //                                         midz,
                //     //                                         midx,
                //     //                                         bottomRightBack->y,
                //     //                                         bottomRightBack->z);
                //     //     }
                //     // }
                //     // if (now->children[pos]->topLeftFront == nullptr)
                //     // {
                //     //     std::cout << "None node" << std::endl;
                //     //     break;
                //     // }
                //     // else
                //     // {
                //     //     now->children[pos]->insert(now->Parent_Points[i].x, now->Parent_Points[i].y, now->Parent_Points[i].z);
                //     // }
                //     now->children[pos]->Parent_Points.push_back(now->Parent_Points[i]);
                //    //now->Parent_Points.erase(now->Parent_Points.begin() + i);
                //    // Parent_Points.erase(remove(Parent_Points.begin(), Parent_Points.end(), Parent_Points[i]), Parent_Points.end());
                // }
                // else
                // {
                //     i++;
                // }
            }
            //ɾ�����д���ڵ�
            now->Parent_Points.clear();
        }
    }

    // Function that returns true if the point
    //(x, y, z) exists in the octree
    int getIndex(double x, double y, double z)
    {
        // topLeftFront = new Point(1, 1, 1);
        // bottomRightBack = new Point(5, 5, 5);
        // Binary search to insert the point(���ַ�)
        if (x < topLeftFront->x || x > bottomRightBack->x || y < topLeftFront->y || y > bottomRightBack->y || z < topLeftFront->z || z > bottomRightBack->z)
        {
            cout << "Point is out of bound" << endl;
            return 0;
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

    vector<Point> retrieve(vector<Point> returnpoint, Point object)
    {
        // ����һ�����ҵ�ͬһ�ӽڵ������е�
        // std::cout<<topLeftFront->x<<std::endl;
        int index = -1;
        index = getIndex(object.x, object.y, object.z);
        // getIndex��children�ᷢ���仯���ѱ���ӽڵ㣬��ָ�붯̬�仯

        if (children[index]->topLeftFront != nullptr && index != -1)
        {
            returnpoint = children[index]->retrieve(returnpoint, object);
        }
        returnpoint.push_back(object); //!!!!
        return returnpoint;
    }
};

// Driver code
int main()
{
    Octree tree(1, 1, 1, 5, 5, 5);
    double m = 2, n = 3, q = 4, min_dis = 100;
    vector<Point> Point_blade, Return_Point;
    Point a1, a2, a3, a4;
    Point min_point;

    // a1.x = 3.0; a1.y = 4.0;  a1.z = 4.0; a2.x = 4.0; a2.y = 4.0;  a2.z = 4.0;
    // a3.x = 2.0; a3.y = 4.0;  a3.z = 3.0; a4.x = 2.0; a4.y = 3.0;  a4.z = 4.0;

    // Point_blade.push_back(a1); Point_blade.push_back(a2);
    // Point_blade.push_back(a3); Point_blade.push_back(a4);

    for (double i = 1.1; i < 5; i = i + 1)
    {
        for (double j = 1.1; j < 5; j = j + 1)
        {
            for (double k = 1.1; k < 5; k = k + 1)
            {
                Point_blade.push_back(Point(i, j, k));
            }
        }
    }

    // ���в���ڵ�
    for (int i = 0; i < Point_blade.size(); i++)
    {
        tree.insert(Point_blade[i].x, Point_blade[i].y, Point_blade[i].z);
        std::cout << Point_blade[i].x << " " << Point_blade[i].y << " " << Point_blade[i].z << std::endl;
    }

    // cout << (tree.find(3.0, 4.0, 4.0)? "Found\n": "Not Found\n");

    // ���в�ѯ�ڵ㣬���ؽڵ�λ�ú��ܱ߽ڵ�
    //  for (int i = 0; i < Point_blade.size(); i++) {
    // 	 Return_Point.clear();
    // 	 Return_Point=tree.retrieve(Return_Point, Point_blade[i]);

    // 	 for (int j = 0; j < Return_Point.size(); j++) {
    // 		 if (Return_Point[j]!= Point_blade[i])
    // 		 {
    // 			 double distance = pow((Return_Point[j].x - Point_blade[i].x), 2) + pow((Return_Point[j].y - Point_blade[i].y), 2) + pow((Return_Point[j].z - Point_blade[i].z), 2);
    // 			 if (distance < min_dis)
    // 			 {
    // 				 min_dis = distance;
    // 				 min_point = Return_Point[j];
    // 			 }
    // 		 }
    // 	 }
    // 	 std::cout << "min_dis " << min_dis << std::endl;
    // 	 std::cout << "min_point " << min_point.x << min_point.y << min_point.z << std::endl;
    //  }
    system("pause");
    return 0;
}