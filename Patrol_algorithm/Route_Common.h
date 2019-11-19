#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <cmath>

const int unuse_user_point_index = -1;

#define PLATFORM_WIN     0
#define PLATFORM_UNIX    1
#define PLATFORM_APPLE   2

#if defined(__WIN32__) || defined(WIN32) || defined(_WIN32) || defined(__WIN64__) || defined(WIN64) || defined(_WIN64)
#  define PSS_PLATFORM PLATFORM_WIN
#elif defined(__APPLE_CC__)
#  define PSS_PLATFORM PLATFORM_APPLE
#else
#  define PSS_PLATFORM PLATFORM_UNIX
#endif

#if PSS_PLATFORM == PLATFORM_WIN
#define PRINTF printf_s
#else
#define PRINTF printf
#endif

//��·�ڵ���Ϣ
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

//����Ϣ
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

//�û��ڵ���Ϣ
class CUserRoutePointInfo
{
public:
    CUserRoutePointInfo() : curr_point_distance_(0.0f), curr_route_ratio_(0.0f)
    {

    }

    CRoutePoint curr_route_point_;          //��ǰ�ڵ�·�ϵĵ���Ϣ
    double      curr_point_distance_;       //��ǰ����֪��·�����������
    double      curr_route_ratio_;          //��ǰ���·�߱���
};

//��·��������Ҫ�Ķ�����Ϣ
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

    CRoutePoint user_last_point_;  //��ǰӳ��·�ߵ�λ��
    int point_index_;              //�����һ��·�߽ڵ�ID
    double step_;                  //��ǰ��󲽽�
    int direction_;                //��ǰ����
    double last_line_disance_;     //��ǰ�����·�߾���
    double last_line_ratio_;       //��ǰ�����·�߱���
};

double Point_to_point_square(CRoutePoint line_target_point, CRoutePoint line_source_point);

double Point_to_point_distance(CRoutePoint line_target_point, CRoutePoint line_source_point);

CRoutePoint Point_to_line_intersection(CRoutePoint line_start_point, CRoutePoint line_end_point, CRoutePoint target_point);

double Point_to_line_distance(CRoutePoint line_start_point, CRoutePoint line_end_point, CRoutePoint target_point, CRoutePoint& intersection_point);


