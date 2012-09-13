#ifndef	RUBY_FFMPEG_VIDEO_STREAM_H
#define	RUBY_FFMPEG_VIDEO_STREAM_H

#include "ruby_ffmpeg.h"

// Object Lifetime
VALUE video_stream_register_class(VALUE module, VALUE super);
VALUE video_stream_new(VALUE reader, AVStream * stream);

#endif // RUBY_FFMPEG_VIDEO_STREAM_H
