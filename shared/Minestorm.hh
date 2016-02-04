#ifndef MINESTORM_HH
# define MINESTORM_HH

# include <QDebug>
# include <iostream>

# define DEBUG(x,y) do { \
  if (y) { qDebug() << x; } \
} while (0)

# define SCREEN_SIZE    800
# define CPS            50
# define EVENT_PER_S    10

#endif // MINESTORM_HH

