#include <youbot_parser/KDLInterface.h>

namespace HardwareEncapsulation {

int KDLInterface::getMilliCount(){
	timeb tb;
	ftime(&tb);
	int nCount = tb.millitm + (tb.time & 0xfffff) * 1000;
	return nCount;
}


KDLInterface::KDLInterface() {
	youbot_hardware = RobotHardware::getInstance();
	
	youbot::YouBotManipulator *youBotArm;
	youBotArm = new youbot::YouBotManipulator("youbot-manipulator");
	youBotArm->doJointCommutation();
	youBotArm->calibrateManipulator();

}

bool KDLInterface::checkJointLimits(KDL::JntArray jointpositions){
	for (int i = 0; i < joinpositions.rows(); i++){
		if (!((jointpositions[i] <= jointMax[i]) && (jointposition[i] >= jointMin[i])))
			return false;
	} 
	return true;
}



bool KDLInterface::checkJointLimits(){
	
	double JointAngle;
	youbot::JointSensedAngle angle;
	
	for(std::size_t i=0;i<5;i++){
		youBotArm->getArmJoint(i+1).getData(angle);
		JointAngle = (double)angle.angle.value();
		if (!((JointAngle <= jointMax[i]) && (JointAngle >= jointMin[i])))
			return false;
	}
	
	return true;
}


bool KDLInterface::SetArmPosition(const KDL::JntArray &jointpositions){
	if(!KDLInterface::checkJointLimits(jointpositions))
		return false;
	
	std::vector<youbot::JointAngleSetpoint> jointSetAngle;
	jointSetAngle.resize(5);
	
	for (int i = 0; i < jointpositions.rows(); i++){
		jointSetAngle[i].angle = jointpositions[i]*radian;
	}
	
	youBotArm->setJointData(jointpositions);
	return true;
}

bool KDLInterface::SetArmPositionWithVelocity(const KDL::JntArray &jointvelocities){
	if(!KDLInterface::checkJointLimits(jointvelocities))
		return false;
	
	
	std::vector<youbot::JointVelocitySetpoint> jointSetVelocity;
	jointSetVelocity.resize(5);
	bool slow_down = false;
	
	double JointAngle;
	youbot::JointSensedAngle angle;
	
	for(std::size_t i=0;i<5;i++){
		youBotArm->getArmJoint(i+1).getData(angle);
		JointAngle = (double)angle.angle.value();
		if(((jointMax[i] - JointAngle) < torable_angular_dist) || ((JointAngle - jointMin[i]) < torable_angular_dist)){
			slow_down = true;
		}
			
	}
	
	
	for (int i = 0; i < jointvelocities.rows(); i++){
		if(slow_down){
			jointSetVelocity[i].angularVelocity = 0.01;
		}else{
			jointSetVelocity[i].angularVelocity = jointvelocities[i]*radian;
		}
	}
	
	youBotArm->setJointData(jointSetVelocity);
	return true;
}

bool KDLInterface::VelocityController(const KDL::JntArray &jointvelocities, int time_in_mills){
	int starting_time = KDLInterface::getMilliCount();
	while(abs(KDLInterface::getMilliCount() - starting_time) < time_in_mills){
		
		
		if(!KDLInterface::checkJointLimits())
			return false;
			
			
		KDLInterface::SetArmPositionWithVelocity(jointvelocities);
	}
	return true;
}

KDLInterface::~KDLInterface() {
	// TODO Auto-generated destructor stub
}

} /* namespace HardwareEncapsulation */
