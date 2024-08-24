#ifndef GODOPUSDECODER_H
#define GODOPUSDECODER_H

#include "opusConfig.h"

#include <godot_cpp/classes/node.hpp>
#include <opus.h>

namespace godot {
	
	class GdOpusDecoder : public Node {
		GDCLASS(GdOpusDecoder, Node);

		protected:
			unsigned int outputBufferSize;
			static void _bind_methods();
			OpusDecoder *opusDecoder;

		public:
			GdOpusDecoder();
			~GdOpusDecoder();
			PackedVector2Array decode(PackedByteArray packet);

	};

}

#endif
