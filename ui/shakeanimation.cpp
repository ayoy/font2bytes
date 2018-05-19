#include "shakeanimation.h"
#include <QWidget>
#include <QDebug>
#include <QPropertyAnimation>

ShakeAnimation::ShakeAnimation(QWidget *target, QObject *parent) :
    QSequentialAnimationGroup(parent),
    m_targetObject(target)
{
    setupAnimations();
}

ShakeAnimation::~ShakeAnimation()
{
}

void ShakeAnimation::setupAnimations()
{
    qreal currentOffset = m_offset;
    int remainingShakes = m_maxShakesCount;

    auto startValue = m_targetObject->pos();
    qDebug() << startValue;

    for (int i = 0; i < animationCount(); i++) {
        removeAnimation(animationAt(0));
    }

    while (currentOffset > 1) {
        QPropertyAnimation *animation = new QPropertyAnimation(m_targetObject, "pos");
        auto endValue = startValue;
        endValue.rx() -= currentOffset;
        animation->setEndValue(endValue);
        currentOffset *= m_breakFactor;
        currentOffset = qRound(currentOffset);
        addAnimation(animation);
        qDebug() << animation->startValue() << animation->endValue();

        animation = new QPropertyAnimation(m_targetObject, "pos");
        endValue = startValue;
        endValue.rx() += currentOffset;
        animation->setEndValue(endValue);
        currentOffset *= m_breakFactor;
        currentOffset = qRound(currentOffset);
        addAnimation(animation);
        qDebug() << animation->startValue() << animation->endValue();

        remainingShakes -= 1;
        if (remainingShakes <= 0) {
            break;
        }
    }

    QPropertyAnimation *animation = new QPropertyAnimation(m_targetObject, "pos");
    animation->setEndValue(startValue);
    addAnimation(animation);
    qDebug() << animation->startValue() << animation->endValue();

    int animationCount = this->animationCount();
    qreal singleAnimationDuration = m_maxDuration / animationCount;

    for (int i = 0; i < animationCount; i++) {
        QPropertyAnimation *animation = static_cast<QPropertyAnimation *>(animationAt(i));
        animation->setDuration(singleAnimationDuration);
    }

    qDebug() << duration();

}
