// Patrol_algorithm.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "UserRoute.h"
#include "RouteInfo.h"
#include "UserRoute.h"

void Test_distance()
{
    CRoutePoint A(0.0f, 0.0f);
    CRoutePoint B(5.0f, 0.0f);
    CRoutePoint P(1.5f, 3.0f);

    CRoutePoint intersection;

    double distance = Point_to_line_distance(A, B, P, intersection);

    PRINTF("[Test_distance]distance=%f!\n", distance);
    PRINTF("[Test_distance]intersection.x=%f,intersection.y=%f!\n", intersection.latitude_, intersection.longitude_);
}

void Test_Route_step()
{
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

    int err = route_info.Calculation_line(curr_user_point, &object_route_info);

    if (err == 0)
    {
        PRINTF("[Test_Route_step]user walk index(%d).\n", object_route_info.point_index_);
        PRINTF("[Test_Route_step]user walk distance(%f).\n", object_route_info.last_line_disance_);
        PRINTF("[Test_Route_step]user walk pos(%f, %f).\n", object_route_info.user_last_point_.latitude_, object_route_info.user_last_point_.longitude_);
        PRINTF("[Test_Route_step]user line ratio(%f%%).\n", object_route_info.last_line_ratio_);
        PRINTF("[Test_Route_step]-----------------------\n");
    }
    else
    {
        PRINTF("[main]user walk error(%s).\n", route_info.Get_calculation_return_error(err).c_str());
    }

    for (int i = 0; i < 10; i++)
    {
        curr_user_point.latitude_ = curr_user_point.latitude_ + 3.0f;
        curr_user_point.longitude_ = 1.0f;

        int err = route_info.Calculation_line(curr_user_point, &object_route_info);

        if (err == 0)
        {
            PRINTF("[Test_Route_step]user walk distance(%d).\n", object_route_info.point_index_);
            PRINTF("[Test_Route_step]user walk distance(%f).\n", object_route_info.last_line_disance_);
            PRINTF("[Test_Route_step]user walk pos(%f, %f).\n", object_route_info.user_last_point_.latitude_, object_route_info.user_last_point_.longitude_);
            PRINTF("[Test_Route_step]user line ratio(%f%%).\n", object_route_info.last_line_ratio_);
            PRINTF("[Test_Route_step]-----------------------\n");
        }
        else
        {
            PRINTF("[Test_Route_step]user walk error(%s).\n", route_info.Get_calculation_return_error(err).c_str());
            PRINTF("[Test_Route_step]-----------------------\n");
        }
    }
}

void Test_User_step()
{
    CRouteInfo route_info;

    route_info.Set_route_id(1);

    route_info.Add_node(CRoutePoint(0.0f, 0.0f), 5);
    route_info.Add_node(CRoutePoint(5.0f, 0.0f), 5);
    route_info.Add_node(CRoutePoint(10.0f, 0.0f), 5);
    route_info.Add_node(CRoutePoint(15.0f, 0.0f), 5);

    CUserRoute user_route("freeeyes");

    user_route.Init(5, 1, 0);

    CRoutePoint curr_user_point(0.0f, 0.0f);

    for (int i = 0; i < 10; i++)
    {
        int err = route_info.Calculation_line(curr_user_point, user_route.Get_object_route_info());

        if (err == 0)
        {
            user_route.Set_object_route_info();
        }
        else
        {
            PRINTF("[Test_Route_step]user walk error(%s).\n", route_info.Get_calculation_return_error(err).c_str());
            PRINTF("[Test_Route_step]-----------------------\n");
        }

        curr_user_point.latitude_ += 3.0f;
    }

    user_route.Display();

}

int main()
{

    //Test_Route_step();
    Test_User_step();

    getchar();
    return 0;
}