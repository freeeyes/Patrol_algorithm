#pragma once
#include <string>
#include "Route_Common.h"
#include <vector>

using namespace std;

class CUserRoute
{
public:
    CUserRoute(string user_name);

    void Init(double step, int route_id, char route_direction);

    CObjectRouteInfo* Get_object_route_info();

    void Set_object_route_info();

    void Clear();

    void Display();

private:
    void Add_route_point_list(CRoutePoint curr_route_point, double curr_point_distance, double curr_route_ratio);

private:
    string              user_name_;         //用户名称
    int                 route_id_;          //当前用户道路ID
    char                route_direction_;   //当前道路方向
    CObjectRouteInfo    object_route_info_; //当前点位信息
    int                 user_curr_route_point_count_;         //当前有效轨迹数量
    vector<CUserRoutePointInfo> user_curr_route_point_list_;  //当前修正后的行走轨迹
};

