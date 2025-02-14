// Copyright (C) 2022 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR LGPL-3.0-only OR GPL-2.0-only OR GPL-3.0-only

#ifndef QCANFRAMEPROCESSOR_H
#define QCANFRAMEPROCESSOR_H

#include <QtCore/QExplicitlySharedDataPointer>
#include <QtCore/QVariantMap>

#include <QtSerialBus/qcancommondefinitions.h>
#include <QtSerialBus/qtserialbusglobal.h>

QT_BEGIN_NAMESPACE

class QCanBusFrame;
class QCanMessageDescription;
class QCanUniqueIdDescription;

class QCanFrameProcessorPrivate;
QT_DECLARE_QESDP_SPECIALIZATION_DTOR_WITH_EXPORT(QCanFrameProcessorPrivate, Q_SERIALBUS_EXPORT)

class Q_SERIALBUS_EXPORT QCanFrameProcessor
{
public:
    enum class Error : quint8 {
        NoError = 0,
        InvalidFrame,
        UnsupportedFrameFormat,
        DecodingError,
        EncodingError,
    };

    struct ParseResult {
        QtCanBus::UniqueId uniqueId = 0;
        QVariantMap signalValues;
    };

    QCanFrameProcessor();
    QCanFrameProcessor(const QCanFrameProcessor &other);
    QCanFrameProcessor(QCanFrameProcessor &&other) noexcept;
    ~QCanFrameProcessor();

    QCanFrameProcessor &operator=(const QCanFrameProcessor &other);
    QT_MOVE_ASSIGNMENT_OPERATOR_IMPL_VIA_PURE_SWAP(QCanFrameProcessor)

    friend bool operator==(const QCanFrameProcessor &lhs, const QCanFrameProcessor &rhs)
    {
        return equals(lhs, rhs);
    }
    friend bool operator!=(const QCanFrameProcessor &lhs, const QCanFrameProcessor &rhs)
    {
        return !equals(lhs, rhs);
    }

    inline void swap(QCanFrameProcessor &other) noexcept { d.swap(other.d); }

    QCanBusFrame prepareFrame(QtCanBus::UniqueId uniqueId, const QVariantMap &signalValues);
    ParseResult parseFrame(const QCanBusFrame &frame);

    Error error() const;
    QString errorString() const;
    QStringList warnings() const;

    QList<QCanMessageDescription> messageDescriptions() const;
    void addMessageDescriptions(const QList<QCanMessageDescription> &descriptions);
    void setMessageDescriptions(const QList<QCanMessageDescription> &descriptions);
    void clearMessageDescriptions();

    QCanUniqueIdDescription uniqueIdDescription() const;
    void setUniqueIdDescription(const QCanUniqueIdDescription &description);

private:
    QExplicitlySharedDataPointer<QCanFrameProcessorPrivate> d;
    friend class QCanFrameProcessorPrivate;

    static bool equals(const QCanFrameProcessor &lhs, const QCanFrameProcessor &rhs);
};

Q_DECLARE_SHARED(QCanFrameProcessor)

QT_END_NAMESPACE

#endif // QCANFRAMEPROCESSOR_H
