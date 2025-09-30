"Symphony Cube – Smart Rubik’s Cube with Indian Music Integration"
   Symphony Cube is an innovative smart Rubik’s Cube designed to blend the joy of puzzles with the creativity of music. Unlike a traditional cube, Symphony Cube integrates Indian classical and contemporary music, RGB light effects, and interactive sensors, making it a unique tool for learning, play, and creativity.
   This project was conceptualized as part of Smart India Hackathon 2025 (SIH 2025) under the hardware innovation category. It is especially designed for children, enabling them not only to solve the cube but also to compose and experience music while playing.

>Features:
1) Indian Music Integration – Each move or face rotation can trigger musical notes inspired by classical instruments and ragas.
2) RGB Lighting Effects – Dynamic lights respond to rotations, patterns, and solved states, creating an immersive play experience.
3) Gamified Learning – Kids can learn music theory while engaging in puzzle-solving.
4) Music Creation Mode – Similar to a keyboard or mouth organ, the cube can be used to compose tunes interactively.
5) Slip Ring Mechanism – Ensures smooth electrical connections while cube faces rotate freely.
6) Built-in Speaker – Produces clear audio output for music playback and sound effects.
7) Child-Friendly Interaction – Designed to encourage creativity, learning, and fun through technology.

>Technical Overview:
  Core Components:
  1) ESP32 Controller – Main microcontroller with Wi-Fi and Bluetooth for processing and connectivity.
  2) Hall Effect Sensors – Detect cube face rotations and trigger music or light responses.
  3) Slip Rings – Enable uninterrupted electrical connections through rotating faces.
  4) RGB LEDs – Provide dynamic lighting effects for interaction and feedback.
  5) Speaker Module – Outputs sound and music generated from the cube.
     
  Software Stack:
  1) Programming Languages: C/C++ (Arduino framework for ESP32)
  2) Firmware: Custom logic for cube face detection, sound synthesis, and LED animations
  3) Libraries: ESP-IDF/Arduino libraries for sensor input, audio playback, and LED control
  
  Working Principle:
  1) Cube Rotation Detection: Hall effect sensors capture the orientation and movement of cube faces.
  2) Signal Processing: The ESP32 interprets sensor data and maps it to specific notes or effects.

>Output Generation:
1) Music notes are played through the speaker.
2) RGB LEDs glow dynamically based on movement or solving patterns.
3) Music Mode: Children can intentionally rotate faces in sequences to generate melodies, similar to playing an instrument.

>Feasibility and Impact:
1) Innovation: Combines puzzle-solving, music creation, and interactive technology in a single device.
2) Educational Value: Helps children learn pattern recognition, rhythm, and creativity.
3) Engagement: Encourages active play while integrating aspects of STEAM (Science, Technology, Engineering, Arts, Mathematics) learning.
4) Scalability: Potential to expand into multiplayer cubes, app-based music recording, or gamified learning platforms.

>Benefits:
1) Promotes appreciation of Indian cultural music among children.
2) Enhances cognitive development through problem-solving and creative expression.
3) Inspires innovation and curiosity in electronics, music, and design.
4) Bridges education and entertainment by turning a toy into a learning companion.

>Future Enhancements:
1) Mobile app for recording and sharing music created with the cube
2) Multiplayer “Symphony Cube Battles” via Bluetooth
3) Advanced AI integration for auto-generating music based on solving patterns
4) Voice interaction and rhythm-based challenges

>Getting Started (Prototype Stage):
1) Hardware Setup: Assemble ESP32, Hall sensors, slip rings, RGB LEDs, and speaker inside cube mechanism.
2) Firmware Upload: Flash the provided Arduino code to ESP32.
3) Power On: Rotate cube faces to see lights and hear music.
4) Experiment: Try creating melodies and explore new interaction patterns.

>References and Inspiration:
1) Indian classical music scales and ragas
2) DIY smart cube projects
3) ESP32 documentation and Arduino libraries
4) Studies on STEAM-based learning for children

>Authors and Contributors:
Developed by Team OverClocked Engineers for Smart India Hackathon 2025.
Special thanks to mentors, peers, and open-source contributors who supported this project.
