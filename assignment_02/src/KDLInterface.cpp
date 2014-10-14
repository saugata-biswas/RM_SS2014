#include <youbot_parser/KDLInterface.h>

namespace HardwareEncapsulation {

KDLInterface::KDLInterface() {
	youbot_hardware = RobotHardware::getInstance();

}

bool KDLInterface::checkJointLimits(KDL::JntArray jointpositions){
	for (int i = 0; i < joinpositions.rows(); i++){
		if (!((jointpositions[i] <= jointMax[i]) && (jointposition[i] >= jointMin[i])))
			return false;
	} 
	return true;
}


bool KDLInterface::SetArmPosition(const KDL::JntArray &jointpositions){
	if(!KDLInterface::checkJointLimits(jointpositions))
		return false;
	
	youbot::YouBotManipulator *youBotArm;
	youBotArm = new youbot::YouBotManipulator("youbot-manipulator");
	youBotArm->doJointCommutation();
	youBotArm->calibrateManipulator();
	
	
	
	std::vector<youbot::JointAngleSetpoint> jointSetAngle;
	jointSetAngle.resize(5);
	
	for (int i = 0; i < joinpositions.rows(); i++){
		jointSetAngle[i].angle = jointpositions[i]*radian;
	}
	
	youBotArm->setJointData(jointpositions);
	return true;
}

KDLInterface::~KDLInterface() {
	// TODO Auto-generated destructor stub
}

} /* namespace HardwareEncapsulation */
