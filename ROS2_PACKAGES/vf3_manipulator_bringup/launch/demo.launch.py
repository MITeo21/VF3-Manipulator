from launch import LaunchDescription
from launch_ros.actions import Node

def generate_launch_description():
    ld = LaunchDescription()

    command_node = Node(
        package="vf3_manipulator",
        executable="command",
    )

    position_giver_node = Node(
        package="vf3_manipulator",
        executable="position_giver"
    )

    friction_change_node = Node(
        package="vf3_manipulator",
        executable="friction_change"
    )

    dynamixel_rw_node = Node(
        package="dynamixel_sdk_examples",
        executable="read_write_node"
    )

    ld.add_action(command_node)
    ld.add_action(position_giver_node)
    ld.add_action(friction_change_node)
    ld.add_action(dynamixel_rw_node)

    return ld