#include "runner.h"

#include <QtCore/QDebug>
#include <QtCore/QCoreApplication>

#include <trikControl/servoMotor.h>
#include <trikControl/sensor.h>

#include "scriptableParts.h"

using namespace scriptRunner;

Runner::Runner()
{
	mEngineWorker.moveToThread(&mWorkerThread);

	connect(this, SIGNAL(threadRun(QString const &)), &mEngineWorker, SLOT(run(QString const &)));
	connect(this, SIGNAL(threadDelete()), &mEngineWorker, SLOT(deleteWorker()));

	mWorkerThread.start();
}

Runner::~Runner()
{
	mEngineWorker.abort();
	emit threadDelete();
	mWorkerThread.wait(1000);
}

void Runner::run(QString const &script)
{
	emit threadRun(script);
}

void Runner::abort()
{
	mEngineWorker.abort();
}
