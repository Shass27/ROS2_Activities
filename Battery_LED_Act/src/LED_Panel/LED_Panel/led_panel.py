#!/usr/bin/env python3
import rclpy
from rclpy.node import Node
from sys_interfaces.msg import LEDStat
from sys_interfaces.srv import ModLED

class LEDPanelNode(Node):
    def __init__(self):
        super().__init__("led_panel")
        self.led_stat = [0,0,0]
        self.led_state_publisher = self.create_publisher(LEDStat, "led_panel_state", 10)
        self.set_led_service = self.create_service(ModLED, "set_led", self.callback_set_led)
        self.get_logger().info("LED Panel node has started.")

    def callback_set_led(self, request: ModLED.Request, response: ModLED.Response):
        if (request.state==True):
            self.led_stat[request.led_num-1] = 1
        else:
            self.led_stat[request.led_num-1] = 0

        msg = LEDStat()
        msg.ledstat = self.led_stat
        self.led_state_publisher.publish(msg)

        return response

def main(args=None):
    rclpy.init(args=args)
    node = LEDPanelNode()
    rclpy.spin(node)
    rclpy.shutdown()


if __name__ == "__main__":
    main()
