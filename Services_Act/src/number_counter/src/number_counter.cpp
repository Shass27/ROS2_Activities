#include "rclcpp/rclcpp.hpp"
#include "example_interfaces/msg/int64.hpp"

class number_counternode : public rclcpp::Node {
    rclcpp::Publisher<example_interfaces::msg::Int64>::SharedPtr publisher_;
    rclcpp::Subscription<example_interfaces::msg::Int64>::SharedPtr subscriber_;
    public:
        number_counternode() : Node("number_counter") {
            subscriber_ = create_subscription<example_interfaces::msg::Int64> (
                "number", 10, std::bind(&number_counternode::getnum, this, std::placeholders::_1));
            publisher_ = create_publisher<example_interfaces::msg::Int64>("number_count", 10);
            RCLCPP_INFO(get_logger(), "Number Counter started");
        }
    private:
        void getnum (const example_interfaces::msg::Int64::SharedPtr msg) {
            auto newMsg = example_interfaces::msg::Int64();
            newMsg.data = msg->data;
            publisher_->publish(newMsg);
        }
};

int main(int argc, char** argv) {
    rclcpp::init(argc, argv);
    auto node = std::make_shared<number_counternode>();
    rclcpp::spin(node);
    rclcpp::shutdown();
}