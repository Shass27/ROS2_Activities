ROS2 Activities

This repository contains a collection of small, independent ROS2 exercises developed while learning core concepts in robot software architecture.

Each folder represents a standalone ROS2 package or experiment.

ROS2_Act/
 ├── activity_01/      # A ROS2 activity (built on C++ or Python or both) to test concepts
 ├── activity_02/
 ├── activity_03/
 ├── ...
 ├── README.md
 └── .gitignore        # Ignores build/, install/, log/, etc.

Activities are intentionally kept concise to highlight one concept at a time.

⸻

To run and test the activities:

Clone the repo

git clone https://github.com/Shass27/ROS2_Activities.git
cd ROS2_Activities

Building and Running

colcon build --packages-select <package_name>
source install/setup.bash
ros2 run <package_name> <executable_name>

⸻

Purpose
	•	To develop a foundational understanding of ROS2.
	•	To document incremental learning through modular examples.
	•	To serve as a reference for future robotics and embedded systems work.
