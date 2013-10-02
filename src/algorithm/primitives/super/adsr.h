#ifndef ADSRTERMINALNODE_H
#define ADSRTERMINALNODE_H

#include "../../node.h"

class ADSRTerminalNode: public node {
public:
    ADSRTerminalNode(param* del, GPMutatableParam* atk, GPMutatableParam* atkh, GPMutatableParam* dec, GPMutatableParam* sus, GPMutatableParam* sush, GPMutatableParam* rel);
    ~ADSRTerminalNode();

	// overrides
    ADSRTerminalNode* get_copy();
	void evaluateBlockPerformance(unsigned firstFrameNumber, unsigned numSamples, float* sampleTimes, unsigned numConstantVariables, float* constantVariables, float* buffer);

    // optional overrides
	void set_render_info(float sr, unsigned block_size, unsigned max_frame_number, float max_frame_start_time);
    void done_rendering();
	void update_mutated_params();

	// class specific
    void fillFromParams();

private:
    double sampleRate;
    bool releaseFinished;
    unsigned framesInEnvelope;
    float* envelope;

    double delay;
    unsigned delayFrames;
    double attack;
    unsigned attackFrames;
    double decay;
    unsigned decayFrames;
    double sustain;
    unsigned sustainFrames;
    double release;
    unsigned releaseFrames;
    double attackheight;
    double sustainheight;
};

#endif
