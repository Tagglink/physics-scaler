const ipc = require('electron').ipcRenderer;

let calculate_button = document.getElementById("calculate");

let gravitational_constant = document.getElementById("gravitational_constant");
let earth_mass = document.getElementById("earth_mass");
let moon_mass = document.getElementById("moon_mass");
let earth_moon_distance = document.getElementById("earth_moon_distance");
let earth_radius = document.getElementById("earth_radius");
let moon_radius = document.getElementById("moon_radius");
let moon_speed = document.getElementById("moon_speed");

let invert_time_button = document.getElementById("invert_time");
let invert_mass_button = document.getElementById("invert_mass");
let invert_length_button = document.getElementById("invert_length");

let time_scale = document.getElementById("time_scale");
let mass_scale = document.getElementById("mass_scale");
let length_scale = document.getElementById("length_scale");

let time_exponent = document.getElementById("time_exponent");
let mass_exponent = document.getElementById("mass_exponent");
let length_exponent = document.getElementById("length_exponent");

time_scale.value = 1;
mass_scale.value = 1;
length_scale.value = 1;

time_exponent.value = 0;
mass_exponent.value = 0;
length_exponent.value = 0;

calculate_button.addEventListener('click', function(){
  ipc.once('calculation_finished', function(event, response) {
    InjectResponse(response);
  });
  ipc.send('calculate', { 
    "time_scale": time_scale.value, 
    "time_exponent": time_exponent.value, 
    "mass_scale": mass_scale.value, 
    "mass_exponent": mass_exponent.value, 
    "length_scale": length_scale.value, 
    "length_exponent": length_exponent.value
  });
});

AddInvertListener(invert_time_button, time_scale, time_exponent);
AddInvertListener(invert_mass_button, mass_scale, mass_exponent);
AddInvertListener(invert_length_button, length_scale, length_exponent);

function InjectResponse(response) {
  gravitational_constant.innerText = response["gravitational_constant"];
  earth_mass.innerText = response["earth_mass"];
  moon_mass.innerText = response["moon_mass"];
  earth_moon_distance.innerText = response["earth_moon_distance"];
  earth_radius.innerText = response["earth_radius"];
  moon_radius.innerText = response["moon_radius"];
  moon_speed.innerText = response["moon_speed"];
}

function AddInvertListener(button, scale_field, exponent_field) {
  button.addEventListener('click', function(){
    scale_field.value = 1 / parseFloat(scale_field.value);
    exponent_field.value = parseFloat(exponent_field.value) * -1;
  });
}