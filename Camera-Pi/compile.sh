echo "Compilation in progress"
g++ $1.cpp -lopencv_highgui -lopencv_core -lopencv_legacy -lopencv_video -lopencv_features2d -lopencv_calib3d -lopencv_imgproc -lopencv_objdetect -L/root/git/raspberrypi/userland/build/lib -lmmal_core -lmmal -l mmal_util -lvcos -lbcm_host -lX11 -lXext -lrt -lstdc++ -L/root/git/robidouille/raspicam_cv -I/root/git/robidouille/raspicam_cv -o $1 Detection.cpp Webcam.cpp Face.cpp -lraspicamcv
echo "Compilation done"
