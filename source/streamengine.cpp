#include "streamengine.h"

StreamEngine::StreamEngine(const QString &objectName) :
    objectName(objectName)
{
    pipeline = gst_parse_launch( "videotestsrc ! videoconvert ! glupload ! qmlglsink name=sink"
                                , NULL);

    sink = gst_bin_get_by_name (GST_BIN (pipeline), "sink");
}

QString StreamEngine::getObjectName()
{
    return objectName;
}

StreamEngine::~StreamEngine()
{
    gst_element_set_state (pipeline, GST_STATE_NULL);
    gst_object_unref (pipeline);
    gst_object_unref (sink);
}

void StreamEngine::setPaused()
{
    gst_element_set_state(pipeline, GST_STATE_PAUSED);
}

void StreamEngine::setPlaying()
{
    gst_element_set_state(pipeline, GST_STATE_PLAYING);
}

GstElement *StreamEngine::getPipeline()
{
    return pipeline;
}

GstElement *StreamEngine::getSink()
{
    return sink;
}

bool StreamEngine::getInit() const
{
    return init;
}

void StreamEngine::setInit(bool newInit)
{
    init = newInit;
}
