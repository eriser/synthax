#include "sin_am.h"

/*
    ========================
    construction/DESTRUCTION
    ========================
*/

synthax::primitive::modulation::sin_am::sin_am(param* vn, param* p, param* o, param* a, node* mod) {
    assert(vn->is_unmutatable() && vn->is_discrete());
    variableNum = vn->get_dvalue();

    params.push_back(vn);
    params.push_back(p);
    params.push_back(o);
    params.push_back(a);

    descendants.push_back(mod);
    arity = 1;

    symbol = "sin_am";
}

synthax::primitive::modulation::sin_am::~sin_am() {
}

/*
    =========
    OVERRidES
    =========
*/

synthax::primitive::modulation::sin_am* synthax::primitive::modulation::sin_am::get_copy() {
    return new sin_am(params[0]->get_copy(), params[1]->get_copy(), params[2]->get_copy(), params[3]->get_copy(), descendants[0] == NULL ? NULL : descendants[0]->get_copy());
}

void synthax::primitive::modulation::sin_am::evaluateBlockPerformance(unsigned firstFrameNumber, unsigned numSamples, float* sampleTimes, unsigned numConstantVariables, float* constantVariables, float* buffer) {
    descendants[0]->evaluateBlockPerformance(firstFrameNumber, numSamples, sampleTimes, numConstantVariables, constantVariables, buffer);
    for (unsigned i = 0; i < numSamples; i++) {
        buffer[i] = (offset + alpha * buffer[i]) * sin (w * (sampleTimes[i]) * (constantVariables[variableNum]));
    }
}

void synthax::primitive::modulation::sin_am::update_mutated_params() {
    node::update_mutated_params();

	// update angular frequency constant
    partial = params[1]->get_value();
    w = 2.0 * M_PI * partial;
	
	// update AM params
    offset = params[2]->get_cvalue();
    alpha = params[3]->get_cvalue();
    
    // minimum/maximum constant and declared in constructor
    synthax::helpers::intervalMultiply(&minimum, &maximum, descendants[0]->minimum, descendants[0]->maximum, alpha, alpha);
    synthax::helpers::intervalAdd(&minimum, &maximum, minimum, maximum, offset, offset);
}