# Yaron Tracker

IR based motion tracking system based on Raspberry Pi, NoIR camera, openFrameworks and OpenCV. It was initially developed for the Material for Solometrics by Yaron Maim as the MA SODA final show at Ufer Studios, UDK Berlin in December 2017.

![Material for Solometrics IR Tracking Device](https://rijnieks.com/images/projects/material-for-solometrics.jpg)

A IR pass filter blocks the visible light from entering the NoIR camera connected to a Raspberry Pi device. OpenCV is used to un-warp the perspective and convert the IR light tracker to x and y coordinates. OpenCV is used again to warp the final render into its allocated space on stage. Thus the 8-point calibration.

[Watch the reference video here](https://youtu.be/BLj_gSjkzxY).

Raspberry Pi spawns a WiFi network and the device hosts a web-based control interface. Calibration can be done with any network-enabled device with a web browser on board. SSH can be used to do advanced configuration or update the software remotely. 

## Usage

This openFrameworks app is built for openFrameworks version **0.9.8**. Make sure you have the following addons in the openFrameworks/addons folder.

- [ofxCv](https://github.com/kylemcdonald/ofxCv) (stable branch)
- [ofxCvPiCam](https://github.com/orgicus/ofxCvPiCam) (Raspberry Pi only)
- [ofxTrueTypeFontUC](https://github.com/kr15h/ofxTrueTypeFontUC)

Additionally you will use addons that come with openFrameworks by default.

- ofxGui
- ofxOpenCv
- ofxOsc

Edit the `addons.make` file and remove Raspberry-Pi-specific addons if you are compiling this on another system.

## Web Interface

Yes - it has one. There are many guides on how to make your Pi to spawn a WiFi network. PHP (yes, seriously) is used for the rather simple back-end. You can find the web interface related files in the [bin/data/web](bin/data/web) directory.

## License

This code is licensed under the terms of the [MIT license](LICENSE.md). If you use it, please make sure that you include the names of the authors: **Krisjanis Rijnieks** (code) and **Yaron Maim** (show).
