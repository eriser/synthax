#include "multiply.h"

/*
    ========================
    construction/DESTRUCTION
    ========================
*/

synthax::primitive::function::multiply::multiply(node* zero, node* one) {
    arity = 2;

    descendants.push_back(zero);
    descendants.push_back(one);

    symbol = "*";
}

synthax::primitive::function::multiply::~multiply() {
}

/*
    =========
    OVERRidES
    =========
*/

synthax::primitive::function::multiply* synthax::primitive::function::multiply::get_copy() {
    multiply* ret = new multiply(descendants[0] == NULL ? NULL : descendants[0]->get_copy(), descendants[1] == NULL ? NULL : descendants[1]->get_copy());
    return ret;
}

void synthax::primitive::function::multiply::evaluateBlockPerformance(unsigned firstFrameNumber, unsigned numSamples, float* sampleTimes, unsigned numConstantVariables, float* constantVariables, float* buffer) {
    descendants[0]->evaluateBlockPerformance(firstFrameNumber, numSamples, sampleTimes, numConstantVariables, constantVariables, buffer);
    descendants[1]->evaluateBlockPerformance(firstFrameNumber, numSamples, sampleTimes, numConstantVariables, constantVariables, descendant_buffers[0]);
    for (unsigned i = 0; i < numSamples; i++) {
        buffer[i] = buffer[i] * descendant_buffers[0][i];
    }
}

void synthax::primitive::function::multiply::update_mutated_params() {
    node::update_mutated_params();
    synthax::helpers::intervalMultiply(&minimum, &maximum, descendants[0]->minimum, descendants[0]->maximum, descendants[1]->minimum, descendants[1]->maximum);
}
