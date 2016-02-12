#ifndef MINESTORM_HH
# define MINESTORM_HH

# include <QDebug>
# include <iostream>

# define DEBUG(x,y) do { \
  if (y) { qDebug() << x; } \
} while (0)

# define SCREEN_SIZE    800
# define MAX_CLIENTS    50
# define CYCLE_PER_S    30
# define EVENT_PER_S    15
# define MAX_PLAYERS    4
# define SERVER_PORT    4242
# define SHIP_SIZE      32
# define SCORE_MINE     100

#endif // MINESTORM_HH

