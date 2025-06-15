from dynio import *
import rclpy
from rclpy.node import Node
from dpali_msgs.msg import DPaliAngles
import atexit

class DPaliBridge(Node):

    def __init__(self):
        super().__init__('dpali_bridge')
        dxl_io = dxl.DynamixelIO('/dev/ttyUSB0',115200)
        self.motors = [dxl_io.new_mx64(0,2),
                       dxl_io.new_mx64(1,2),
                       dxl_io.new_mx64(2,2),
                       dxl_io.new_mx64(1,2)]
        
        for motor in self.motors:
            motor.torque_enable()

        atexit.register(self.on_exit)
        
        self.publisher_ = self.create_publisher(DPaliAngles, 'dpali/current_angles', 10)
        timer_period = 0.1  # seconds
        self.timer = self.create_timer(timer_period, self.timer_callback)
        
        self.subscription = self.create_subscription(DPaliAngles, 'dpali/set_angles', self.listener_callback,10)

    def on_exit(self):
        self.get_logger().info("Destroying Node")
        for motor in self.motors:
            motor.torque_disable()

    def timer_callback(self):
        angles = self.read_angles()
        msg = DPaliAngles()
        msg.motor0 = angles[0]
        msg.motor1 = angles[1]
        self.publisher_.publish(msg)
        self.get_logger().info(f'Publishing angles: "{angles}"')
    
    def read_angles(self):
        angles = [0,0,0,0]
        for motor in range(len(self.motors)):
            angles[motor] = self.motors[motor].get_angle()
        return angles
    
    def listener_callback(self, msg:DPaliAngles):
        set_angles = [msg.motor0,
                      msg.motor1,
                      msg.motor2,
                      msg.motor3]
        for idx,motor in enumerate(self.motors):
            motor.set_angle(set_angles[idx])
        self.get_logger().info(f'Set angles: "{set_angles}"')

    
def main(args=None):
    rclpy.init(args=args)

    dpali_bridge = DPaliBridge()

    rclpy.spin(dpali_bridge)

    dpali_bridge.destroy_node()
    rclpy.shutdown()