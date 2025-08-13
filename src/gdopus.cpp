#include "gdopus.h"

#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/classes/audio_server.hpp>

#include <godot_cpp/variant/utility_functions.hpp>

using namespace godot;

void GdOpus::init_opus(){
	int decoder_err;
	opusDecoder = opus_decoder_create(sample_rate, 2, &decoder_err);
	ERR_FAIL_COND(decoder_err != OPUS_OK);

	int encoder_err;
	opusEncoder = opus_encoder_create(sample_rate, 2, OPUS_APPLICATION_VOIP, &encoder_err);	
	ERR_FAIL_COND(encoder_err != OPUS_OK);

	opus_encoder_ctl(opusEncoder, OPUS_SET_SIGNAL(OPUS_SIGNAL_VOICE));
}

GdOpus::GdOpus(){
	init_opus();
}

GdOpus::~GdOpus(){
	
	opus_decoder_destroy(opusDecoder);
	opus_encoder_destroy(opusEncoder);
}


int GdOpus::get_resampler_input_size(){
	return (AudioServer::get_singleton()->get_mix_rate()*480)/sample_rate;
}

PackedByteArray GdOpus::encode(PackedVector2Array samples){

	int encoder_frame_sample_count = sample_rate*frame_duration;
	
	PackedByteArray encoded;

	if(samples.size() != encoder_frame_sample_count){
		UtilityFunctions::printerr("GODOT OPUS ENCODER INPUT ERROR : Expected ", encoder_frame_sample_count, " samples, got ", samples.size());
		return encoded; 
	}

	encoded.resize(sizeof(float)*encoder_frame_sample_count*2);
	
	int len = opus_encode_float(opusEncoder,
		   	(float*) samples.ptr(), encoder_frame_sample_count,
		   	encoded.ptrw(), encoded.size()
			); 

	encoded.resize(len);	

	return encoded;
}

PackedVector2Array GdOpus::decode(PackedByteArray packet){

	int decoder_frame_sample_count = sample_rate*frame_duration;
	
	PackedVector2Array decoded;

	decoded.resize(decoder_frame_sample_count);

	int len = opus_decode_float(opusDecoder,
		   	packet.ptr(), packet.size(),
		   	(float*) decoded.ptrw(), decoder_frame_sample_count,
			0
			); 

	if(len != decoder_frame_sample_count){
		UtilityFunctions::printerr("GODOT OPUS DECODING ERROR : Packet contained ", len ,", expected ", decoder_frame_sample_count);
		return decoded;
	}

	return decoded;
}

void GdOpus::config(int sample_rate, int frame_duration_ms){
	
	opus_decoder_destroy(opusDecoder);
	opus_encoder_destroy(opusEncoder);

	sample_rate = sample_rate;
	frame_duration = frame_duration_ms/1000.0;
	
	init_opus();
}

void GdOpus::_bind_methods(){
	
	ClassDB::bind_method(D_METHOD("encode", "sample_frame"), &GdOpus::encode);
	// ClassDB::set_method_info("GdOpus", "encode", PropertyInfo(Variant::NIL, ""), "Encode stereo data PackedVector2Array into bytes using Opus.");
	ClassDB::bind_method(D_METHOD("decode", "bytes_frame"), &GdOpus::decode);
	// ClassDB::set_method_info("GdOpus", "decode", PropertyInfo(Variant::NIL, ""), "Decode stereo data PackedVector2Array from bytes using Opus.");
	ClassDB::bind_method(D_METHOD("get_resampler_input_size"), &GdOpus::get_resampler_input_size);
	// ClassDB::set_method_info("GdOpus", "get_resampler_input_size", PropertyInfo(Variant::INT, "return_value"), "Return the resampler input size.");
	ClassDB::bind_method(D_METHOD("config", "new_sample_rate", "new_frame_duration_ms"), &GdOpus::config);
	// ClassDB::set_method_info("GdOpus", "config", PropertyInfo(Variant::NIL, ""), "Configure the encoder to the given sample rate and frame duration (in milliseconds), static method.");

}
