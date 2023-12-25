#include <QGuiApplication>
#include <QQmlApplicationEngine>

extern "C"
{
#include <libavcodec/avcodec.h>
#include <libavformat/avformat.h>
#include <libswscale/swscale.h>
#include <libavdevice/avdevice.h>
#include <libavformat/version.h>
#include <libavutil/time.h>
#include <libavutil/mathematics.h>
#include <libavfilter/avfilter.h>
}

void test_ffmpeg()
{
    printf("avcodec version is %u \n",avcodec_version());
    printf("avdevice version is %u \n",avdevice_version());
    printf("avfilter version is %u \n",avfilter_version());
    printf("avfilter version is %u \n",avformat_version());
}

int main(int argc, char *argv[])
{
    test_ffmpeg();

    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    const QUrl url(u"qrc:/qt-ffmpeg-tools/main.qml"_qs);
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
        &app, [url](QObject *obj, const QUrl &objUrl) {
            if (!obj && url == objUrl)
                QCoreApplication::exit(-1);
        }, Qt::QueuedConnection);
    engine.load(url);

    return app.exec();
}
