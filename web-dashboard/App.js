import React, { useEffect, useState } from "react";
import mqtt from "mqtt";
import "./App.css";
import policeLogo from "./components/Police-removebg.png";

const MQTT_BROKER_URL = "wss://test.mosquitto.org:8081";
const MQTT_TOPIC = "esp32/alcohol";

const drivers = [
  { name: "Ravi Kumar", phone: "9876543210", vehicle: "TS 08 AB 1234" },
  { name: "Sita Rani", phone: "9123456789", vehicle: "TS 09 CD 5678" },
  { name: "Manoj Yadav", phone: "9900112233", vehicle: "TS 10 EF 9101" },
  { name: "Anjali Gupta", phone: "9988776655", vehicle: "TS 11 GH 2345" }
];

export default function App() {
  const [alerts, setAlerts] = useState([]);
  const [activeTab, setActiveTab] = useState("home");
  const [selectedLocation, setSelectedLocation] = useState(null);
  const [isLoggedIn, setIsLoggedIn] = useState(false);

  // Load saved alerts
  useEffect(() => {
    const savedAlerts = JSON.parse(localStorage.getItem("alerts")) || [];
    setAlerts(savedAlerts);
  }, []);

  // MQTT connection
  useEffect(() => {
    const client = mqtt.connect(MQTT_BROKER_URL);

    client.on("connect", () => {
      console.log("Connected to MQTT broker");
      client.subscribe(MQTT_TOPIC);
    });

    client.on("message", (topic, message) => {
      const data = JSON.parse(message.toString());

      if (data.alcohol > 2000) {
        const randomDriver =
          drivers[Math.floor(Math.random() * drivers.length)];

        const newAlert = {
          alcoholLevel: data.alcohol,
          latitude: data.latitude || 17.519804,
          longitude: data.longitude || 78.372888,
          driverName: randomDriver.name,
          driverPhone: randomDriver.phone,
          driverVehicle: randomDriver.vehicle,
          timestamp: new Date().toISOString(),
          status: "pending"
        };

        const updatedAlerts = [newAlert, ...alerts];
        setAlerts(updatedAlerts);
        localStorage.setItem("alerts", JSON.stringify(updatedAlerts));
      }
    });

    return () => client.end();
  }, [alerts]);

  const markAsCompleted = (index) => {
    const updated = alerts.map((a, i) =>
      i === index ? { ...a, status: "completed" } : a
    );
    setAlerts(updated);
    localStorage.setItem("alerts", JSON.stringify(updated));
  };

  const deleteAlert = (index) => {
    const updated = alerts.filter((_, i) => i !== index);
    setAlerts(updated);
    localStorage.setItem("alerts", JSON.stringify(updated));
  };

  const filteredAlerts = {
    home: alerts.filter((a) => a.status !== "completed"),
    pending: alerts.filter((a) => a.status === "pending"),
    completed: alerts.filter((a) => a.status === "completed")
  };

  return (
    <div className="dashboard-container">
      <header className="dashboard-header">
        <img src={policeLogo} alt="Police Logo" className="police-logo" />
        <div>
          <h1>Telangana State Police</h1>
          <h3>Drunk Driving Dashboard</h3>
        </div>
      </header>

      <div className="tabs">
        <button onClick={() => setActiveTab("home")}>Home</button>
        <button onClick={() => setActiveTab("pending")}>Pending</button>
        <button onClick={() => setActiveTab("completed")}>Completed</button>
      </div>

      <h2>{activeTab.toUpperCase()} ALERTS</h2>

      {filteredAlerts[activeTab].length === 0 ? (
        <p>No alerts available</p>
      ) : (
        filteredAlerts[activeTab].map((alert, index) => (
          <div className="alert-card" key={index}>
            <p><b>Driver:</b> {alert.driverName}</p>
            <p><b>Phone:</b> {alert.driverPhone}</p>
            <p><b>Vehicle:</b> {alert.driverVehicle}</p>
            <p><b>Alcohol:</b> {alert.alcoholLevel}</p>

            <button onClick={() => setSelectedLocation(alert)}>
              View Location
            </button>

            {alert.status === "pending" && (
              <button onClick={() => markAsCompleted(index)}>
                Mark Completed
              </button>
            )}

            <button onClick={() => deleteAlert(index)}>Delete</button>
          </div>
        ))
      )}

      {selectedLocation && (
        <div className="map-popup">
          <button onClick={() => setSelectedLocation(null)}>Close</button>
          <iframe
            title="Map"
            width="100%"
            height="300"
            src={`https://maps.google.com/maps?q=${selectedLocation.latitude},${selectedLocation.longitude}&z=15&output=embed`}
          />
        </div>
      )}
    </div>
  );
}
