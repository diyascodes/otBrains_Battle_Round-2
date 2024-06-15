# Solution code for the Two-wheeled Self-Balancing Robot

import time

class TWSBRobot:
    def __init__(self):
        self.angle = 0
        self.motor_speed = 0

    def read_sensors(self):
        # Simulated sensor readings
        self.angle = 0  # This would be replaced with actual sensor data

    def calculate_motor_speed(self):
        # Simplified PID control
        Kp = 1.0
        self.motor_speed = -Kp * self.angle

    def update_motors(self):
        # Simulate motor update
        print(f"Motor speed set to {self.motor_speed}")

    def balance(self):
        self.read_sensors()
        self.calculate_motor_speed()
        self.update_motors()

robot = TWSBRobot()
while True:
    robot.balance()
    time.sleep(0.1)
