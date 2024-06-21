#include "streamviewer.h"

#include <QQmlEngine>
#include <QQuickItem>
#include <QQuickWindow>

#include <QRunnable>
#include <QQmlContext>
#include <QQmlProperty>

class SetPlaying : public QRunnable
{
public:
    SetPlaying( const StreamViewer & viewer, int indexVideoItem0, int indexVideoItem1) :
        viewer(viewer),
        indexVideoItem0(indexVideoItem0),
        indexVideoItem1(indexVideoItem1)
    {};

    ~SetPlaying() = default;

    void run ();

    void setStartPipline(int index);

    const StreamViewer & viewer;
    int indexVideoItem0;
    int indexVideoItem1;
};

void SetPlaying::run ()
{
    setStartPipline(indexVideoItem0);
    setStartPipline(indexVideoItem1);
}

void SetPlaying::setStartPipline(int index)
{
    GstStateChangeReturn ret;

    ret = gst_element_set_state(viewer.streams.at(index)->getPipeline(), GST_STATE_PLAYING);
    if (ret == GST_STATE_CHANGE_FAILURE) {
        g_printerr("Unable to set the pipeline to the playing state.\n");
        gst_object_unref(viewer.streams.at(index)->getPipeline());
    }
    else{
        viewer.streams.at(index)->setInit(true);
    }
}

StreamViewer::StreamViewer(int index, QWidget *parent)
    : QQuickWidget(parent)
{
    setResizeMode(QQuickWidget::SizeRootObjectToView);
    qmlContext = rootContext();
    qmlContext->setContextProperty("backend", this);

    gst_init (NULL, NULL);

    setupDefaultData();

    const QUrl sourceUrl(QStringLiteral("qrc:/qml/StreamWindow.qml"));
    setSource(sourceUrl);

    auto videoItem1 = rootObject()->findChild<QQuickItem *> ("videoItem1");
    auto videoItem2 = rootObject()->findChild<QQuickItem *> ("videoItem2");

    int indexVideoItem0 = armIndexHelper.value(index).first;
    int indexVideoItem1 = armIndexHelper.value(index).second;

    QQmlProperty::write(videoItem1, "objectName", streams.at(indexVideoItem0)->getObjectName());
    QQmlProperty::write(videoItem2, "objectName", streams.at(indexVideoItem1)->getObjectName());

    initialConnection(indexVideoItem0);
    initialConnection(indexVideoItem1);

    quickWindow()->scheduleRenderJob (new SetPlaying(*this, indexVideoItem0, indexVideoItem1),
                                      QQuickWindow::BeforeSynchronizingStage);
}

void StreamViewer::initialConnection(int index)
{
    auto videoItem = rootObject()->findChild<QQuickItem *> (streams.at(index)->getObjectName());
    g_assert (videoItem);
    g_object_set(streams.at(index)->getSink(), "widget", videoItem, NULL);
}

void StreamViewer::setupDefaultData()
{
    streams.emplace_back(std::make_unique<StreamEngine>("videoItem1_1"));
    streams.emplace_back(std::make_unique<StreamEngine>("videoItem1_2"));

    armIndexHelper.insert(1, {0,1});

    streams.emplace_back(std::make_unique<StreamEngine>("videoItem2_1"));
    streams.emplace_back(std::make_unique<StreamEngine>("videoItem2_2"));

    armIndexHelper.insert(2, {2,3});
}
