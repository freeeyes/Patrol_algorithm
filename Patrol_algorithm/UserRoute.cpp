#include "UserRoute.h"

CUserRoute::CUserRoute(string user_name) : route_id_(0), route_direction_(0), user_curr_route_point_count_(0)
{
    user_name_ = user_name;
}

void CUserRoute::Init(double step, int route_id, char route_direction)
{
    route_id_                = route_id;
    route_direction_         = route_direction;
    object_route_info_.step_ = step;
}

CObjectRouteInfo* CUserRoute::Get_object_route_info()
{
    return &object_route_info_;
}

void CUserRoute::Set_object_route_info()
{
    if (user_curr_route_point_count_ > 0)
    {
        if (user_curr_route_point_list_[user_curr_route_point_count_ - 1].curr_route_ratio_ < object_route_info_.last_line_ratio_)
        {
            Add_route_point_list(object_route_info_.user_last_point_, object_route_info_.last_line_disance_, object_route_info_.last_line_ratio_);
        }
    }
    else
    {
        Add_route_point_list(object_route_info_.user_last_point_, object_route_info_.last_line_disance_, object_route_info_.last_line_ratio_);
    }
}

void CUserRoute::Clear()
{
    object_route_info_.Clear();
    user_curr_route_point_list_.clear();
    user_curr_route_point_count_ = 0;
}

void CUserRoute::Display()
{
    for (int i = 0; i < user_curr_route_point_count_; i++)
    {
        if (i == 0)
        {
            cout << "(" << user_curr_route_point_list_[i].curr_route_point_.latitude_
                 << "," << user_curr_route_point_list_[i].curr_route_point_.longitude_
                 << ")<" << user_curr_route_point_list_[i].curr_route_ratio_ << "%>";
        }
        else
        {
            cout << "-->(" << user_curr_route_point_list_[i].curr_route_point_.latitude_
                 << "," << user_curr_route_point_list_[i].curr_route_point_.longitude_
                 << ")<" << user_curr_route_point_list_[i].curr_route_ratio_ << "%>";
        }
    }

    cout << endl;
}

void CUserRoute::Add_route_point_list(CRoutePoint curr_route_point, double curr_point_distance, double curr_route_ratio)
{
    CUserRoutePointInfo user_route_point_info;

    user_route_point_info.curr_route_point_ = curr_route_point;
    user_route_point_info.curr_point_distance_ = curr_point_distance;
    user_route_point_info.curr_route_ratio_ = curr_route_ratio;

    user_curr_route_point_list_.push_back(user_route_point_info);
    user_curr_route_point_count_++;
}

