#include <Wire.h>
#include <Adafruit_LSM303_U.h>
#include <math.h>

Adafruit_LSM303_Accel_Unified accel = Adafruit_LSM303_Accel_Unified(54321);
Adafruit_LSM303_Mag_Unified mag = Adafruit_LSM303_Mag_Unified(12345);

void setup() {
  Serial.begin(115200);
  delay(1000);

  if (!accel.begin()) {
    Serial.println("Error: acelerómetro no detectado.");
    while (1);
  }

  if (!mag.begin()) {
    Serial.println("Error: magnetómetro no detectado.");
    while (1);
  }

  Serial.println("LSM303 sensores funcionando");
}

void loop() {
  sensors_event_t a, m;
  accel.getEvent(&a);
  mag.getEvent(&m);

  // Aceleración
  float ax = a.acceleration.x;
  float ay = a.acceleration.y;
  float az = a.acceleration.z;

  // Calcular pitch y roll basados en Z hacia arriba
  float pitch = atan2(-ax, sqrt(ay * ay + az * az));
  float roll  = atan2(ay, az);

  // Magnetómetro
  float mx = m.magnetic.x;
  float my = m.magnetic.y;
  float mz = m.magnetic.z;

  // Compensación magnética con los nuevos ángulos
  float mx_comp = mx * cos(pitch) + mz * sin(pitch);
  float my_comp = mx * sin(roll) * sin(pitch) + my * cos(roll) - mz * sin(roll) * cos(pitch);

  // Calcular heading
  float heading = atan2(-mx_comp, my_comp) * 180.0 / PI;
  if (heading < 0) heading += 360.0;

  // Mostrar
  Serial.print("Heading: ");
  Serial.print(heading, 2);
  Serial.print("°  |  Accel [m/s²]: ");
  Serial.print(ax, 2); Serial.print(", ");
  Serial.print(ay, 2); Serial.print(", ");
  Serial.print(az, 2);
  Serial.print("  |  Mag [uT]: ");
  Serial.print(mx, 2); Serial.print(", ");
  Serial.print(my, 2); Serial.print(", ");
  Serial.println(mz, 2);

  delay(500);
}
