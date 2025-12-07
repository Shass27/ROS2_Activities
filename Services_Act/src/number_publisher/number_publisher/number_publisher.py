import rclpy
from rclpy.node import Node
from example_interfaces.msg import Int64

class NumberPublisherNode(Node):
    def __init__(self):
        super().__init__("number_publisher")
        self.publisher_=self.create_publisher(Int64, "number", 10)
        self.number = 0
        self.timer_ = self.create_timer(1, self.publish_number)
        self.get_logger().info("Number Publisher started")

    def publish_number(self):
        msg = Int64()
        msg.data = self.number
        self.publisher_.publish(msg)
        self.number+=2

def main(args=None):
    rclpy.init(args=args)
    node = NumberPublisherNode()
    rclpy.spin(node)
    rclpy.shutdown()

if __name__ == "__main__":
    main()