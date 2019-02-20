defmodule Mandel do

  def mandelbrot(width, height, x, y, k, depth) do
    trans = fn(w, h) ->
      Cmplx.new(x + k *(w - 1), y - k * (h - 1))
    end

    rows(width, height, trans, depth, [])
  end

  defp rows(_, 0, _, _, rows) do rows end
  defp rows(width, height, trans, depth, acc) do
    rows(width, height - 1, trans, depth, 
      [row(width, height, trans, depth, []) | acc]
     )

  end

  defp row(0, _, _, _, acc) do acc end
  defp row(width, height, trans, depth, acc) do
    row(width - 1, height, trans, depth, 
      [Color.convert(Brot.mandelbrot(trans.(width, height), depth), depth) 
        | acc]
    )
  end

  def demo() do
    small(-2.6, 1.2, 1.2)
  end

  def small(x0, y0, xn) do
    width = 960
    height = 540
    depth = 64
    k = (xn - x0) / width
    image = Mandel.mandelbrot(width, height, x0, y0, k, depth)
    PPM.write("small.ppm", image)
  end


end
