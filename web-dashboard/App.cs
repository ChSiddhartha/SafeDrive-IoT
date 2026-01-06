body {
margin: 0;
padding: 0;
font-family: "Segoe UI", Tahoma, Geneva, Verdana, sans-serif;
background: linear-gradient(to right, #c2d9ec, #e0f0fc); Light police blue gradient /
}
/Dashboard Container
.dashboard-container {
height: 100vh;
width: 100vw;
padding: 20px;
background-color: #ffffff;
box-sizing: border-box;
text-align: center;
overflow-y: auto;
}
/* Header Styles */
.dashboard-header {
display: flex;
align-items: center;
justify-content: space-between;
padding: 10px 20px;
background: linear-gradient(to right, #002855, #b30000);
color: white;
}
.police-logo {
width: 70px;
height: auto;
}
.header-text {
flex: 1;
}
.header-text h1 {
margin: 0;
font-size: 28px;
}
.header-text h3 {
margin: 5px 0 0 0;
font-weight: normal;
font-size: 18px;
}
.login-btn-container {
display: flex;
justify-content: flex-end;
}
.login-btn {
background-color: black;
border: none;
padding: 10px 20px;
font-size: 16px;
color: blue;
cursor: pointer;
border-radius: 5px;
}
.login-btn:hover {
background-color: blue;
color: white;
}
/* Alerts Grid */
.alerts-container {
display: grid;
grid-template-columns: repeat (3, 1fr); /* 3 alerts per row on desktop */
gap: 20px;
width: 100%;
max-width: 1200px;
margin: 20px auto;
padding: 10px;
box-sizing: border-box;
}
.alert-card {
background: linear-gradient(to right, #dbeeff, #f2f9ff);
border: 1px solid #8aaedf;
border-left: 6px solid #b30000;
padding: 15px 20px;
border-radius: 10px;
text-align: left;
transition: box-shadow 0.3s ease;
}
.alert-card:hover {
box-shadow: 0 8px 20px rgba(0, 0, 0, 0.1);
}
.alert-driver {
font-size: 20px;
font-weight: bold;
color: #002855;
text-transform: uppercase;
margin-bottom: 10px;
}
.alert-card p {
margin: 6px 0;
font-size: 15px;
color: #002855;
}
.alert-card strong {
color: #000;}
.alert-card.completed {
background-color: #e8f5e9;
border-left: 6px solid green;
}
/* Buttons */
button {
margin-top: 10px;
padding: 8px 14px;
border: none;
border-radius: 8px;
font-weight: bold;
cursor: pointer;
transition: background-color 0.3s;
display: inline-block;
}
.alert-card button {
margin-right: 10px;
}
/* View Location Button Police Blue */
button:first-of-type {
background-color:#002855;
color: white;
}
button:first-of-type:hover {
background-color: #1b3a66;
}
button:last-of-type {
background-color: #c30010;
white; color:
}
button:last-of-type:hover {
background-color: #9e000d;
}
/* Tabs */
.tabs {
display: flex;
justify-content: center;
margin: 20px 0;
}
.tabs button {
padding: 10px 20px;
border: none;
background: #ddd;
cursor: pointer;
margin: 0 5px;
border-radius: 5px;
font-weight: bold;
}
.tabs.active {
background-color: #007bff;
color: white;
}
.tabs button:hover {
background-color: #0056b3;
color: white;
}
/* Map OverLay */
.map-overlay {
position: fixed;
top: 0;
left: 0;
width: 100vw;
height: 100vh;
background-color: rgba(0, 0, 0, 0.7);
display: flex;
justify-content: center;
align-items: center;
z-index: 1000;
}
.map-popup{
background:
white;
padding: 20px;
width: 90%;
max-width: 800px;
border-radius: 12px;
box-shadow: 0 8px 30px Irgba(0, 0, 0, 0.3);
position: relative;
animation: fadeIn 0.3s ease;
}
.map-container {
margin-top: 25px;
text-align: center;
}
.map-container h4 {
margin-bottom: 10px;
color: #333;
}
iframe {
border-radius: 12px;
border: 0;
box-shadow: 0 4px 12px Irgba(0, 0, 0, 0.1);
}
/* Close Button */
.close-btn {
position: absolute;
top: 10px;
right: 15px;
background: #c30010;
border: none;
color: white;
font-size: 18px;
border-radius: 50%;
width: 32px;
height: 32px;
cursor: pointer;
transition: background-color 0.2s ease;
}
.close-btn:hover {
background-color: #9e000d;
}
/* Animation */
@keyframes fadeIn {
from { transform: scale(0.9); opacity: 0; }
to { transform: scale(1); opacity: 1; }
}
/* Responsive Design */
@media (max-width: 992px) {
.alerts-container {
grid-template-columns: repeat(2, 1fr); /* 2 alerts per row on tablet */
}
}
@media (max-width: 600px) {
.alerts-container {
grid-template-columns: 1fr; /* 1 alert per row on mobile */
}
}