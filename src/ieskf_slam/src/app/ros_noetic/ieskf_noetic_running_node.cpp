#include "wrapper/ros_noetic/ieskf_frontend_noetic_wrapper.h"

int main(int argc,char* argv[])
{
  ros::init(argc,argv,"front_end_running_node");
  ros::NodeHandle nh;
  std::shared_ptr<ROSNoetic::IESKFFrontEndWrapper>front_end_ptr;//这里只是声明了一个std::shared_ptr 类型的变量，他是个空指针，没有志向任何对象，因此不会发生构造
  front_end_ptr = std::make_shared<ROSNoetic::IESKFFrontEndWrapper>(nh);//分配并构造对象，返回的是共享指针,在这里分配内存构造对象，因此在这里发生构造。
  return 0;
}