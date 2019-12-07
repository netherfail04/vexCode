/*----------------------------------------------------------------------------*/
//bruhchain
//main.cpp
/*----------------------------------------------------------------------------*/

#include "vex.h"

// A global instance of vex::brain used for printing to the V5 brain screen
vex::brain       Brain;
vex::competition Competition;
vex::controller ctrl1 = vex::controller(vex::controllerType::primary);
//vex::controller ctrl2 = vex::controller(vex::controllerType::partner);
vex::motor FL = vex::motor(vex::PORT13,false);
vex::motor FR = vex::motor(vex::PORT19,false);
vex::motor BL = vex::motor(vex::PORT11,false);
vex::motor BR = vex::motor(vex::PORT20, false);
vex::motor Lift = vex::motor(vex::PORT17,false);       
vex::motor Ramp = vex::motor(vex::PORT18,false);
vex::motor IntakeL = vex::motor(vex::PORT15,false);
vex::motor IntakeR = vex::motor(vex::PORT12, false);

const double diameter = 10.16;
const double circumference = diameter * 3.141592; 

bool macroPressed = false;

double getDegs(double distanceInCm)
{
  return ((360 * distanceInCm) / circumference);
}

void pre_auton( void ) {
 //do the shit  
}

void FW(double time, bool wait)
{
  Brain.resetTimer();
  while(Brain.Timer < time * 1000)
  {
    BR.spin(vex::directionType::rev, 30, vex::percentUnits::pct);
    FR.spin(vex::directionType::rev, 30, vex::percentUnits::pct);
    BL.spin(vex::directionType::fwd, 30, vex::percentUnits::pct);
    FL.spin(vex::directionType::fwd, 30, vex::percentUnits::pct);
  }
  if(Brain.Timer >= time * 1000) {
    BR.stop();
    FR.stop();
    BL.stop();
    FL.stop();
  }
}

void BW(double time)
{
  Brain.resetTimer();
  while(Brain.Timer < time * 1000)
  {
    BR.spin(vex::directionType::fwd, 50, vex::percentUnits::pct);
    FR.spin(vex::directionType::fwd, 50, vex::percentUnits::pct);
    BL.spin(vex::directionType::rev, 50, vex::percentUnits::pct);
    FL.spin(vex::directionType::rev, 50, vex::percentUnits::pct);
  }
  if(Brain.Timer >= time * 1000) {
    BR.stop();
    FR.stop();
    BL.stop();
    FL.stop();
  }
}

//STACKING MACRO
//TODO:: Figure out how to get the bot to seamlessly stack.
void score( void ){
  FL.spin(vex::directionType::fwd, 30, vex::velocityUnits::pct);
  FR.spin(vex::directionType::rev, 30, vex::velocityUnits::pct);
  BL.spin(vex::directionType::fwd, 30, vex::velocityUnits::pct);
  BR.spin(vex::directionType::rev, 30, vex::velocityUnits::pct);
  IntakeL.spin(vex::directionType::fwd, 30, vex::velocityUnits::pct);
  IntakeR.spin(vex::directionType::rev, 30, vex::velocityUnits::pct);
  vex::task::sleep(1500);
  FL.stop();
  FR.stop();
  BL.stop();
  BR.stop();
  IntakeL.stop();
  IntakeR.stop();
}

void DeployArms(float timeSecs)
{
  IntakeL.spin(vex::directionType::fwd, 100, vex::velocityUnits::pct);
  IntakeR.spin(vex::directionType::rev, 100, vex::velocityUnits::pct);
  Lift.spin(vex::directionType::fwd, 100, vex::velocityUnits::pct);
  vex::task::sleep(1500);
  IntakeL.stop();
  IntakeR.stop();
  Lift.spin(vex::directionType::rev, 100, vex::velocityUnits::pct);
  vex::task::sleep(1500);
  Lift.stop();
}

void block( void){
  /*while(getDegs(100) <=  NULL){
    
  }*/
}

void TurnLeft(int speed, int degs)
{
    FL.resetRotation();
    FR.resetRotation();
    BL.resetRotation();
    BR.resetRotation();

    FL.rotateFor((degs * -2),vex::rotationUnits::deg, speed * -1, vex::velocityUnits::pct, false);
    FR.rotateFor((degs * -2),vex::rotationUnits::deg, speed, vex::velocityUnits::pct, false);
    BL.rotateFor((degs * -2),vex::rotationUnits::deg, speed * -1, vex::velocityUnits::pct, false);
    BR.rotateFor((degs * -2),vex::rotationUnits::deg, speed, vex::velocityUnits::pct, true);
}

void TurnRight(int speed, int degs)
{
    FL.resetRotation();
    FR.resetRotation();
    BL.resetRotation();
    BR.resetRotation();

    FL.rotateFor((degs * -2),vex::rotationUnits::deg, speed, vex::velocityUnits::pct, false);
    FR.rotateFor((degs * -2),vex::rotationUnits::deg, speed * -1, vex::velocityUnits::pct, false);
    BL.rotateFor((degs * -2),vex::rotationUnits::deg, speed, vex::velocityUnits::pct, false);
    BR.rotateFor((degs * -2),vex::rotationUnits::deg, speed * -1, vex::velocityUnits::pct, true);
}

void start_auton( void ) {
  DeployArms(2.0f);
  FW(2.0, true);
  BW(2.0);
  //vex::task::sleep(15000);
}

void usercontrol( void ) {
  //start_auton();
  while (1) {
    //STARTOF: AXIS CONTROLS

    FL.spin(vex::directionType::fwd, (ctrl1.Axis3.value() + ctrl1.Axis1.value()) / 2, vex::velocityUnits::pct);
    FR.spin(vex::directionType::rev, (ctrl1.Axis3.value() - ctrl1.Axis1.value()) / 2, vex::velocityUnits::pct);
    BL.spin(vex::directionType::fwd, (ctrl1.Axis3.value() + ctrl1.Axis1.value()) / 2, vex::velocityUnits::pct);
    BR.spin(vex::directionType::rev, (ctrl1.Axis3.value() - ctrl1.Axis1.value()) / 2, vex::velocityUnits::pct);

    //START_AUTON
    if(ctrl1.ButtonX.pressing() && ctrl1.ButtonUp.pressing())
    {
      ctrl1.Screen.clearScreen();
      ctrl1.Screen.print("user activated auton");
      start_auton();
    }

    //left-right
    /*
    if(ctrl1.Axis1.position() > 10){
      frpct -= ctrl1.Axis1.position();
      brpct -= ctrl1.Axis1.position();
    } else if(ctrl1.Axis1.position() < -10){
      flpct = 0;
      blpct = 0;
    } 
    */

    //stoping
    /*
    if(ctrl1.Axis1.position() < 10 && ctrl1.Axis1.position() > -10 && ctrl1.Axis3.position() < 10 && ctrl1.Axis3.position() > -10) {
      BR.stop();
      BL.stop();
      FR.stop();
      FL.stop();
    }
    */

    //ENDOF AXIS CONTROLS

    //BUTTON CONTROLS

    //lift
    if(ctrl1.ButtonR1.pressing())
    {
      Lift.spin(vex::directionType::fwd, 100, vex::velocityUnits::pct);
    }
    if(ctrl1.ButtonR2.pressing())
    {
      Lift.spin(vex::directionType::rev, 100, vex::velocityUnits::pct);
    }
    if(!ctrl1.ButtonR1.pressing() && !ctrl1.ButtonR2.pressing())
    {
      Lift.stop(vex::brakeType::hold);
    }

    //Rollers
    if(ctrl1.ButtonL2.pressing())
    {
      IntakeL.spin(vex::directionType::fwd, 100, vex::velocityUnits::pct);
      IntakeR.spin(vex::directionType::rev, 100, vex::velocityUnits::pct);
    }
    if(ctrl1.ButtonL1.pressing())
    {
      IntakeL.spin(vex::directionType::rev, 100, vex::velocityUnits::pct);
      IntakeR.spin(vex::directionType::fwd, 100, vex::velocityUnits::pct);
    }
    if(!ctrl1.ButtonL1.pressing() && !ctrl1.ButtonL2.pressing())
    {
      IntakeL.stop(vex::brakeType::hold);
      IntakeR.stop(vex::brakeType::hold);
    }

    //Tray
    if(ctrl1.ButtonRight.pressing())
    {
      Ramp.spin(vex::directionType::fwd, 100, vex::percentUnits::pct);
    }
    if(ctrl1.ButtonLeft.pressing())
    {
      Ramp.spin(vex::directionType::fwd, 40, vex::percentUnits::pct);
    }
    if(ctrl1.ButtonY.pressing())
    {
      Ramp.spin(vex::directionType::rev, 100, vex::percentUnits::pct);
    }
    if(!ctrl1.ButtonRight.pressing() && !ctrl1.ButtonY.pressing() && !ctrl1.ButtonLeft.pressing())
    {
      Ramp.stop(vex::brakeType::hold);
    }
    vex::task::sleep(20); //Sleep the task for a short amount of time to prevent wasted resources. 
  }
}

int main() {
    //Set up callbacks for autonomous and driver control periods.
    Competition.autonomous( start_auton );
    //start_auton();
    Competition.drivercontrol( usercontrol );   
    pre_auton();
    //Prevent main from exiting with an infinite loop.                        
    while(1) {
      vex::task::sleep(100);//Sleep the task for a short amount of time to prevent wasted resources.
    }    
}