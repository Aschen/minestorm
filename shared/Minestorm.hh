#ifndef MINESTORM_HH
# define MINESTORM_HH

# include <QDebug>
# include <iostream>

# define DEBUG(x,y) do { \
  if (y) { qDebug() << x; } \
} while (0)

# define SCREEN_SIZE 800
//#ifdef _DEBUG
//#define TRACE(MSG) std::cout << MSG << "\t" << __CLASS__ <<  __FUNCTION__ << " ligne " << __LINE__ << std::endl;
//#else
//#define TRACE(MSG)
//#endi

#endif // MINESTORM_HH

