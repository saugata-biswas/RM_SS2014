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
	const double jointMax[] = {5.840139, 2.617989, -0.0157081, 3.42919, 5.641589};
	const double jointMin[] = {0.01006921, 0.01006921, -5.0264, 0.0221391, 0.11062};

public:
	KDLInterface();
	bool SetArmPosition(const KDL::JntArray &);
	virtual ~KDLInterface();
};

}

#endif 
