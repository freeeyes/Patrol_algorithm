#include "Route_Common.h"

double Point_to_point_square(CRoutePoint line_target_point, CRoutePoint line_source_point)
{
    return (line_target_point.latitude_ - line_source_point.latitude_)*(line_target_point.latitude_ - line_source_point.latitude_) + (line_target_point.longitude_ - line_source_point.longitude_)*(line_target_point.longitude_ - line_source_point.longitude_);
}

double Point_to_point_distance(CRoutePoint line_target_point, CRoutePoint line_source_point)
{
    return sqrt(Point_to_point_square(line_target_point, line_source_point));
}

CRoutePoint Point_to_line_intersection(CRoutePoint line_start_point, CRoutePoint line_end_point, CRoutePoint target_point)
{
    CRoutePoint intersection_point;

    double A = (line_start_point.longitude_ - line_end_point.longitude_) / (line_start_point.latitude_ - line_end_point.latitude_);
    double B = line_start_point.longitude_ - A * line_start_point.longitude_;
    /// > 0 = ax +b -y;  ��Ӧ���߷���Ϊ -x -ay + m = 0;(mmΪϵ��)
    /// > A = a; B = b;
    double m = target_point.latitude_ + A * target_point.longitude_;

    /// ����ֱ�߽�������
    intersection_point.latitude_ = (m - A * B) / (A*A + 1);
    intersection_point.longitude_ = A * intersection_point.latitude_ + B;

    return intersection_point;
}

double Point_to_line_distance(CRoutePoint line_start_point, CRoutePoint line_end_point, CRoutePoint target_point, CRoutePoint& intersection_point)
{
    //ʸ����
    double r = ((target_point.latitude_ - line_start_point.latitude_)*(line_end_point.latitude_ - line_start_point.latitude_) + (target_point.longitude_ - line_start_point.longitude_)*(line_end_point.longitude_ - line_start_point.longitude_)) / Point_to_point_square(line_start_point, line_end_point);

    if (r <= 0)
    {
        intersection_point = line_start_point;
        return Point_to_point_distance(line_start_point, target_point);    //��һ�����, ����AP�ĳ�
    }
    else if (r >= 1)
    {
        intersection_point = line_end_point;
        return Point_to_point_distance(line_end_point, target_point);    //�ڶ������, ����BP�ĳ���
    }
    else                           //���������, ����PC�ĳ���
    {
        intersection_point = Point_to_line_intersection(line_start_point, line_end_point, target_point);
        double AC = r * Point_to_point_distance(line_start_point, line_end_point);  //����AC�ĳ���,(AC=r*|AB|)
        return sqrt(Point_to_point_square(line_start_point, target_point) - AC * AC); //�ٹ��ɶ�����PC�ĳ���
    }
}

