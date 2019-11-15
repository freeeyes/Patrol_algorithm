// Patrol_algorithm.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "UserRoute.h"
#include "RouteInfo.h"

int main()
{
    /*
    CRoutePoint A(0.0f, 0.0f);
    CRoutePoint B(5.0f, 0.0f);
    CRoutePoint P(1.5f, 3.0f);

    CRoutePoint intersection;

    double distance = Point_to_line_distance(A, B, P, intersection);

    printf("distance=%f!\n", distance);
    printf("intersection.x=%f,intersection.y=%f!\n", intersection.latitude_, intersection.longitude_);
    */

    CRouteInfo route_info;

    route_info.Set_route_id(1);

    route_info.Add_node(CRoutePoint(0.0f, 0.0f), 5);
    route_info.Add_node(CRoutePoint(5.0f, 0.0f), 5);
    route_info.Add_node(CRoutePoint(10.0f, 0.0f), 5);
    route_info.Add_node(CRoutePoint(15.0f, 0.0f), 5);

    CRoutePoint curr_user_point(0.0f, 0.0f);

    CObjectRouteInfo object_route_info;

    object_route_info.user_last_point_ = curr_user_point;
    object_route_info.step_ = 5;
    object_route_info.direction_ = 0;
    object_route_info.last_line_disance_ = 0.0f;

    curr_user_point.latitude_ = 1.0f;
    curr_user_point.longitude_ = 1.0f;

    int err = route_info.Calculation_line(curr_user_point, object_route_info);

    if (err == 0)
    {
        printf_s("[main]user walk distance(%d).\n", object_route_info.point_index_);
        printf_s("[main]user walk distance(%f).\n", object_route_info.last_line_disance_);
        printf_s("[main]user walk pos(%f, %f).\n", object_route_info.user_last_point_.latitude_, object_route_info.user_last_point_.longitude_);
    }
    else
    {
        printf_s("[main]user walk error(%s).\n", route_info.Get_calculation_return_error(err).c_str());
    }

    getchar();
    return 0;
}