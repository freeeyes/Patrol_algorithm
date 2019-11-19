#pragma once
#include <vector>
#include "Route_Common.h"

using namespace std;

//道路信息
class CRouteInfo
{
public:
    CRouteInfo();

    void Set_route_id(int route_id);

    int Get_route_id();

    int Get_node_count();

    void Add_node(CRoutePoint route_point, int route_width);

    bool Get_line_point(int point_index, CRoutePoint& curr_line_point);

    int Calculation_line(CRoutePoint user_curr_point, CObjectRouteInfo* object_route_info);

    string Get_calculation_return_error(int err);

private:
    void Get_min_distance(int point_index, char direction, CRoutePoint user_curr_point, int& min_point_index, CRoutePoint& min_intersection_point, double& min_distance);

private:
    vector<CRouteNode> route_node_list_;
    int route_id_;
    int route_node_count_;
};

