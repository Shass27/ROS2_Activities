import rclpy
from rclpy.node import Node
from sys_interfaces.srv import ModLED
from functools import partial

class BatteryNode(Node):
    def __init__(self):
        super().__init__("battery")
        self.batterystate = True
        self.time = 0

        self.modled_client = self.create_client(ModLED, "set_led")
        while not self.modled_client.wait_for_service(1):
            self.get_logger().warning("Waiting for set_led set_led server")

        self.battery_timer = self.create_timer(1, self.update_battery_state)

    def update_battery_state(self):
        self.time += 1

        if self.time == 4 and self.batterystate:
            self.time = 0
            self.batterystate = False
            self.get_logger().info("Battery is empty! Charging...")
            self.set_led(2, True)

        elif self.time == 6 and self.batterystate == False:
            self.time = 0
            self.batterystate = True
            self.get_logger().info("Battery is full.")
            self.set_led(2, False)

    def set_led(self, led_num, state):
        request = ModLED.Request()
        request.led_num = led_num
        request.state = state
        self.modled_client.call_async(request)

def main(args=None):
    rclpy.init(args=args)
    node = BatteryNode()
    rclpy.spin(node)
    rclpy.shutdown()

if __name__ == "__main__":
    main()