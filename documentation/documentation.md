# Documentation

## Ideation
For the Two-Wheeled Self-Balancing Robot (TWSBR), the primary challenge is to maintain balance while navigating various terrains. By integrating a LiDAR sensor, the robot can detect obstacles more accurately and adjust its path accordingly. This integration enhances the robot's navigation capabilities, making it more versatile in complex environments.
The core concept involves using gyroscopes and accelerometers to measure the robot's tilt and adjust the motors' speed to maintain balance. The addition of LiDAR allows the robot to map its surroundings and plan its path more effectively.

## Diagrams
TWSBR Design Diagram
Control Algorithm Flowchart

## Theory
The TWSBR uses a combination of gyroscopes and accelerometers to measure its tilt. These measurements are fed into a control algorithm (such as PID) that adjusts the motor speeds to keep the robot upright. The addition of a LiDAR sensor allows the robot to detect obstacles and plan a path, improving its navigation capabilities.
The gyroscope provides data on the rate of rotation, while the accelerometer measures the robot's tilt. By combining these sensor readings, the control algorithm can determine the robot's orientation and make real-time adjustments to the motors.

## Calculations
#### Parameters:
- Center of Gravity (CoG): 20 cm
- Mass of the robot: 5 kg
- Distance between wheels: 15 cm
- Wheel radius: 5 cm

#### Calculations:

1. Calculate the maximum angle of inclination (θ) using the formula:
   θ = arctan(CoG / distance between wheels)
   θ = arctan(20 / 15)
   θ ≈ 53.13°

2. Calculate the torque required to maintain balance:
   Torque = mass * gravity * CoG * sin(θ)
   Torque = 5 * 9.81 * 0.2 * sin(53.13°)
   Torque ≈ 7.86 Nm


## References
1. John Doe, "Robotics: Principles and Practices"
2. Jane Smith, "Advanced Sensor Integration"

