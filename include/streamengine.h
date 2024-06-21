#pragma once

#include <gst/gst.h>
#include <QUrl>
#include <QObject>

class StreamEngine : public QObject{
    Q_OBJECT

public:

    StreamEngine(const QString & objectName);
    QString getObjectName();
    ~StreamEngine();

    void setPaused();
    void setPlaying();

    GstElement *getPipeline();
    GstElement *getSink();

    bool getInit() const;
    void setInit(bool newInit);

    int getIndex() const;

private:

    GstElement *pipeline;
    GstElement *rtspsrc;
    GstElement *depayloader;
    GstElement *decoder;
    GstElement *sink;
    GstElement *glupload;

    QString objectName;

    bool init = false;
};

