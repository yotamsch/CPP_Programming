#ifndef __ALGORITHM_REGISTRATION_H_
#define __ALGORITHM_REGISTRATION_H_

#include <functional>
#include <memory>

#include "PlayerAlgorithm.h"

class AlgorithmRegistration {
public:
	AlgorithmRegistration(std::string id, std::function<std::unique_ptr<PlayerAlgorithm>()>);
};

//TODO: follow in forum about the decision on whether to keep the typo in RSPPLAYER_##ID or to keep it in correct way as it is now
#define REGISTER_ALGORITHM(ID) \
AlgorithmRegistration register_me_##ID \
	(#ID, []{return std::make_unique<RSPPlayer_##ID>();} );

#endif