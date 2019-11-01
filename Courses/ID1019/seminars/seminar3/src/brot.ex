defmodule Brot do

  def mandelbrot(c, m) do 
    z0 = Cmplx.new(0, 0)
    i = 0
    mtest(i, z0, c, m)
  end

  def mtest(m, _, _, m) do 0 end
  def mtest(i, z, c, m) do
    cond do
      Cmplx.abs(z) > 2 ->
        i
      true ->
        mtest(i + 1, Cmplx.add(Cmplx.sqr(z), c), c, m) 
    end 
  end
end
