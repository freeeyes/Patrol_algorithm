#pragma once
#include <string>
#include "Route_Common.h"

using namespace std;

class CUserRoute
{
public:
    CUserRoute(string user_name);

    void Init(double step, int route_id, char route_direction);

private:
    string      user_name_;         //用户名称
    CRoutePoint user_last_point_;   //当前用户节点
    double      user_last_distance; //用户当前做过的线路最长距离
    double      step_;              //当前设备步进最大距离
    int         route_id_;          //当前用户道路ID
    int         route_node_index_;  //当前所在道路节点ID
    char        route_direction_;   //当前道路方向
};

