# AUTONOMOUS_OBSTACLE_AVOIDING_CAR

# PROJECT_OVERVIEW:
An autonomous obstacle-avoiding car that uses an ultrasonic sensor mounted on a servo motor to scan its surroundings at 0°, 90°, and 180°. An Arduino UNO processes distance data and controls navigation, while an L298N motor driver controls the speed and direction of the DC motors.

# COMPONENTS_USED:
-Arduino uno 
-Ultrasonic sensor 
-Servo motor
-L298N motor drive
-2x24000 mah lithium battery (3.7v)
-Battery holder
-4xDC motor
-4x wheels 
-Jumper wires 
-Switch

# HOW_IT_WORKS:
The ultrasonic sensor continuously measures the distance between the car and nearby obstacles. The sensor is mounted on a servo motor, which rotates to different angles to scan the left, front, and right sides of the car.

The Arduino UNO processes the distance data received from the ultrasonic sensor. When an obstacle is detected, the Arduino determines a clear direction and controls the car's movement accordingly. The L298N motor driver controls the speed and direction of the DC motors, allowing the car to move autonomously and avoid obstacles.

# FEATURES:
-Autonomous Navigation
-Obstacle Detection
-Automatic Obstacle Avoidance
-Servo-Based Scanning 
-Real-Time Decision Making 
-Motor Speed and Direction Control 

## Future Improvements
- Bluetooth control
- Smartphone control
- Camera-based navigation
