# PUTM_VP_SIM
## Introduction
PUT Motorsport Vehicle Performance group project of Torque Vectoring algorithm using CarMaker and Simulink.
## Table of contents
- [Start simulation](#start-simulation)
- [Model description](#model-description)
  - [Reference Generator](#reference-generator)
  - [Upper Controller](#upper-controler)
  - [Normal Load Transfer](#normal-load-transfer)
  - [Torque Allocator: Dynamic Distribution](#torque-allocator-dynamic-distribution)
  - [Dynamic Distribution Method](#dynamic-distribution-method)
- [Variables description](#variables)
- [IPGDriver's Learning and Adaptation Mechanisms](#driver)
  - [Learning Procedure](#learning-procedure)
  - [Adaptation Mechanisms](#adaptation-mechanisms)
  - [Use Cases Demonstrating Repeatability and Accuracy](#use-cases-demonstrating-repeatability-and-accuracy)

## Start simulation
Downlad src_cm4sl.zip file and unpack this.
To start the simulation, first we have to link Matlab (Simulink) with CarMaker. Open Matlab and choose working directory to src_cm4sl folder. Now run 2 scripts: cmenv.m - this script links Matlab and Simulink with CarMaker package installed on our computer. We have to make sure that IPG CarMaker package is installed in correct directory. The default directory for CarmMaker is
```bash
C:/IPG/carmaker/win64-12.0.1
```
If we have different path to our IPG package, we must change _cminstdir_ variable to your destination.
After running cmenv.m script, we can run the script.m file. This file contains constants values for our model. Further description
of these values is availble in [Variable Description](#variables) section.

Next step is opening the exact model we are working on. Run OPENXWD.mdl which is Simulink model of the car. Click on Open CarMaker GUI. CarMaker window is going to pop up, where we have to choose model of the car. [zdjęcie]. Then choose the track [zdjecie]. Now CarMaker is ready to run. We can make it by either pressing start button in CarMaker GUI or by running Simulink, but there is one more thing to do and it's driver adaptation. Firstly, change driver type to racing driver[zdjecie]. There are 2 types of driver adaptation programs[zdjecie]. The first one is to learn the basic steering of the car and it lasts for about half an hour. TO shorten this time we ca change the speed of simulation[zdjecie]. Second one is to learn the track and it's optional (the first training is enough for the driver to be consistent and fast). More about behavior and training of the driver can be read in [Driver training and behavior](#driver) section.
Navigation to Torque Vectoring model: CarMaker -> IPG Vehicle -> TV

## Model description

### Reference Generator

The Reference Generator converts the driver’s inputs into control references. The key inputs are the acceleration pedal input ($d_a$), brake pedal input ($d_b$), and the steering wheel angle ($\delta$). These inputs are used to derive the driver’s desired speed, acceleration, and direction of the vehicle. The generated references include the yaw rate request ($\gamma_{ref}$) and the total torque request ($T_t$).

The formulas for the reference generation are:

$$ \gamma_{ref} = \frac{v_x}{L(1 + K_u v_x^2)} \delta $$

$$ T_t = T_{max}(d_a - d_b) $$

where:
- $v_x$ is the longitudinal velocity,
- $L$ is the wheelbase,
- $K_u$ is the desired understeer gradient,
- $T_{max}$ is the maximum torque output of all motors combined.

### Upper Controller

The Upper Controller is responsible for controlling the vehicle dynamics by adhering to the control references (e.g., $\gamma_{ref}$). In this implementation, a yaw rate controller is used, designed with a Proportional-Integral (PI) architecture. The controller operates based on the error ($e_{\gamma}$) between the reference yaw rate ($\gamma_{ref}$) and the measured yaw rate ($\gamma$), producing a yaw moment ($\Delta M_z$) as output.

The controller equation is:

$$ \Delta M_z(t) = k_p e_{\gamma}(t) + k_i \int_{0}^{t} e_{\gamma}(\tau) d\tau $$

where:
- $k_p$ is the proportional gain,
- $k_i$ is the integral gain,
- $e_{\gamma} = \gamma_{ref} - \gamma$ is the yaw rate error.


### Normal Load Transfer

Normal load transfer occurs during maneuvers involving longitudinal or lateral acceleration due to inertia. This process is essential for the torque vectoring algorithm.

The normal loads $F_{zFL}$, $F_{zFR}$, $F_{zRL}$, $F_{zRR}$ of the front-left, front-right, rear-left, and rear-right tires, respectively, can be described as:

$$ F_{zFL} = \frac{mgl_r}{2L} - \frac{m_hg}{2L} \dot{v}_x - \frac{ml_rhg}{2Ll_s} \dot{v}_y $$

$$ F_{zFR} = \frac{mgl_r}{2L} - \frac{m_hg}{2L} \dot{v}_x + \frac{ml_rhg}{2Ll_s} \dot{v}_y $$

$$ F_{zRL} = \frac{mgl_f}{2L} + \frac{m_hg}{2L} \dot{v}_x - \frac{ml_fhg}{2Ll_s} \dot{v}_y $$

$$ F_{zRR} = \frac{mgl_f}{2L} + \frac{m_hg}{2L} \dot{v}_x + \frac{ml_fhg}{2Ll_s} \dot{v}_y $$

where $h_g$ is the height of the center of mass, $L = l_f + l_r$, $l_f$ is the distance from the center of gravity to the front axle, and $l_r$ is the distance from the center of gravity to the rear axle.


### Torque Allocator: Dynamic Distribution

The torque allocator distributes the total torque demand $T_t$ and the corrective yaw moment $\Delta M_z$ to the individual wheels. The dynamic distribution method accounts for the normal load transfer.

### Dynamic Distribution Method

The dynamic distribution adjusts the torques based on the ratio of the vertical load of each wheel to the total vertical load $F_{zT}$:

$$ T_{FL} = \frac{F_{zFL}}{F_{zT}} \left(T_t - \frac{\Delta M_z r_w}{l_s}\right) $$

$$ T_{FR} = \frac{F_{zFR}}{F_{zT}} \left(T_t + \frac{\Delta M_z r_w}{l_s}\right) $$

$$ T_{RL} = \frac{F_{zRL}}{F_{zT}} \left(T_t - \frac{\Delta M_z r_w}{l_s}\right) $$

$$ T_{RR} = \frac{F_{zRR}}{F_{zT}} \left(T_t + \frac{\Delta M_z r_w}{l_s}\right) $$

where:
- $T_{FL}$, $T_{FR}$, $T_{RL}$, $T_{RR}$ are the torques for the front-left, front-right, rear-left, and rear-right wheels respectively,
- $F_{zFL}$, $F_{zFR}$, $F_{zRL}$, $F_{zRR}$ are the vertical loads on these wheels,
- $F_{zT} = F_{zFL} + F_{zFR} + F_{zRL} + F_{zRR}$ is the total vertical load,
- $r_w$ is the wheel radius,
- $l_s$ is the half-width of the vehicle.

<a name="variables"></a>
## Variables description
All variables you can find in file _script.m_

List of variables and their placement:

ki=0.05; % gain of integrating controller - Upper Controller

kp=0.5; % gain of proportional controller - Upper Controller

g=9.81; % gravity acceleration - Torque distribution - FZFL, FZFR, etc. and T_FL, T_FR, etc.

L=2.6; % axle base - Reference Generator and Torque distribution - FZFL, FZFR, etc.

lr=0.5; % distance between rear axle to CoG - Torque distribution - FZFL, FZFR, etc.

lf=2.1; % distance between front axle to CoG - Torque distribution - FZFL, FZFR, etc.

h=0.25; % height of CoG - Torque distribution - FZFL, FZFR, etc. 

m=180; % car mass - Torque distribution - FZFL, FZFR, etc. and T_FL, T_FR, etc.

ls=1.242; % wheelbase - Torque distribution - FZFL, FZFR, etc. and T_FL, T_FR, etc.

rw=0.217; % wheel radius - Speed Estimator and Torque distribution - T_FL, T_FR, etc.

drive_ratio=10; % ratio of main gearbox - Torque distribution

<a name="driver"></a>
## IPGDriver's Learning and Adaptation Mechanisms
### Learning Procedure
IPGDriver incorporates a detailed learning procedure designed to ensure the driver model accurately reflects real-world driving behavior through systematic learning and adaptation. This procedure is essential for ensuring that the driver in the simulation can handle various driving conditions consistently and predictably.

Basic Knowledge Phase:

This phase involves initial parameter estimation based on simple maneuvers. For example, a step input is applied to the steering wheel, and the system measures the vehicle's response times. These responses help in determining the preview times (tPreview) and other crucial parameters.
The driver model adjusts its parameters iteratively to better match the desired course. For instance, if the vehicle initially deviates from a U-turn, adjustments are made until the model can accurately and consistently follow the desired path​​.
Longitudinal Dynamics:

This aspect of the learning involves optimizing acceleration and braking responses. The system learns how to manage speed based on the vehicle's dynamics and the required driving task, such as maintaining a specific speed profile or achieving a target velocity efficiently.
Parameters like throttle response and braking force are fine-tuned to ensure smooth and realistic longitudinal control, minimizing deviations from the desired speed​​.
Lateral Dynamics:

In lateral dynamics, the system focuses on steering accuracy. By collecting data on how the vehicle responds to steering inputs, the model can adjust its steering behavior to follow the intended path more closely.
The system uses gathered data to refine preview times and steering angles, ensuring the vehicle can navigate turns and maintain lane position accurately​​.
### Adaptation Mechanisms
IPGDriver's adaptation mechanisms ensure that the driver model evolves and improves its performance over time, learning from each simulation run.

Driver Adaption:

The driver model adapts to the vehicle's specific characteristics, such as its handling and response to inputs. This adaptation is crucial for ensuring that the model can handle the vehicle under various conditions consistently.
The adaption process includes continuous learning from the vehicle's reactions, which helps in fine-tuning the control actions for steering, throttle, and braking​​.
Race Driver Adaption:

For high-performance scenarios, such as racing, the driver model undergoes specialized adaption. This phase involves optimizing the driver model to achieve the best possible performance on a track, focusing on maximizing speed while maintaining control.
This optimization process includes monitoring and adjusting parameters related to longitudinal and lateral slip, ensuring that the vehicle can navigate the track at high speeds with precision​​.
### Use Cases Demonstrating Repeatability and Accuracy
Several use cases illustrate how IPGDriver's learning and adaptation ensure repeatability and accuracy in simulations.

ISO Lane Change:

The ISO lane change use case highlights the system's ability to improve performance through learning. Initially, an untrained driver model may struggle to follow the lane change maneuver accurately. However, after the learning process, the driver model can execute the lane change with high precision, demonstrating the system's ability to reduce variability and enhance control​​.
Following a Speed Profile:

In scenarios where the vehicle needs to follow a predefined speed profile, IPGDriver can maintain the desired speed with minimal deviation. This capability is a direct result of the driver model's learning and adaptation, which ensures that the vehicle's velocity closely aligns with the target speed throughout the simulation​​.
Conclusion
IPGDriver's comprehensive learning and adaptation mechanisms ensure that the driver model can handle various driving scenarios with consistency and accuracy. The process involves iterative learning, fine-tuning of control parameters, and specialized adaptations for different driving tasks. These capabilities make IPGDriver a robust tool for simulating realistic driving behavior and evaluating the performance of driving algorithms, providing reliable insights into how these algorithms might perform in real-world conditions.


