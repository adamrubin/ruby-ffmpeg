#include <ruby.h>

#include <libavformat/avformat.h>
#include <libavcodec/avcodec.h>
#include <libavutil/pixdesc.h>
#include <libswscale/swscale.h>

#include "ruby_ffmpeg_util.h"

/*
**	Conversion.
*/

// Convert FFMPEG dictionary to Ruby hash
VALUE av_dictionary_to_ruby_hash(AVDictionary * dict) {
	VALUE metadata = rb_hash_new();

	AVDictionaryEntry * temp = NULL;
	while (temp = av_dict_get(dict, "", temp, AV_DICT_IGNORE_SUFFIX)) {
		rb_hash_aset(metadata, ID2SYM(rb_intern(temp->key)), rb_str_new2(temp->value));
	}

	return metadata;
}

// Convert FFMPEG error to Ruby string description
VALUE av_error_to_ruby_string(int error) {
	char temp[1024];
	av_strerror(error, &temp[0], sizeof(temp));
	return rb_str_new2(temp);
}

// Convert FFMPEG PixelFormat to symbol
VALUE av_pixel_format_to_symbol(enum PixelFormat format) {
	char const * name = av_get_pix_fmt_name(format);
	return name ? ID2SYM(rb_intern(name)) : Qnil;
}

// Convert symbol to FFMPEG PixelFormat
VALUE symbol_to_av_pixel_format(VALUE symbol) {
	char const * name = rb_id2name(SYM2ID(symbol));
	return av_get_pix_fmt(name);
}

// Convert FFMPEG SampleFormat to symbol
VALUE av_sample_format_to_symbol(enum AVSampleFormat format) {
	char const * name = av_get_sample_fmt_name(format);
	return name ? ID2SYM(rb_intern(name)) : Qnil;
}

// Convert FFMPEG MediaType to symbol
VALUE av_media_type_to_symbol(enum AVMediaType type) {
	char const * name = av_get_media_type_string(type);
	return name ? ID2SYM(rb_intern(name)) : Qnil;
}

// Convert symbol to interpolation method
int symbol_to_interpolation_filter(VALUE symbol) {
	char const * name = rb_id2name(SYM2ID(symbol));
	if (strcmp(name, "fast_bilinear") == 0) return SWS_FAST_BILINEAR;
	if (strcmp(name, "bilinear") == 0)		return SWS_BILINEAR;
	if (strcmp(name, "bicubic") == 0)		return SWS_BICUBIC;
	if (strcmp(name, "x") == 0)				return SWS_X;
	if (strcmp(name, "point") == 0)			return SWS_POINT;
	if (strcmp(name, "area") == 0)			return SWS_AREA;
	if (strcmp(name, "bicublin") == 0)		return SWS_BICUBLIN;
	if (strcmp(name, "gauss") == 0)			return SWS_GAUSS;
	if (strcmp(name, "sinc") == 0)			return SWS_SINC;
	if (strcmp(name, "lanczos") == 0)		return SWS_LANCZOS;
	if (strcmp(name, "spline") == 0)		return SWS_SPLINE;
	return 0;
}
