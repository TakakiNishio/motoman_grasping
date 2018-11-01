#include <moveit/move_group_interface/move_group.h>

int main(int argc, char** argv)
{
  // Initialization of the ROS node
  ros::init(argc, argv, "moving_the_robot");
  ros::NodeHandle node_handle;
  ros::AsyncSpinner spinner(1);
  spinner.start();

  // Initialization of moveit
  moveit::planning_interface::MoveGroupInterface group("arm");

  // Setting the start position
  robot_state::RobotState robot_state_start(*group.getCurrentState());
  group.setStartState(robot_state_start);

  // Setting the goal position
  std::map<std::string, double> joints;

  // <group_state name="default" group="arm">
  //   <joint name="joint_1" value="-0.0001745329" />
  //   <joint name="joint_2" value="-0.35203291" />
  //   <joint name="joint_3" value="2.27294228" />
  //   <joint name="joint_4" value="0.0003490659" />
  //   <joint name="joint_5" value="1.22173" />
  //   <joint name="joint_6" value="3.14159" />
  // </group_state>


  joints["joint_1"] = -0.785398163;
  joints["joint_2"] = -0.35203291;
  joints["joint_3"] = 2.27294228;
  joints["joint_4"] = 0.0003490659;
  joints["joint_5"] = 1.22173;
  joints["joint_6"] = 3.14159;

  group.setJointValueTarget(joints);

  // Running the moveit planning
  moveit::planning_interface::MoveGroup::Plan result_plan;
  group.plan(result_plan);
  group.move();

  ros::spinOnce();
  ros::shutdown();
  return 0;
}