#include "pacer.h"
#include "tinygl.h"

void main (void)
{
   //pacer_init (10000);
   tinygl_init (10000);

   tinygl_draw_line (tinygl_point (0, 2), tinygl_point (0, 4),1);

   while (1)
   {
       //pacer_wait ();
       tinygl_update ();
   }
}
