#ifndef ROBOT_H_
#define ROBOT_H_

/*
 * This file represents the robot and all its functions
 *   by: Chris McClanahan
 *
 */

#include "CVcam.h"
#include "GuppyCam.h"
#include <stdlib.h>
#include "opencv/highgui.h"
#include "Point2D.h"
#include "vision.h"

#include "mapgen.h"
#include "../motors/old/motors_old.h"

/*===== Camera Settings ===========================================*/
/* Determines camera compatability.
 * This must be set to 0 to load videos via command line. 
 * Note -- this is dead, use config file
 */
//#define USE_FIREWIRE_CAMERA 0
/*=================================================================*/

class Robot
{
public:
	// default constructor, use a camera
	Robot();

	// constructor for loading a camera, or a video file
	Robot(const char* filename);

	// destructor
	virtual ~Robot();

	/* Cleans up any resources that were allocated
	 * Init will have this called on atexit (stdlib.h) so the
	 * user does not need to call this */
	static void destroy();

	/* the vision source */
	GuppyCam camera_firewire;
	CVcam camera_usb;

	/* the vision processing object */
	Vision vp;
	int doVision;
	int doTransform;

	// initializes various things before main loop (mainly CV images)
	int init();

	// cleans up image buffers
	void releaseAllImages();

	// runs the robot (loops processFunc)
	void Go();

	// MAIN LOOP
	void processFunc();

	// initializes opengl and glut
	void initGlut();

	// refreshes glut window with raw image data
	void updateGlutDisplay();

	// gets image mask to mark void transform area
	void getGlutMask(int call);

	// starts the robot
	void startRobotThread(void* obj);

	/* the robot thread
	 * this is static so "atexit()" works */
	static pthread_t robotThread;

	// connects to the camera (USB or 1394)
	void connectToCamera();
	// sorry to hack camera sorce this way...
	int USE_FIREWIRE_CAMERA;
	// to load a video
	std::string videofilename;

	// gets raw image
	int GrabImage();

	// view to display
	int trackbarVal;

	// structure for saving video
	CvVideoWriter* cvVideoWriter;
	void createVideoWriter();

	// velocity headings for robot
	// heading.x = rotational speed
	// heading.y = forward speed
	Point2D<int> heading_vision;
	Point2D<int> heading_sensors;
	Point2D<int> heading_main;
	Point2D<int> heading_mapping;

	// avg heading control
	// k_motors = the % of new value to use
	float k_motors;

	// xml conf
	void LoadXMLSettings();

	// map generator and slam processing
	MapGen mapper;
	int doMapping;

	// motor control
	//Motors_Old motors;
	int motorsMaxSpeed;//0-255
	int useMotors;

	OSMC_driver osmcd;
};

#endif /*ROBOT_H_*/

