#include "decoder.h"

#include <godot_cpp/core/class_db.hpp>

#include <godot_cpp/variant/utility_functions.hpp>
#include <godot_cpp/classes/audio_server.hpp>

using namespace godot;	 



GdOpusDecoder::GdOpusDecoder(){
	int err;
	opusDecoder = opus_decoder_create(OPUS_SAMPLE_RATE, 2, &err);	
	ERR_FAIL_COND(err != OPUS_OK);
}

GdOpusDecoder::~GdOpusDecoder(){
	opus_decoder_destroy(opusDecoder);
}

PackedVector2Array GdOpusDecoder::decode(PackedByteArray packet){
	
	PackedVector2Array decoded;

	decoded.resize(OPUS_FRAME_SAMPLE_COUNT);

	int len = opus_decode_float(opusDecoder,
		   	packet.ptrw(), packet.size(),
		   	(float*) decoded.ptrw(), OPUS_FRAME_SAMPLE_COUNT,
			0
			); 

	if(len != OPUS_FRAME_SAMPLE_COUNT){
		UtilityFunctions::printerr("GODOT OPUS DECODING ERROR : Packet contained ", len ,", expected ", OPUS_FRAME_SAMPLE_COUNT);
		return decoded;
	}

	return decoded;

			
}

void GdOpusDecoder::_bind_methods(){
	
	ClassDB::bind_method(D_METHOD("decode"), &GdOpusDecoder::decode);

}
