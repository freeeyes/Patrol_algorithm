#include "UserRoute.h"

CUserRoute::CUserRoute(string user_name) : user_last_distance(0.0l), step_(0.0l), route_id_(0), route_node_index_(unuse_user_point_index), route_direction_(0)
{
    user_name_ = user_name;
}

void CUserRoute::Init(double step, int route_id, char route_direction)
{
    step_            = step;
    route_id_        = route_id;
    route_direction_ = route_direction;
}

