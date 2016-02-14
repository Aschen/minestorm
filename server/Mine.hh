#ifndef MINE_HH
#define MINE_HH

# include <QPoint>

# include "Entity.hh"

using namespace std;

class Mine : public Entity
{
public:
    /*   /!\ MUST MATCH Element::Type /!\   */
    enum TypeMine {
        Small       = 0,
        Medium      = 5,
        Big         = 6,
        Small_On    = 7,
        Medium_On   = 8,
        Big_On      = 9,
        Exploded    = 11
    };

private:
    TypeMine        _typeMine;
    bool            _armed;
    qint32          _size;
    quint32         _delay;
    quint32         _timer;

public:
    //Constructor
    Mine(TypeMine typeMine, const QPointF &point);
    virtual ~Mine();

    void            activate();

    //Entity Interface
    QPointF         center() const override;
    bool            makeEntityMove() override;

    //Getter & Setter
    qint32          size() const;
    void            setSize(qint32 size);
    TypeMine        typeMine() const;
    bool            armed() const;
};

#endif // MINE_HH
