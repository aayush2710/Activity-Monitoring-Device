# Activity Monitoring Device
A small device which tracks 4 physical states.
1) Sitting
2) Standing
3) Walking
4) Running

Components Used - Genuino 101
Genuino 101 is a learning and development board based on Intel Curie module. The board recognises gestures, and features a six-axis accelerometer and gyroscope. It also hass a inbuilt Bluetooth Low Energy (BLE). The intel curie module has a inbuilt Pattern Matching Engine. It has a 128 node hardware neural network with two classification alogirthms - the RBF kernel SVM(Support Vector Machine) and K Nearest Neighbours Classification.

# Steps
1) Train the Genuino 101 Board - We collected datasets for various sensor values in 4 physical states. We trained the board using CuriePME library. Code is given [here](https://github.com/aayush2710/Activity-Monitoring-Device/blob/master/Training%20Data/Training%20Model/trainer/trainer.ino).
2) The prediction using RBF kernel SVM was transmitted to android app.
3) The [android app](https://github.com/aayush2710/Activity-Monitoring-Device/tree/master/ActivityMonitorAPP) recorded the values and stored it on our Google Firebase backend.
4) Daily stats were made available to users and appropriate recommendations were made.
