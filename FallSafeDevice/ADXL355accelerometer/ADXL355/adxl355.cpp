  #include "adxl355.h"
  
  /*
                   x  					| +g
                   |					|
                   |					|
                   |				    \/
                   |
   upright is like ------------- y 
  			      /
				 /
				/
			   /
              z
  */
  
  //initialize object with a serial number and x, y and z pins
  adxl355::adxl355(uint8_t sn, uint8_t x, uint8_t y, uint8_t z){
    serial_number = sn;
	xpin = x;
	ypin = y;
	zpin = z;
  }
  
  //set the x y and z axis raw sensor values
  void adxl355::update_values(){
    x = analogRead(xpin);
    y = analogRead(ypin);
    z = analogRead(zpin);
    convert_to_acceleration();
  }

  //convert the raw values to acceleration terms in g
  void adxl355::convert_to_acceleration(){
    x_acc = (float)-(x-340)/69;
    y_acc = (float)-(y-341)/69;
    z_acc = (float)(z-352)/69;
  }
  
  //rms value of 3-axis
  float adxl355::rms_acceleration(){
	  return(sqrt(x_acc*x_acc+y_acc*y_acc+z_acc*z_acc));
  }
  //detect fall
  bool adxl355::is_falling(){
	float prev_x = x;
	float prev_y = y;
	float prev_z = z;
	
	//close to freefall
	if(rms_acceleration()<freefall_value){
		delay(2);
		update_values();
		if(x-prev_x < 0 || x-prev_x == 0 || abs(x-prev_x) < 0.05){
			fall_triggered = true;
			return true;
		}
	}
	else
		return false;
  }

  //which direction is it oriented?
  String adxl355::get_orientation(){
		int direction;
		direction = orientation_direction;
		switch(direction){
			case 0: return upright;
			case 1: return backward_fall;
			case 2: return forward_fall;
			case 3: return left_fall;
			case 4: return right_fall;
			default: return "unknown";
		}
  }
  
 //orientation setter function
 void adxl355::set_orientation(){
	  //upright
	  if(x_acc > 0.9)
		  orientation_direction = 0;
	  //backward fall
	  else if(z_acc > 0.3)
		  orientation_direction = 1;
	  //forward fall
	  else if(z_acc < -0.3)
		  orientation_direction = 2;
	  //left fall
	  else if(y_acc > 0.3)
		  orientation_direction = 3;
	  //right fall
	  else if(y_acc < -0.3)
		  orientation_direction = 4;
  }

  //display the raw sensor data values
  void adxl355::display_raw_values(){
    Serial.print(x);
    Serial.print("    ");
    Serial.print(y);
    Serial.print("    ");
    Serial.println(z);
  }

  //display values in units of g
  void adxl355::display_values(){
    Serial.print(x_acc);
    Serial.print("g    ");
    Serial.print(y_acc);
    Serial.print("g    ");
    Serial.print(z_acc);
    Serial.println("g    ");
  }