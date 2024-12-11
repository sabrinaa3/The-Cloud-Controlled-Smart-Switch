# The-Cloud-Controlled-Smart-Switch

This is a group project from my engineering design lab. The Cloud-Controlled Smart Switch was designed to easily and conveniently enhance safety by reducing the risks associated with leaving home appliances on, such as potential fire hazards.

# How it works
This repo contains the code for the website and the backend communication with an ESP32 that triggers a relay switching an appliance on or off. By entering the IP address of the ESP32 found over local network into a browser, users gain access to the website and can toggle the appliance on or off and view the power of their appliance.

System Breakdown: 

- Buttons trigger JavaScript functions.
- JavaScript sends HTTP requests to the ESP32 server.
- The ESP32 processes the request and performs actions (e.g., toggling GPIO pins).
- Feedback can be displayed on the webpage for user confirmation.
  
![Screenshot 2024-12-11 121215](https://github.com/user-attachments/assets/7aadd267-2561-4bee-849b-b7281d561525)

# Setup Instructions

Hardware Requirements: 

- ESP32 microcontroller
- Relay module (for controlling appliances)
- Appliance to be controlled (e.g., a lamp or fan)
- Power supply for ESP32 and relay module
- Breadboard and jumper wires

Circuit: 

Connect the ESP32 to the relay module and the appliance as follows:

- ESP32 GPIO Pin: Connect to the control pin of the relay module.
- VCC: Connect to the 3.3V or 5V pin of the ESP32 (depending on the relay's requirement).
- GND: Connect to ESP32's GND.
- Relay Output: Connect the appliance in series with the relay output terminals.

Ensure all connections are secure and the appliance's power requirements match the relay specifications.

Software Setup: 

Install Required Tools:

- Download and install the Arduino IDE.
- Add the ESP32 board to the Arduino IDE.
  
Upload the Code:

- Open the provided files in the Arduino IDE.

Configure your Wi-Fi credentials in this part of the code:
*Note that we used our iPhone's hotspot*

const char* ssid = "Your_SSID";
const char* password = "Your_PASSWORD";
Select the appropriate board and port from the Tools menu.
Click Upload to flash the code to your ESP32.

Find the ESP32's IP Address:

- Open the Arduino IDE’s Serial Monitor.
- The ESP32 will print its IP address after connecting to Wi-Fi.

Access the Website:

- Open a web browser and enter the IP address displayed in the Serial Monitor.

You can now control the appliance via the web interface, viewing the power use and status of the appliance.

# Troubleshooting

ESP32 Not Connecting to Wi-Fi:

- Double-check your SSID and password in the code.
- Ensure the Wi-Fi network is operational and the ESP32 is within range.

Cannot Access Web Interface:

- Verify the IP address using the Serial Monitor.
- Ensure your device is on the same local network as the ESP32.

Relay Not Responding:

- Confirm the relay is connected to the correct GPIO pin (check the main.ino code for the assigned pin).
- Test the relay independently by toggling the GPIO pin manually.
  
Unexpected Behavior:

- Check power supply stability.
- Inspect all connections for loose wires.

# The Creators and Demo

https://youtu.be/SOHArXEwPrQ?si=N9ZeGFoTOBPwjlLe

