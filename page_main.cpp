#include <pgmspace.h>
#include "page_main.h"

const char PAGE_MAIN[] PROGMEM = R"=====( 
<!DOCTYPE html>
<html lang="en" class="js-focus-visible">
<head>
  <meta charset="UTF-8">
  <meta name="viewport" content="width=device-width, initial-scale=1.0">
  <title>The Cloud-Controlled Smart Switch</title>
  <style>
    table {
      width: 100%;
      border-spacing: 0px;
    }
    tr {
      border: 1px solid white;
      font-family: "Verdana", "Arial", sans-serif;
      font-size: 20px;
    }
    th {
      padding: 20px;
	  padding: 3px 15px;
      background-color: #343a40;
      color: #FFFFFF !important;
    }
    td {
	  height: 20px;
      padding: 3px 15px;
    }
    .status, .category {
      font-family: "Verdana", "Arial", sans-serif;
      font-size: 20px;
      font-weight: bold;
      color: #000000;
      padding-left: 10px;
      text-align: left;
    }
    .tabledata {
      font-size: 24px;
      position: relative;
      padding-left: 5px;
      padding-top: 5px;
      height: 25px;
      border-radius: 5px;
      color: #FFFFFF;
      line-height: 20px;
      transition: all 200ms ease-in-out;
      background-color: #00AA00;
    }
    .btn {
      background-color: #444444;
      color: white;
      padding: 10px 20px;
      border: none;
      border-radius: 10px;
      cursor: pointer;
      font-size: 16px;
    }
    .navbar {
      width: 100%;
      height: 50px;
      padding: 10px;
      background-color: #FFF;
      border-bottom: 5px solid #293578;
      display: flex;
      align-items: center;
    }
    .navtitle {
      float: left;
      height: 50px;
      font-family: "Verdana", "Arial", sans-serif;
      font-size: 50px;
      font-weight: bold;
      line-height: 50px;
      padding-left: 20px;
    } 
	table tr:first-child th:first-child {
      border-top-left-radius: 5px;
    }
    table tr:first-child th:last-child {
      border-top-right-radius: 5px;
    }
    table tr:last-child td:first-child {
      border-bottom-left-radius: 5px;
    }
    table tr:last-child td:last-child {
      border-bottom-right-radius: 5px;
    }
  </style>
</head>
<body style="background-color: #efefef;" onload="initialize()">

<header>
  <div class="navbar">
    <div class="navtitle">The Cloud-Controlled Smart Switch</div>
  </div>
</header>

<main class="container" style="margin-top:70px">
  <div class="category">Power Readings</div>
  <table style="width:50%; margin: 20px 0;">
    <thead>
      <tr>
        <th>Pin</th>
        <th>Power</th>
      </tr>
    </thead>
    <tbody>
      <tr>
        <td>Analog Pin 32</td>
        <td><div class="tabledata" id="W0">Loading...</div></td>
      </tr>
    </tbody>
  </table>

  <div class="category">Control</div>
  <button id="toggleButton" class="btn" onclick="toggleRelay()">Toggle</button>
  <div id="status" class="status">Status: Not connected</div>
</main>

<footer style="text-align: center; margin-top: 20px; color: #AAAAAA; font-family: 'Arial', sans-serif;">
  ESP32 Controls and Data Updates
</footer>

<script>
  let applianceStatus = "not connected";  // Initial appliance status

  function initialize() {
    updateStatus();
    setInterval(updateStatus, 1000); // Update status every second
    setInterval(updatePower, 500); // Update power readings every second
  }

  function toggleRelay() {
    if (applianceStatus === "not connected" || applianceStatus === "off") {
      fetch('/relay/on');
      applianceStatus = "on";  // Appliance turns on
      document.getElementById("toggleButton").innerText = "Toggle";  // Button text
    } else if (applianceStatus === "on") {
      fetch('/relay/off');
      applianceStatus = "off";  // Appliance turns off
      document.getElementById("toggleButton").innerText = "Toggle";  // Button text
    }
    displayStatus();
  }

  function updateStatus() {
    fetch("/getStatus")
      .then(response => response.text())
      .then(status => {
        applianceStatus = status === "on" ? "on" : status === "off" ? "off" : "not connected";
        displayStatus();
      });
  }

  function displayStatus() {
    const statusEl = document.getElementById("status");
    if (applianceStatus === "on") {
      statusEl.innerText = "Status: On";
      statusEl.style.color = "#00AA00"; // Green
    } else if (applianceStatus === "off") {
      statusEl.innerText = "Status: Off";
      statusEl.style.color = "#FFCC00"; // Yellow
    } else {
      statusEl.innerText = "Status: Not connected";
      statusEl.style.color = "#FF0000"; // Red
    }
  }

  function updatePower() {
    fetch("/getpowerUsage")
      .then(response => response.text())
      .then(power => {
        const powerElement = document.getElementById("W0");
        if (power && !isNaN(power)) {
          powerElement.innerText = `${power} W`;
        }
      })
      .catch(() => {
        document.getElementById("W0").innerText = "Error";
      });
  }
</script>

</body>
</html>
)=====";
