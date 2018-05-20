#include "shakeanimation.h"
#include <QWidget>
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

    for (int i = 0; i < animationCount(); i++) {
        removeAnimation(animationAt(0));
    }

    while (currentOffset > 1) {
        addPosAnimation(startValue, &currentOffset, Left);
        addPosAnimation(startValue, &currentOffset, Right);

        remainingShakes -= 1;
        if (remainingShakes <= 0) {
            break;
        }
    }

    QPropertyAnimation *animation = new QPropertyAnimation(m_targetObject, "pos");
    animation->setEndValue(startValue);
    addAnimation(animation);

    int animationCount = this->animationCount();
    qreal singleAnimationDuration = m_maxDuration / animationCount;

    for (int i = 0; i < animationCount; i++) {
        QPropertyAnimation *animation = static_cast<QPropertyAnimation *>(animationAt(i));
        animation->setDuration(singleAnimationDuration);
    }
}

void ShakeAnimation::addPosAnimation(QPoint startValue, qreal *offset, Direction direction)
{
    QPropertyAnimation *animation = new QPropertyAnimation(m_targetObject, "pos");
    auto endValue = startValue;
    if (direction == Left) {
        endValue.rx() -= *offset;
    } else {
        endValue.rx() += *offset;
    }
    animation->setEndValue(endValue);
    *offset *= m_breakFactor;
    *offset = qRound(*offset);
    addAnimation(animation);
}
