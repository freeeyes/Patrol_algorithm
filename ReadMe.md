# Route patrol algorithm

Support longitude and latitude route determination, set the route, and automatically attach to the existing route according to the points uploaded by the user's actual walking, and get the percentage of route completion.
Used for patrol trip statistics.
  
##install:  
(1) Use VS2017 under windows.    
(2) use ./configure;make under linux.     
  
##example:    

```C  
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
```  

##output:  
```  
[Test_User_step]user walk error(route is finished)
[Test_User_step]-----------------------

[Test_User_step]user walk error(route is finished)
[Test_User_step]-----------------------

(0,0)<0%>-->(39.908,116.395)<14.5636%>-->(39.908,116.395)<29.1271%>-->(39.908,116.395)<43.6907%>-->(39.9081,116.395)<72.2222%>-->(39.9081,116.395)<72.8178%>-->(39.9081,116.395)<87.3813%>-->(39.9081,116.395)<100%>
```  