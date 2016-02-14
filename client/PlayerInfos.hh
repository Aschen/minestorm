#ifndef PLAYERINFOS_HH
# define PLAYERINFOS_HH

# include <QHash>
# include <QSharedPointer>
# include <QColor>
# include <QBrush>

# include "IDrawable.hh"
# include "Element.hh"

class PlayerInfos : public IDrawable
{
private:
    const quint32   _number;
    const QPoint    _position;
    quint32         _score;
    quint32         _lives;
    QString         _pseudo;
    QString         _scoreText;
    QColor          _color;
    QBrush          _brush;

public:
    PlayerInfos(quint32 number, const QPoint &position);
    virtual ~PlayerInfos();

    void            score(quint32 score);
    quint32         score() const;
    void            lives(quint32 lives);
    quint32         lives() const;
    quint32         number() const;
    const QString   &pseudo() const;
    void            pseudo(const QString &pseudo);

    // IDrawable interface
public:
    void            draw(QPainter &painter, Images &images) const override;
};

#endif // PLAYERINFOS_HH
