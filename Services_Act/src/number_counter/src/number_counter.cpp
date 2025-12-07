#include "rclcpp/rclcpp.hpp"
#include "example_interfaces/msg/int64.hpp"
#include "example_interfaces/srv/set_bool.hpp"

using namespace std::placeholders;

class number_counternode : public rclcpp::Node {
    rclcpp::Publisher<example_interfaces::msg::Int64>::SharedPtr publisher_;
    rclcpp::Subscription<example_interfaces::msg::Int64>::SharedPtr subscriber_;
    rclcpp::Service<example_interfaces::srv::SetBool>::SharedPtr server_;
    int number = 0;
    public:
        number_counternode() : Node("number_counter") {
            subscriber_ = create_subscription<example_interfaces::msg::Int64> (
                "number", 10, std::bind(&number_counternode::getnum, this, std::placeholders::_1));
            publisher_ = create_publisher<example_interfaces::msg::Int64>("number_count", 10);
            server_ = create_service<example_interfaces::srv::SetBool>("reset_counter",
                    std::bind(&number_counternode::reset, this, _1, _2));
            RCLCPP_INFO(get_logger(), "Number Counter started");
        }
    private:
        void getnum (const example_interfaces::msg::Int64::SharedPtr msg) {
            number += msg->data;
            auto newMsg = example_interfaces::msg::Int64();
            newMsg.data = number;
            publisher_->publish(newMsg);
        }
        void reset(
                    const example_interfaces::srv::SetBool::Request::SharedPtr request,
                    example_interfaces::srv::SetBool::Response::SharedPtr response)
        {
            if (request->data){
                number=0;
                response->success=true;
                response->message = "Reset succesful";
            }
            else {
                response->success=false;
                response->message = "Reset failed";
            }

        }
};

int main(int argc, char** argv) {
    rclcpp::init(argc, argv);
    auto node = std::make_shared<number_counternode>();
    rclcpp::spin(node);
    rclcpp::shutdown();
}