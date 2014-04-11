#include <youbot_parser/KDLInterface.h>

namespace HardwareEncapsulation {

KDLInterface::KDLInterface() {
	youbot_hardware = RobotHardware::getInstance();

}

bool KDLInterface::checkJointLimits(KDL::JntArray jointpositions){

	return true;
}


bool KDLInterface::SetArmPosition(const KDL::JntArray &jointpositions){

	//check for joint limits and command arm position
	return false; //after implementation change it to true.
}

KDLInterface::~KDLInterface() {
	// TODO Auto-generated destructor stub
}

} /* namespace HardwareEncapsulation */
