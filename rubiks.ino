/*
 * Rubik's Cube Movement Detector with Audio Feedback
 * Reads A3144 Hall Effect Sensors and plays musical notes (Sa Re Ga Ma Pa Dha Ni Sa)
 * for different cube face movements: Left, Right, Up, Down, Front, Back, Middle-Vertical, Middle-Horizontal
 * 
 * Hardware: ESP32 + 8x A3144 Hall sensors + Mini magnet speaker in cube core + LiPo battery
 * Detection: Triggers when rotation completes (magnet passes sensor)
 */

#include <Arduino.h>

// ===== PIN CONFIGURATION =====
// A3144 Hall Effect Sensor Pins (Digital Input - LOW when magnet detected)
// Using boot-safe GPIOs for reliable operation
const int SENSOR_LEFT   = 23;  // L move - Sa
const int SENSOR_RIGHT  = 22;  // R move - Re
const int SENSOR_UP     = 21;  // U move - Ga
const int SENSOR_DOWN   = 19;  // D move - Ma
const int SENSOR_FRONT  = 18;  // F move - Pa
const int SENSOR_BACK   = 5;   // B move - Dha
const int SENSOR_MIDDLE_V = 17;  // M move (vertical) - Ni
const int SENSOR_MIDDLE_H = 16;  // E move (horizontal) - Sa (high)

// Speaker Pin (PWM capable)
const int SPEAKER_PIN = 32;

// PWM Configuration
const int PWM_CHANNEL = 0;
const int PWM_RESOLUTION = 8;

// ===== MUSICAL NOTES (Indian Sargam in Hz) =====
// Using middle octave (Madhya Saptak)
const int NOTE_SA  = 262;  // C4 - Sa
const int NOTE_RE  = 294;  // D4 - Re
const int NOTE_GA  = 330;  // E4 - Ga
const int NOTE_MA  = 349;  // F4 - Ma
const int NOTE_PA  = 392;  // G4 - Pa
const int NOTE_DHA = 440;  // A4 - Dha
const int NOTE_NI  = 494;  // B4 - Ni
const int NOTE_SA_HIGH = 523; // C5 - Sa (upper)

// Note duration in milliseconds (optimized for mini magnet speaker)
const int NOTE_DURATION = 250;  // Shorter for quick feedback
const int NOTE_GAP = 30;        // Brief gap between notes

// ===== MOVEMENT DETECTION =====
struct SensorState {
  int pin;
  bool lastState;
  bool currentState;
  unsigned long lastDebounceTime;
  unsigned long lastTriggerTime;  // For cooldown period
  const char* name;
  int note;
};

SensorState sensors[] = {
  {SENSOR_LEFT,     HIGH, HIGH, 0, 0, "L (Left)",      NOTE_SA},
  {SENSOR_RIGHT,    HIGH, HIGH, 0, 0, "R (Right)",     NOTE_RE},
  {SENSOR_UP,       HIGH, HIGH, 0, 0, "U (Up)",        NOTE_GA},
  {SENSOR_DOWN,     HIGH, HIGH, 0, 0, "D (Down)",      NOTE_MA},
  {SENSOR_FRONT,    HIGH, HIGH, 0, 0, "F (Front)",     NOTE_PA},
  {SENSOR_BACK,     HIGH, HIGH, 0, 0, "B (Back)",      NOTE_DHA},
  {SENSOR_MIDDLE_V, HIGH, HIGH, 0, 0, "M (Mid-Vert)",  NOTE_NI},
  {SENSOR_MIDDLE_H, HIGH, HIGH, 0, 0, "E (Mid-Horiz)", NOTE_SA_HIGH}
};

const int NUM_SENSORS = sizeof(sensors) / sizeof(sensors[0]);
const unsigned long DEBOUNCE_DELAY = 100; // milliseconds (increased for rotation completion)
const unsigned long COOLDOWN_PERIOD = 500; // Prevent re-trigger during same rotation

// ===== FUNCTION DECLARATIONS =====
void playNote(int frequency, int duration);
void playStartupMelody();
void checkSensors();

void setup() {
  Serial.begin(115200);
  delay(500);
  Serial.println("\n=== Rubik's Cube Movement Detector ===");
  Serial.println("Initializing...");

  // Configure sensor pins as INPUT_PULLUP
  // A3144 outputs LOW when magnet is near, HIGH otherwise
  for (int i = 0; i < NUM_SENSORS; i++) {
    pinMode(sensors[i].pin, INPUT_PULLUP);
    sensors[i].lastState = digitalRead(sensors[i].pin);
    sensors[i].currentState = sensors[i].lastState;
  }

  // Configure PWM for speaker
  ledcSetup(PWM_CHANNEL, 1000, PWM_RESOLUTION);
  ledcAttachPin(SPEAKER_PIN, PWM_CHANNEL);

  Serial.println("Playing startup melody...");
  playStartupMelody();

  Serial.println("\n=== Ready to detect movements ===");
  Serial.println("Rotate Rubik's cube faces to trigger notes!");
  Serial.println("\nNote Mapping (Sargam Scale):");
  Serial.println("  L (Left)       -> Sa  (262 Hz)");
  Serial.println("  R (Right)      -> Re  (294 Hz)");
  Serial.println("  U (Up)         -> Ga  (330 Hz)");
  Serial.println("  D (Down)       -> Ma  (349 Hz)");
  Serial.println("  F (Front)      -> Pa  (392 Hz)");
  Serial.println("  B (Back)       -> Dha (440 Hz)");
  Serial.println("  M (Mid-Vert)   -> Ni  (494 Hz)");
  Serial.println("  E (Mid-Horiz)  -> Sa' (523 Hz)");
  Serial.println("\nPowered by LiPo battery");
  Serial.println("================================\n");
}

void loop() {
  checkSensors();
  delay(10); // Small delay to prevent excessive CPU usage
}

// ===== SENSOR CHECKING WITH DEBOUNCE =====
void checkSensors() {
  unsigned long currentTime = millis();

  for (int i = 0; i < NUM_SENSORS; i++) {
    int reading = digitalRead(sensors[i].pin);

    // Check if state changed
    if (reading != sensors[i].lastState) {
      sensors[i].lastDebounceTime = currentTime;
    }

    // If enough time has passed, consider it a valid state change
    if ((currentTime - sensors[i].lastDebounceTime) > DEBOUNCE_DELAY) {
      // If state actually changed
      if (reading != sensors[i].currentState) {
        sensors[i].currentState = reading;

        // Trigger on falling edge (magnet detected - sensor goes LOW)
        // AND check cooldown period to avoid multiple triggers per rotation
        if (sensors[i].currentState == LOW && 
            (currentTime - sensors[i].lastTriggerTime) > COOLDOWN_PERIOD) {
          
          Serial.print("🎵 Rotation Complete: ");
          Serial.print(sensors[i].name);
          Serial.print(" -> ");
          Serial.print(sensors[i].note);
          Serial.println(" Hz");

          playNote(sensors[i].note, NOTE_DURATION);
          sensors[i].lastTriggerTime = currentTime;
        }
      }
    }

    sensors[i].lastState = reading;
  }
}

// ===== AUDIO FUNCTIONS =====
void playNote(int frequency, int duration) {
  if (frequency > 0) {
    ledcWriteTone(PWM_CHANNEL, frequency);
    delay(duration);
  }
  ledcWriteTone(PWM_CHANNEL, 0); // Stop sound
  delay(NOTE_GAP);
}

void playStartupMelody() {
  // Play ascending scale: Sa Re Ga Ma Pa Dha Ni Sa
  int melody[] = {NOTE_SA, NOTE_RE, NOTE_GA, NOTE_MA, NOTE_PA, NOTE_DHA, NOTE_NI, NOTE_SA_HIGH};
  int durations[] = {200, 200, 200, 200, 200, 200, 200, 400};

  for (int i = 0; i < 8; i++) {
    playNote(melody[i], durations[i]);
  }

  delay(300);

  // Play descending: Sa Ni Dha Pa Ma Ga Re Sa
  for (int i = 7; i >= 0; i--) {
    playNote(melody[i], 150);
  }
}

// ===== UTILITY FUNCTIONS =====
void printSensorStates() {
  Serial.print("Sensor States: ");
  for (int i = 0; i < NUM_SENSORS; i++) {
    Serial.print(sensors[i].name);
    Serial.print("=");
    Serial.print(sensors[i].currentState == LOW ? "ACTIVE" : "idle");
    Serial.print(" ");
  }
  Serial.println();
}
