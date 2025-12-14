# Lightweight Tissue Tonometer for Detecting Pitting Edema

This repository contains the source code, calibration scripts, and supporting documentation for a capstone project at **Case Western Reserve University**: the design and implementation of a lightweight tissue tonometer device for detecting and classifying **pitting edema**.

---

## Overview
Pitting edema is a clinical symptom characterized by swelling and indentation of tissue due to fluid accumulation. Current diagnostic methods are subjective, relying on visual inspection and manual grading.  
This project introduces the foundation for a future **feedback-controlled tonometer** device that applies a known force and measures tissue displacement, enabling **objective, standardized diagnosis**.

---

## Subsystems
The device integrates three primary subsystems:

- **Force Sensing**  
  - Custom capacitive sensor using penny plates.  
  - FDC1004 capacitance-to-digital converter.  
  - Digital Butterworth low-pass filter for noise reduction.

- **Displacement Sensing**  
  - TCND5000 infrared photodiode sensor.  
  - Exponential low-pass filter for smoothing.  
  - Calibration script converts ADC values to displacement (mm).

- **Pressure Actuation**  
  - Pneumatic bellow system driven by syringe pump.  
  - Designed to apply ~9 N of controlled force.  
  - Displacement range: 6–10 cm.

---

## Repository Contents
- `fdc1004_calibration.ino` → Arduino script for force sensor calibration.  
- `tcnd5000_calibration.ino` → Arduino script for displacement sensor calibration.  
- `Lightweight Tissue Tonometer For Detecting Pitting Edema Technical Report` → Final technical report excerpts documenting methodology, design constraints, and results.
-     

---

## Features
- Sensor calibration with **digital filtering** (Butterworth + exponential smoothing).  
- Conversion of raw ADC values into **voltage and displacement measurements**.  
- Classification of pitting edema into **four clinical grades** based on indentation depth.  
- Debug output for plotting and verification.  

---

## Clinical Grading Scale
| Grade | Indentation Depth |
|-------|------------------|
| 1+    | < 2 mm |
| 2+    | 2–4 mm |
| 3+    | 4–6 mm |
| 4+    | 6–8 mm |

---

## PCB Versions
Two iterations of the printed circuit board (PCB) were developed during the project:

- **Version 1**  
  - Incorporated a motor driver to enable future integration of feedback control.  
  - Layout was less optimized, leading to challenges with signal stability and trace routing.  

- **Version 2**  
  - Motor driver was removed to simplify design and improve tracing.  
  - Enhanced connections for the FDC1004, TCND5000, and supporting components.  
  - More compact and reliable layout.  

Future students should build upon Version 2, but consider further improvements in **shielding** to prepare the design for clinical-grade testing.

---

## Bellow Versions
Multiple versions of the pneumatic bellow were designed and tested:

- **Version 1**  
  - Cast in Dragon Skin 20A silicone rubber.  
  - Wall thickness of 3 mm, triangular folds.  
  - Achieved ~8 mm displacement, below the target of 12 mm.  

- **Version 2**  
  - Reduced wall thickness to 2.5 mm for greater flexibility.  
  - Added a fourth fold to increase expansion area.  
  - Material switched to Silicone Shore 0030 for improved compliance.  
  - Achieved closer to the target displacement range.  

Future students should explore **harder and stiffer silicone materials** to ensure the bellow holds stable under pressure while still achieving the required displacement.

---

## Recommendations for Future Work
- **Electronics**:  
  - Explore PCB miniaturization for wearable applications.    
  - Improve shielding to reduce environmental noise in capacitance measurements.  
  - Investigate a more precise **IR displacement sensor**, since the current TCND5000 loses accuracy beyond ~15 mm.  
    - Note: The sensor begins measuring at ~50 mm due to the combined height of the bellow and acrylic plate, limiting precision.  
  - Improve the **capacitive force sensor design**:  
    - Consider dielectric material between plates.  
    - Add shielding (e.g., enclosing box) to reduce interference from external capacitance sources such as nearby human bodies.
    - Improve shilding on the coaxial wire.  

- **Mechanical Design**:  
  - Refine bellow molds for consistent wall thickness.  
  - Use stiffer silicone materials to improve stability under pressure.
  - Cast a bellow that is black or a darker color to reduce light environmental noise in the IR sensor.   

- **Software**:  
  - Implement closed-loop feedback control for force and displacement.  
  - Add rebound-time measurement to align with full clinical grading standards.    

---

## Getting Started
1. Clone this repository:
   ```bash
   git clone https://github.com/Jhosua351/lightweight-tissue-tonometer.git
