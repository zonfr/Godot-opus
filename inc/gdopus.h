#ifndef GODOPUS_H
#define GODOPUS_H

#include "opusConfig.h"

#include <godot_cpp/classes/node.hpp>
#include <opus.h>

namespace godot {
	
	class GdOpus : public Node {
		GDCLASS(GdOpus, Node);

		protected:
			OpusEncoder *opusEncoder;
			OpusDecoder *opusDecoder;
			
			static void _bind_methods();

		public:
			void init_opus();
			GdOpus();
			~GdOpus();
			PackedByteArray encode(PackedVector2Array samples);
			PackedVector2Array decode(PackedByteArray packet);
			//utility function for resampler
			// int get_resampler_input_size();
			void config(int sample_rate, int frame_duration_ms);
	};
	
	inline int sample_rate = OPUS_SAMPLE_RATE;
	inline float frame_duration = OPUS_FRAMEDURATION_MS/1000.0;
}

#endif
