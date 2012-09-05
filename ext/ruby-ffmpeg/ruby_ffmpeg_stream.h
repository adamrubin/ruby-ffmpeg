#ifndef	RUBY_FFMPEG_STREAM_H
#define	RUBY_FFMPEG_STREAM_H

#include <ruby.h>

#include <libavformat/avformat.h>
#include <libavcodec/avcodec.h>
#include <libswscale/swscale.h>

// Object Lifetime
VALUE stream_register_class(VALUE module);
VALUE stream_new(VALUE format, AVStream * stream);

#endif // RUBY_FFMPEG_STREAM_H
