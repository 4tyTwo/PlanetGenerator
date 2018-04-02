#include "RiverGenerator.h"



RiverGenerator::RiverGenerator()
{
}


void RiverGenerator::generation(int base_x, int base_y, int x, int y, int& sign) {
  std::string water = "water";
  int length = y - base_y;
  int mx = base_x + ((x - base_x) / 2), my = base_y + ((y - base_y) / 2);
  int newy = my, newx = mx;
  if (length <= 32) {
    if (base_x == x) {
      for (int i = base_y; i<y; i++)
        (*data)[x][y]->setType(water);
    }
    else {
      mx = base_x + ((x - base_x) / 2), my = base_y + ((y - base_y) / 2);
      int coeff = length / 2.4;
      if (abs(x - base_x) > length) {
        length = abs(x - base_x);
        coeff = length / 5;
        newy = my + sign * (rand() % coeff + length / 12);
        //sign*=-1;
        if (newy >= data->y_size())
          newy = data->y_size() - newx % data->y_size() - 1;
        if (newy < 0)
          newy = abs(newy);
        int newx = mx;
      }
      else {
        newx = mx + sign * (rand() % coeff + length / 4);
        sign *= -1;
        if (newx >= data->x_size())
          newx = data->x_size() - newx % data->x_size() - 1;
        if (newx < 0)
          newx = abs(newx);
        newy = my;
      }
      curve(base_x, base_y, newx, newy, x, y);
      return;
    }
  }
  int coeff = length / 7;
  if (abs(x - base_x > length)) {
    length = abs(x - base_x);
    coeff = length / 12;
    newy = my + sign * (rand() % coeff + length / 35);
    //sign *= -1;
    if (newy < 0)
      newy = abs(newy);
    else
      if (newy >= y)
        newy = y - 1;
    if (newy < 0)
      newy = abs(newy);
  }
  else {
    newx = mx + sign * (rand() % coeff + length / 35);
    sign *= -1;
    if (newx < 0)
      newx = abs(newx);
    else
      if (newx >= x)
        newx = x - 1;
    if (newx < 0)
      newx = abs(newx);
  }
  generation(newx, newy, x, y, sign);
  generation(base_x, base_y, newx, newy, sign);
}

void RiverGenerator::line(int x0, int y0, int x1, int y1){
  std::string water = "water";
  int deltax = abs(x1 - x0), deltay = abs(y1 - y0);
  double error = 0;
  if (deltay <= deltax) {
    double deltaerr = (double)deltay / deltax;
    int y = y0, x = x0;
    int diry = y1 - y0;
    if (diry > 0)
      diry = 1;
    else
      diry = -1;
    if (x1 - x > 0)
      for (x = x0; x < x1; x++) {
        (*data)[x][y]->setType(water);
        error += deltaerr;
        if (error > 0.5) {
          y = y + diry;
          error -= 1.0;
        }
      }
    else
      for (x = x0; x >= x1; x--) {
        (*data)[x][y]->setType(water);
        error += deltaerr;
        if (error > 0.5) {
          y = y + diry;
          error -= 1.0;
        }
      }
  }
  else {
    double deltaerr = (double)deltax / deltay;
    int y = y0, x = x0;
    int dirx = x1 - x0;
    if (dirx > 0)
      dirx = 1;
    else
      dirx = -1;
    if (y0 < y1)
      for (y = y0; y < y1; y++) {
        (*data)[x][y]->setType(water);
        error += deltaerr;
        if (error > 0.5) {
          x = x + dirx;
          error -= 1.0;
        }
      }
    else
      for (y = y0; y >= y1; y--) {
        (*data)[x][y]->setType(water);
        error += deltaerr;
        if (error > 0.5) {
          x = x + dirx;
          error -= 1.0;
        }
      }
  }
}

void RiverGenerator::curve(int x0, int y0, int x1, int y1, int x2, int y2) {
  int x = x0 - x1, y = y0 - y1;
  double t = x0 - 2 * x1 + x2, r;
  if ((long)x*(x2 - x1) > 0) { /* horizontal cut at P4? */
    if ((long)y*(y2 - y1) > 0) /* vertical cut at P6 too? */
      if (fabs((y0 - 2 * y1 + y2) / t * x) > abs(y)) { /* which first? */
        x0 = x2; x2 = x + x1; y0 = y2; y2 = y + y1; /* swap points */
      } /* now horizontal cut at P4 comes first */
    t = (x0 - x1) / t;
    r = (1 - t)*((1 - t)*y0 + 2.0*t*y1) + t * t*y2; /* By(t=P4) */
    t = (x0*x2 - x1 * x1)*t / (x0 - x1); /* gradient dP4/dx=0 */
    x = floor(t + 0.5); y = floor(r + 0.5);
    r = (y1 - y0)*(t - x0) / (x1 - x0) + y0; /* intersect P3 | P0 P1 */
    curveSeg(x0, y0, x, floor(r + 0.5), x, y);
    r = (y1 - y2)*(t - x2) / (x1 - x2) + y2; /* intersect P4 | P1 P2 */
    x0 = x1 = x; y0 = y; y1 = floor(r + 0.5); /* P0 = P4, P1 = P8 */
  }
  if ((long)(y0 - y1)*(y2 - y1) > 0) { /* vertical cut at P6? */
    t = y0 - 2 * y1 + y2; t = (y0 - y1) / t;
    r = (1 - t)*((1 - t)*x0 + 2.0*t*x1) + t * t*x2; /* Bx(t=P6) */
    t = (y0*y2 - y1 * y1)*t / (y0 - y1); /* gradient dP6/dy=0 */
    x = floor(r + 0.5); y = floor(t + 0.5);
    r = (x1 - x0)*(t - y0) / (y1 - y0) + x0; /* intersect P6 | P0 P1 */
    curveSeg(x0, y0, floor(r + 0.5), y, x, y);
    r = (x1 - x2)*(t - y2) / (y1 - y2) + x2; /* intersect P7 | P1 P2 */
    x0 = x; x1 = floor(r + 0.5); y0 = y1 = y; /* P0 = P6, P1 = P7 */
  }
  curveSeg(x0, y0, x1, y1, x2, y2); /* remaining part */
}

void RiverGenerator::curveSeg(int x0, int y0, int x1, int y1, int x2, int y2) {
  /* plot a limited quadratic Bezier segment */
  std::string water = "water";
  int sx = x2 - x1, sy = y2 - y1;
  long xx = x0 - x1, yy = y0 - y1, xy; /* relative values for checks */
  double dx, dy, err, cur = xx * sy - yy * sx; /* curvature */
  //assert(xx*sx <= 0 && yy*sy <= 0); /* sign of gradient must not change */
  if (sx*(long)sx + sy * (long)sy > xx*xx + yy * yy) { /* begin with longer part */
    x2 = x0; x0 = sx + x1; y2 = y0; y0 = sy + y1; cur = -cur; /* swap P0 P2 */
  }
  if (cur != 0) { /* no straight line */
    xx += sx; xx *= sx = x0 < x2 ? 1 : -1; /* x step direction */
    yy += sy; yy *= sy = y0 < y2 ? 1 : -1; /* y step direction */
    xy = 2 * xx*yy; xx *= xx; yy *= yy; /* differences 2nd degree */
    if (cur*sx*sy < 0) { /* negated curvature? */
      xx = -xx; yy = -yy; xy = -xy; cur = -cur;
    }
    dx = 4.0*sy*cur*(x1 - x0) + xx - xy; /* differences 1st degree */
    dy = 4.0*sx*cur*(y0 - y1) + yy - xy;
    xx += xx; yy += yy; err = dx + dy + xy; /* error 1st step */
    do {
      (*data)[x0][y0]->setType(water); /* plot curve */
      if (x0 == x2 && y0 == y2) return; /* last pixel -> curve finished */
      y1 = 2 * err < dx; /* save value for test of y step */
      if (2 * err > dy) { x0 += sx; dx -= xy; err += dy += yy; } /* x step */
      if (y1) { y0 += sy; dy -= xy; err += dx += xx; } /* y step */
    } while (dy < 0 && dx > 0); /* gradient negates -> algorithm fails */
  }
  line(x0, y0, x2, y2); /* plot remaining part to end */
}


void RiverGenerator::generate() {
  //Имея желаемое число рек, пытаемся нарисовать их, находя подходящее кол-во точек
  std::string mountain = "mountain";
  float max = data->maxHeight();
  int length;
  for (int rivers = 0; rivers < number; rivers++)
    for (int i = 0; i < data->x_size(); i++)
      for (int j = 0; j < data->y_size(); j++) {
        if (!(*data)[i][j]->Type().compare(mountain) && i+4 < data->x_size() && j+4 < data->y_size())
          if (!(*data)[i + 4][j + 4]->Type().compare(mountain)) {
            //Нашли нормальный исток для реки, ищем место для устья
            length = data->x_size() * data->y_size
          }
      }
}

RiverGenerator::~RiverGenerator()
{
}
