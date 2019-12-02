#include "Route_Common.h"

double rad(double d)
{
    return d * pi / 180.0f;
}

double Point_to_point_square(CRoutePoint line_target_point, CRoutePoint line_source_point)
{
    return (line_target_point.latitude_ - line_source_point.latitude_)*(line_target_point.latitude_ - line_source_point.latitude_) + (line_target_point.longitude_ - line_source_point.longitude_)*(line_target_point.longitude_ - line_source_point.longitude_);
}

double Point_to_point_distance(CRoutePoint line_target_point, CRoutePoint line_source_point)
{
    double a;
    double b;
    double radLat1 = rad(line_target_point.latitude_);
    double radLat2 = rad(line_source_point.latitude_);
    a = radLat1 - radLat2;
    b = rad(line_target_point.longitude_) - rad(line_source_point.longitude_);
    double s = 2 * asin(sqrt(pow(sin(a / 2), 2) + cos(radLat1)*cos(radLat2)*pow(sin(b / 2), 2)));
    s = s * EARTH_RADIUS;
    s = s * 1000;
    return s;
}

CRoutePoint Point_to_line_intersection(CRoutePoint line_start_point, CRoutePoint line_end_point, CRoutePoint target_point)
{
    CRoutePoint intersection_point;

    double A = (line_start_point.longitude_ - line_end_point.longitude_) / (line_start_point.latitude_ - line_end_point.latitude_);
    double B = line_start_point.longitude_ - A * line_start_point.longitude_;
    /// > 0 = ax +b -y;  对应垂线方程为 -x -ay + m = 0;(mm为系数)
    /// > A = a; B = b;
    double m = target_point.latitude_ + A * target_point.longitude_;

    /// 求两直线交点坐标
    intersection_point.latitude_ = (m - A * B) / (A*A + 1);
    intersection_point.longitude_ = A * intersection_point.latitude_ + B;

    return intersection_point;
}

double Point_to_line_distance(CRoutePoint line_start_point, CRoutePoint line_end_point, CRoutePoint target_point, CRoutePoint& intersection_point)
{
    //矢量法
    double r = ((target_point.latitude_ - line_start_point.latitude_)*(line_end_point.latitude_ - line_start_point.latitude_) + (target_point.longitude_ - line_start_point.longitude_)*(line_end_point.longitude_ - line_start_point.longitude_)) / Point_to_point_square(line_start_point, line_end_point);

    if (r <= 0)
    {
        intersection_point = line_start_point;
        return Point_to_point_distance(line_start_point, target_point);    //第一种情况, 返回AP的长
    }
    else if (r >= 1)
    {
        intersection_point = line_end_point;
        return Point_to_point_distance(line_end_point, target_point);    //第二种情况, 返回BP的长度
    }
    else                           //第三种情况, 返回PC的长度
    {
        intersection_point = Point_to_line_intersection(line_start_point, line_end_point, target_point);
        return Point_to_point_distance(line_start_point, intersection_point);
    }
}

