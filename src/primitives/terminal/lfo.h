#ifndef TERMINAL_LFO_H
#define TERMINAL_LFO_H

#include "../base/lfo_b.h"

namespace synthax{namespace primitive{namespace terminal{
	class lfo : public base::lfo_b {
	public:
		lfo(param* rate);
		~lfo();

		// overrides
		lfo* get_copy();
		void evaluateBlockPerformance(unsigned firstFrameNumber, unsigned numSamples, float* sampleTimes, unsigned numConstantVariables, float* constantVariables, float* buffer);

	private:
	};
}}}

#endif