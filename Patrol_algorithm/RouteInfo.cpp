#include "RouteInfo.h"

CRouteInfo::CRouteInfo() : route_id_(0), route_node_count_(0)
{
}

void CRouteInfo::Set_route_id(int route_id)
{
    route_id_ = route_id;
}

int CRouteInfo::Get_route_id()
{
    return route_id_;
}

int CRouteInfo::Get_node_count()
{
    return route_node_count_;
}

void CRouteInfo::Add_node(CRoutePoint route_point, int route_width)
{
    CRouteNode node;

    node.latitude_ = route_point.latitude_;
    node.longitude_  = route_point.longitude_;
    node.routewidth_ = route_width;

    if (route_node_count_ > 0)
    {
        //计算上一个点到现在节点的距离
        CRouteNode last_node = route_node_list_[route_node_count_ - 1];
        CRoutePoint last_point(last_node.latitude_, last_node.longitude_);
        CRoutePoint curr_point(node.latitude_, node.longitude_);

        node.curr_line_length_ = route_node_list_[Get_node_count() - 1].curr_line_length_ + Point_to_point_distance(last_point, curr_point);
    }

    route_node_list_.push_back(node);
    route_node_count_++;
}

bool CRouteInfo::Get_line_point(int point_index, CRoutePoint& curr_line_point)
{
    if (point_index < 0 || point_index >= Get_node_count())
    {
        return false;
    }

    curr_line_point.latitude_  = route_node_list_[point_index].latitude_;
    curr_line_point.longitude_ = route_node_list_[point_index].longitude_;
    return true;
}

int CRouteInfo::Calculation_line(CRoutePoint user_curr_point, CObjectRouteInfo* object_route_info)
{
    if (route_node_count_ < 2)
    {
        return 1;
    }

    if (object_route_info->point_index_ == unuse_user_point_index)
    {
        //如果是第一个节点
        if (0 == object_route_info->direction_)
        {
            object_route_info->point_index_ = 0;
        }
        else
        {
            object_route_info->point_index_ = Get_node_count() - 1;
        }
    }

    if((object_route_info->point_index_ == Get_node_count() - 1 && 0 == object_route_info->direction_)
       || (object_route_info->point_index_ == 0 && 1 == object_route_info->direction_))
    {
        //如果已经走完，则不计算
        return 2;
    }

    //开始计算，从当前点开始，之后的所有线路点，用户距离哪个线路最近
    int min_point_index = 0;
    double min_distance = 0.0f;
    CRoutePoint min_intersection_point;
    Get_min_distance(object_route_info->point_index_, object_route_info->direction_, user_curr_point, min_point_index, min_intersection_point, min_distance);

    //判断当前距离是否大于最大路宽，属于无效点
    if (min_distance > route_node_list_[min_point_index].routewidth_)
    {
        return 3;
    }

    //计算是否超过最大步长，超过了属于无效点
    CRoutePoint  curr_line_start_point(route_node_list_[min_point_index].latitude_, route_node_list_[min_point_index].longitude_);
    double curr_line_distance = route_node_list_[min_point_index].curr_line_length_ + Point_to_point_distance(curr_line_start_point, min_intersection_point);

    if (curr_line_distance > object_route_info->last_line_disance_ && curr_line_distance - object_route_info->last_line_disance_ > object_route_info->step_)
    {
        return 4;
    }

    //修改对应的数据
    if (curr_line_distance > object_route_info->last_line_disance_)
    {
        object_route_info->last_line_disance_ = curr_line_distance;
        object_route_info->point_index_ = min_point_index;
        object_route_info->user_last_point_ = min_intersection_point;
        object_route_info->last_line_ratio_ = (curr_line_distance / route_node_list_[Get_node_count() - 1].curr_line_length_) * 100.0f;
    }

    return 0;
}

std::string CRouteInfo::Get_calculation_return_error(int err)
{
    if (0 == err)
    {
        return "calculation ok";
    }
    else if (1 == err)
    {
        return "incomplete line";
    }
    else if (2 == err)
    {
        return "line is finish";
    }
    else if (3 == err)
    {
        return "more than the road width";
    }
    else if (4 == err)
    {
        return "more than the step width";
    }
    else
    {
        return "unknow";
    }
}

void CRouteInfo::Get_min_distance(int point_index, char direction, CRoutePoint user_curr_point, int& min_point_index, CRoutePoint& min_intersection_point, double& min_distance)
{
    CRoutePoint line_start_point;
    CRoutePoint line_end_point;
    min_point_index = 0;
    min_distance = 0.0f;

    if (0 == direction)
    {
        //顺序方向
        int point_distance_Shortest = point_index;

        for (int i = point_index; i < Get_node_count() - 1; i++)
        {
            if (false == Get_line_point(i, line_start_point) || false == Get_line_point(i + 1, line_end_point))
            {
                break;
            }

            if (i == point_distance_Shortest)
            {
                min_point_index = point_index;
                min_distance = Point_to_line_distance(line_start_point, line_end_point, user_curr_point, min_intersection_point);
            }
            else
            {
                double curr_distance = 0.0f;
                CRoutePoint curr_intersection_point;

                curr_distance = Point_to_line_distance(line_start_point, line_end_point, user_curr_point, curr_intersection_point);

                if (curr_distance < min_distance)
                {
                    min_point_index = i;
                    min_distance = curr_distance;
                    min_intersection_point = curr_intersection_point;
                }
            }
        }
    }
    else
    {
        //逆序方向
        int point_distance_Shortest = point_index;

        for (int i = Get_node_count() - 1; i > 0; i--)
        {
            if (false == Get_line_point(i, line_start_point) || false == Get_line_point(i - 1, line_end_point))
            {
                break;
            }

            if (i == point_distance_Shortest)
            {
                min_point_index = point_index;
                min_distance = Point_to_line_distance(line_start_point, line_end_point, user_curr_point, min_intersection_point);
            }
            else
            {
                double curr_distance = 0.0f;
                CRoutePoint curr_intersection_point;

                curr_distance = Point_to_line_distance(line_start_point, line_end_point, user_curr_point, curr_intersection_point);

                if (curr_distance < min_distance)
                {
                    min_point_index = i;
                    min_distance = curr_distance;
                    min_intersection_point = curr_intersection_point;
                }
            }
        }
    }
}

