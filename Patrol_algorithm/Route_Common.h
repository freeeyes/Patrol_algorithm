#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <cmath>
#include <iostream>

using namespace std;

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

    void clear()
    {
        latitude_  = 0.0f;
        longitude_ = 0.0f;
    }

    double latitude_;
    double longitude_;
};

//用户节点信息
class CUserRoutePointInfo
{
public:
    CUserRoutePointInfo() : curr_point_distance_(0.0f), curr_route_ratio_(0.0f)
    {

    }

    CRoutePoint curr_route_point_;          //当前在道路上的点信息
    double      curr_point_distance_;       //当前在已知道路上已行走里程
    double      curr_route_ratio_;          //当前完成路线比率
};

//线路计算中需要的对象信息
class CObjectRouteInfo
{
public:
    CObjectRouteInfo() : point_index_(unuse_user_point_index), step_(0), direction_(0), last_line_disance_(0.0f), last_line_ratio_(0.0f)
    {

    }

    void Clear()
    {
        user_last_point_.clear();
        point_index_       = unuse_user_point_index;
        direction_         = 0;
        last_line_disance_ = 0.0f;
        last_line_ratio_   = 0.0f;
    }

    CRoutePoint user_last_point_;  //当前映射路线点位置
    int point_index_;              //最近的一个路线节点ID
    double step_;                  //当前最大步进
    int direction_;                //当前方向
    double last_line_disance_;     //当前已完成路线距离
    double last_line_ratio_;       //当前已完成路线比率
};

double Point_to_point_square(CRoutePoint line_target_point, CRoutePoint line_source_point);

double Point_to_point_distance(CRoutePoint line_target_point, CRoutePoint line_source_point);

CRoutePoint Point_to_line_intersection(CRoutePoint line_start_point, CRoutePoint line_end_point, CRoutePoint target_point);

double Point_to_line_distance(CRoutePoint line_start_point, CRoutePoint line_end_point, CRoutePoint target_point, CRoutePoint& intersection_point);


