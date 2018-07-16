#ifndef ADXL355_H
#define ADXL355_H
#include<Arduino.h>

class adxl355{
	public:
		  uint8_t serial_number;
		  int xpin;
		  int ypin;
		  int zpin;
		  
		  //sensor axis variables
          int x;
          int y;
          int z;
		  
		  //acceleration in units of g
          float x_acc;
          float y_acc;
          float z_acc;
		  
		  //orientation storing variable
		  int orientation_direction;
		  
		  //other variables
		  bool 	fall_triggered = false;
          const String forward_fall = "forward";
          const String backward_fall = "backward";
		  const String left_fall = "left";
          const String right_fall = "right";
		  const String upright = "upright";
		  //value to set threshold of frefall value of g 
		  const float freefall_value = 0.33;
		  
		  //constructor
		  adxl355(uint8_t sn, uint8_t x, uint8_t y, uint8_t z);
		  //set sensor values direct
		  void update_values();
		  //convert to g
		  void convert_to_acceleration();
		  //get rms value of acceleration
		  float rms_acceleration();
		  
		  //orientation and fall related functions
		  void set_orientation();
		  bool is_falling();
		  String get_orientation();
		  
		  //display functions
		  void display_raw_values();
		  void display_values();
};
#endif