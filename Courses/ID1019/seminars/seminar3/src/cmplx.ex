defmodule Cmplx do

  def new(r, i) do {r, i} end

  def add({r1, i1}, {r2, i2}) do 
    {r1 + r2, i1 + i2}
  end

  def sqr({r, i}) do 
    {:math.pow(r, 2) - :math.pow(i, 2), (2 * r * i)} 
  end

  def abs({r, i}) do 
    :math.sqrt(:math.pow(r, 2) + :math.pow(i, 2))
  end

end
