This tool provides a visual analysis of transient responses and smoothing effects in electrical networks. 
By manipulating component values such as Inductance (L) and Capacitance (C), users can directly observe the impact on current and voltage ripple.


Supported Filter Topologies:
L-Filter: Inductive smoothing of the load current.

RC-Filter: Combination of resistance and capacitance for voltage stabilization.

LC-Filter: Second-order low-pass filter for maximum smoothing efficiency.

Direct Mode: Unfiltered representation for performance comparison.


Software Architecture
The project strictly follows the Model-View-Controller (MVC) design pattern:

Model: Numerical solver for the underlying Differential Equations (ODE) of the circuit components.

View: Custom rendering engine using Win32 GDI for flicker-free visualization of complex function graphs.

Controller: Abstraction layer coupling GUI events (sliders/buttons) with physical parameters.


Key Technical Features
Flicker-Free Rendering: Optimized graphics output by intercepting WM_ERASEBKGND and implementing manual background clearing.

Custom Coordinate System: Dynamic scaling engine supporting both linear and logarithmic axis representations.

Robust Memory Management: Full implementation of the Rule of Three (Destructor, Copy Constructor, Assignment Operator) for leak-proof dynamic memory handling.

Polymorphism: Utilization of abstract controller base classes for various control strategies.


![Strom_und_Spannungsglättung_C++](https://github.com/user-attachments/assets/b4476ba2-2bbf-461e-9e2d-00c23f23fa86)


