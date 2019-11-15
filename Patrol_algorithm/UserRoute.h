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
    string      user_name_;         //�û�����
    CRoutePoint user_last_point_;   //��ǰ�û��ڵ�
    double      user_last_distance; //�û���ǰ��������·�����
    double      step_;              //��ǰ�豸����������
    int         route_id_;          //��ǰ�û���·ID
    int         route_node_index_;  //��ǰ���ڵ�·�ڵ�ID
    char        route_direction_;   //��ǰ��·����
};

