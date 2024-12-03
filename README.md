**README for Distance Sensing and TouchDesigner Integration**

---

### Overview

This project demonstrates the use of an Arduino-based distance sensor (GYTOF10M module) connected to TouchDesigner via serial communication. The system captures real-time distance data and visualizes it dynamically within the TouchDesigner environment. This project showcases a creative blend of hardware interaction and digital art.

---

### Key Features

- **Real-Time Distance Measurement**: Captures accurate distance values using the GYTOF10M sensor.
- **Data Visualization**: Maps distance values to visual elements in TouchDesigner for interactive displays.
- **Expandable**: Includes the potential to use additional parameters (e.g., signal strength, temperature) for more complex visualizations.

---

### Hardware Setup

1. **Components**:
   - **GYTOF10M distance sensor**.
   - **Arduino-compatible board** (e.g., Arduino Uno).
   - USB cable for Arduino-PC connection.

2. **Connections**:
   - **GYtof_TX → Pin 10** (Arduino RX).
   - **GYtof_RX → Pin 11** (Arduino TX).
   - **VCC → VCC**.
   - **GND → GND**.

---

### Software Setup

#### Arduino
1. Open the provided `arduino_usart.ino` file in Arduino IDE.
2. Upload the code to your Arduino board:
   - Select the appropriate COM port.
   - Match the baud rate to `115200`.
3. Verify the distance data is being output via the Arduino Serial Monitor.

#### TouchDesigner
1. Open TouchDesigner and create a new project.
2. Add a **Serial DAT** node:
   - Set the `Port` parameter to your Arduino’s COM port.
   - Match the baud rate (`115200`).
3. Parse the distance data:
   - Use CHOP nodes to process the incoming data.
   - Map the distance values to visual elements like object scale, position, or color.

---

### Code Highlights

- **Distance Calculation**:
  ```cpp
  my_tof.distance = (Re_buf[4] << 8) | Re_buf[5];
  ```
  Outputs distance in millimeters. Converted to centimeters before sending:
  ```cpp
  Serial.print((float)my_tof.distance / 10);
  ```
- **Data Parsing**: Ensures only valid frames are processed by verifying checksum:
  ```cpp
  if (sum == Re_buf[i]) { ... }
  ```

