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
    string              user_name_;         //�û�����
    int                 route_id_;          //��ǰ�û���·ID
    char                route_direction_;   //��ǰ��·����
    CObjectRouteInfo    object_route_info_; //��ǰ��λ��Ϣ
    int                 user_curr_route_point_count_;         //��ǰ��Ч�켣����
    vector<CUserRoutePointInfo> user_curr_route_point_list_;  //��ǰ����������߹켣
};

