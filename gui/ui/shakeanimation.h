#ifndef SHAKEANIMATION_H
#define SHAKEANIMATION_H

#include <QSequentialAnimationGroup>

class ShakeAnimation : public QSequentialAnimationGroup
{
    Q_OBJECT

    Q_PROPERTY(QWidget * targetObject READ targetObject)
    Q_PROPERTY(int offset READ offset WRITE setOffset)
    Q_PROPERTY(int maxShakesCount READ maxShakesCount WRITE setMaxShakesCount)
    Q_PROPERTY(qreal breakFactor READ breakFactor WRITE setBreakFactor)
    Q_PROPERTY(int maxDuration READ maxDuration WRITE setMaxDuration)

public:
    explicit ShakeAnimation(QWidget *target, QObject *parent = nullptr);
    virtual ~ShakeAnimation();

    inline QWidget * targetObject() const { return m_targetObject; }

    inline int offset() const { return m_offset; }
    inline void setOffset(int offset) { m_offset = offset; }

    inline int maxShakesCount() const { return m_maxShakesCount; }
    inline void setMaxShakesCount(int count) { m_maxShakesCount = count; }

    inline qreal breakFactor() const { return m_breakFactor; }
    inline void setBreakFactor(qreal breakFactor) { m_breakFactor = breakFactor; }

    inline int maxDuration() const { return m_maxDuration; }
    inline void setMaxDuration(int maxDuration) { m_maxDuration = maxDuration; }

private:
    void setupAnimations();

    enum Direction { Left, Right };
    void addPosAnimation(QPoint startValue, qreal *offset, Direction direction);

    QWidget *m_targetObject;
    int m_offset { 15 };
    qreal m_breakFactor { 0.8 };
    int m_maxShakesCount { 6 };
    int m_maxDuration { 700 };
};

#endif // SHAKEANIMATION_H
