#ifndef CONSTANT_H
#define CONSTANT_H

#include "../../node.h"

namespace synthax{namespace primitive{namespace terminal{
	class constant : public node {
	public:
		constant(bool pi, param* v);
		~constant();

		// overrides
		constant* get_copy();
		void evaluateBlockPerformance(unsigned firstFrameNumber, unsigned numSamples, float* sampleTimes, unsigned numConstantVariables, float* constantVariables, float* buffer);

		// optional overrides
		void set_render_info(float sr, unsigned block_size, unsigned max_frame_number, float max_frame_start_time);
		void done_rendering();
		void update_mutated_params();

	private:
		bool isPi;
		double value;
	};
}}}

#endif