// Patrol_algorithm.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "UserRoute.h"
#include "RouteInfo.h"
#include "UserRoute.h"

void Test_distance()
{
    CRoutePoint A(39.9080785f, 116.395729f);
    CRoutePoint B(39.9080785f, 116.395729f);
    double distance = Point_to_point_distance(A, B);

    cout << "[Test_distance]distance=" << distance << endl;
}

void Test_user_distance()
{
    CRoutePoint A(39.9080585f, 116.394729f);
    CRoutePoint B(39.9080785f, 116.394729f);
    CRoutePoint P(39.9080786f, 116.394749f);

    CRoutePoint intersection;

    double distance = Point_to_line_distance(A, B, P, intersection);

    cout << "[Test_user_distance]distance=" << distance << endl;
    cout << "[Test_user_distance]intersection.x=" << intersection.latitude_ << ",intersection.y=" << intersection.longitude_ << endl;
}

void Test_Route_step()
{
    CRouteInfo route_info;

    route_info.Set_route_id(1);

    route_info.Add_node(CRoutePoint(39.9080075f, 116.394729f), 50);
    route_info.Add_node(CRoutePoint(39.9080285f, 116.394729f), 50);
    route_info.Add_node(CRoutePoint(39.9080585f, 116.394729f), 50);
    route_info.Add_node(CRoutePoint(39.9080785f, 116.394729f), 50);

    CRoutePoint curr_user_point(39.9080075f, 116.394749f);

    CObjectRouteInfo object_route_info;

    object_route_info.user_last_point_ = curr_user_point;
    object_route_info.step_ = 100;
    object_route_info.direction_ = 0;
    object_route_info.last_line_disance_ = 0.0f;

    for (int i = 0; i < 10; i++)
    {
        int err = route_info.Calculation_line(curr_user_point, &object_route_info);

        if (err == 0)
        {
            cout << "[Test_Route_step]user walk index(" << object_route_info.point_index_ << ")" << endl;
            cout << "[Test_Route_step]user walk distance(" << object_route_info.last_line_disance_ << ")" << endl;
            cout << "[Test_Route_step]user walk pos(" << object_route_info.user_last_point_.latitude_ << "," << object_route_info.user_last_point_.longitude_ << ")" << endl;
            cout << "[Test_Route_step]user line ratio(" << object_route_info.last_line_ratio_ << ")" << endl;
            cout << "[Test_Route_step]-----------------------\n" << endl;
        }
        else
        {
            cout << "[Test_Route_step]user walk error(" << route_info.Get_calculation_return_error(err).c_str() << ")" << endl;
            cout << "[Test_Route_step]-----------------------\n" << endl;
        }

        curr_user_point.latitude_ = curr_user_point.latitude_ + 0.00001f;
    }
}

void Test_User_step()
{
    CRouteInfo route_info;

    route_info.Set_route_id(1);

    route_info.Add_node(CRoutePoint(39.9080075f, 116.394729f), 50);
    route_info.Add_node(CRoutePoint(39.9080285f, 116.394729f), 50);
    route_info.Add_node(CRoutePoint(39.9080585f, 116.394729f), 50);
    route_info.Add_node(CRoutePoint(39.9080785f, 116.394729f), 50);

    CUserRoute user_route("freeeyes");

    user_route.Init(100.0f, 1, 0);

    CRoutePoint curr_user_point(39.9080075f, 116.394749f);

    for (int i = 0; i < 10; i++)
    {
        int err = route_info.Calculation_line(curr_user_point, user_route.Get_object_route_info());

        if (err == 0)
        {
            user_route.Set_object_route_info();
        }
        else
        {
            cout << "[Test_User_step]user walk error(" << route_info.Get_calculation_return_error(err).c_str() << ")" << endl;
            cout << "[Test_User_step]-----------------------\n" << endl;
        }

        curr_user_point.latitude_ += 0.00001f;
    }

    user_route.Display();

}

int main()
{
    //Test_distance();
    //Test_user_distance();
    //Test_Route_step();
    Test_User_step();

    getchar();
    return 0;
}