#ifndef MINESTORM_HH
# define MINESTORM_HH

# include <QDebug>

# define DEBUG(x,y) do { \
  if (x) { qDebug() << y; } \
} while (0)


#endif // MINESTORM_HH

