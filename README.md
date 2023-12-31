# Quadruped Robot Project

## Overview

This project implements a quadruped robot named OK1 using Arduino, with support for ROS and Gazebo simulation. The robot is designed to walk on four legs and can be controlled both physically and through software.

## Features

- Quadruped robot hardware based on Arduino Mega 2560.
- A Remote Controller
- ROS (Robot Operating System) support for high-level control and communication.
- Gazebo simulation environment for testing and development.
- Modular and extensible design for customization.

## Folder Structure

- **`/CAD-Hardware`**: Contains 3D printing files for the robot parts.
- **`/Arduino`**: Arduino code for controlling the robot.
- **`/ROS_ws`**: ROS packages for communication and control.
- **`/media`**: Files for Gazebo simulation.

![render0](https://github.com/omerKurkutlu/OK1-QuadrupedRobot/assets/53236244/e8f19957-b274-43f2-a274-e71f6e638073)




## Enjoying OK1 Robot (Video)

[![We are enjoying OK1 Robot.](https://img.youtube.com/vi/7ynvawNMwWk/0.jpg)](https://www.youtube.com/watch?v=7ynvawNMwWk&ab_channel=%C3%96merKurkutlu)


## Remote controller usage instructions 
![remote](https://github.com/omerKurkutlu/OK1-QuadrupedRobot/assets/53236244/2ecdcddc-efc1-45f6-b638-c44f203aaf1d)


## Getting Started for ROS and Gazebo

Follow these steps to get started with the ROS and Gazebo simulation environment for the OK1 Quadruped Robot:

1. **Clone the Repository:**

    ```bash
    git clone https://github.com/omerKurkutlu/OK1-QuadrupedRobot.git
    ```

2. **Navigate to the ROS Workspace:**

    ```bash
    cd ROS_ws
    ```

3. **Build the ROS Workspace:**

    ```bash
    catkin_make
    ```

4. **Source the Workspace:**

    ```bash
    source ./devel/setup.bash
    ```

5. **Launch the Robot:**

    - For Rviz Visualization:

        ```bash
        roslaunch ok1_moveit_config demo.launch
        ```

    - For Gazebo Simulation:

        ```bash
        roslaunch ok1_moveit_config demo_gazebo.launch
        ```

These commands will set up the necessary environment for ROS and Gazebo, allowing you to visualize and simulate the OK1 Quadruped Robot. Make sure to follow the instructions carefully, and feel free to explore the ROS workspace for additional details.
 
![r1](https://github.com/omerKurkutlu/OK1-QuadrupedRobot/assets/53236244/10049687-1cb5-4f1a-949e-f875c591d6bd)


## OK1 Robot Simulation (Video)
[![OK1 Robot - Quadruped Robot Gazebo Simulation](https://img.youtube.com/vi/0DxQdT6U4pM/0.jpg)](https://www.youtube.com/watch?v=0DxQdT6U4pM&list=PLxYZuRPj6mQbpEWxYQ2gAdy5SrHOGtlZl&ab_channel=%C3%96merKurkutlu)
[![OK1 Robot - Quadruped Robot based on ROS and MoveIt](https://img.youtube.com/vi/SKkTH99PJiU/0.jpg)](https://www.youtube.com/watch?v=SKkTH99PJiU&list=PLxYZuRPj6mQbpEWxYQ2gAdy5SrHOGtlZl&index=2&ab_channel=%C3%96merKurkutlu)

## 3D Printing Files and Assembly Instructions

You can find the 3D printing files in the designated folders. Feel free to explore the following directories:

- [Folder 1: OK1 Printing Files]([link/to/folder1](https://github.com/omerKurkutlu/OK1-QuadrupedRobot/tree/main/CAD-Hardware/OK1-stl))
- [Folder 2: Remote Controller Printing Files]([link/to/folder1](https://github.com/omerKurkutlu/OK1-QuadrupedRobot/tree/main/CAD-Hardware/Remote-stl))

Additionally, assembly instructions are available in a series of video tutorials. Follow the steps in the video series linked below:

[Assembly Video Series]([link/to/assembly/videos](https://www.youtube.com/watch?v=DqhxIvC9eWk&list=PLxYZuRPj6mQb903nfbroYomobq1NtwxHy&pp=gAQBiAQB))






### OK1 Printings

| NO. | Part Name                             | QTY. |
| --- | ------------------------------------- | ---- |
| 1   | Chassis_Sholder_plate_Rear            | 2    |
| 2   | Chassis_Sholder_plate_Front           | 2    |
| 3   | Chassis_plate_for_electronics        | 1    |
| 4   | Chassis_plate_for_battery            | 1    |
| 5   | Chassis_side_plate_with_socket_hole  | 1    |
| 6   | Chassis_side_plate                   | 1    |
| 7   | Chassis_bridge_upper                 | 2    |
| 8   | Chassis_brigde_lower                 | 2    |
| 9   | cover_back                           | 1    |
| 10  | cover_front                          | 1    |
| 11  | cover_upper                          | 1    |
| 12  | cover_bottom                         | 1    |
| 13  | cover_face                           | 1    |
| 14  | Leg_lowerLeg_Left                    | 2    |
| 15  | Leg_UpperLeg_Left                    | 2    |
| 16  | Leg_upperLeg_ServoConnector_left     | 2    |
| 17  | Chassis_sholder                      | 4    |
| 18  | shoe                                 | 4    |
| 19  | cover_upperLeg_liner_R               | 4    |
| 20  | Leg_lowerLeg_Right                   | 2    |
| 21  | Leg_UpperLeg_Right                   | 2    |
| 22  | Leg_upperLeg_ServoConnector_Right    | 2    |
|  | NUMBER OF PARTS | 41 |

### Remote Controller Printings
| NO.   | PART NAME            | QTY. |
| ---   | ---------------      | ---  |
| 1     | Back_Cover           | 1    |
| 2     | Remote_main_body_V2  | 1    |
| 3     | joystick_frame       | 3    |
|  | NUMBER OF PARTS | 5 |

### ELECTRONICS for OK1
| NO. | PART NAME               | QTY. |
| --- | ----------------------- | ---- |
| 1   | Arduino Mega 2560       | 1    |
| 2   | Relay Body              | 2    |
| 3   | NRF_module              | 1    |
| 4   | NRF_regulator           | 1    |
| 5   | lm2596board             | 1    |
| 6   | PowerDistributor        | 1    |
| 7   | battery                 | 1    |
| 8   | Regulator 10A DC-DC     | 4    |
| 9   | led                     | 6    |
| 10  | cam                     | 1    |
| 11  | Electronics_Switch      | 1    |
| 12  | Servo-DS3225MG          | 12   |
|  | NUMBER OF COMPONENTS | 32 |

### ELECTRONICS for Remote Controller
| NO. | PART NAME                | QTY. |
| --- | ------------------------ | ---- |
| 1   | Arduino Mega 2560        | 1    |
| 2   | NRF_module               |      |
| 3   | NRF_regulator            | 1    |
| 4   | Chassis-Front            | 1    |
| 5   | Chassis-Back             | 1    |
| 6   | lm2596 Board             | 1    |
| 7   | PowerDistributor Board   | 1    |
| 8   | battery 1.5 volt         | 4    |
| 9   | Battery case             | 1    |
| 10  | led(green&red)           | 2    |
| 11  | Nokia Screen 5510        | 1    |
| 12  | Remote_Switch            | 1    |
| 13  | JoyStick                 | 3    |
| 14  | Potansiometre            | 2    |
| 15  | Buttons                  | 8    |
| 16  | Robot_switch             | 1    |
| 17  | screws                   | 25   |

### HARDWAREs
| NO. | PART NAME    | QTY. |
| --- | ------------ | ---- |
| 1   | nut          | 4    |
| 2   | bearing      | 8    |
| 3   | Servo-horn   | 12   |
| 4   | screw-m3     | 30   |

### EXTERNALS
| NO. | PART NAME      | QTY. |
| --- | -------------- | ---- |
| 1   | LiPo Charger   | 1    |
| 2   | Box            | 1    |
| 3   | Jumpers        | 1    |
| 4   | Cables         | 1    |



