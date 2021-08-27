#include "Batch/Batch.hh"
#include "Batch/IBatchGenerator.hh"
#include "RawImage.hh"
#include "Tools/Helpers.hh"

namespace Rayon
{
  Batch::Batch(IBatchGenerator* parent,
               UInt32Vec2_t     start,
               UInt32Vec2_t     end,
               RawImage*        img,
               int              rpp)
    : _parent(parent), _start(start), _end(end), _img(img), _rpp(rpp == 0 ? 1 : rpp)
  {
  }

  void Batch::forEachWork(WorkFunction_t f)
  {
    auto               side = _rpp < 0 ? Tools::Pow(2, -_rpp) : 1;
    std::vector<Color> colors;

    if (_rpp > 1)
    {
      colors.resize(_rpp * _rpp);
    }

    for (int x = _start.x; x < _end.x; x += side)
    {
      for (int y = _start.y; y < _end.y; y += side)
      {
        if (_rpp <= 1)
        {
          auto color = f(x, y);

          fillColor(x, y, color);
        }
        else
        {
          double inv = 1.0 / (_rpp + 1.0);

          for (int i = 0; i < _rpp; ++i)
          {
            double offX = (i + 1.0) * inv;

            for (int j = 0; j < _rpp; ++j)
            {
              double offY = (j + 1.0) * inv;

              colors[i * _rpp + j] = f(offX + x, offY + y);
            }
          }

          fillColor(x, y, Color::average(colors));
        }
      }
    }
  }

  void Batch::fillColor(int x, int y, const Color& color)
  {
    if (_rpp < 0)
    {
      auto side = Tools::Pow(2, -_rpp);

      for (int i = x; i < x + side && i < _img->width(); ++i)
      {
        for (int j = y; j < y + side && j < _img->height(); ++j)
        {
          _img->pixel(i, j) = color;
        }
      }
    }
    else
    {
      _img->pixel(x, y) = color;
    }
  }
};  // namespace Rayon