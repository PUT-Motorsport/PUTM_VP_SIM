# PUTM_VP_SIM
## Introduction
PUT Motorsport Vehicle Performance group project of Torque Vectoring algorithm using CarMaker and Simulink.
## Table on contents
- [Start simulation](#start-simulation)
- [Model description](#model-description)
- [Variables description](#variables)
- [Driver training and behavior](#driver)

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
## Driver training and behavior
Tu bedzie driver ale jeszcze go nie ma


