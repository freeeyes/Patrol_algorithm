#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <cmath>

const int unuse_user_point_index = -1;

//道路节点信息
class CRouteNode
{
public:
    CRouteNode() : latitude_(0.0f), longitude_(0.0f), routewidth_(0.0f), curr_line_length_(0.0f)
    {
    }

    CRouteNode(double latitude, double longitude, double routewidth)
    {
        latitude_   = latitude;
        longitude_  = longitude;
        routewidth_ = routewidth;
    }

    double latitude_;
    double longitude_;
    double routewidth_;
    double curr_line_length_;
};

//点信息
class CRoutePoint
{
public:
    CRoutePoint() : latitude_(0.0f), longitude_(0.0f)
    {
    }

    CRoutePoint(double latitude, double longitude)
    {
        latitude_ = latitude;
        longitude_ = longitude;
    }

    double latitude_;
    double longitude_;
};

//线路计算中需要的对象信息
class CObjectRouteInfo
{
public:
    CObjectRouteInfo() : point_index_(unuse_user_point_index), step_(0), direction_(0), last_line_disance_(0.0f)
    {

    }

    CRoutePoint user_last_point_;
    int point_index_;
    int step_;
    int direction_;
    double last_line_disance_;
};

double Point_to_point_square(CRoutePoint line_target_point, CRoutePoint line_source_point);

double Point_to_point_distance(CRoutePoint line_target_point, CRoutePoint line_source_point);

CRoutePoint Point_to_line_intersection(CRoutePoint line_start_point, CRoutePoint line_end_point, CRoutePoint target_point);

double Point_to_line_distance(CRoutePoint line_start_point, CRoutePoint line_end_point, CRoutePoint target_point, CRoutePoint& intersection_point);


