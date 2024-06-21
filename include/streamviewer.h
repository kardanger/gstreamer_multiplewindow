#pragma once

#include <QQuickWidget>
#include <gst/gst.h>

#include "streamengine.h"

class StreamViewer : public QQuickWidget {
Q_OBJECT
public:

    explicit StreamViewer(int index, QWidget* parent);

    ~StreamViewer() = default;

    void setupDefaultData();

    using StreamEnginePtr = std::unique_ptr<StreamEngine>;

    std::vector<StreamEnginePtr> streams;

    QMap<int, QPair<int, int>> armIndexHelper;

signals:
    void startStreaming(const QString& objectName);

private:

    void initialConnection(int index);

    QQmlEngine* qmlEngine;
    QQmlContext* qmlContext;

    GstElement *pipeline;
    GstElement *rtspsrc;
    GstElement *depayloader;
    GstElement *decoder;
    GstElement *sink;
    GstElement *glupload;
};
