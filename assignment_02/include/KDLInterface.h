#ifndef KDL_INTERFACE_H_
#define KDL_INTERFACE_H_

#include <kdl/jntarray.hpp>
#include <youbot/YouBotBase.hpp>
#include <youbot/YouBotManipulator.hpp>
#include <vector>

namespace HardwareEncapsulation {

class KDLInterface {

private:
	bool checkJointLimits(KDL::JntArray);

public:
	KDLInterface();
	bool SetArmPosition(const KDL::JntArray &);
	virtual ~KDLInterface();
};

}

#endif 
