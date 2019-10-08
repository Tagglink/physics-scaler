#include <iostream>
#include <cmath>
#include <string>
#include <algorithm>
#include <napi.h>

namespace {
  const int state_length = 7;

  // meters^3, kilograms^-1 and seconds^-2
  const double gravitational_constant = 6.67 * pow(10, -11);

  // kilograms
  const double earth_mass = 5.97 * pow(10, 24);
  const double moon_mass = 7.35 * pow(10, 22);

  // meters
  const double earth_moon_distance = 384.4 * pow(10, 6);
  const double earth_radius = 6.3 * pow(10, 6);
  const double moon_radius = 1.7 * pow(10, 6);

  // meters per second
  const double moon_speed = 1024.74160;

} // namespace

inline double scaled_gravitational_constant(
  double c, 
  double mass_scale, 
  double length_scale, 
  double time_scale)
{
  c *= pow(length_scale, 3);
  c *= 1.0 / mass_scale;
  c *= 1.0 / (time_scale * time_scale);

  return c;
}

double* CalculateScale(
  const double time_scale, 
  const double mass_scale, 
  const double length_scale
  ) {
  double* new_state = new double[::state_length];
  
  new_state[0] = scaled_gravitational_constant(::gravitational_constant,
    mass_scale, length_scale, time_scale);
  
  new_state[1] = ::earth_mass * mass_scale;
  new_state[2] = ::moon_mass * mass_scale;

  new_state[3] = ::earth_moon_distance * length_scale;
  new_state[4] = ::earth_radius * length_scale;
  new_state[5] = ::moon_radius * length_scale;

  new_state[6] = (::moon_speed * length_scale) / time_scale;

  return new_state;
}

Napi::Object CalculateScaleWrap(const Napi::CallbackInfo& info) {
  Napi::Env env = info.Env();

  if (
    info.Length() < 1 || 
    !info[0].IsObject() 
    ){
    Napi::TypeError::New(env, "Expected a string, number and object.").
      ThrowAsJavaScriptException();
  }

  Napi::Object scales = info[0].As<Napi::Object>();
  Napi::Object state = Napi::Object::New(env);
  double time_scale = scales.Get("time_scale").As<Napi::Number>().DoubleValue() * 
    pow(10, scales.Get("time_exponent").As<Napi::Number>().DoubleValue());

  double mass_scale = scales.Get("mass_scale").As<Napi::Number>().DoubleValue() * 
    pow(10, scales.Get("mass_exponent").As<Napi::Number>().DoubleValue());
  
  double length_scale = scales.Get("length_scale").As<Napi::Number>().DoubleValue() *
    pow(10, scales.Get("length_exponent").As<Napi::Number>().DoubleValue());

  double* new_state = CalculateScale(
    time_scale,
    mass_scale,
    length_scale
  );
  
  state.Set("gravitational_constant", Napi::Number::New(env, new_state[0]));
  state.Set("earth_mass", Napi::Number::New(env, new_state[1]));
  state.Set("moon_mass", Napi::Number::New(env, new_state[2]));
  state.Set("earth_moon_distance", Napi::Number::New(env, new_state[3]));
  state.Set("earth_radius", Napi::Number::New(env, new_state[4]));
  state.Set("moon_radius", Napi::Number::New(env, new_state[5]));
  state.Set("moon_speed", Napi::Number::New(env, new_state[6]));

  delete[] new_state;

  return state;
}

Napi::Object InitAll(Napi::Env env, Napi::Object exports) {
  exports.Set("calculate_scale", Napi::Function::New(env, CalculateScaleWrap));
  return exports;
}

NODE_API_MODULE(physicsaddon, InitAll)