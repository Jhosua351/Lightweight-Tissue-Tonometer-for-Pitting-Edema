# Lightweight Tissue Tonometer for Detecting Pitting Edema

This repository contains the source code, calibration scripts, and supporting documentation for a capstone project at **Case Western Reserve University**: the design and implementation of a lightweight tissue tonometer device for detecting and classifying **pitting edema**.

---

## Overview
Pitting edema is a clinical symptom characterized by swelling and indentation of tissue due to fluid accumulation. Current diagnostic methods are subjective, relying on visual inspection and manual grading.  
This project introduces the set for a future **feedback-controlled tonometer** devices that applies a known force and measures tissue displacement, enabling **objective, standardized diagnosis**.

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
  - Displacement range: 6-10 cm.

---

## Repository Contents
- `fdc1004_calibration.ino` → Arduino script for force sensor calibration.  
- `tcnd5000_calibration.ino` → Arduino script for displacement sensor calibration.  
- `report/` → Final technical report excerpts documenting methodology, design constraints, and results.    

---

## Features
- Sensor calibration with **digital filtering** (Butterworth + exponential smoothing).  
- Conversion of raw ADC values into **voltage and displacement measurements**.  
- Classification of pitting edema into **four clinical grades** based on indentation depth.  
- Debug output for plotting and verification.  

---

## 📊 Clinical Grading Scale
| Grade | Indentation Depth |
|-------|------------------|
| 1+    | < 2 mm
| 2+    | 2–4 mm
| 3+    | 4–6 mm
| 4+    | 6–8 mm

---

## 🚀 Getting Started
1. Clone this repository:
   ```bash
   git clone https://github.com/Jhosua351/lightweight-tissue-tonometer.git
