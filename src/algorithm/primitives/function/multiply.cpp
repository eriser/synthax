#include "MultiplyNode.h"

/*
    ========================
    construction/DESTRUCTION
    ========================
*/

MultiplyNode::MultiplyNode(node* zero, GPNode* one) {
    arity = 2;

    descendants.push_back(zero);
    descendants.push_back(one);

    symbol = "*";
}

MultiplyNode::~MultiplyNode() {
}

/*
    =========
    OVERRidES
    =========
*/

MultiplyNode* MultiplyNode::get_copy() {
    MultiplyNode* ret = new MultiplyNode(descendants[0] == NULL ? NULL : descendants[0]->get_copy(), descendants[1] == NULL ? NULL : descendants[1]->getCopy());
    return ret;
}

void MultiplyNode::evaluateBlockPerformance(unsigned firstFrameNumber, unsigned numSamples, float* sampleTimes, unsigned numConstantVariables, float* constantVariables, float* buffer) {
    descendants[0]->evaluateBlockPerformance(firstFrameNumber, numSamples, sampleTimes, numConstantVariables, constantVariables, buffer);
    descendants[1]->evaluateBlockPerformance(firstFrameNumber, numSamples, sampleTimes, numConstantVariables, constantVariables, descendant_buffers[0]);
    for (unsigned i = 0; i < numSamples; i++) {
        buffer[i] = buffer[i] * descendant_buffers[0][i];
    }
}

void MultiplyNode::update_mutated_params() {
    FunctionNode::update_mutated_params();
    intervalMultiply(&minimum, &maximum, descendants[0]->minimum, descendants[0]->maximum, descendants[1]->minimum, descendants[1]->maximum);
}
