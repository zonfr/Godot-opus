#include "encoder.h"

#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/classes/audio_server.hpp>

#include <godot_cpp/variant/utility_functions.hpp>

using namespace godot;	 

GdOpusEncoder::GdOpusEncoder(){

	int err;
	opusEncoder = opus_encoder_create(OPUS_SAMPLE_RATE, 2, OPUS_APPLICATION_VOIP, &err);	
	ERR_FAIL_COND(err != OPUS_OK);

	opus_encoder_ctl(opusEncoder, OPUS_SET_SIGNAL(OPUS_SIGNAL_VOICE));

}

GdOpusEncoder::~GdOpusEncoder(){
	
	opus_encoder_destroy(opusEncoder);
}

int GdOpusEncoder::getResamplerInputSize(){
	return (AudioServer::get_singleton()->get_mix_rate()*480)/OPUS_SAMPLE_RATE;
}

PackedByteArray GdOpusEncoder::encode(PackedVector2Array samples){
	
	PackedByteArray encoded;

	if(samples.size() != OPUS_FRAME_SAMPLE_COUNT){
		UtilityFunctions::printerr("GODOT OPUS ENCODER INPUT ERROR : Expected", OPUS_FRAME_SAMPLE_COUNT, "samples, got ", samples.size());
		return encoded; 
	}

	encoded.resize(sizeof(float)*OPUS_FRAME_SAMPLE_COUNT*2);
	
	int len = opus_encode_float(opusEncoder,
		   	(float*) samples.ptr(), OPUS_FRAME_SAMPLE_COUNT,
		   	encoded.ptrw(), encoded.size()
			); 

	encoded.resize(len);	

	return encoded;

			
}

void GdOpusEncoder::_bind_methods(){
	
	ClassDB::bind_method(D_METHOD("encode"), &GdOpusEncoder::encode);
	ClassDB::bind_method(D_METHOD("getResamplerInputSize"), &GdOpusEncoder::getResamplerInputSize);

}
