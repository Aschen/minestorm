#ifndef MINESTORM_HH
# define MINESTORM_HH

# include <QDebug>
# include <iostream>

# define DEBUG(x,y) do { \
  if (y) { qDebug() << x; } \
} while (0)

# define SCREEN_SIZE    800
# define CYCLE_PER_S    50
# define EVENT_PER_S    10
# define MAX_PLAYERS    4
# define SERVER_PORT    4242

#endif // MINESTORM_HH

